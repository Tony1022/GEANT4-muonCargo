#include "TCPhysicsList.hh"

TCPhysicsList::TCPhysicsList(){
        // EM physics
        RegisterPhysics(new G4EmStandardPhysics());
}

TCPhysicsList::~TCPhysicsList(){}