// What physics do I need in the simulation
#ifndef PHYSICSLIST_HH
#define PHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

class PhysicsList : public G4VModularPhysicsList{
public:
        PhysicsList();
        ~PhysicsList();
};

#endif