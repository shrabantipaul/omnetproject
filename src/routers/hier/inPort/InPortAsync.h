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

#ifndef __MYPROJECT_ASYNC_INPORT_H_
#define __MYPROJECT_ASYNC_INPORT_H_

#include <omnetpp.h>
using namespace omnetpp;

#include "../../../NoCs_m.h"
#include "../FlitMsgCtrl.h"

class InPortAsync: public cSimpleModule {
private:
    // parameters
    bool collectPerHopWait; // Controls per hop wait time collection
    int numVCs; // number of supported VCs
    int flitsPerVC; // number of buffers available per VC
    simtime_t statStartTime; // in sec

    // state
    std::vector<cQueue> QByiVC; // Q[ivc]
    std::vector<int> curOutVC; // current packet output VC per in VC
    std::vector<int> curOutPort; // current packet output port per in VC
    std::vector<int> curPktId; // the current packet id on the VC (0 means not inside packet)
    std::vector<bool> curNack; // Is current vc sent Nack (i.e. doesnt have nothing to send even though gnt is received)

    // methods
    void sendCredit(int vc, int numFlits);
    void sendReq(NoCFlitMsg *msg);
    void sendFlit(NoCFlitMsg *msg);
    void handleCalcOPResp(NoCFlitMsg *msg);
    void handleInFlitMsg(NoCFlitMsg *msg);
    void handleGntMsg(NoCGntMsg *msg);
    void handlePopMsg(NoCPopMsg *msg);
    void measureQlength();

    // statistics
    std::vector<std::vector<cStdDev> > qTimeBySrcDst_head_flit; // VC acquiring time
    std::vector<std::vector<cStdDev> > qTimeBySrcDst_body_flits; // transmission time: queue time of body flits untill it sent (doesnt include inter delay of the router and the transmission time over the link)
    cOutVector QLenVec; // Queue length
    std::vector<simtime_t> sendReqtime; // record the sendReq time in order to measure the vc acquiring latency

    // we later define the attached extended info for a FLIT in the InPort
    class inPortFlitInfo* getFlitInfo(NoCFlitMsg *msg);

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
public:
    virtual ~InPortAsync();

};

#endif
