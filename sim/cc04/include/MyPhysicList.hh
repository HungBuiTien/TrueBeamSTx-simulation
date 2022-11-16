#ifndef MYPHYSICLIST_HH
#define MYPHYSICLIST_HH

#include "G4VUserPhysicsList.hh"
#include "G4ParticleTypes.hh"
#include "G4PhysicsListHelper.hh"
#include "G4SystemOfUnits.hh"

#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"

#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuMultipleScattering.hh"
#include "G4WentzelVIModel.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4CoulombScattering.hh"

#include "G4hMultipleScattering.hh"
#include "G4ionIonisation.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"

#include "G4StepLimiter.hh"

class MyPhysicList : public G4VUserPhysicsList
{
public:
	MyPhysicList();
	virtual ~MyPhysicList();

protected:
	// construction of particles
	void ConstructParticle();

	// construct processes and register them to particles
	void ConstructProcess();

	// setting a range cut value for all particles
	void SetCuts();

protected:
	void SetGammaCut(G4double);
	void SetElectronCut(G4double);
	void SetPositronCut(G4double);
	//void SetProtonCut(G4double);

protected:
	G4double fCutForGamma;
	G4double fCutForElectron;
	G4double fCutForPositron;
	//G4double fCutForProton;

protected:
	void ConstructEM();
	void ConstructGeneral();
};

#endif