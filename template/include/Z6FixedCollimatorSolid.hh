#ifndef __Z6FIXEDCOLLIMATORSOLID_HH__
#define __Z6FIXEDCOLLIMATORSOLID_HH__

#include "HyperParameters.hh"

#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4SubtractionSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

G4VSolid* FixedCollimatorSolid(
  G4double _x_top, // Полная длина большей части вдоль OX
  G4double _z,     // Полная длина вдоль OZ
  G4double _y      // Полная длина вдоль y
){
  G4double  dx1 = _x_top / 2.0;
  G4double  dx2 = dx1 / 2.0;
  G4double  dy1 =  _y / 4.0;
  G4double  dy2 =  _y / 4.0;
  G4double  dz  = _z / 2.0;

  // Основной объём
  G4Trd* trd = new G4Trd("_trd", dx1, dx2, dy1, dy2, dz);

  // Вычитаемый объём
  G4Box* box = new G4Box("_box",
                         _x_top / 4.0 + 1 * mm,
                         world_size_y,
                         world_size_z);

  // TODO Оптимизировать вектор трансляции (вероятно через static)
  return new G4SubtractionSolid(
    "_res",
    trd,
    box,
    nullptr,
    G4ThreeVector(- _x_top / 4.0, 0, 0));
}

#endif
