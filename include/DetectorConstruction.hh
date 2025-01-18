// Define detector geometry

#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

// main class to inherit
#include "G4VUserDetectorConstruction.hh"

// define a box
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4VisAttributes.hh"
#include "G4Color.hh"

#include "SensitiveDetector.hh"
#include "ChemicalContent.hh"
#include "InputParameters.hh"

class Detectorconstruction : public G4VUserDetectorConstruction{
public:
        Detectorconstruction();
        virtual ~Detectorconstruction(); //the destructor is already defined in G4VUserDetectorConstruction

        virtual G4VPhysicalVolume *Construct(); //order to build up the detector geometry
private:
        G4LogicalVolume *logicRPC_x, *logicRPC_y, *logicTruck;
        
        // Construct sensitive detector and/or addition electromagnetic field
        virtual void ConstructSDandField();
};

#endif