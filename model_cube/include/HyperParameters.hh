#ifndef __HYPERPARAMETERS_HH__
#define __HYPERPARAMETERS_HH__

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"

// == == == == == == == == == == == == == == == == == == == == == == ==
// Конфигурация мира.
//
G4Material* world_material =
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

/*constexpr G4double world_size_x = 20 * CLHEP::cm;
constexpr G4double world_size_y = 20 * CLHEP::cm;
constexpr G4double world_size_z = 20 * CLHEP::cm;*/
constexpr G4double world_radius = 16 * CLHEP::cm;


// == == == == == == == == == == == == == == == ==
// Параметры анода
//
constexpr G4double anode_radius = 3.0*CLHEP::cm;
constexpr G4double anode_angel = M_PI_4;
constexpr G4double anode_len = 9.0*CLHEP::cm;

G4Material* anode_material =
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");

// == == == == == == == == == == == == == == == ==
// Параметры сферы детектора
//
G4Material* target_material =
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

#endif
