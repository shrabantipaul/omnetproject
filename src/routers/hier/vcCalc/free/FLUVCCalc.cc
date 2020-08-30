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
