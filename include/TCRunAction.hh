#ifndef TCRUNACTION_HH
#define TCRUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

class TCRunAction : public G4UserRunAction{
public:
      TCRunAction();
      ~TCRunAction();

      virtual void BeginOfRunAction(const G4Run *);
      virtual void EndOfRunAction(const G4Run *);
};

#endif