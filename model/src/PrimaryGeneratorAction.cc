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
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
  fParticleGun->SetParticleEnergy(10 * MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
  static int i = 0;
  const int n = 6;

  fParticleGun->SetParticleDefinition(
      G4ParticleTable::GetParticleTable()->FindParticle("gamma"));

  G4double r = 20 * cm;
  double sini = std::sin(i/6.0 * 2 * M_PI);
  double cosi = std::cos(i/6.0 * 2 * M_PI);

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(sini, 0, cosi));

  G4double dx = (G4UniformRand() - 0.5) * cm;
  G4double dy = (G4UniformRand() - 0.5) * cm;
  G4double dz = (G4UniformRand() - 0.5) * cm;
  G4double pos = 147.5 * CLHEP::cm;
  fParticleGun->SetParticlePosition(G4ThreeVector(dx -r*sini,
                                                  0 + dy,
                                                  pos + dz -r*cosi));

  fParticleGun->GeneratePrimaryVertex(anEvent);

  i = (i + 1) % n;
}
