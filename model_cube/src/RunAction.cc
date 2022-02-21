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

RunAction::RunAction()
: G4UserRunAction(),
  fEdep(0.),
  fEdep2(0.)
{
  auto analysis = G4AnalysisManager::Instance();
  analysis->SetFirstNtupleId(0);
  analysis->SetFirstNtupleColumnId(0);

  analysis->CreateNtuple("ParticleData", "Position");
  //analysis->CreateNtupleDColumn(0, "eDep");
  analysis->CreateNtupleSColumn(0, "particle_name");
  analysis->CreateNtupleDColumn(0, "X");
  analysis->CreateNtupleDColumn(0, "Y");
  analysis->CreateNtupleDColumn(0, "Z");
  analysis->CreateNtupleDColumn(0, "vX");
  analysis->CreateNtupleDColumn(0, "vY");
  analysis->CreateNtupleDColumn(0, "vZ");
  analysis->CreateNtupleDColumn(0, "energy");
  analysis->FinishNtuple(0);


  //analysis->CreateNtuple("DoseData", "DD");
  //analysis->CreateNtupleSColumn(1, "particle_name");
  //analysis->CreateNtupleDColumn(1, "energy");
  //analysis->FinishNtuple(1);
}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run* run)
{
  auto analysis = G4AnalysisManager::Instance();
  std::stringstream ss;
  ss << "Run" << run->GetRunID();
  analysis->OpenFile(ss.str());
}

void RunAction::EndOfRunAction(const G4Run* run)
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
