#ifndef MYDETECTORCONSTRUCTION_HH
#define	MYDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Orb.hh"

#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4VisAttributes.hh"

#include "G4MultiUnion.hh"
#include "G4SubtractionSolid.hh"

#include "G4RunManager.hh"
#include "globals.hh"

#include "MyDetectorMessenger.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"


class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();

private:
	//virtual void ConstructSDandField();

private:
	// methods
	//
	void DefineMaterials();
	G4VPhysicalVolume* DefineVolumes();

	G4bool check_overlap = true;
	static G4ThreadLocal G4GlobalMagFieldMessenger* fMagFieldMessenger;

public:
	// Solid volume
	G4Box* solidWorld;

	// Logical volume
	G4LogicalVolume* logicWorld;

	// Physical volume
	G4VPhysicalVolume* physWorld , * physPhantom, * physDet;

	// Material
	G4Material* Air, * Water, *Steel, *C552;

	G4VisAttributes* graySteel;

	
	MyDetectorMessenger* detectorMessenger;

public:
	// get methods
	//
	G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

private:
	G4LogicalVolume* fScoringVolume;
};


#endif