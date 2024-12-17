#include "TCRunAction.hh"

TCRunAction::TCRunAction(){
      G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

      // CreateH1 means create histogram, 1-dimension
      analysisManager->CreateH1("Edep", "Energy deposit", 100, 0., 1.1 * MeV);

      analysisManager->CreateNtuple("Photons", "Photons");
      analysisManager->CreateNtupleIColumn("iEvent");
      analysisManager->CreateNtupleDColumn("fX");
      analysisManager->CreateNtupleDColumn("fY");
      analysisManager->CreateNtupleDColumn("fZ");
      analysisManager->CreateNtupleDColumn("fGlobalTime");
      analysisManager->CreateNtupleDColumn("fWlen");
      analysisManager->FinishNtuple(0);
}

TCRunAction::~TCRunAction(){

}

void TCRunAction::BeginOfRunAction(const G4Run *run){
      G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
      G4int runID = run->GetRunID();

      std::stringstream strRunID;
      strRunID << runID;

      analysisManager->OpenFile("output" + strRunID.str() + ".root");
}

void TCRunAction::EndOfRunAction(const G4Run *run){
      // Local object is easier to handle
      G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

      // Wait, here seems is the standard ROOT format....
      // Otherwise nothing will appear after the program ends
      analysisManager->Write();
      analysisManager->CloseFile();

      G4int runID = run->GetRunID();

      G4cout << "Finishing run " << runID << G4endl;
}