#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "G4AnalysisManager.hh"
#include "g4csv_defs.hh"

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
  if (volume->GetName() != "Box")
    return;

  if (not step->IsFirstStepInVolume()){
    return;
  }

  auto track = step->GetTrack();
  auto particle = track->GetDynamicParticle();
  auto energy = particle->GetKineticEnergy();
  auto particle_name = particle->GetDefinition()->GetParticleName();

  auto pos = step->GetPreStepPoint()->GetPosition();
  auto vel = step->GetPreStepPoint()->GetMomentum();



  auto analysis = G4AnalysisManager::Instance();
  analysis->FillNtupleSColumn(0, 0, particle_name);

  if (track->GetCreatorProcess() == NULL){
    analysis->FillNtupleSColumn(0, 1, "user");
  }
  else {
    analysis->FillNtupleSColumn(0, 1, track->GetCreatorProcess()->GetProcessName());
  }
  analysis->FillNtupleIColumn(0, 2, track->GetParentID());
  analysis->FillNtupleDColumn(0, 3, energy / CLHEP::MeV);

  // analysis->FillNtupleDColumn(0, 4, step->GetTotalEnergyDeposit());

/*   analysis->FillNtupleDColumn(0, 4, pos.getX() / CLHEP::mm);
  analysis->FillNtupleDColumn(0, 5, pos.getY() / CLHEP::mm);
  analysis->FillNtupleDColumn(0, 6, pos.getZ() / CLHEP::mm);
  analysis->FillNtupleDColumn(0, 7, vel.getX() / CLHEP::mm);
  analysis->FillNtupleDColumn(0, 8, vel.getY() / CLHEP::mm);
  analysis->FillNtupleDColumn(0, 9, vel.getZ() / CLHEP::mm); */
  analysis->AddNtupleRow(0);
}
