#include <iostream>

#include "G4RunManager.hh"     //Core of running G4
#include "G4MTRunManager.hh"   //For multi-thread running
#include "G4UImanager.hh"   //For user interface
#include "G4VisManager.hh"  //For visualization
#include "G4VisExecutive.hh"  
#include "G4UIExecutive.hh"

// Self-defined simulation details
#include "TCPhysicsList.hh"
#include "TCDetectorConstruction.hh"
#include "TCActionInitialization.hh"

#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4SDManager.hh"

int main(int argc, char** argv){
        // Initialize the happy user interface
        //G4UIExecutive *ui = new G4UIExecutive(argc, argv);
        G4UIExecutive *ui; // not to initialize here in order to initialize this at a later point

        // different way if multi-threaded in installed
        #ifdef G4MULTITHREADED 
                G4MTRunManager *runManager = new G4MTRunManager;
        #else
                G4RunManager *runManager = new G4RunManager;
        #endif

        // Physics list
        runManager->SetUserInitialization(new TCPhysicsList());

        // Detector construction
        runManager->SetUserInitialization(new TCDetectorconstruction());

        // Action initialization
        runManager->SetUserInitialization(new TCActionInitialization());

        // start the UI only if the number of command line arguments is equal to one
        // Otherwise, no UI is showed, just run in the batch mode
        G4UImanager *UImanager = G4UImanager::GetUIpointer();
        if(argc == 1){
                ui = new G4UIExecutive(argc, argv);
                G4VisManager *visManager = new G4VisExecutive;
                visManager->Initialize();
        
                UImanager->ApplyCommand("/control/execute vis.mac");
                ui->SessionStart();
        }
        else{
                G4String command = "/control/execute ";
                G4String fileName = argv[1];
                UImanager->ApplyCommand(command + fileName);
        }
        
        // new trick: install ROOT file viewer the vscode extension if you don't want to open root each time to see histograms
        return 0;
}