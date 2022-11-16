#include "MyDetectorMessenger.hh"
#include "MyDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4SystemOfUnits.hh"


MyDetectorMessenger::MyDetectorMessenger(
	MyDetectorConstruction* detector)
	:GammaKnifeDetector(detector)
{

	calorimeterDir = new G4UIdirectory("/calorimeter/");
	calorimeterDir->SetGuidance("Command to rotate the spherical phantom");


	calorimeterHelmetSizeCmd = new G4UIcmdWithAnInteger("/calorimeter/helmetSize", this);
	calorimeterHelmetSizeCmd->SetGuidance("Set helmet size(4, 8, 14, 18)");
	calorimeterHelmetSizeCmd->SetParameterName("Size", false);
	calorimeterHelmetSizeCmd->AvailableForStates(G4State_Idle, G4State_PreInit);
}

MyDetectorMessenger::~MyDetectorMessenger()
{
	delete calorimeterDir;
}

void MyDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
	if (command == calorimeterHelmetSizeCmd)
	{
		//GammaKnifeDetector->SetHelmetSize(calorimeterHelmetSizeCmd->GetNewIntValue(newValue));
	}
}
