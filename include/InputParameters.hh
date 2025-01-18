#ifndef INPUTPARAMETERS_HH
#define INPUTPARAMETERS_HH

#include "G4UnitsTable.hh"

class InputParameters{
public:

    InputParameters();
    ~InputParameters();

    G4double C2H2F4_temp, C2H2F4_pressure, C2H2F4_density;
    G4double C4H10_temp, C4H10_pressure, C4H10_density;
    G4double SF6_temp, SF6_pressure, SF6_density;
    G4double RPCgas_temp, RPCgas_pressure, RPCgas_density;

    G4double NH4NO3_density;

    G4double xWorld, yWorld, zWorld, xTruckFull, yTruckFull, zTruckFull, rpcLength, rpcWidth, rpcThickness, leadThickness, leadSize;

    void RPC_parameters();
    void cargoContent_parameters();
    void world_parameters();
    void blocker_parameters();
};

#endif