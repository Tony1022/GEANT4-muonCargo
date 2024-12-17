#include "TCSensitiveDetector.hh"

TCSensitiveDetector::TCSensitiveDetector(G4String name) : G4VSensitiveDetector(name){
    // To make sure at the start, there is no problem
    fTotalEnergyDeposited = 0.;
}

TCSensitiveDetector::~TCSensitiveDetector(){

}

void TCSensitiveDetector::Initialize(G4HCofThisEvent *){
    // Reset the detector each time when restart
    fTotalEnergyDeposited = 0.;
}

G4bool TCSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *touchHist){
    
    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();

    G4double fglobalTime = preStepPoint->GetGlobalTime();
    G4ThreeVector posPhoton = preStepPoint->GetPosition();
    G4ThreeVector momPhoton = preStepPoint->GetMomentum();

    G4double fMomPhotonMag = momPhoton.mag(); // mag() for magnitude
    G4double fWlen = (1.239841939 * eV/fMomPhotonMag) * 1E+03;

    analysisManager->FillNtupleIColumn(0, 0, eventID);
    analysisManager->FillNtupleDColumn(0, 1, posPhoton[0]);
    analysisManager->FillNtupleDColumn(0, 2, posPhoton[1]);
    analysisManager->FillNtupleDColumn(0, 3, posPhoton[2]);
    analysisManager->FillNtupleDColumn(0, 4, posPhoton[3]);
    analysisManager->FillNtupleDColumn(0, 5, fWlen);
    // Means our row is finished
    analysisManager->AddNtupleRow(0);

    // G4 built-in function to access energy info
    // Very strong bro...
    G4double fEnergyDeposited = aStep->GetTotalEnergyDeposit();

    if (fEnergyDeposited > 0){
        fTotalEnergyDeposited += fEnergyDeposited;
    }

    return true;
}

void TCSensitiveDetector::EndOfEvent(G4HCofThisEvent *){
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    
    // Fill histogram here, not Ntuple
    analysisManager->FillH1(0, fTotalEnergyDeposited);

    G4cout << "Deposited energy: " << fTotalEnergyDeposited << G4endl;
}