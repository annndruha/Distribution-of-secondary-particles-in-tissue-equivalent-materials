#include "DetectorConstruction.hh"

#include "G4RunManager.hh"

#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"

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
  /*G4Box* solidWorld =
    new G4Box("World",
       0.5 * world_size_x, 0.5 * world_size_y, 0.5 * world_size_z);*/
  G4Sphere* solidWorld = new G4Sphere("World",
                                  0,
                                  world_radius,
                                  0,
                                  2*M_PI,
                                  0,
                                  2*M_PI);

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

// == == == == == == == == == == == == == == == ==
// Создание анода
// как вычитание из цилиндра наклонённого параллелипипеда
//
  auto cylinder = new G4Tubs("Cylinder",
                          0.,
                          anode_radius,
                          anode_len,
                          0.,
                          2*M_PI);
  auto box = new G4Box("box",
                        anode_len*sin(abs(anode_angel)),
                        anode_len*sin(abs(anode_angel)),
                        anode_len*2);
  auto rm = new G4RotationMatrix(0, -anode_angel, 0);
  auto tm = new G4ThreeVector(0,0, -anode_len);
  auto anode = new G4SubtractionSolid("anode", cylinder, box, rm, *tm);


  G4LogicalVolume* logic = new G4LogicalVolume(anode, anode_material, "Anode");
  new G4PVPlacement(
    0,
    G4ThreeVector(0,
                  0,
                  0),
    logic,
    "Anode",
    logicWorld,
    false,
    0,
    false);
// == == == == == == == == == == == == == == == ==
// Создание объёма детектора
//
  auto target = new G4Sphere("Target",
                              world_radius - 0.01*cm,
                              world_radius,
                              0,
                              2*M_PI,
                              0,
                              2*M_PI);


  G4LogicalVolume* logic_tg = new G4LogicalVolume(target, target_material, "Target");
  new G4PVPlacement(
    0,
    G4ThreeVector(0,
                  0,
                  0),
    logic_tg,
    "Target",
    logicWorld,
    false,
    0,
    false);


  return physWorld;
}