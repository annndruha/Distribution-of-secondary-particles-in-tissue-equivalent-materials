/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Para.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include <math.h>

B1DetectorConstruction::B1DetectorConstruction()
    : G4VUserDetectorConstruction(),
      fScoringVolume(0)
{
}

B1DetectorConstruction::~B1DetectorConstruction()
{
}

G4VPhysicalVolume *B1DetectorConstruction::Construct()
{
  G4NistManager *nist = G4NistManager::Instance();

  // Concrete cube
  G4double box_len = 20 * cm;
  G4Box *box = new G4Box("Box", box_len, box_len, box_len);
  G4Material *concrete = nist->FindOrBuildMaterial("G4_CONCRETE");
  G4LogicalVolume *logicWorld_box = new G4LogicalVolume(box, concrete, "CONCRETE");
  G4VisAttributes *vis_concrete = new G4VisAttributes(G4Color(0.2, 0.2, 0.2));
  logicWorld_box->SetVisAttributes(vis_concrete);

  // Graphite parallelepiped
  G4Para *para = new G4Para("Parallelepiped", box_len, box_len, box_len, M_PI / 4, 0, 0);
  G4Material *graphite = nist->FindOrBuildMaterial("G4_GRAPHITE");
  G4LogicalVolume *logicWorld_para = new G4LogicalVolume(para, graphite, "GRAPHITE");
  G4VisAttributes *vis_graphite = new G4VisAttributes(G4Color(0.4, 0.4, 0.4));
  logicWorld_para->SetVisAttributes(vis_graphite);

  // Air world
  G4Box *box_world = new G4Box("World", 100 * cm, 100 * cm, 100 * cm);
  G4Material *air = nist->FindOrBuildMaterial("G4_AIR");
  G4LogicalVolume *logicWorld_mother = new G4LogicalVolume(box_world, air, "World");

  // Create world
  G4VPhysicalVolume *physWorld =
      new G4PVPlacement(0,
                        G4ThreeVector(),
                        logicWorld_mother,
                        "World",
                        0,
                        false,
                        0,
                        true);

  new G4PVPlacement(0,
                    G4ThreeVector(),
                    logicWorld_para,
                    "Para",
                    logicWorld_mother,
                    false,
                    0,
                    true);

  new G4PVPlacement(0,
                    G4ThreeVector(box_len, 2 * box_len, 0), // Box located at parallelepiped surface
                    logicWorld_box,
                    "Box",
                    logicWorld_mother,
                    false,
                    0,
                    true);

  return physWorld;
}