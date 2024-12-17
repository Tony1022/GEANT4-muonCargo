#include "TCDetectorConstruction.hh"

TCDetectorconstruction::TCDetectorconstruction(){

}

TCDetectorconstruction::~TCDetectorconstruction(){

}

G4VPhysicalVolume *TCDetectorconstruction::Construct(){
        G4bool checkOverlaps = true; //If overlap, G4 cannot calculate the boundaries correctly and everything goes wrong

        G4NistManager *nist  = G4NistManager::Instance();

        // Here specify what material exists in your world (the frame that you are probing in)
        G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
        G4Material *leadMat = nist->FindOrBuildMaterial("G4_Pb");
        G4Material *frameMat = nist->FindOrBuildMaterial("G4_BAKELITE");

        // Here define the real RPC gas
        // The "G4_" prefix is for G4Material, no need if it is G4Element
        G4Element* elC = nist->FindOrBuildElement("C");
        G4Element* elH = nist->FindOrBuildElement("H");
        G4Element* elF = nist->FindOrBuildElement("F");
        G4Element* elS = nist->FindOrBuildElement("S");

        G4double density1 = 1.977*kg/m3;
        G4double density2 = 1.977*kg/m3;
        G4double density3 = 1.977*kg/m3;
        G4double gasDensity = 183*mg/cm3;
        G4double temperature = 293.15 * kelvin;
        G4double pressure = 1.0 * atmosphere;

        // Define the new gas material
        G4Material* C2H2F4 = new G4Material("C2H2F4", density1, 3, kStateGas, temperature, pressure);

        // Add elements to the material
        C2H2F4->AddElement(elC, 2); // 2 atoms of Carbon
        C2H2F4->AddElement(elH, 2); // 2 atoms of Hydrogen
        C2H2F4->AddElement(elF, 4); // 4 atoms of Fluorine

        G4Material* C4H10 = new G4Material("C4H10", density2, 2, kStateGas, temperature, pressure);
        C4H10->AddElement(elC, 4);
        C4H10->AddElement(elH, 10);

        G4Material* SF6 = new G4Material("SF6", density3, 2, kStateGas, temperature, pressure);
        SF6->AddElement(elS, 1);
        SF6->AddElement(elF, 6);

        G4Material* rpcGas = new G4Material("rpcGas", gasDensity, 3, kStateGas, temperature, pressure);
        rpcGas->AddMaterial(C2H2F4, 94.7*perCent);
        rpcGas->AddMaterial(C4H10, 5.0*perCent);
        rpcGas->AddMaterial(SF6, 0.3*perCent);

        // Here define your world
        G4double xWorld = 20. *m;
        G4double yWorld = 20. *m;
        G4double zWorld = 20. *m;

        // G4Box: definition of the shape - a cube box
        G4Box *solidWorld = new G4Box("solidWorld", 0.5*xWorld, 0.5*yWorld, 0.5*zWorld);
        // logic volume = physical volume with material filled in
        G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
        // 0: no rotation is applied
        // G4ThreeVector(0., 0., 0.): world volume appear at the center of coord. system
        // "physWorld": name
        // 0: no mother volume (i.e. physWorld is inside a container) here
        // false: we don't want to use it as a boolean (on/off switch button)
        // 0: copy number, as it is possible to have several physical volumes in a logical volume
        // checkOverlaps: ensure the overlap is counted
        G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);
        
        // Built a scintillator layer
        G4double leadThickness = 5. * mm;
        G4double leadSize = 8. * m;
        G4Box *solidLead = new G4Box("solidLead", 0.5*leadSize, 0.5*leadSize, 0.5*leadThickness);
        G4LogicalVolume *logicLead = new G4LogicalVolume(solidLead, leadMat, "logicLead");
        G4VPhysicalVolume *physLead = new G4PVPlacement(0, G4ThreeVector(0., 0., 8. * m), logicLead, "physLead", logicWorld, false, checkOverlaps);

        G4VisAttributes *leadVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 1.0, 0.5));
        leadVisAtt->SetForceSolid(true);
        logicLead->SetVisAttributes(leadVisAtt);

        // Built RPC layer
        G4double rpcLength = 6.0 * m;
        G4double rpcWidth = 3.0 * m;
        G4double rpcThickness = 20.0 * cm;

        // RPC P4 x
        G4Box *rpc_4x = new G4Box("rpc_4x", 0.5*rpcLength, 0.5*rpcWidth, 0.5*rpcThickness);
        logicRPC_4x = new G4LogicalVolume(rpc_4x, rpcGas, "logicRPC_4x");
        G4VPhysicalVolume *physRPC_4x = new G4PVPlacement(0, G4ThreeVector(0., 0., 7.5 * m), logicRPC_4x, "physRPC_4x", logicWorld, false, checkOverlaps);
        
        G4VisAttributes *rpc_4xVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 0.0, 0.5));
        rpc_4xVisAtt->SetForceSolid(true);
        logicRPC_4x->SetVisAttributes(rpc_4xVisAtt);

        // RPC P4 y
        G4Box *rpc_4y = new G4Box("rpc_4y", 0.5*rpcLength, 0.5*rpcWidth, 0.5*rpcThickness);
        logicRPC_4y = new G4LogicalVolume(rpc_4y, rpcGas, "logicRPC_4y");
        G4VPhysicalVolume *physRPC_4y = new G4PVPlacement(0, G4ThreeVector(0., 0., 7.0 * m), logicRPC_4y, "physRPC_4y", logicWorld, false, checkOverlaps);
        
        G4VisAttributes *rpc_4yVisAtt = new G4VisAttributes(G4Color(0.0, 1.0, 0.0, 0.5));
        rpc_4yVisAtt->SetForceSolid(true);
        logicRPC_4y->SetVisAttributes(rpc_4yVisAtt);

        // RPC P3 x
        G4Box *rpc_3x = new G4Box("rpc_3x", 0.5*rpcLength, 0.5*rpcWidth, 0.5*rpcThickness);
        logicRPC_3x = new G4LogicalVolume(rpc_3x, rpcGas, "logicRPC_3x");
        G4VPhysicalVolume *physRPC_3x = new G4PVPlacement(0, G4ThreeVector(0., 0., 6.5 * m), logicRPC_3x, "physRPC_3x", logicWorld, false, checkOverlaps);
        
        G4VisAttributes *rpc_3xVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 0.0, 0.5));
        rpc_3xVisAtt->SetForceSolid(true);
        logicRPC_3x->SetVisAttributes(rpc_3xVisAtt);

        // RPC P3 y
        G4Box *rpc_3y = new G4Box("rpc_3y", 0.5*rpcLength, 0.5*rpcWidth, 0.5*rpcThickness);
        logicRPC_3y = new G4LogicalVolume(rpc_3y, rpcGas, "logicRPC_3y");
        G4VPhysicalVolume *physRPC_3y = new G4PVPlacement(0, G4ThreeVector(0., 0., 6.0 * m), logicRPC_3y, "physRPC_3y", logicWorld, false, checkOverlaps);
        
        G4VisAttributes *rpc_3yVisAtt = new G4VisAttributes(G4Color(0.0, 1.0, 0.0, 0.5));
        rpc_3yVisAtt->SetForceSolid(true);
        logicRPC_3y->SetVisAttributes(rpc_3yVisAtt);

        // RPC P2 x
        G4Box *rpc_2x = new G4Box("rpc_2x", 0.5*rpcLength, 0.5*rpcWidth, 0.5*rpcThickness);
        logicRPC_2x = new G4LogicalVolume(rpc_2x, rpcGas, "logicRPC_2x");
        G4VPhysicalVolume *physRPC_2x = new G4PVPlacement(0, G4ThreeVector(0., 0., -0.5 * m), logicRPC_2x, "physRPC_2x", logicWorld, false, checkOverlaps);
        
        G4VisAttributes *rpc_2xVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 0.0, 0.5));
        rpc_2xVisAtt->SetForceSolid(true);
        logicRPC_2x->SetVisAttributes(rpc_2xVisAtt);

        // RPC P2 y
        G4Box *rpc_2y = new G4Box("rpc_2y", 0.5*rpcLength, 0.5*rpcWidth, 0.5*rpcThickness);
        logicRPC_2y = new G4LogicalVolume(rpc_2y, rpcGas, "logicRPC_2y");
        G4VPhysicalVolume *physRPC_2y = new G4PVPlacement(0, G4ThreeVector(0., 0., -1.0 * m), logicRPC_2y, "physRPC_2y", logicWorld, false, checkOverlaps);
        
        G4VisAttributes *rpc_2yVisAtt = new G4VisAttributes(G4Color(0.0, 1.0, 0.0, 0.5));
        rpc_2yVisAtt->SetForceSolid(true);
        logicRPC_2y->SetVisAttributes(rpc_2yVisAtt);

        // RPC P1 x
        G4Box *rpc_1x = new G4Box("rpc_1x", 0.5*rpcLength, 0.5*rpcWidth, 0.5*rpcThickness);
        logicRPC_1x = new G4LogicalVolume(rpc_1x, rpcGas, "logicRPC_1x");
        G4VPhysicalVolume *physRPC_1x = new G4PVPlacement(0, G4ThreeVector(0., 0., -1.5 * m), logicRPC_1x, "physRPC_1x", logicWorld, false, checkOverlaps);
        
        G4VisAttributes *rpc_1xVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 0.0, 0.5));
        rpc_1xVisAtt->SetForceSolid(true);
        logicRPC_1x->SetVisAttributes(rpc_1xVisAtt);

        // RPC P1 y
        G4Box *rpc_1y = new G4Box("rpc_1y", 0.5*rpcLength, 0.5*rpcWidth, 0.5*rpcThickness);
        logicRPC_1y = new G4LogicalVolume(rpc_1y, rpcGas, "logicRPC_1y");
        G4VPhysicalVolume *physRPC_1y = new G4PVPlacement(0, G4ThreeVector(0., 0., -2.0 * m), logicRPC_1y, "physRPC_1y", logicWorld, false, checkOverlaps);
        
        G4VisAttributes *rpc_1yVisAtt = new G4VisAttributes(G4Color(0.0, 1.0, 0.0, 0.5));
        rpc_1yVisAtt->SetForceSolid(true);
        logicRPC_1y->SetVisAttributes(rpc_1yVisAtt);

        return physWorld;
}

void TCDetectorconstruction:: ConstructSDandField(){
        TCSensitiveDetector *sensDet = new TCSensitiveDetector("SensitiveDetector");
        logicRPC_4x->SetSensitiveDetector(sensDet);
        logicRPC_4y->SetSensitiveDetector(sensDet);
        logicRPC_3x->SetSensitiveDetector(sensDet);
        logicRPC_3y->SetSensitiveDetector(sensDet);
        logicRPC_2x->SetSensitiveDetector(sensDet);
        logicRPC_2y->SetSensitiveDetector(sensDet);
        logicRPC_1x->SetSensitiveDetector(sensDet);
        logicRPC_1y->SetSensitiveDetector(sensDet);
        
        // To ensure the Initialize() and EndOfEvent() defined previously are being called
        G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
}