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

// ================================================ GPS gun ================================================

/* PrimaryGeneratorAction::PrimaryGeneratorAction(): G4VUserPrimaryGeneratorAction(), fGPS(0)
{
  fGPS = new G4GeneralParticleSource();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fGPS;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
  fGPS->GeneratePrimaryVertex(anEvent);
} */


// ================================================ Custom gun =============================================

/* PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction(), fParticleGun(0)
{
  fParticleGun = new G4ParticleGun();
  fParticleGun->SetParticleEnergy(250 * MeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
  static int i = 0;
  const int n = 6;

  G4double r = 20 * cm;
  double sini = std::sin(i/6.0 * 2 * M_PI);
  double cosi = std::cos(i/6.0 * 2 * M_PI);
  G4double dx = (G4UniformRand() - 0.5) * cm;
  G4double dy = (G4UniformRand() - 0.5) * cm;
  G4double dz = (G4UniformRand() - 0.5) * cm;
  G4double pos = 0 * CLHEP::cm;

  fParticleGun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("neutron")); 
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(sini, 0, cosi));
  fParticleGun->SetParticlePosition(G4ThreeVector(dx -r*sini, 0 + dy, pos + dz -r*cosi));


  fParticleGun->GeneratePrimaryVertex(anEvent);
  i = (i + 1) % n;
} */


// ================================================ CSV gun =============================================

PrimaryGeneratorAction::PrimaryGeneratorAction(): G4VUserPrimaryGeneratorAction(), fParticleGun(0)
{
  fParticleGun = new G4ParticleGun();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
  static int i = 0;
  std::vector<std::vector<std::string>> data = csv_reader.getData();

  G4double z_shift =  -60* CLHEP::cm;

  G4String name = data[i][0];
  G4double x = stod(data[i][1]) * CLHEP::cm;
  G4double y = stod(data[i][2]) * CLHEP::cm;
  G4double z = -20.1* CLHEP::cm; // stod(data[i][3]) * CLHEP::cm + z_shift;
  G4double vx = stod(data[i][4]);
  G4double vy = stod(data[i][5]);
  G4double vz = stod(data[i][6]);
  G4double energy = stod(data[i][7]) * MeV;



  fParticleGun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle(name));
  fParticleGun->SetParticlePosition(G4ThreeVector(x, y, z));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(vx, vy, vz));
  fParticleGun->SetParticleEnergy(energy);
  fParticleGun->GeneratePrimaryVertex(anEvent);
  if (i < csv_reader.len()-1){
    i++;
  }
}