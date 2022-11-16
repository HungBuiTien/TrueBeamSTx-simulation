#include "MyEventAction.hh"



MyEventAction::MyEventAction(MyRunAction* runAction)
: fRunAction(runAction)
{
	fEdep = 0.;
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
	// initialisation per event
	fEdep = 0.;
}

void MyEventAction::EndOfEventAction(const G4Event* event)
{
	G4cout << "Energy deposition: " << fEdep << G4endl;

	// get analysis manager
	G4AnalysisManager* man = G4AnalysisManager::Instance();

	fRunAction->AddEdep(fEdep);
	
}