#ifndef MYENVENTACTION_HH
#define MYENVENTACTION_HH

#include "G4UserEventAction.hh"

#include "MyAnalysis.hh"
#include "MyRunAction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4Event.hh"

#include "globals.hh"
#include <iomanip>
#include "Randomize.hh"
#include "G4UnitsTable.hh"
#include "G4AnalysisManager.hh"


class MyEventAction : public G4UserEventAction
{
public:
    MyEventAction(MyRunAction* runAction);
    virtual ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }

private:
    MyRunAction* fRunAction = nullptr;
    G4double   fEdep = 0.;

};

#endif
