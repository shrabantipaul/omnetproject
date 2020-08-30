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
// The Arbiter count the number of outstanding requests
// It arbitrates on a clock timed by the clk message of type pop
//
// When a grant is sent to the inPort as a result of arbitration selecting this
// port/vc the ReqsoVC Reqs counter is decreased. If a NAK is received the counter is
// increased again.
//
// Arbitration:
// Configured by arbitration_type parameter:
// 		0 - winner takes all
//      1 - round robin
//
// Single Req queue for all request, get service by FIFO

// Asynchronous Router:
// Arbitrates when:
//   1) Gets FlitMsg.
//   2) Gets ReqMsg.
//   3) Gets AckMsg.
//   4) Gets CreditMsg.
//   5) Finished to transmit.

#include "SchedAsync.h"

Define_Module(SchedAsync)
;

