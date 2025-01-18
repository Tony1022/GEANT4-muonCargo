#include "InputParameters.hh"

InputParameters::InputParameters(){
    xWorld = 20.0;
    yWorld = 20.0;
    zWorld = 20.0;
}

InputParameters::~InputParameters(){

}

void InputParameters::RPC_parameters(){
    C2H2F4_temp = 293.15;
    C2H2F4_pressure = 1.0;
    C2H2F4_density = 1.977;
    C4H10_temp = 293.15;
    C4H10_pressure = 1.0;
    C4H10_density = 1.977;
    SF6_temp = 293.15;
    SF6_pressure = 1.0;
    SF6_density = 1.977;
    RPCgas_temp = 293.15;
    RPCgas_pressure = 1.0;
    RPCgas_density = 1.977;

    rpcLength = 10.0;
    rpcWidth = 8.0;
    rpcThickness = 20.0;
}

void InputParameters::cargoContent_parameters(){
    NH4NO3_density = 1.72;
    xTruckFull = 6.0;
    yTruckFull = 2.5;
    zTruckFull = 3.0;
}

void InputParameters::world_parameters(){
    
}

void InputParameters::blocker_parameters(){
    leadThickness = 30.0;
    leadSize = 16.0;
}