#ifndef TCACTIONINITIALIZATION_HH
#define TCACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "TCPrimaryGenerator.hh"
#include "TCRunAction.hh"

class TCActionInitialization : public G4VUserActionInitialization{
public:
    TCActionInitialization();
    ~TCActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

};

#endif