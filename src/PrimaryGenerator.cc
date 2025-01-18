#include "PrimaryGenerator.hh"

G4double PrimaryGenerator::GenerateUniformInRange(G4double minRange, G4double maxRange){
    G4double randomValue = CLHEP::RandFlat::shoot(minRange, maxRange);
    //G4cout << "Random Uniform Value: " << randomValue << G4endl;
    return randomValue;
}

PrimaryGenerator::PrimaryGenerator(){
    // Here set how many particle you want to shoot
    fParticleGun = new G4ParticleGun(1);

    // Particle type
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

    G4double E = GenerateUniformInRange(1., 3.);
    // Here specify what particle do you want to shoot
    G4ParticleDefinition *particle = particleTable->FindParticle("mu-");

    fParticleGun->SetParticleDefinition(particle);
    
}

PrimaryGenerator::~PrimaryGenerator(){
    delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event *anEvent){
    G4double rndx = GenerateUniformInRange(-10.0, 10.0);
    G4double rndy = GenerateUniformInRange(-10.0, 10.0);
    G4double rndz = GenerateUniformInRange(7.0, 12.0);

    // Particle position
    G4double x = rndx * m;
    G4double y = rndy * m;
    G4double z = rndz * m;

    G4ThreeVector pos(x,y,z);

    fParticleGun->SetParticlePosition(pos);

    // Particle direction
    G4double px = GenerateUniformInRange(-0.2, 0.2);
    G4double py = GenerateUniformInRange(-0.2, 0.2);
    G4double pz = GenerateUniformInRange(-1, 0.); //ensure the particle shoot to z-direction

    G4ThreeVector mom(px,py,pz);

    fParticleGun->SetParticleMomentumDirection(mom);

    G4double E = GenerateUniformInRange(1., 3.);
    fParticleGun->SetParticleEnergy(E *GeV);

    // Create vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);
}