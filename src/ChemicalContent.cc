#include "ChemicalContent.hh"

ChemicalContent::ChemicalContent(){
    G4NistManager *nist  = G4NistManager::Instance();

    elC  = nist->FindOrBuildElement("C");
    elH  = nist->FindOrBuildElement("H");
    elF  = nist->FindOrBuildElement("F");
    elS  = nist->FindOrBuildElement("S");
    elN  = nist->FindOrBuildElement("N");
    elO  = nist->FindOrBuildElement("O");
    air = nist->FindOrBuildMaterial("G4_AIR");
    lead = nist->FindOrBuildMaterial("G4_Pb");

}

ChemicalContent::~ChemicalContent(){
    delete elC, elH, elF, elO, elN, elS, C2H2F4, SF6, C4H10;
}

void ChemicalContent::gasComponent(G4double rho1, G4double rho2, G4double rho3, G4double rhoRPC, 
                                   G4double temp1, G4double temp2, G4double temp3, G4double tempRPC, 
                                   G4double press1, G4double press2, G4double press3, G4double pressRPC){
    
    C2H2F4 = new G4Material("C2H2F4", rho1*kg/m3, 3, kStateGas, temp1*kelvin, press1*atmosphere);

    // Add elements to the material
    C2H2F4->AddElement(elC, 2); // 2 atoms of Carbon
    C2H2F4->AddElement(elH, 2); // 2 atoms of Hydrogen
    C2H2F4->AddElement(elF, 4); // 4 atoms of Fluorine

    C4H10 = new G4Material("C4H10", rho2*kg/m3, 2, kStateGas, temp2*kelvin, press2*atmosphere);
    C4H10->AddElement(elC, 4);
    C4H10->AddElement(elH, 10);

    SF6 = new G4Material("SF6", rho3*kg/m3, 2, kStateGas, temp3*kelvin, press3*atmosphere);
    SF6->AddElement(elS, 1);
    SF6->AddElement(elF, 6);

    rpcGas = new G4Material("rpcGas", rhoRPC*kg/m3, 3, kStateGas, tempRPC*kelvin, pressRPC*atmosphere);
    rpcGas->AddMaterial(C2H2F4, 94.7*perCent);
    rpcGas->AddMaterial(C4H10, 5.0*perCent);
    rpcGas->AddMaterial(SF6, 0.3*perCent);
}

void ChemicalContent::cargoComponent(G4double density){
    ammoniumNitrate = new G4Material("ammoniumNitrate", density*g/cm3, 3);
	ammoniumNitrate->AddElement(elN, 2);
	ammoniumNitrate->AddElement(elH, 4);
	ammoniumNitrate->AddElement(elO, 3);
}

