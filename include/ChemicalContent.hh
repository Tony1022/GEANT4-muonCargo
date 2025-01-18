#ifndef CHEMICALCONTENT_HH
#define CHEMICALCONTENT_HH

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4SDManager.hh"
#include "G4Element.hh"

class ChemicalContent{
public:
    ChemicalContent();
    ~ChemicalContent();

    void gasComponent(G4double rho1, G4double rho2, G4double rho3, G4double rhoRPC, 
                      G4double temp1, G4double temp2, G4double temp3, G4double tempRPC, 
                      G4double press1, G4double press2, G4double press3, G4double pressRPC);

    void cargoComponent(G4double density);

    G4Material *ammoniumNitrate, *rpcGas, *air, *lead;

private:
    G4Element *elC, *elH, *elF, *elS, *elN, *elO;
    G4Material *C2H2F4, *SF6, *C4H10;
};

#endif