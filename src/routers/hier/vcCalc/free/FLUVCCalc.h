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

#ifndef __MYPROJECT_ASYNC_VCCALC_H_
#define __MYPROJECT_ASYNC_VCCALC_H_

#include <omnetpp.h>
using namespace omnetpp;

#include "../../../../NoCs_m.h"
#include "../../HierRouter.h"
#include "../../FlitMsgCtrl.h"

class FLUVCCalc: public cSimpleModule {
private:
    // params
    const char* schedType;

    // state
    std::vector< const std::vector<int> * > opCredits;
    std::vector< const std::vector<int> * > opVCUsage;
    int lastSrc, lastDst, lastOVC;

    // methods
    class Sched *getSchedOnPort(int op);
    void handlePacketMsg(NoCFlitMsg *msg);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
