// This is the program to simulate Gamma ART-6000TM
// Version: 2.0
// Date: 12/14/2021
// Author: Hung Bui Tien
// Email: hungbuitien19081997@gmail.com
// Organization: Hanoi University of Science and Technology 


#include <iostream>
#include "G4Types.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4Types.hh"
#include "Randomize.hh"
#include "G4SteppingVerbose.hh"

#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "MyDetectorConstruction.hh"
#include "MyPhysicList.hh"
#include "MyActionInitialization.hh"

#include "G4ScoringManager.hh"


namespace {
	void PrintUsage() {
		G4cerr << " Usage: " << G4endl;
		G4cerr << " GammaKnife [-m macro ] [-u UIsession] [-t nThreads] [-nps nHistories]" << G4endl;
		G4cerr << "   note: -t option is available only for multi-threaded mode."
			<< G4endl;
	}
}

int main(int argc, char** argv)
{
	// Evaluate arguments
	//
	if (argc > 7) {
		PrintUsage();
		return 1;
	}

	G4String nps;
	G4String macro;
	G4String session;

#ifdef G4MULTITHREADED
	G4int nThreads = 0;
#endif
	for (G4int i = 1; i < argc; i = i + 2) {
		if (G4String(argv[i]) == "-m") macro = argv[i + 1];
		else if (G4String(argv[i]) == "-u") session = argv[i + 1];
		else if (G4String(argv[i]) == "-nps") nps = argv[i + 1];
#ifdef G4MULTITHREADED
		else if (G4String(argv[i]) == "-t") {
			nThreads = G4UIcommand::ConvertToInt(argv[i + 1]);

		}
#endif
		else {
			PrintUsage();
			return 1;
		}
	}

	// Detect interactive mode (if no macro provided) and define UI session
    //
	G4UIExecutive* ui = 0;
	if (!macro.size()) {
		ui = new G4UIExecutive(argc, argv, session);
	}

	// Optionally: choose a different Random engine...
	//
	G4Random::setTheEngine(new CLHEP::MTwistEngine);

	// Construct the default run manager
	//
/*	
#ifdef G4MULTITHREADED
	G4MTRunManager* runManager = new G4MTRunManager();
	if (nThreads > 0) {
		runManager->SetNumberOfThreads(nThreads);
	}
#else
	G4RunManager* runManager = new G4RunManager;
#endif
*/
	G4RunManager* runManager = new G4RunManager;

	// Activate UI-command base scorer
	G4ScoringManager* scManager = G4ScoringManager::GetScoringManager();
	scManager->SetVerboseLevel(1);
	
	//Choose the Random engine and reset the seed (before the RunManager)
	//
	CLHEP::MixMaxRng* randomEngine = new CLHEP::MixMaxRng();
	G4Random::setTheEngine(randomEngine);
	CLHEP::HepRandom::setTheSeed(time(NULL));

	// Set mandatory initialization classes
	//
	auto detConstruction = new MyDetectorConstruction();
	runManager->SetUserInitialization(detConstruction);

	auto phys = new MyPhysicList();
	runManager->SetUserInitialization(phys);

	auto actionInitialization = new MyActionInitialization();
	runManager->SetUserInitialization(actionInitialization);

	// Initialize G4 kernel
	//
	runManager->Initialize();

	// Initialize visualization
	//
	G4VisManager* visManager = nullptr;
	visManager = new G4VisExecutive;
	visManager->Initialize();

	// Get the pointer to the User Interface manager
	auto UImanager = G4UImanager::GetUIpointer();


	// Process macro or start UI session
	//
	if (macro.size()) {
		// batch mode
		//G4String command0 = "/ run/numberOfThreads ";
		//UImanager->ApplyCommand(command0 + nThreads);
		G4String command = "/control/execute ";
		UImanager->ApplyCommand(command + macro);
		G4String command1 = "/run/beamOn ";
		UImanager->ApplyCommand(command1 + nps);
	}
	else {
		// interactive mode : define UI session
		UImanager->ApplyCommand("/control/execute defaultMacro.mac");
		ui->SessionStart();
		delete ui;
	}
	delete visManager;
	delete runManager;

	return 0;
}