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
#include "Field.hh"

#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"
#include "G4FieldManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4PVParameterised.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4TransportationManager.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"


DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

DetectorConstruction::~DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
/*   ExN04Field* myField = new ExN04Field;
  G4FieldManager* fieldMgr
    = G4TransportationManager::GetTransportationManager()->
      GetFieldManager();
  fieldMgr-> SetDetectorField(myField);
  fieldMgr-> CreateChordFinder(myField); */

  G4Box* solidWorld = new G4Box("World", world_len, world_len, world_len);

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,              // its solid
                        world_material,          // its material
                        "World");                // its name

/*   auto field = new ExN04Field;
  auto manager = new G4FieldManager(field);
  logicWorld -> SetFieldManager(manager, true); */

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
/*   auto cylinder = new G4Tubs("Cylinder",
                          0.,
                          anode_radius,
                          anode_len,
                          0.,
                          2*M_PI);

  auto rm = new G4RotationMatrix(0, -anode_angel, 0);
  auto tm = new G4ThreeVector(0,0, -anode_len);
  auto anode = new G4SubtractionSolid("anode", cylinder, box, rm, *tm); */

  auto box = new G4Box("box", box_len, box_len, box_len);
  G4LogicalVolume* logic_box = new G4LogicalVolume(box, box_material, "Box");

  new G4PVPlacement(
    0,
    G4ThreeVector(0,
                  0,
                  0),
    logic_box,
    "Box",
    logicWorld,
    false,
    0,
    false);
// == == == == == == == == == == == == == == == ==
// Создание объёма детектора
//
/*   auto target = new G4Sphere("Target",
                              world_radius - 0.01*cm,
                              world_radius,
                              0,
                              2*M_PI,
                              0,
                              2*M_PI); */


/*   G4LogicalVolume* logic_tg = new G4LogicalVolume(target, target_material, "Target"); */

/*   new G4PVPlacement(
    0,
    G4ThreeVector(0,
                  0,
                  0),
    logic_box,
    "Box",
    logicWorld,
    false,
    0,
    false); */


  return physWorld;
}