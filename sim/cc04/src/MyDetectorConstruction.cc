#include "MyDetectorConstruction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
	// Messenger to change parameters of the geometry
	detectorMessenger = new MyDetectorMessenger(this);
}

MyDetectorConstruction::~MyDetectorConstruction()
{
	delete detectorMessenger;
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{

	// Define materials 
	DefineMaterials();

	// Define volumes
	return DefineVolumes();
}

void MyDetectorConstruction::DefineMaterials()
{
	// NIST
	G4NistManager* nist = G4NistManager::Instance();
	Air = nist->FindOrBuildMaterial("G4_AIR");
	Water = nist->FindOrBuildMaterial("G4_WATER");

	G4Element* elFe = G4NistManager::Instance()->FindOrBuildElement("Fe");
    G4Element* elNi = G4NistManager::Instance()->FindOrBuildElement("Ni");
    G4Element* elCr = G4NistManager::Instance()->FindOrBuildElement("Cr");
    Steel = new G4Material("StainlessSteel", 7.80 * g/cm3, 3 /* components */);
    Steel -> AddElement(elFe, 70 * perCent);
    Steel -> AddElement(elCr, 18 * perCent);
    Steel -> AddElement(elNi, 12 * perCent);

	G4VisAttributes * graySteel = new G4VisAttributes(G4Colour(0.5 ,0.5 ,0.5));
  	graySteel -> SetVisibility(true);
  	graySteel -> SetForceSolid(true);

	G4Element* elH = G4NistManager::Instance()->FindOrBuildElement("H");
    G4Element* elC = G4NistManager::Instance()->FindOrBuildElement("C");
    G4Element* elO = G4NistManager::Instance()->FindOrBuildElement("O");
	G4Element* elF = G4NistManager::Instance()->FindOrBuildElement("F");
	G4Element* elSi = G4NistManager::Instance()->FindOrBuildElement("Si");

	C552 = new G4Material("C552", 1.76 * g/cm3, 5 /* components */);
    C552 -> AddElement(elH, 2.468 * perCent);
    C552 -> AddElement(elC, 50.161 * perCent);
    C552 -> AddElement(elO, 0.04527 * perCent);
	C552 -> AddElement(elF, 46.5209 * perCent);
	C552 -> AddElement(elO, 0.3973 * perCent);

	// Print materials
	G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}


G4VPhysicalVolume* MyDetectorConstruction::DefineVolumes()
{
	// ------------------------------------------------------------------------------------------
	// Mother world volume
	// ------------------------------------------------------------------------------------------
	solidWorld = new G4Box("solidWorld", 50 * cm, 50 * cm, 50 * cm);
	logicWorld = new G4LogicalVolume(solidWorld, Air, "logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0, check_overlap);

	logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

	// Phantom
	G4Box* solidPhantom = new G4Box("solidPhantom", 15.*cm, 15*cm, 15*cm);
	G4LogicalVolume* logicPhantom = new G4LogicalVolume(solidPhantom, Water, "logicPhantom");
	G4RotationMatrix* Rot = new G4RotationMatrix;  	// Rotates X and Z axes only
	Rot->rotateY(90.*deg);                     		// Rotates 45 degrees
	physPhantom = new G4PVPlacement(Rot, G4ThreeVector(0., -15. *cm, 0.), logicPhantom, "physPhantom", logicWorld, false, 0, check_overlap);
	//logicPhantom->SetVisAttributes(G4VisAttributes::GetInvisible());

	// Detector
	G4RotationMatrix rotm  = G4RotationMatrix();

	G4Tubs* solidTub_Part1 = new G4Tubs("logicTub_Part1", 0. , 2.4 *mm, 2.1/2. *mm, 0. *deg, 360. *deg);
	G4ThreeVector position1 = G4ThreeVector(0., 0., 0.);

	G4Sphere* solidSphere_Part2 = new G4Sphere("solidSphere_Part2", 0., 2.4 *mm, 0., 360. *deg, 0., 90. *deg);
	G4ThreeVector position2 = G4ThreeVector(0., 0., 1.05 *mm);

	G4Tubs* solidTub_Part3 = new G4Tubs("logicTub_Part3", 0. , 3.4 *mm, 3.9/2. *mm, 0. *deg, 360. *deg);
	G4ThreeVector position3 = G4ThreeVector(0., 0., -3. *mm);
	
	G4Tubs* solidTub_Part4 = new G4Tubs("logicTub_Part4", 0. , 5.0 *mm, 17.0/2. *mm, 0. *deg, 360. *deg);
	G4ThreeVector position4 = G4ThreeVector(0., 0., -13.45 *mm);

	G4Tubs* solidTub_Part5 = new G4Tubs("logicTub_Part5", 0. , 3.4 *mm, 1.0/2. *mm, 0. *deg, 360. *deg);
	G4ThreeVector position5 = G4ThreeVector(0., 0., -22.45 *mm);

	G4Tubs* solidTub_Part6 = new G4Tubs("logicTub_Part6", 0. , 5.0 *mm, 5.2/2. *mm, 0. *deg, 360. *deg);
	G4ThreeVector position6 = G4ThreeVector(0., 0., -25.55 *mm);

	G4Tubs* solidTub_Part7 = new G4Tubs("logicTub_Part7", 0. , 3.4 *mm, 15.5/2. *mm, 0. *deg, 360. *deg);
	G4ThreeVector position7 = G4ThreeVector(0., 0., -35.90 *mm);

	G4Transform3D tr1 = G4Transform3D(rotm, position1);
	G4Transform3D tr2 = G4Transform3D(rotm, position2);
	G4Transform3D tr3 = G4Transform3D(rotm, position3);
	G4Transform3D tr4 = G4Transform3D(rotm, position4);
	G4Transform3D tr5 = G4Transform3D(rotm, position5);
	G4Transform3D tr6 = G4Transform3D(rotm, position6);
	G4Transform3D tr7 = G4Transform3D(rotm, position7);

	G4MultiUnion* solidDet = new G4MultiUnion("solidDet");
	solidDet->AddNode(*solidTub_Part1, tr1);
	solidDet->AddNode(*solidSphere_Part2, tr2);
	solidDet->AddNode(*solidTub_Part3, tr3);
	solidDet->AddNode(*solidTub_Part4, tr4);
	solidDet->AddNode(*solidTub_Part5, tr5);
	solidDet->AddNode(*solidTub_Part6, tr6);
	solidDet->AddNode(*solidTub_Part7, tr7);
	solidDet->Voxelize();

	G4LogicalVolume* logicDet = new G4LogicalVolume(solidDet, C552, "logicDet");
	physDet = new G4PVPlacement(0, G4ThreeVector(0., 0. *cm, 0.), logicDet, "physDet", logicPhantom, false, 0, check_overlap);

	// Inner electrode
	G4Tubs* solidElectrode = new G4Tubs("solidElectrode", 0. , 0.5 *mm, 2.1 *mm, 0., 360 *deg);
	G4LogicalVolume* logicElectrode = new G4LogicalVolume(solidElectrode, Steel, "logicElectrode");
	new G4PVPlacement(0, G4ThreeVector(), logicElectrode, "physElectrode", logicDet, false, 0, check_overlap);
	logicElectrode -> SetVisAttributes(graySteel);

	// Sensitive det
	G4Tubs* solidSen_Part1 = new G4Tubs("solidSen_Part1", 0.5 *mm , 2.0 *mm, 2.1/2. *mm, 0. *deg, 360. *deg);
	G4ThreeVector position11 = G4ThreeVector(0., 0., 0.);

	G4Sphere* solidSen_Part2 = new G4Sphere("solidSen_Part2", 0., 2.0 *mm, 0., 360. *deg, 0., 90. *deg);
	G4ThreeVector position21 = G4ThreeVector(0., 0., 1.05 *mm);

	G4Transform3D tr11 = G4Transform3D(rotm, position11);
	G4Transform3D tr21 = G4Transform3D(rotm, position21);
	G4MultiUnion* solidSen = new G4MultiUnion("solidSen");
	solidSen->AddNode(*solidSen_Part1, tr11);
	solidSen->AddNode(*solidSen_Part2, tr21);
	solidSen->Voxelize();
	G4LogicalVolume* logicSen = new G4LogicalVolume(solidSen, Air, "logicSen");
	new G4PVPlacement(0, G4ThreeVector(), logicSen, "physSen", logicDet, false, 0, check_overlap);
	
	// Set Scoring Volume
	fScoringVolume = logicSen;

	return physWorld;
}
