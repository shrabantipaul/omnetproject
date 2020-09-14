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

#ifndef __MYPROJECT_OPCALC_H_
#define __MYPROJECT_OPCALC_H_

#include <omnetpp.h>
using namespace omnetpp;

#include "../../../../NoCs_m.h"
#include "../../FlitMsgCtrl.h"

class XYOPCalc : public cSimpleModule
{
private:
    // parameters
    int numCols,numRows,layers; // the total number of columns in the simulations
    int rx, ry, rz;  // the local router x and y coordinates
    int northPort, westPort, southPort, eastPort,upperPort,lowerPort; // port indexes on the router to be used
    int corePort; // port index where the core module connects
    const char *portType; // the name of the actual module used for Port_Ifc
    const char *coreType; // the name of the actual module used for Core_Ifc

    // methods:

    // convert core and router id's into row and col (X and Y)
    int rowColByID(int id, int &x, int &y, int &z);
    // return true if the module is a "Port"
    bool isPortModule(cModule *mod);
    // Get the pointer to the remote Port module on the given port module
    cModule *getPortRemotePort(cModule *port);
    // return true if the module is a "Core"
    bool isCoreModule(cModule *mod);
    // Get the pointer to the remote Core module on the given port module
    cModule *getPortRemoteCore(cModule *port);
    // obtain the index of the current port out_sw port vector connecting to the port
    int getIdxOfSwPortConnectedToPort(cModule *port);
    // analyze Mesh topology and fill in the port numbers to be used for routing
    int analyzeMeshTopology();
    // handle the message
    void handlePacketMsg(NoCFlitMsg* msg);
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
