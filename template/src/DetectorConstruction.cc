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
#include "Z6MakeLeaf.hh"
#include "Z6FixedCollimatorSolid.hh"
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

void ConstructTarget(G4LogicalVolume* _mother_volume){
  auto solid = new G4Tubs(
    "Target",
    0,
    target_r,
    target_size_z / 2.0,
    0,
    CLHEP::twopi);

  G4LogicalVolume* logic = new G4LogicalVolume(solid, target_material, "Target");

  new G4PVPlacement(
    0,
    G4ThreeVector(target_position_x,
                  target_position_y,
                  target_position_z),
    logic,
    "Target",
    _mother_volume,
    false,
    0,
    false);
}

void ConstructFixedPrimaryCollimator(G4LogicalVolume* _mother_volume){
  G4double Rmin1 = fixed_primary_collimator_r_max;
  G4double Rmax1 = Rmin1 + fixed_collimators_thickness;
  G4double Rmin2 = fixed_primary_collimator_r_min;
  G4double Rmax2 = Rmin2 + fixed_collimators_thickness;

  auto solid = new G4Cons(
    "FixedPrime",
    Rmin1,
    Rmax1,
    Rmin2,
    Rmax2,
    fixed_primary_collimator_size_z / 2.0,
    0,
    CLHEP::twopi);

  G4LogicalVolume* logic = new G4LogicalVolume(
    solid,
    fixed_primary_collimator_material,
    "FixedPrime");

  new G4PVPlacement(
    0,
    G4ThreeVector(fixed_primary_collimator_position_x,
                  fixed_primary_collimator_position_y,
                  fixed_primary_collimator_position_z),
    logic,
    "FixedPrime",
    _mother_volume,
    false,
    0,
    false);
}

void ConstructFixedSecondaryCollimator(G4LogicalVolume* _mother_volume){
  return;

  G4double Rmin1 = fixed_secondary_collimator_r_max;
  G4double Rmax1 = Rmin1 + fixed_collimators_thickness;
  G4double Rmin2 = fixed_secondary_collimator_r_min;
  G4double Rmax2 = Rmin2 + fixed_collimators_thickness;

  auto solid = new G4Cons(
    "FixedSecond",
    Rmin1,
    Rmax1,
    Rmin2,
    Rmax2,
    fixed_secondary_collimator_size_z / 2.0,
    0,
    CLHEP::twopi);

  G4LogicalVolume* logic = new G4LogicalVolume(
    solid,
    fixed_secondary_collimator_material,
    "FixedSecond");

  new G4PVPlacement(
    0,
    G4ThreeVector(fixed_secondary_collimator_position_x,
                  fixed_secondary_collimator_position_y,
                  fixed_secondary_collimator_position_z),
    logic,
    "FixedSecond",
    _mother_volume,
    false,
    0,
    false);
}

void ConstructMLC(G4LogicalVolume* _mother_volume){
  G4int Q = 1; // Размер поля будет равен QxQ cm

  G4ThreeVector tstep(leaf_size_x, 0, 0);
  G4ThreeVector copy_shift(0, leaf_size_y / 2.0 + (Q * 5) * CLHEP::mm, 0.0);

  // Строим первый слой
  G4ThreeVector proximal_layer_start_translation(
    - 0.5 * leaf_size_x * proximal_layer_leafs_number,
    0,
    fixed_primary_collimator_position_z
    - (fixed_primary_collimator_size_z / 2.0 + leaf_size_z / 2.0));

  G4ThreeVector translation = proximal_layer_start_translation;
  for(int i = 0; i < proximal_layer_leafs_number; ++i, translation += tstep){
    if(i == (proximal_layer_leafs_number - Q) / 2){
      for(int j = 0; j < Q; ++j, ++i, translation += tstep){
        MakeLeaf(translation + copy_shift, _mother_volume);
        MakeLeaf(translation - copy_shift, _mother_volume);
      }
      translation -= tstep;
    }
    else{
      MakeLeaf(translation, _mother_volume);
      MakeLeaf(translation, _mother_volume);
    }
  }

  // Строим второй слой
  G4ThreeVector distal_layer_start_translation(
    - 0.5 * leaf_size_x * distal_layer_leafs_number,
    0,
    fixed_primary_collimator_position_z
    - (fixed_primary_collimator_size_z / 2.0 + leaf_size_z / 2.0)
    - leaf_size_z);

  translation = distal_layer_start_translation;
  copy_shift.setY(leaf_size_y / 2.0 + (Q * 5)* CLHEP::mm);
  for(int i = 0; i < distal_layer_leafs_number; ++i, translation += tstep){
    if(i == (distal_layer_leafs_number - Q) / 2){
      for(int j = 0; j < Q; ++j, ++i, translation += tstep){
        MakeLeaf(translation + copy_shift, _mother_volume);
        MakeLeaf(translation - copy_shift, _mother_volume);
      }
      translation -= tstep;
    }
    else{
      MakeLeaf(translation, _mother_volume);
      MakeLeaf(translation, _mother_volume);
    }
  }
}

void ConstructPhantom(G4LogicalVolume* _mother_volume){
  auto solid = new G4Box(
    "Phantom",
    phantom_size_x,
    phantom_size_y,
    phantom_size_z);

  G4LogicalVolume* logic = new G4LogicalVolume(solid, phantom_material, "Phantom");

  new G4PVPlacement(
    0,
    G4ThreeVector(phantom_position_x,
                  phantom_position_y,
                  phantom_position_z),
    logic,
    "Phantom",
    _mother_volume,
    false,
    0,
    false);
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();

  auto w = nist->FindOrBuildMaterial("G4_W");
  auto cu = nist->FindOrBuildMaterial("G4_Cu");
  auto air = nist->FindOrBuildMaterial("G4_AIR");
  auto water = nist->FindOrBuildMaterial("G4_WATER");

  G4Box* solidWorld =
    new G4Box("World",
       0.5 * world_size_x, 0.5 * world_size_y, 0.5 * world_size_z);

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,   // its solid
                        world_material,          // its material
                        "World");     // its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      false);                //overlaps checking

  ConstructTarget(logicWorld);
  // auto w_target = Z6CreateBTarget("W",
  //                                 target_size_x,
  //                                 target_size_y,
  //                                 target_size_z,
  //                                 target_material,
  //                                 G4ThreeVector(target_position_x,
  //                                               target_position_y,
  //                                               target_position_z),
  //                                 logicWorld);

  ConstructFixedPrimaryCollimator(logicWorld);
  ConstructFixedSecondaryCollimator(logicWorld);
  ConstructMLC(logicWorld);
  ConstructPhantom(logicWorld);

  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
