#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include <sstream>

#include "Z6CreateBTarget.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  auto air = nist->FindOrBuildMaterial("G4_AIR");

  G4double world_sizeXY = 10 * cm,
           world_sizeZ  = 10 * cm;

  G4Box* solidWorld =
    new G4Box("World", 0.5*world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ);

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,
                        air,
                        "World");

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,
                      G4ThreeVector(),
                      logicWorld,
                      "World",
                      0,
                      false,
                      0,
                      false);

  auto materials = {
    nist->FindOrBuildMaterial("G4_Li"),
    nist->FindOrBuildMaterial("G4_NITROBENZENE"),
    nist->FindOrBuildMaterial("G4_W"),
    nist->FindOrBuildMaterial("G4_Cu"),
    nist->FindOrBuildMaterial("G4_WATER")
  };

  G4double ph_x_size = 10.0 * mm,
           ph_y_size = 10.0 * mm,
           ph_z_size =  1.0 * mm;

  G4Box* solid = new G4Box("Phantom", ph_x_size / 2.0, ph_y_size / 2.0, ph_z_size / 2.0);

  int j = 0;
  for(auto i: materials){
    std::stringstream ss;

    ss << "Phantom_" << j;

    G4LogicalVolume* logic =
      new G4LogicalVolume(solid, i, ss.str());

    new G4PVPlacement(0,
                      G4ThreeVector(0, 0, ph_z_size * j),
                      logic,
                      ss.str(),
                      logicWorld,
                      false,
                      0,
                      false);
    ++j;
  }

  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
