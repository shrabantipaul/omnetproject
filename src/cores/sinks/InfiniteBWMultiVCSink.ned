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

package sampleproject.cores.sinks;

//
// A Simple Sink - with no back pressure
//
simple InfiniteBWMultiVCSink like Sink_Ifc
{
    parameters:
        double statStartTime @unit(s); // time of first flit to record
        int numVCs;                    // number of VCs
        int flitSize @unit(byte);      // the flit size in bytes
         
    @display("i=block/sink");
    gates:
        inout in;
}

// For details about statistics, please refer to InfiniteBWMultiVCSink.h & InfiniteBWMultiVCSink.cc