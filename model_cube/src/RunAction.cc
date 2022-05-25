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

#include "G4AnalysisManager.hh"
#include "g4csv_defs.hh"

#include <sstream>

RunAction::RunAction() : G4UserRunAction(), fEdep(0.), fEdep2(0.)
{
  auto analysis = G4AnalysisManager::Instance();
  analysis->SetDefaultFileType("csv");

    analysis->SetFirstNtupleId(0);
    analysis->SetFirstNtupleColumnId(0);
    analysis->CreateNtuple("ParticleData", "Position");
    analysis->CreateNtupleSColumn(0, "particle_name");
    analysis->CreateNtupleSColumn(0, "creator_process");
    analysis->CreateNtupleIColumn(0, "parentID");
    analysis->CreateNtupleDColumn(0, "energy");
    analysis->CreateNtupleDColumn(0, "z");
    analysis->CreateNtupleDColumn(0, "dE");
    analysis->FinishNtuple(0);

/*   analysis->CreateNtuple("All particles", "Data");
  analysis->CreateNtupleSColumn(0, "name");
  analysis->CreateNtupleDColumn(0, "x");
  analysis->CreateNtupleDColumn(0, "y");
  analysis->CreateNtupleDColumn(0, "z");
  analysis->CreateNtupleDColumn(0, "vx");
  analysis->CreateNtupleDColumn(0, "vy");
  analysis->CreateNtupleDColumn(0, "vz");
  analysis->CreateNtupleDColumn(0, "E");
  analysis->FinishNtuple(0); */
}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run *run)
{
  auto analysis = G4AnalysisManager::Instance();
  std::stringstream ss;
  ss << "Run" << run->GetRunID();
  analysis->OpenFile(ss.str());
}

void RunAction::EndOfRunAction(const G4Run *run)
{
  auto analysis = G4AnalysisManager::Instance();
  std::stringstream ss;
  ss << "Run end" << run->GetRunID();
  analysis->Write();
  analysis->CloseFile();
}

void RunAction::AddEdep(G4double edep)
{
  std::stringstream ss;
  ss << "Run end" << edep;
}
