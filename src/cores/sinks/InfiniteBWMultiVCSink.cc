//
// Copyright (C) 2010-2011 Eitan Zahavi, The Technion EE Department
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

// Behavior
// This sink is simple - it assumes NO delay on receiving packets
// so on the received FLIT a credit is generated.
//
// PktId check is valid only for single source .
//
#include "InfiniteBWMultiVCSink.h"
Define_Module(InfiniteBWMultiVCSink)
;

void InfiniteBWMultiVCSink::initialize() {
    numVCs = par("numVCs");

    end2EndLatency.setName("end-to-end-latency-ns"); // end-to-end latency per flit
    networkLatency.setName("network-latency-ns"); // network-latency per flit
    packetLatency.setName("packet-network-latency-ns"); // network-latency per packet

    sourceId.setName("source-id");
    destinationId.setName("destination-id");
    flitHopCount.setName("hop-count");
    // statistics for head-flits only
    SoPEnd2EndLatency.setName("SoP-end-to-end-latency-ns");
    SoPLatency.setName("SoP-network-latency-ns");
    SoPQTime.setName("SoP-queueing-time-ns");

    // statistics for tail-flits only
    EoPEnd2EndLatency.setName("EoP-end-to-end-latency-ns");
    EoPLatency.setName("EoP-network-latency-ns");
    EoPQTime.setName("EoP-queueing-time-ns");

    numReceivedPkt.setName("number-received-packets");

    // Vectors
    end2EndLatencyVec.setName("end-to-end-latency-ns");

    numRecPkt = 0;

    vcFLITs.resize(numVCs, 0);
    vcFlitIdx.resize(numVCs, 0);
    curPktId.resize(numVCs, -1);

    SoPFirstNetTime.resize(numVCs, 0);
    statStartTime = par("statStartTime");

    // send the credits to the other size
    for (int vc = 0; vc < numVCs; vc++)
        sendCredit(vc, 100);

    SoPEnd2EndLatencyHist.setName("SoP-E2E-Latency-Hist");
    SoPEnd2EndLatencyHist.setMode(cHistogram::MODE_INTEGERS);
}

void InfiniteBWMultiVCSink::sendCredit(int vc, int num) {
    char credName[64];
    sprintf(credName, "cred-%d-%d", vc, 1);
    NoCCreditMsg *crd = new NoCCreditMsg(credName);
    crd->setKind(NOC_CREDIT_MSG);
    crd->setVC(vc);
    crd->setFlits(num);
    send(crd, "in$o");
}

void InfiniteBWMultiVCSink::handleMessage(cMessage *msg) {
    NoCFlitMsg *flit = dynamic_cast<NoCFlitMsg*> (msg);
    int vc = flit->getVC();
    sendCredit(vc, 1);
    std::cout<<"\n ##########"<<flit->getSrcId()<<"##"<<flit->getDstId();
    int srcId = flit->getSrcId();
    int dstId = flit->getDstId();
    int hopCount = flit->getHopCount();

    sourceId.collect(srcId);
    destinationId.collect(dstId);
    flitHopCount.collect(hopCount);
    // some statistics
    if (simTime() > statStartTime) {
        vcFLITs[vc]++;

        if (flit->getFirstNet()) {
            throw cRuntimeError(
                    "-E- BUG - received flit on vc %d, but firstNet flag set is true !",
                    vc);
        }

        double eed = (simTime().dbl() - msg->getCreationTime().dbl());
        double d = (simTime().dbl() - flit->getFirstNetTime().dbl());
        double eed_ns = eed * 1e9;
        double d_ns = d * 1e9;

        end2EndLatency.collect(eed_ns);
        networkLatency.collect(d_ns);
        end2EndLatencyVec.record(eed_ns);
        std::cout<<"\n ///////"<<d_ns;
        if (flit->getType() == NOC_START_FLIT) {
            SoPEnd2EndLatency.collect(eed_ns);
            SoPEnd2EndLatencyHist.collect(eed_ns);

            SoPLatency.collect(d_ns);
            SoPQTime.collect(1e9 * (flit->getInjectTime().dbl()
                    - msg->getCreationTime().dbl()));

            if (SoPFirstNetTime[vc] == 0) {
                SoPFirstNetTime[vc] = flit->getFirstNetTime();
                EV<< "-I- " << getFullPath() << "Assign SoPFirstNetTime[" << vc <<"]=" <<SoPFirstNetTime[vc] << endl;
            } else {
                throw cRuntimeError(
                        "-E- BUG - SoPFirstNetTime[%d] != 0 at SoP statistics procedure ",
                        vc);
            }
            numRecPkt++;
        }

        std::cout<<"\n srcid "<<flit->getSrcId()<<" dest id "<<flit->getDstId()<<" packets "<<numRecPkt;


        if (flit->getType() == NOC_END_FLIT) {
            EoPEnd2EndLatency.collect(eed_ns);
            EoPLatency.collect(d_ns);
            EoPQTime.collect(1e9 * (flit->getInjectTime().dbl() - msg->getCreationTime()).dbl());
            if (SoPFirstNetTime[vc] != 0) { // avoid collecting statistics when statStartTime is between SoP and EoP
                packetLatency.collect(1e9 * (simTime().dbl() - SoPFirstNetTime[vc].dbl()));
            }
            SoPFirstNetTime[vc] = 0;
            EV<< "-I- " << getFullPath() << "Assign statistics to [" << vc <<"]" << endl;

        }

    }

    // Some checking...
    // PktId check ...
    if (flit->getType() == NOC_START_FLIT) {
        if (curPktId[vc] == -1) {
            curPktId[vc] = flit->getPktId();
        } else {
            throw cRuntimeError(
                    "-E- BUG - Received SoP Index %d but expecting Pkt index %d on vc %d",
                    flit->getPktId(), curPktId[vc], vc);
        }
    } else {

        if (flit->getPktId() != curPktId[vc]) {
            throw cRuntimeError(
                    "-E- BUG - Received Pkt Index %d but expecting Pkt index %d on vc %d",
                    flit->getPktId(), curPktId[vc], vc);
        }

    }

    if (flit->getType() == NOC_END_FLIT) {
        curPktId[vc] = -1;
    }

    // flit Idx check ...
    if (vcFlitIdx[vc] != flit->getFlitIdx()) {
        throw cRuntimeError(
                "-E- BUG - Received flit Index %d but expecting flit index %d on vc %d",
                flit->getFlitIdx(), vcFlitIdx[vc], vc);
    }

    if (flit->getType() == NOC_END_FLIT) {
        if (vcFlitIdx[vc] == (flit->getFlits() - 1)) {
            vcFlitIdx[vc] = 0;
        } else {
            throw cRuntimeError(
                    "-E- BUG - Received flit EoP but expecting flit index %d on vc %d",
                    vcFlitIdx[vc], vc);
        }

    } else {
        vcFlitIdx[vc]++;
    }

    delete msg;
}

void InfiniteBWMultiVCSink::finish() {
    char name[32];
    double totalFlits = 0;
    int flitSize_B = par("flitSize"); // in bytes
    for (int vc = 0; vc < numVCs; vc++) {
        sprintf(name, "flit-per-vc-%d", vc);
        recordScalar(name, vcFLITs[vc]);
        totalFlits += vcFLITs[vc];
    }
    if (simTime() > statStartTime) {
        SoPEnd2EndLatency.record();
        SoPEnd2EndLatencyHist.record();
        SoPLatency.record();
        SoPQTime.record();
        EoPEnd2EndLatency.record();
        EoPLatency.record();
        EoPQTime.record();

        packetLatency.record();
        networkLatency.record();
        end2EndLatency.record();

        sourceId.record();
        destinationId.record();
        flitHopCount.record();
        numReceivedPkt.collect(numRecPkt);
        numReceivedPkt.record();
        double BW_MBps = 1e-6 * totalFlits * flitSize_B / (simTime().dbl()- statStartTime);
        recordScalar("Sink-Total-BW-MBps", BW_MBps);
    }
}

