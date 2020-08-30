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

// Created: 2010-2-30 for project sampleproject

package sampleproject.topologies;

import sampleproject.routers.Router_Ifc;
import sampleproject.cores.NI_Ifc;

import ned.DelayChannel;

// we use same Link channel for the mesh
channel Link extends ned.DatarateChannel
{
    datarate = 16Gbps; // 32 lines of 2ns clock
    delay = 0us;
}

//
// A generated network with grid topology.
//
network Mesh
{
    parameters:
        string routerType;
        string coreType;
        int columns = default(3);
        int rows = default(3);
        int layers = default(3);
    submodules:
        router[columns*rows*layers]: <routerType> like Router_Ifc {
            parameters:
                numPorts = 7;
                id = index;
                @display("p=100,100,matrix,$columns,150,150");
            gates:
                in[7];
                out[7];
        }

        core[columns*rows*layers]: <coreType> like NI_Ifc {
            parameters:
                id = index;
                @display("p=170,165,matrix,$columns,150,150");
        }

    connections allowunconnected:
        for r=0..rows-1, for c=0..columns-1 {
            // ports on routers are 0 = north, 1 = west, 2 = south, 3 = east, 4 = core, 5=up,6=down
            // connect south north (all but last row)
            router[r*columns+c].in[2] <--> Link <--> router[(r+1)*columns+c].out[0] if r!=rows-1;
            router[r*columns+c].out[2] <--> Link <--> router[(r+1)*columns+c].in[0] if r!=rows-1;
            // connect east west (all but on last column)
            router[r*columns+c].in[3] <--> Link <--> router[r*columns+c+1].out[1] if c!=columns-1;
            router[r*columns+c].out[3] <--> Link <--> router[r*columns+c+1].in[1] if c!=columns-1;

            // connect the Cores to port 4
            router[r*columns+c].in[4] <--> Link <--> core[r*columns+c].out;
            router[r*columns+c].out[4] <--> Link <--> core[r*columns+c].in;

        }

        //2nd layer
        for r=0..rows-1, for c=0..columns-1 {
            // ports on routers are 0 = north, 1 = west, 2 = south, 3 = east, 4 = core, 5=up,6=down
            // connect south north (all but last row)
            router[r*columns+c+9].in[2] <--> Link <--> router[(r+1)*columns+c+9].out[0] if r!=rows-1;
            router[r*columns+c+9].out[2] <--> Link <--> router[(r+1)*columns+c+9].in[0] if r!=rows-1;
            // connect east west (all but on last column)
            router[r*columns+c+9].in[3] <--> Link <--> router[r*columns+c+1+9].out[1] if c!=columns-1;
            router[r*columns+c+9].out[3] <--> Link <--> router[r*columns+c+1+9].in[1] if c!=columns-1;

            // connect the Cores to port 4
            router[r*columns+c+9].in[4] <--> Link <--> core[r*columns+c+9].out;
            router[r*columns+c+9].out[4] <--> Link <--> core[r*columns+c+9].in;
        }

        //3rd layer
        for r=0..rows-1, for c=0..columns-1 {
            // ports on routers are 0 = north, 1 = west, 2 = south, 3 = east, 4 = core, 5=up,6=down
            // connect south north (all but last row)
            router[r*columns+c+18].in[2] <--> Link <--> router[(r+1)*columns+c+18].out[0] if r!=rows-1;
            router[r*columns+c+18].out[2] <--> Link <--> router[(r+1)*columns+c+18].in[0] if r!=rows-1;
            // connect east west (all but on last column)
            router[r*columns+c+18].in[3] <--> Link <--> router[r*columns+c+1+18].out[1] if c!=columns-1;
            router[r*columns+c+18].out[3] <--> Link <--> router[r*columns+c+1+18].in[1] if c!=columns-1;

            // connect the Cores to port 4
            router[r*columns+c+18].in[4] <--> Link <--> core[r*columns+c+18].out;
            router[r*columns+c+18].out[4] <--> Link <--> core[r*columns+c+18].in;
        }


        //port 5 (lower layer)
        //port 6 (upper layer) 

        //connection between layer1 and layer2
        //connect port6 of layer1 to port5 of layer2
        for r=0..rows-1, for c=0..columns-1 {
            router[r*columns+c].in[6] <--> Link <--> router[r*columns+c+9].out[5];
            router[r*columns+c].out[6] <--> Link <--> router[r*columns+c+9].in[5];
        }

        //connection between layer2 and layer3
        //connect port6 of layer2 to port5 of layer3
        for r=0..rows-1, for c=0..columns-1 {
            router[r*columns+c+9].in[6] <--> Link <--> router[r*columns+c+18].out[5];
            router[r*columns+c+9].out[6] <--> Link <--> router[r*columns+c+18].in[5];
        }


            //connect to upper layer
//         for r=0..rows-1, for c=0..columns-1 {
//             
//            router[r*columns+c].in[5] <--> Link <--> router[9].out[0];
//            router[0].out[5] <--> Link <--> router[9].in[0]; 
//            
//        }

//        router[1].in[1] <--> Link <--> router[0].out[3];
//        router[1].out[1] <--> Link <--> router[0].in[3];
//        router[1].in[2] <--> Link <--> router[4].out[0];
//        router[1].out[2] <--> Link <--> router[4].in[0];
//        router[1].in[3] <--> Link <--> router[2].out[1];
//        router[1].out[3] <--> Link <--> router[2].in[1];
//        router[1].in[4] <--> Link <--> core[1].out;
//        router[1].out[4] <--> Link <--> core[1].in;

}
