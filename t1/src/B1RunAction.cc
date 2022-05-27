                                                                                      //
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1RunAction.cc
/// \brief Implementation of the B1RunAction class

#include "B1RunAction.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "analysis.hh"
#include "G4Neutron.hh"

#include "globals.hh"

#include <iostream>
#include <fstream>
#include <sstream>

extern G4double E_tot;
extern G4double E_n;
extern G4double Et;
extern G4int nn;
extern G4double brems[200];

std::stringstream ss;
std::string fileName;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



B1RunAction::B1RunAction()
: G4UserRunAction(),
  fEdep(0.),
  fEdep2(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::~B1RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::BeginOfRunAction(const G4Run*)
{
  auto analysis = G4AnalysisManager::Instance();

  analysis->OpenFile("results.csv");

  analysis->SetFirstNtupleId(0);
  analysis->SetFirstNtupleColumnId(0);

  analysis->CreateNtuple("All particles", "Data");
  analysis->CreateNtupleSColumn(0, "name");
/*   analysis->CreateNtupleDColumn(0,  "x");
  analysis->CreateNtupleDColumn(0,  "y");
  analysis->CreateNtupleDColumn(0,  "z");
  analysis->CreateNtupleDColumn(0,  "vx");
  analysis->CreateNtupleDColumn(0,  "vy");
  analysis->CreateNtupleDColumn(0,  "vz"); */
  analysis->CreateNtupleDColumn(0,  "E");
  analysis->FinishNtuple(0);
/*
  analysis->CreateNtuple("NEUTRONS", "Depth-dose distribution");
  analysis->CreateNtupleDColumn(1, "dE");
  analysis->CreateNtupleDColumn(1,  "x");
  analysis->CreateNtupleDColumn(1,  "y");
  analysis->CreateNtupleDColumn(1,  "z");
  analysis->CreateNtupleDColumn(1,  "E");
  analysis->FinishNtuple(1);
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::EndOfRunAction(const G4Run* run)
{
  auto analysis = G4AnalysisManager::Instance();
  analysis->Write();
  analysis->CloseFile();
  /*G4cout << "End of processes" << G4endl;
  G4cout << "Total E dep = " << E_tot << G4endl;
  G4cout << "Neutron E dep = " << E_n << G4endl;*/
  //G4cout << "Number of neutrons = " << nn << " with total energy Et = " << Et << G4endl;
  /*for (int u = 0; u < 200; u++)
    G4cout << u*100 << " , " << brems[u] <<  G4endl;*/
  ss.str(std::string());
  ss << "Neutrons.txt";
  fileName = ss.str();
  std::ofstream FileEn(fileName.c_str(), std::ios::app);
  //FileEn << "########## "<< "Number of Neutrones " << aRun->GetNumberOfEventToBeProcessed() << " with energy "<< Energy << "  MeV" << G4endl;
 // FileEn << "########## "<< "Electrons " << aRun->GetNumberOfEventToBeProcessed() << " with Energy= " << Energy << "MeV" << G4endl;

  FileEn << "Test3" << G4endl;
  G4int u;
  for (u = 1; u < 200; u++)
  {
  FileEn << u*0.05 << " , " << brems[u] <<  G4endl;
  }
  FileEn << "  " << G4endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::AddEdep(G4double edep)
{}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::AddBrems(G4double E)
{

}
