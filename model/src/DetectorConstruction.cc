#include "DetectorConstruction.hh"

#include "G4RunManager.hh"

#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "HyperParameters.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

DetectorConstruction::~DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4Box* solidWorld =
    new G4Box("World",
       0.5 * world_size_x, 0.5 * world_size_y, 0.5 * world_size_z);

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,              // its solid
                        world_material,          // its material
                        "World");                // its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      false);                //overlaps checking



  auto solid = new G4Box("Target", target_size_x, target_size_y, target_size_z);
  G4LogicalVolume* logic = new G4LogicalVolume(solid, target_material, "Target");

  new G4PVPlacement(
    0,
    G4ThreeVector(target_position_x,
                  target_position_y,
                  target_position_z),
    logic,
    "Target",
    logicWorld,
    false,
    0,
    false);

  return physWorld;
}