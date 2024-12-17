// Define detector geometry

#ifndef TCDETECTORCONSTRUCTION_HH
#define TCDETECTORCONSTRUCTION_HH

// main class to inherit
#include "G4VUserDetectorConstruction.hh"

// define a box
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh" // use of units
#include "G4UnitsTable.hh"

#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4SDManager.hh"

#include "TCSensitiveDetector.hh"

class TCDetectorconstruction : public G4VUserDetectorConstruction{
public:
        TCDetectorconstruction();
        virtual ~TCDetectorconstruction(); //the destructor is already defined in G4VUserDetectorConstruction

        virtual G4VPhysicalVolume *Construct(); //order to build up the detector geometry
private:
        G4LogicalVolume *logicRPC_4x;
        G4LogicalVolume *logicRPC_4y;
        G4LogicalVolume *logicRPC_3x;
        G4LogicalVolume *logicRPC_3y;
        G4LogicalVolume *logicRPC_2x;
        G4LogicalVolume *logicRPC_2y;
        G4LogicalVolume *logicRPC_1x;
        G4LogicalVolume *logicRPC_1y;
        
        // Construct sensitive detector and/or addition electromagnetic field
        virtual void ConstructSDandField();
};

#endif