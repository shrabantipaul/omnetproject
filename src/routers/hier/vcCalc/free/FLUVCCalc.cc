//
// Copyright (C) 2010-2011 Yaniv Ben-Itzhak, The Technion EE Department
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "FLUVCCalc.h"

// Behavior:
//
// NOTE: on each VC there is only 1 packet being received at a given time
// Also there is one packet being arbitrated on each out port
//
// On new packet arrival a sequence of sending (and then receiving same msg)
// to calcVc and then calcOp is performed.
//
// On FLIT receive the it is queued and a Req is sent.
//
// Each FLIT has to pass scheduling: REQ->GNT->ACK/NAK
//
// A REQ may be GNT by the Scheduler. It places that packet into the "in-flight".
// It also needs to send back an ACK to the Scheduler followed by the FLIT at the top of
// the QByOPiVCoVC
//
// If a NAK is provided (since the port is already too busy) the Scheduler will later
// send a GNT for the same VC.OP again.
//
// Whenever a FLIT/PKT is sent on out a credit is sent on the in$o.
//
// There is no delay modeling for the internal crossbar. It is assumed that if
// a grant is provided it happens at least FLIT time after previous one
//
Define_Module(FLUVCCalc)
;

// based on the assumed structure of a Port containing the VcCalc
// connected by sw_in to the other port Sched
Sched *
FLUVCCalc::getSchedOnPort(int op) {
    if (op >= getParentModule()->gateSize("sw_in")) return NULL;
    cGate *oGate = getParentModule()->gate("sw_in", op);
    if (!oGate) return NULL;
    cGate *remLowestGate = oGate->getPathEndGate();
    if (!remLowestGate) return NULL;
    cModule *mod = remLowestGate->getOwnerModule();
    if (mod->getModuleType() != cModuleType::get(schedType)) return NULL;
    return dynamic_cast<Sched*>(mod);
}

void FLUVCCalc::initialize()
{
    schedType = par("schedType");
    // get pointer to the Sched Credits on each out port
    for (int i=0; i< getParentModule()->gateSize("sw_in"); i++) {
        const Sched *sched = getSchedOnPort(i);
        if (sched) {
            opCredits.push_back(sched->getCredits());
            opVCUsage.push_back(sched->getVCUsage());
        } else {
            EV << "-W- " << getFullPath()
                << " Could not find scheduler credit for port" << i << endl;
            opCredits.push_back(NULL);
            opVCUsage.push_back(NULL);
        }
    }
    lastSrc = lastDst = -1;
}

// based on the available credits on the msg outPort
// select the first VC with the max num credits
void FLUVCCalc::handlePacketMsg(NoCFlitMsg *msg)
{
    int oVC;
    cObject *obj = msg->getControlInfo();
    if (obj == NULL) {
        throw cRuntimeError("-E- %s BUG - No Control Info for FLIT: %s",
                getFullPath().c_str(), msg->getFullName());
    }

    inPortFlitInfo *info = dynamic_cast<inPortFlitInfo*>(obj);
    int op = info->outPort;
    if (!opCredits[op]) {
        throw cRuntimeError("No Credits Vec for Port:%d", op);
    }

    // if the source and destination matches the last decision
    // we have a back to back packets of same flow - use same VC
    if ((lastSrc == msg->getSrcId()) && (lastDst == msg->getDstId()) ) {
        oVC = lastOVC;
    } else {

        int maxCreds = 0;
        int maxCredsVc = 0;
        int minUsage = 10000;

        // look through all VCs on the out port the one with max credits and usage
        for (unsigned int vc = 0; vc < opCredits[op]->size(); vc++) {
            int credits = (*opCredits[op])[vc];
            int usage = (*opVCUsage[op])[vc];

            if ((credits > maxCreds) || ((credits == maxCreds) && (usage < minUsage)) ){
                maxCredsVc = vc;
                maxCreds = credits;
                minUsage = usage;
            }
        }
        oVC = maxCredsVc;
        lastSrc = msg->getSrcId();
        lastDst = msg->getDstId();
        lastOVC = oVC;
    }
    Sched *sched = getSchedOnPort(op);
    sched->incrVCUsage(oVC);
    msg->setVC(oVC);
    send(msg, "calc$o");
}

void FLUVCCalc::handleMessage(cMessage *msg)
{
    int msgType = msg->getKind();
    if ( msgType == NOC_FLIT_MSG ) {
        handlePacketMsg( (NoCFlitMsg*)msg);
    } else {
        throw cRuntimeError("Does not know how to handle message of type %d", msg->getKind());
        delete msg;
    }
}
