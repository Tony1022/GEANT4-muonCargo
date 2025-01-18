#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization(){

}

ActionInitialization::~ActionInitialization(){

}

// Histograms will be created in the master thread
void ActionInitialization::BuildForMaster() const{
    RunAction *runAction = new RunAction();
    SetUserAction(runAction);
}

void ActionInitialization::Build() const{
    PrimaryGenerator *generator = new PrimaryGenerator();
    SetUserAction(generator);

    RunAction *runAction = new RunAction();
    SetUserAction(runAction);
}