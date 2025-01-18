#ifndef PRIMARYGENERATOR_HH
#define PRIMARYGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeneralParticleSource.hh"
#include "/home/tonyplus/geant4/source/externals/clhep/include/CLHEP/Random/RandFlat.h"
#include "/home/tonyplus/geant4/source/externals/clhep/include/CLHEP/Random/Randomize.h"

class PrimaryGenerator : public G4VUserPrimaryGeneratorAction{
public:
    PrimaryGenerator();
    ~PrimaryGenerator();

    virtual void GeneratePrimaries(G4Event *);

    G4double GenerateUniformInRange(G4double minRange, G4double maxRange);

private:
    G4ParticleGun *fParticleGun;
    G4GeneralParticleSource fParticleSource;
};


#endif