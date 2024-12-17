#include "TCActionInitialization.hh"

TCActionInitialization::TCActionInitialization(){

}

TCActionInitialization::~TCActionInitialization(){

}

// Histograms will be created in the master thread
void TCActionInitialization::BuildForMaster() const{
    TCRunAction *runAction = new TCRunAction();
    SetUserAction(runAction);
}

void TCActionInitialization::Build() const{
    TCPrimaryGenerator *generator = new TCPrimaryGenerator();
    SetUserAction(generator);

    TCRunAction *runAction = new TCRunAction();
    SetUserAction(runAction);
}