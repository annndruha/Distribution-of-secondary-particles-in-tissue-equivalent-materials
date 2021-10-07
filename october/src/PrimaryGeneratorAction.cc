#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  fParticleGun = new G4ParticleGun();
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, -1));
  fParticleGun->SetParticleEnergy(5 * MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  static int i = 0;
  static const char* particle[] = {
    "e+", "e-", "gamma", "proton", "neutron", "alpha"};

  fParticleGun->SetParticleDefinition(
    G4ParticleTable::GetParticleTable()->FindParticle(particle[i]));

  fParticleGun->SetParticlePosition(G4ThreeVector(
    (G4UniformRand() - 0.5) * 10.0 * mm,
    (G4UniformRand() - 0.5) * 10.0 * mm,
    50 * mm
  ));

  fParticleGun->GeneratePrimaryVertex(anEvent);

  i = (i + 1) % 6;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
