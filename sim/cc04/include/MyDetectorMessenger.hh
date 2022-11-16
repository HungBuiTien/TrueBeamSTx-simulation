#ifndef MYDETECTORMESSENGER_HH
#define MYDETECTORMESSENGER_HH

#include "globals.hh"
#include "G4UImessenger.hh"

#include "G4UIcmdWithAnInteger.hh"

class MyDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;

class MyDetectorMessenger : public G4UImessenger
{
public:
    MyDetectorMessenger(MyDetectorConstruction*);
    ~MyDetectorMessenger();

    void SetNewValue(G4UIcommand*, G4String);

private:

    // Pointer to the detector component
    MyDetectorConstruction* GammaKnifeDetector;

    G4UIdirectory* calorimeterDir; // Control of the calorimeter

    G4UIcmdWithAnInteger* calorimeterHelmetSizeCmd;

};


#endif // !MYDETECTORMESSENGER_HH
