#ifndef MYACTIONINITIALIZATION_HH
#define MYACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "MyPrimaryGenerator.hh"
#include "MyRunAction.hh"
#include "MyEventAction.hh"
#include "MySteppingAction.hh"

class MyActionInitialization : public G4VUserActionInitialization
{
public:
	MyActionInitialization();
	~MyActionInitialization();
	
	virtual void BuildForMaster() const;
	virtual void Build() const;
};

#endif