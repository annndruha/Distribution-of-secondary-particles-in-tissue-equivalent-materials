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

constexpr G4double world_size_x = 200 * CLHEP::cm;
constexpr G4double world_size_y = 200 * CLHEP::cm;
constexpr G4double world_size_z = 200 * CLHEP::cm;

// == == == == == == == == == == == == == == == == == == == == == == ==
// Конфигруации тормозной мишени.
// Примечание: здесь и далее указываются ПОЛНЫЕ размеры объектов.
//
G4Material* target_material =
    G4NistManager::Instance()->FindOrBuildMaterial("G4_W");

constexpr G4double target_size_x = 10.0 * CLHEP::cm;
constexpr G4double target_size_y = 10.0 * CLHEP::cm;
constexpr G4double target_size_z = 10.0 * CLHEP::cm;


// == == == == == == == == == == == == == == == ==
// Позиция мишени
constexpr G4double target_position_x = 0.0;
constexpr G4double target_position_y = 0.0;
constexpr G4double target_position_z = world_size_x / 2.0 - target_size_x / 2.0;

#endif
