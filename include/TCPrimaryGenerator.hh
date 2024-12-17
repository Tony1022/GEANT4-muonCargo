#ifndef TCPRIMARYGENERATOR_HH
#define TCPRIMARYGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

class TCPrimaryGenerator : public G4VUserPrimaryGeneratorAction{
public:
    TCPrimaryGenerator();
    ~TCPrimaryGenerator();

    virtual void GeneratePrimaries(G4Event *);

private:
    G4ParticleGun *fParticleGun;
};


#endif