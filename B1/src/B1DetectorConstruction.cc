/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4Box.hh"
#include "G4Para.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
    : G4VUserDetectorConstruction(),
      fScoringVolume(0)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume *B1DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager *nist = G4NistManager::Instance();

  // Envelope parameters
  //
  G4double env_sizeXY = 150 * cm, env_sizeZ = 150 * cm;
  G4Material *env_mat = nist->FindOrBuildMaterial("G4_AIR");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXY = 1.2 * env_sizeXY;
  G4double world_sizeZ = 1.2 * env_sizeZ;
  G4Material *world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box *solidWorld =
      new G4Box("World",                                                    //its name
                0.5 * world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ); //its size

  G4LogicalVolume *logicWorld =
      new G4LogicalVolume(solidWorld, //its solid
                          world_mat,  //its material
                          "World");   //its name

  G4VPhysicalVolume *physWorld =
      new G4PVPlacement(0,               //no rotation
                        G4ThreeVector(), //at (0,0,0)
                        logicWorld,      //its logical volume
                        "World",         //its name
                        0,               //its mother  volume
                        false,           //no boolean operation
                        0,               //copy number
                        checkOverlaps);  //overlaps checking

  //
  // Envelope
  //
  G4Box *solidEnv =
      new G4Box("Envelope",                         //its name
                env_sizeXY, env_sizeXY, env_sizeZ); //its size

  G4LogicalVolume *logicEnv =
      new G4LogicalVolume(solidEnv,    //its solid
                          env_mat,     //its material
                          "Envelope"); //its name

  new G4PVPlacement(0,               //no rotation
                    G4ThreeVector(), //at (0,0,0)
                    logicEnv,        //its logical volume
                    "Envelope",      //its name
                    logicWorld,      //its mother  volume
                    false,           //no boolean operation
                    0,               //copy number
                    checkOverlaps);  //overlaps checking
  //==============================================================================
  //
  // Concrete cube
  //
  G4double box_len = 5 * cm;
  G4double offset = 10 * cm;

  G4ThreeVector pos1 = G4ThreeVector(offset, offset, offset);
  G4Box *box = new G4Box("Box", box_len, box_len, box_len);
  G4Material *concrete = nist->FindOrBuildMaterial("G4_CONCRETE");
  G4LogicalVolume *logicWorld_box = new G4LogicalVolume(box, concrete, "Box");
  new G4PVPlacement(0,
                    pos1, // Box located at parallelepiped surface G4ThreeVector(box_len, 2 * box_len, 0)
                    logicWorld_box,
                    "Box",
                    logicEnv,
                    false,
                    0,
                    true);

  //
  // Graphite parallelepiped
  //
  G4ThreeVector pos2 = G4ThreeVector(offset + box_len, offset + 2 * box_len, offset);
  G4Para *para = new G4Para("Parallelepiped", box_len, box_len, box_len, M_PI / 4, 0, 0);
  G4Material *graphite = nist->FindOrBuildMaterial("G4_GRAPHITE");
  G4LogicalVolume *logicWorld_para = new G4LogicalVolume(para, graphite, "Parallelepiped");
  new G4PVPlacement(0,
                    pos2,
                    logicWorld_para,
                    "Para",
                    logicEnv,
                    false,
                    0,
                    true);

  //==============================================================================
  return physWorld;
}