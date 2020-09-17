//
// Copyright (C) 2010-2011 Eitan Zahavi, The Technion EE Department
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

#include "XYOPCalc.h"
#include "../../../../NoCs_m.h"

Define_Module(XYOPCalc)
;

int XYOPCalc::rowColByID(int id, int &x, int &y, int &z)
{
    x = id % numCols;
    z = id / (numRows*numCols);
    y = (id / numCols) - (z*numRows);
    std::cout<<"\n id is "<<id<<"x="<<x<<"y="<<y<<"z="<<z;
    return(0);
}

// return true if the provided cModule pointer is a Port
bool
XYOPCalc::isPortModule(cModule *mod)
{
    return(mod->getModuleType() == cModuleType::get(portType));
}

// return the pointer to the port on the other side of the given port or NULL
cModule *
XYOPCalc::getPortRemotePort(cModule *port)
{
    cGate *gate = port->gate("out$o");
    if (!gate) return NULL;
    cGate *remGate = gate->getPathEndGate()->getPreviousGate();
    if (!remGate) return NULL;
    cModule *neighbour = remGate->getOwnerModule();
    if (!isPortModule(neighbour)) return NULL;
    if (neighbour == port) return NULL;
    return neighbour;
}

// return true if the provided cModule pointer is a Core
bool
XYOPCalc::isCoreModule(cModule *mod)
{
    return(mod->getModuleType() == cModuleType::get(coreType));
}

// return the pointer to the Core on the other side of the given port or NULL
cModule *
XYOPCalc::getPortRemoteCore(cModule *port)
{
    cGate *gate = port->gate("out$o");
    if (!gate) return NULL;
    cGate *remGate = gate->getPathEndGate()->getPreviousGate();
    if (!remGate) return NULL;
    cModule *neighbour = remGate->getOwnerModule();
    if (!isCoreModule(neighbour)) return NULL;
    if (neighbour == port) return NULL;
    return neighbour;
}

// Given the port pointer find the index idx such that sw_out[idx]
// connect to that port
int
XYOPCalc::getIdxOfSwPortConnectedToPort(cModule *port)
{
//    std::cout<<"\n getIdxOfSwPortConnectedToPort(cModule *port)";
    for (int i=0; i< getParentModule()->gateSize("sw_in"); i++) {
        cGate *oGate = getParentModule()->gate("sw_in", i);
        if (!oGate) return -1;
        cGate *remGate = oGate->getPathEndGate()->getPreviousGate();
        if (!remGate) return -1;
        cModule *neighbour = remGate->getOwnerModule();
        if (neighbour == port)
            return i;
    }
    return -1;
}

// Analyze the topology of this router and obtain the port numbers
// connected to the 6 directions
int
XYOPCalc::analyzeMeshTopology()
{
    // if not found the port numbers will be -1
    northPort = -1;
    westPort  = -1;
    southPort = -1;
    eastPort  = -1;
    corePort  = -1;
    upperPort = -1;
    lowerPort = -1;

    cModule *router = getParentModule()->getParentModule();

    // go over all the router ports and check their remote side if they are of type "Port"
    for (cModule::SubmoduleIterator iter(router); !iter.end(); iter++) {
        if (! isPortModule(*iter)) continue;
        cModule *port = *iter;

        // get the port module on the other side of the
        cModule *remPort = getPortRemotePort(port);
        cModule *remCore = getPortRemoteCore(port);

        // obtain the idx of this port sw_out[idx] that connects to port
        int portIdx = getIdxOfSwPortConnectedToPort(port);

        if (remCore) {
            // remote side is the core connected to the router
            int x,y,z;
            rowColByID(remCore->par("id"), x, y,z);
            if ((rx == x) && (ry == y) && (rz == z)) {
                EV << "-I- " << getParentModule()->getFullPath()
                    << " connected through sw_out[" << portIdx
                    << "] to Core port: " << port->getFullPath() << endl;
                corePort = portIdx;
            } else {
                throw cRuntimeError("Port: %s and connected Core %s do not share the same x:%d and y:%d and z:%d",
                        port->getFullPath().c_str(), remCore->getFullPath().c_str(),
                        x, y,z);
            }
        } else if (remPort) {
            // remote side is another router port
            // get the remote port x,y,z
            int x,y,z;
            rowColByID(remPort->getParentModule()->par("id"), x, y, z);
            std::cout << "\n ********* " <<"rx = "<<rx<<"x= "<<x;
            std::cout  << "********* " <<"ry = "<<ry<<"y= "<<y;
            std::cout  << "********* " <<"rz = "<<rx<<"z= "<<z;
            if ((rx == x) && (ry == y) && (rz == z)) {
                throw cRuntimeError("Ports: %s and %s share the same x:%d and y:%d and z:%d",
                        port->getFullPath().c_str(), remPort->getFullPath().c_str(), x, y,z);
            } else if ((rx == x) && (ry == y + 1)) {
                // remPort is south port
                if (southPort != -1) {
                    throw cRuntimeError("Already found a south port: %d for ports: %s."
                            " %s is miss-configured",
                            southPort, port->getFullPath().c_str(),
                            remPort->getFullPath().c_str());
                } else {
                    EV << "-I- " << getParentModule()->getFullPath()
                        << " connected through sw_out[" << portIdx
                        << "] to South port: " << port->getFullPath() << endl;
                    southPort = portIdx;
                }
            } else if ((rx == x) && (ry == y - 1)) {
                // remPort is north port
                if (northPort != -1) {
                    throw cRuntimeError("Already found a north port: %d for ports: %s."
                            " %s is miss-configured",
                            northPort, port->getFullPath().c_str(),
                            remPort->getFullPath().c_str());
                } else {
                    EV << "-I- " << getParentModule()->getFullPath()
                        << " connected through sw_out[" << portIdx
                        << "] to North port: " << port->getFullPath() << endl;
                    northPort = portIdx;
                }
            } else if ((rx == x + 1) && (ry == y)) {
                // remPort is west port
                if (westPort != -1) {
                    throw cRuntimeError("Already found a west port: %d for ports: %s."
                            " %s is miss-configured",
                            westPort, port->getFullPath().c_str(),
                            remPort->getFullPath().c_str());
                } else {
                    EV << "-I- " << getParentModule()->getFullPath()
                        << " connected through sw_out[" << portIdx
                        << "] to West port: " << port->getFullPath() << endl;
                    westPort = portIdx;
                }
            } else if ((rx == x - 1) && (ry == y)) {
                // remPort is east port
                if (eastPort != -1) {
                    throw cRuntimeError("Already found an east port: %d for ports: %s."
                            " %s is miss-configured",
                            eastPort, port->getFullPath().c_str(),
                            remPort->getFullPath().c_str());
                } else {
                    EV << "-I- " << getParentModule()->getFullPath()
                        << " connected through sw_out[" << portIdx
                        << "] to East port: " << port->getFullPath() << endl;
                    eastPort = portIdx;
                }
            } else if (rz == z + 1) {
                // remPort is upper port
                if (upperPort != -1) {
                    throw cRuntimeError("Already found an upper port: %d for ports: %s."
                            " %s is miss-configured",
                            upperPort, port->getFullPath().c_str(),
                            remPort->getFullPath().c_str());
                } else {
                    EV << "-I- " << getParentModule()->getFullPath()
                        << " connected through sw_out[" << portIdx
                        << "] to Upper port: " << port->getFullPath() << endl;
                    upperPort = portIdx;
                }
            } else if (rz == z - 1) {
                // remPort is lower port
                if (lowerPort != -1) {
                    throw cRuntimeError("Already found an lower port: %d for ports: %s."
                            " %s is miss-configured",
                            lowerPort, port->getFullPath().c_str(),
                            remPort->getFullPath().c_str());
                } else {
                    EV << "-I- " << getParentModule()->getFullPath()
                        << " connected through sw_out[" << portIdx
                        << "] to lower port: " << port->getFullPath() << endl;
                    lowerPort = portIdx;
                }
            } else {
                throw cRuntimeError("Found a non Mesh connection between %s (%d,%d,%d) and %s (%d,%d,%d)",                " %s is miss-configured",
                        port->getFullPath().c_str(), rx,ry,rz,
                        remPort->getFullPath().c_str(),x,y,z);
            }
        }
    }

    if (corePort < 0) {
        EV << "-W- " << getParentModule()->getFullPath()
            << " could not find corePort (of coreType:" << coreType << ")" << endl;
    }
    return(0);
}

void XYOPCalc::initialize()
{
    coreType = par("coreType");
    portType = par("portType");

    // the id is supposed to be on the router
    cModule *router = getParentModule()->getParentModule();
    int id = router->par("id");
    numCols = router->getParentModule()->par("columns");
    numRows = router->getParentModule()->par("rows");
    layers =  router->getParentModule()->par("layers");
    rowColByID(id, rx, ry, rz);
//    std::cout<<"\n rx"<<rx<<"ry"<<ry<<"rz"<<rz;
    // Analyze the connections of this port building the port number to be used for routing
    analyzeMeshTopology();
    EV << "-I- " << getFullPath() << " Found N/W/S/E/C/U/L ports:" << northPort
            << "/" << westPort << "/" << southPort << "/"
            << eastPort << "/" << corePort<< "/" << upperPort<< "/" << lowerPort << endl;
    WATCH(northPort);
    WATCH(westPort);
    WATCH(eastPort);
    WATCH(southPort);
    WATCH(corePort);
    WATCH(upperPort);
    WATCH(lowerPort);
}

void XYOPCalc::handlePacketMsg(NoCFlitMsg* msg)
{
    int dx, dy, dz;
    rowColByID(msg->getDstId(), dx, dy,dz);
    int swOutPortIdx;
    std::cout<<"dx"<<dx<<"rx"<<rx<<"dy"<<dy<<"ry"<<ry<<"dz"<<dz<<"rz"<<rz;
    if ((dx == rx) && (dy == ry) && (dz == rz)) {
        swOutPortIdx = corePort;
    }
    std::cout<<"\n***********"<<"e"<<eastPort<<"w"<<westPort<<"s"<<southPort<<"n"<<northPort<<"u"<<upperPort<<"l"<<lowerPort<<"c"<<corePort;
    std::cout<<"rz"<<rz<<"dz"<<dz;
    if ((rz % 2) == 0){
        //route within the layer
        std::cout<<"inside even layer";
            if (dx > rx) {
                swOutPortIdx = eastPort;
            } else if (dx < rx) {
                swOutPortIdx = westPort;
            } else if (dy > ry) {
                swOutPortIdx = northPort;
            } else if (dy < ry ){
                swOutPortIdx = southPort;
            }
            if(dx==rx && dy==ry){
          //change the layer
            if((dz - rz) > 0){
                swOutPortIdx = lowerPort;
            } else if((dz - rz) < 0){
                swOutPortIdx = upperPort;
            }
          }
    }
    if ((rz % 2) != 0){
        //change the layer
            if((dz - rz) > 0){
                swOutPortIdx = upperPort;
            } else if((dz - rz) < 0){
                swOutPortIdx = lowerPort;
            }
            if(dz==rz){
        //route within the layer
            if (dx > rx) {
                swOutPortIdx = eastPort;
            } else if (dx < rx) {
                swOutPortIdx = westPort;
            } else if (dy > ry) {
                swOutPortIdx = northPort;
            } else if (dy < ry) {
                swOutPortIdx = southPort;
            }
            }
    }
    if (swOutPortIdx < 0) {
        throw cRuntimeError("Routing dead end at %s (%d,%d,%d) "
                "for destination %d (%d,%d,%d)",
                getParentModule()->getFullPath().c_str(), rx,ry,rz,
                msg->getDstId(),dx,dy,dz);
    }

    // TODO - move into a common header for msgs ?
    cObject *obj = msg->getControlInfo();
    if (obj == NULL) {
        throw cRuntimeError("-E- %s BUG - No Control Info for FLIT: %s",
                getFullPath().c_str(), msg->getFullName());
    }

    inPortFlitInfo *info = dynamic_cast<inPortFlitInfo*>(obj);
    info->outPort = swOutPortIdx;
    send(msg, "calc$o");
}

void XYOPCalc::handleMessage(cMessage *msg)
{
    int msgType = msg->getKind();
    if ( msgType == NOC_FLIT_MSG ) {
        handlePacketMsg((NoCFlitMsg*)msg);
    } else {
        throw cRuntimeError("Does not know how to handle message of type %d", msg->getKind());
        delete msg;
    }
}
