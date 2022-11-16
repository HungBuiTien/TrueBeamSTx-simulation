#ifndef MYSTEPPINGACTION_HH
#define MYSTEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

#include "MyEventAction.hh"
#include "MyDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"

#include "globals.hh"
#include "G4SystemOfUnits.hh"

#include "G4LogicalVolume.hh"

#include "G4AnalysisManager.hh"


class MyEventAction;
class G4LogicalVolume;

class MySteppingAction : public G4UserSteppingAction
{
  public:
    MySteppingAction(MyEventAction * eventAction);
    virtual ~MySteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step* );

  private:
    MyEventAction* fEventAction;
};

#endif