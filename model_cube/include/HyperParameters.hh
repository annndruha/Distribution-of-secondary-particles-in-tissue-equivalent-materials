#ifndef __HYPERPARAMETERS_HH__
#define __HYPERPARAMETERS_HH__

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"

// == == == == == == == == == == == == == == == == == == == == == == ==
// Конфигурация мира.
//
constexpr G4double world_dx = 21 * CLHEP::cm;
constexpr G4double world_dy = 21 * CLHEP::cm;
constexpr G4double world_dz = 0.4 * CLHEP::m;

G4Material *world_material =
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

// == == == == == == == == == == == == == == == ==
// Параметры облучаемого объекта
//
constexpr G4double box_len = 20 * CLHEP::cm;


// == == == == == == == == == == == == == == == ==
// Для создания своего материала
//
/* G4Element* H = G4NistManager::Instance()-->FindOrBuildElement(1);
G4Element* C = G4NistManager::Instance()-->FindOrBuildElement(6);
G4Element* O = G4NistManager::Instance()-->FindOrBuildElement(8);
G4Element* N = G4NistManager::Instance()-->FindOrBuildElement(7);
G4Element* K = G4NistManager::Instance()-->FindOrBuildElement(19);
G4Element* P = G4NistManager::Instance()-->FindOrBuildElement(15);
G4Element* S = G4NistManager::Instance()-->FindOrBuildElement(16);
G4Element* Mg = G4NistManager::Instance()-->FindOrBuildElement(12);
G4Element* Ca = G4NistManager::Instance()-->FindOrBuildElement(20);
G4Element* Zn = G4NistManager::Instance()-->FindOrBuildElement(30);
G4Element* Na = G4NistManager::Instance()-->FindOrBuildElement(11);
G4Element* Cl = G4NistManager::Instance()-->FindOrBuildElement(17);
G4Element* Fe = G4NistManager::Instance()-->FindOrBuildElement(26);
G4Element* Si = G4NistManager::Instance()-->FindOrBuildElement(14);
G4Element* Cr = G4NistManager::Instance()-->FindOrBuildElement(24);
G4Element* Ti = G4NistManager::Instance()-->FindOrBuildElement(22);
G4Element* Mn = G4NistManager::Instance()-->FindOrBuildElement(25);
G4Element* Ni = G4NistManager::Instance()-->FindOrBuildElement(28);
G4Element* Cu = G4NistManager::Instance()-->FindOrBuildElement(29);
G4Element* Pb = G4NistManager::Instance()-->FindOrBuildElement(82);
G4Element* Al = G4NistManager::Instance()-->FindOrBuildElement(13);

G4Material* termoplast = new G4Material("D16AT", 2.77 * g / cm3, 9);
termoplast->AddElement(Fe, 0.50 * perCent);
termoplast->AddElement(Si, 0.50 * perCent);
termoplast->AddElement(Mn, 0.90 * perCent);
termoplast->AddElement(Cr, 0.10 * perCent);
termoplast->AddElement(Ti, 0.15 * perCent);
termoplast->AddElement(Al, 90.90 * perCent);
termoplast->AddElement(Cu, 4.90 * perCent);
termoplast->AddElement(Mg, 1.80 * perCent);
termoplast->AddElement(Zn, 0.25 * perCent); */
#endif
