#include "PhysicsList.hh"

PhysicsList::PhysicsList(){
  	// EM physics
  	RegisterPhysics(new G4EmStandardPhysics());
		RegisterPhysics(new G4OpticalPhysics());  
		RegisterPhysics(new G4DecayPhysics());  
		RegisterPhysics(new G4RadioactiveDecayPhysics());  
}

PhysicsList::~PhysicsList(){}