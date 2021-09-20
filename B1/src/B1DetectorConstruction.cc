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
#include <math.h>


B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }


B1DetectorConstruction::~B1DetectorConstruction()
{ }


G4VPhysicalVolume* B1DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();

  // Concrete cube
  G4double Box_len = 20*cm;
  G4Box* box = new G4Box("Box", Box_len, Box_len, Box_len);
  G4Material* concrete = nist->FindOrBuildMaterial("G4_CONCRETE");
  G4LogicalVolume* logicWorld_box = new G4LogicalVolume(box, concrete, "CONCRETE");


  // Graphite parallelepiped
  G4double Para_len = 20*cm;
  G4double pAlpha = M_PI/4;
  G4double pTheta = 0;
  G4double pPhi = 0;
  G4Para* para = new G4Para("Parallelepiped", Para_len, Para_len, Para_len, pAlpha, pTheta, pPhi);
  G4Material* graphite = nist->FindOrBuildMaterial("G4_GRAPHITE");
  G4LogicalVolume* logicWorld_para = new G4LogicalVolume(para, graphite, "GRAPHITE");

  // Air world
  G4double World_len = 100*cm;
  G4Box* box_world = new G4Box("World", World_len, World_len, World_len);
  G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
  G4LogicalVolume* logicWorld_mother = new G4LogicalVolume(box_world, air, "World");


  G4VPhysicalVolume* physWorld = 
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
                    G4ThreeVector(Box_len, 2*Box_len, 0), // Box located at parallelepiped surface
                    logicWorld_box,
                    "Box",
                    logicWorld_mother,
                    false,
                    0,
                    true);

  return physWorld;                    
}