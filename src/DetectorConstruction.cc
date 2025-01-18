#include "DetectorConstruction.hh"

Detectorconstruction::Detectorconstruction(){

}

Detectorconstruction::~Detectorconstruction(){

}

G4VPhysicalVolume *Detectorconstruction::Construct(){
        InputParameters* ns = new InputParameters();
        ChemicalContent* matter = new ChemicalContent();
        G4bool checkOverlaps = true; //If overlap, G4 cannot calculate the boundaries correctly and everything goes wrong

        // Here define your world
        G4Box *solidWorld = new G4Box("solidWorld", 0.5*(ns->xWorld)*m, 0.5*(ns->yWorld)*m, 0.5*(ns->zWorld)*m);
        G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, matter->air, "logicWorld");
        G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);
        
        ns->blocker_parameters();

        // Built a scintillator layer
        G4Box *solidLead = new G4Box("solidLead", 0.5*(ns->leadSize)*m, 0.5*(ns->leadSize)*m, 0.5*(ns->leadThickness)*cm);
        G4LogicalVolume *logicLead = new G4LogicalVolume(solidLead, matter->lead, "logicLead");
        G4VPhysicalVolume *physLead = new G4PVPlacement(0, G4ThreeVector(0., 0., 8. * m), logicLead, "physLead", logicWorld, false, checkOverlaps);

        G4VisAttributes *leadVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 1.0, 0.5));
        leadVisAtt->SetForceSolid(true);
        logicLead->SetVisAttributes(leadVisAtt);

        ns->cargoContent_parameters();
        matter->cargoComponent(ns->NH4NO3_density);

        // Create truck
	G4Box *solidTruck = new G4Box("solidTruck", 0.5*(ns->xTruckFull)*m, 0.5*(ns->yTruckFull)*m, 0.5*(ns->zTruckFull)*m);
	logicTruck = new G4LogicalVolume(solidTruck, matter->ammoniumNitrate, "logicTruck");
	G4VPhysicalVolume *physTruck = new G4PVPlacement(0, G4ThreeVector(1., 0., 1.), logicTruck, "physTruck", logicWorld, false, 0, true); 

        G4VisAttributes *truckVis = new G4VisAttributes(G4Color(0.0, 1.0, 0.0, 0.5));
        truckVis->SetForceSolid(true);
        logicTruck->SetVisAttributes(truckVis);
        
        ns->RPC_parameters();
        matter->gasComponent(ns->C2H2F4_density, ns->C4H10_density, ns->SF6_density, ns->RPCgas_density,
                             ns->C2H2F4_temp, ns->C4H10_temp, ns->SF6_temp, ns->RPCgas_temp,
                             ns->C2H2F4_pressure, ns->C4H10_pressure, ns->SF6_pressure, ns->RPCgas_pressure);
        
        // Built RPC layer
        // RPC x-plate
        G4Box *rpc_x = new G4Box("rpc_x", 0.5*(ns->rpcLength)*m, 0.5*(ns->rpcWidth)*m, 0.5*(ns->rpcThickness)*mm);
        logicRPC_x = new G4LogicalVolume(rpc_x, matter->rpcGas, "logicRPC_x");
        G4VPhysicalVolume *physRPC_x = new G4PVPlacement(0, G4ThreeVector(0., 0., 4.0 * m), logicRPC_x, "physRPC_x", logicWorld, false, checkOverlaps);
        
        G4VisAttributes *rpc_xVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 0.0, 0.5));
        rpc_xVisAtt->SetForceSolid(true);
        logicRPC_x->SetVisAttributes(rpc_xVisAtt);

        // RPC y-plate
        G4Box *rpc_y = new G4Box("rpc_y", 0.5*(ns->rpcLength)*m, 0.5*(ns->rpcWidth)*m, 0.5*(ns->rpcThickness)*mm);
        logicRPC_y = new G4LogicalVolume(rpc_y, matter->rpcGas, "logicRPC_y");
        G4VPhysicalVolume *physRPC_y = new G4PVPlacement(0, G4ThreeVector(0., 0., -2.0 * m), logicRPC_y, "physRPC_y", logicWorld, false, checkOverlaps);
        
        G4VisAttributes *rpc_yVisAtt = new G4VisAttributes(G4Color(0.0, 1.0, 0.0, 0.5));
        rpc_yVisAtt->SetForceSolid(true);
        logicRPC_y->SetVisAttributes(rpc_yVisAtt);

        return physWorld;
}

void Detectorconstruction:: ConstructSDandField(){
        SensitiveDetector *sensDet = new SensitiveDetector("SensitiveDetector");
        logicRPC_x->SetSensitiveDetector(sensDet);
        logicRPC_y->SetSensitiveDetector(sensDet);
        
        // To ensure the Initialize() and EndOfEvent() defined previously are being called
        G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
}