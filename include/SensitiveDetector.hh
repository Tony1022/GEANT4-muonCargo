#ifndef SENSITIVEDETECTOR_HH
#define SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

class SensitiveDetector : public G4VSensitiveDetector{
public:
    SensitiveDetector(G4String);
    ~SensitiveDetector();

private:
    // total energy deposited per event to our sensitive detector
    G4double fTotalEnergyDeposited;

    // This will be called by G4 when a new event start
    // "G4HCofThisEvent" = G4 Hit Collection of this event
    // Important only if we want to do analysis and reconstruction within G4
    // or add noise to the detection
    virtual void Initialize(G4HCofThisEvent *) override;
    virtual void EndOfEvent(G4HCofThisEvent *) override;

    // Main function that handles whatever happens during the time when the particle is inside the detector
    // in which step, we can get some information from it 
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *) override;

};

#endif