#ifndef __HYPERPARAMETERS_HH__
#define __HYPERPARAMETERS_HH__

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"

// TODO Вводить переменные внутри namespace.
// TODO G4double-величина "вес" размера объекта для его учёта
//      при расчёте объёма мира.

// == == == == == == == == == == == == == == == == == == == == == == ==
// Конфигруации тормозной мишени.
// Примечание: здесь и далее указываются ПОЛНЫЕ размеры объектов.
//
G4Material* target_material =
    G4NistManager::Instance()->FindOrBuildMaterial("G4_W");

constexpr G4double target_r = 2.0 * CLHEP::cm;
constexpr G4double target_size_x = 2.0 * CLHEP::cm;
constexpr G4double target_size_y = 2.0 * CLHEP::cm;
constexpr G4double target_size_z = 0.1 * CLHEP::cm;

// == == == == == == == == == == == == == == == == == == == == == == ==
// Конфигруации лепестка / ов.
//
G4Material* leaf_material =
    G4NistManager::Instance()->FindOrBuildMaterial("G4_W");

constexpr G4double leaf_length = 23.4 * CLHEP::cm;
constexpr G4double leaf_heigth = 07.7 * CLHEP::cm;
constexpr G4double leaf_width  = 01.0 * CLHEP::cm;

constexpr G4double leaf_size_x = leaf_width;
constexpr G4double leaf_size_y = leaf_length;
constexpr G4double leaf_size_z = leaf_heigth;

constexpr G4int proximal_layer_leafs_number = 29;
constexpr G4int   distal_layer_leafs_number = 28;

// == == == == == == == == == == == == == == == == == == == == == == ==
// Конфигруация 1-го фиксированного коллиматора.
//
G4Material* fixed_primary_collimator_material =
    G4NistManager::Instance()->FindOrBuildMaterial("G4_W");

constexpr G4double fixed_primary_collimator_size_z = 396.0 * CLHEP::mm;

const G4double fixed_collimators_theta = std::atan(
    (distal_layer_leafs_number * leaf_width / 2.0) / fixed_primary_collimator_size_z);

const G4double fixed_collimators_thickness = 1 * CLHEP::cm;

constexpr G4double fixed_primary_collimator_r_min = target_r;

const G4double fixed_primary_collimator_r_max
    = fixed_primary_collimator_size_z * std::tan(fixed_collimators_theta);

// == == == == == == == == == == == == == == == == == == == == == == ==
// Конфигруация ионной камеры (временно отсутствует в геометрии).
// Но расстояние под неё зерезервировано.
//
constexpr G4double ion_chamber_size_x = 0.0 * cm;
constexpr G4double ion_chamber_size_y = 0.0 * cm;
constexpr G4double ion_chamber_size_z = 0.0 * cm;

// == == == == == == == == == == == == == == == == == == == == == == ==
// Конфигруация 2-го фиксированного коллиматора.
//
G4Material* fixed_secondary_collimator_material =
    G4NistManager::Instance()->FindOrBuildMaterial("G4_W");

constexpr G4double fixed_secondary_collimator_size_z = 100. * CLHEP::mm;

const G4double fixed_secondary_collimator_r_min
    = fixed_primary_collimator_r_max;

const G4double fixed_secondary_collimator_r_max
    = 200. * CLHEP::mm * std::tan(fixed_collimators_theta);

// == == == == == == == == == == == == == == == == == == == == == == ==
// Конфигруация фантома.
//
constexpr G4double phantom_size_x = 10.0 * CLHEP::cm;
constexpr G4double phantom_size_y = 10.0 * CLHEP::cm;
constexpr G4double phantom_size_z = 10.0 * CLHEP::cm;

// == == == == == == == == == == == == == == == == == == == == == == ==
// Конфигурация мира.
//
G4Material* world_material =
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

constexpr G4double world_size_x = 200 * CLHEP::cm;
constexpr G4double world_size_y = 200 * CLHEP::cm;
constexpr G4double world_size_z = 200 * CLHEP::cm;
// constexpr G4double world_size_x = 0.5 * (target_size_x
//                                 + fixed_primary_collimator_size_x_top
//                                 + ion_chamber_size_x
//                                 + fixed_secondary_collimator_size_x_top
//                                 + leaf_size_x
//                                 + phantom_size_x);

// constexpr G4double world_size_y = 0.5 * (target_size_y
//                                 + fixed_primary_collimator_size_y
//                                 + ion_chamber_size_y
//                                 + fixed_secondary_collimator_size_y
//                                 + leaf_size_y
//                                 + phantom_size_y);

// constexpr G4double world_size_z = 0.5 * (target_size_y
//                                 + fixed_primary_collimator_size_y
//                                 + ion_chamber_size_y
//                                 + fixed_secondary_collimator_size_y
//                                 + leaf_size_y
//                                 + phantom_size_y);

// == == == == == == == == == == == == == == == == == == == == == == ==
// Позиционирование объектов, исходя из их размеров.
//

// == == == == == == == == == == == == == == == ==
// Позиция мишени
constexpr G4double target_position_x = 0.0;
constexpr G4double target_position_y = 0.0;
constexpr G4double target_position_z = world_size_x / 2.0 - target_size_x / 2.0;

// == == == == == == == == == == == == == == == ==
// Позиция 1-го фиксированного коллиматора
/* constexpr G4double fixed_primary_collimator_position_x
    = target_position_x;

constexpr G4double fixed_primary_collimator_position_y
    = target_position_y;

constexpr G4double fixed_primary_collimator_position_z
    = target_position_z - (target_size_z / 2.0 + fixed_primary_collimator_size_z / 2.0); */

// == == == == == == == == == == == == == == == ==
// Ионизирующей камеры.
/* constexpr G4double ion_chamber_position_x = target_position_x;
constexpr G4double ion_chamber_position_y = target_position_y;

constexpr G4double ion_chamber_position_z =
    fixed_primary_collimator_position_z
    - (fixed_primary_collimator_size_z / 2.0 + ion_chamber_size_z / 2.0); */

// == == == == == == == == == == == == == == == ==
// Позиция 2-го фиксированного коллиматора
/* constexpr G4double fixed_secondary_collimator_position_x
    = fixed_primary_collimator_position_x;

constexpr G4double fixed_secondary_collimator_position_y = target_position_y;

constexpr G4double fixed_secondary_collimator_position_z
    = ion_chamber_position_z
    - (ion_chamber_size_z / 2.0 + fixed_secondary_collimator_size_z / 2.0); */

// TODO
// == == == == == == == == == == == == == == == ==
// Позиция 1-го листка коллиматора.

// == == == == == == == == == == == == == == == ==
// Позиция фантома.

/* G4Material* phantom_material
    = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");

constexpr G4double phantom_position_x = 0;
constexpr G4double phantom_position_y = 0;
constexpr G4double phantom_position_z
    = fixed_primary_collimator_position_z
      - fixed_primary_collimator_size_z / 2.0
      - 2 * leaf_size_z
      - 25 * CLHEP::cm; */

#endif
