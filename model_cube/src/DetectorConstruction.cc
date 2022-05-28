#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4Colour.hh"
#include "G4Element.hh"

#include "G4FieldManager.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4PVParameterised.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4TransportationManager.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"

#include "DetectorConstruction.hh"
#include "HyperParameters.hh"
#include "Field.hh"

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction(), fScoringVolume(0)
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
  // == == == == == == == == == == == == == == == ==
  // Создание мира
  //
  G4Box *solidWorld = new G4Box("World", world_dx, world_dy, world_dz);

  G4LogicalVolume *logicWorld =
      new G4LogicalVolume(solidWorld,     // its solid
                          world_material, // its material
                          "World");       // its name

  G4VPhysicalVolume *physWorld =
      new G4PVPlacement(0,               // no rotation
                        G4ThreeVector(), // at (0,0,0)
                        logicWorld,      // its logical volume
                        "World",         // its name
                        0,               // its mother  volume
                        false,           // no boolean operation
                        0,               // copy number
                        false);          // overlaps checking
  // == == == == == == == == == == == == == == == ==
  // Создание маски
  //


  // == == == == == == == == == == == == == == == ==
  // Создание объёма куба
  //
/*   G4NistManager* nist = G4NistManager::Instance();
  G4Element* H = nist->FindOrBuildElement(1);
  G4Element* C = nist->FindOrBuildElement(6);
  G4Element* O = nist->FindOrBuildElement(8);
  G4Element* N = nist->FindOrBuildElement(7);
  G4Element* K = nist->FindOrBuildElement(19);
  G4Element* P = nist->FindOrBuildElement(15);
  G4Element* S = nist->FindOrBuildElement(16);
  G4Element* Mg = nist->FindOrBuildElement(12);
  G4Element* Ca = nist->FindOrBuildElement(20);
  G4Element* Zn = nist->FindOrBuildElement(30);
  G4Element* Na = nist->FindOrBuildElement(11);
  G4Element* Cl = nist->FindOrBuildElement(17);
  G4Element* Fe = nist->FindOrBuildElement(26);
  G4Element* Si = nist->FindOrBuildElement(14);
  G4Element* Cr = nist->FindOrBuildElement(24);
  G4Element* Ti = nist->FindOrBuildElement(22);
  G4Element* Mn = nist->FindOrBuildElement(25);
  G4Element* Ni = nist->FindOrBuildElement(28);
  G4Element* Cu = nist->FindOrBuildElement(29);
  G4Element* Pb = nist->FindOrBuildElement(82);
  G4Element* Al = nist->FindOrBuildElement(13);

  G4Material* acrylic = new G4Material("G4_ACRYLIC", 1.19 * g / cm3, 3);
  acrylic->AddElement(C, 5);
  acrylic->AddElement(H, 8);
  acrylic->AddElement(O, 2);
  G4Material *box_material = acrylic; //!!!!!!!!!!!!! */


  G4Material *box_material =
    G4NistManager::Instance()->FindOrBuildMaterial("G4_A-150_TISSUE"); //G4_POLYSTYRENE //G4_WATER //G4_PARAFFIN"
  
  
  auto box = new G4Box("box", box_len, box_len, box_len);
  G4LogicalVolume *logic_box = new G4LogicalVolume(box, box_material, "Box");

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

  return physWorld;
}