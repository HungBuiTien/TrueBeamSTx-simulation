#include "MyPrimaryGenerator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	particleSource = new G4GeneralParticleSource();
	
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete particleSource;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	particleSource->GeneratePrimaryVertex(anEvent);
}