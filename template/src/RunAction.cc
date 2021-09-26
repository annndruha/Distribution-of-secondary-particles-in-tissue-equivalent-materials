#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "g4csv.hh"

#include <sstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
: G4UserRunAction(),
  fEdep(0.),
  fEdep2(0.)
{
  auto analysis = G4AnalysisManager::Instance();
  analysis->SetFirstNtupleId(0);
  analysis->SetFirstNtupleColumnId(0);

  analysis->CreateNtuple("DoseDist", "DD");
  analysis->CreateNtupleDColumn(0, "eDep");
  analysis->CreateNtupleDColumn(0, "X");
  analysis->CreateNtupleDColumn(0, "Y");
  analysis->CreateNtupleDColumn(0, "Z");
  analysis->FinishNtuple(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* run)
{
  auto analysis = G4AnalysisManager::Instance();
  std::stringstream ss;
  ss << "Run" << run->GetRunID();
  analysis->OpenFile(ss.str());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
 auto analysis = G4AnalysisManager::Instance();
 analysis->Write();
 analysis->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::AddEdep(G4double edep)
{
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
