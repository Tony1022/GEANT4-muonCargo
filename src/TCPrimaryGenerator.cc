#include "TCPrimaryGenerator.hh"

TCPrimaryGenerator::TCPrimaryGenerator(){
    // Here set how many particle you want to shoot
    fParticleGun = new G4ParticleGun(1);

    // Particle position
    G4double x = 0. * m;
    G4double y = 0. * m;
    G4double z = 15. * m;

    G4ThreeVector pos(x,y,z);

    // Particle direction
    G4double px = 0.;
    G4double py = 0.;
    G4double pz = -1.; //ensure the particle shoot to z-direction

    G4ThreeVector mom(px,py,pz);

    // Particle type
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    // Here specify what particle do you want to shoot
    G4ParticleDefinition *particle = particleTable->FindParticle("mu-");

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleEnergy(1. *GeV);
    fParticleGun->SetParticleDefinition(particle);
}

TCPrimaryGenerator::~TCPrimaryGenerator(){
    delete fParticleGun;
}

void TCPrimaryGenerator::GeneratePrimaries(G4Event *anEvent){
    // Create vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);
}