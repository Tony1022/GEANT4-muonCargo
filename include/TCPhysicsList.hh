// What physics do I need in the simulation
#ifndef TCPHYSICSLIST_HH
#define TCPHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"

class TCPhysicsList : public G4VModularPhysicsList{
public:
        TCPhysicsList();
        ~TCPhysicsList();
};

#endif