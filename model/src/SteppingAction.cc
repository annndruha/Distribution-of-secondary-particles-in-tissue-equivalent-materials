#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "g4csv.hh"

SteppingAction::SteppingAction(EventAction *eventAction)
    : G4UserSteppingAction(),
      fEventAction(eventAction),
      fScoringVolume(0)
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step *step)
{
  // get volume of the current step
  G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  // check if we are in scoring volume
  // G4cout << volume->GetName() << G4endl;
  if (volume->GetName() != "Target")
    return;

  auto edep = step->GetTotalEnergyDeposit();
  //if (edep == 0)
  //  return;

  auto track = step->GetTrack();
  auto particle = track->GetDynamicParticle();
  auto energy = particle->GetKineticEnergy();
  auto particle_name = particle->GetDefinition()->GetParticleName();
  auto pos = step->GetPreStepPoint()->GetPosition();

  auto analysis = G4AnalysisManager::Instance();
  analysis->FillNtupleDColumn(0, 0, edep);
  analysis->FillNtupleDColumn(0, 1, pos.getX() / CLHEP::mm);
  analysis->FillNtupleDColumn(0, 2, pos.getY() / CLHEP::mm);
  analysis->FillNtupleDColumn(0, 3, pos.getZ() / CLHEP::mm);
  analysis->AddNtupleRow(0);

  analysis->FillNtupleSColumn(1, 0, particle_name);
  analysis->FillNtupleDColumn(1, 1, energy / CLHEP::MeV);
  analysis->AddNtupleRow(1);
}
