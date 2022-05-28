#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "G4AnalysisManager.hh"
#include "g4csv_defs.hh"

SteppingAction::SteppingAction(EventAction *eventAction) : G4UserSteppingAction(), fEventAction(eventAction), fScoringVolume(0)
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step *step)
{
    G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    auto track = step->GetTrack();
    if (volume->GetName() != "Box")
      return;

    if (not step->IsFirstStepInVolume())
      return;

    if (not track->GetCreatorProcess() == NULL)
      return;

    
    auto particle = track->GetDynamicParticle();
    auto energy = particle->GetKineticEnergy();
    auto particle_name = particle->GetDefinition()->GetParticleName();
    auto dE  = step->GetTotalEnergyDeposit();
    auto pos = step->GetPreStepPoint()->GetPosition();


/*     auto analysis = G4AnalysisManager::Instance();
    analysis->FillNtupleSColumn(0, 0, particle_name);
    if (track->GetCreatorProcess() == NULL)
    {
      analysis->FillNtupleSColumn(0, 1, "user");
    }
    else
    {
      analysis->FillNtupleSColumn(0, 1, track->GetCreatorProcess()->GetProcessName());
    }

    analysis->FillNtupleDColumn(0, 2, energy / CLHEP::MeV);
    analysis->FillNtupleDColumn(0, 3, pos.getZ() / CLHEP::cm);
    analysis->FillNtupleDColumn(0, 4, dE / CLHEP::MeV);
    analysis->AddNtupleRow(0); */
    auto analysis = G4AnalysisManager::Instance();
    analysis->FillNtupleSColumn(0, 0, particle_name);
  /*   analysis->FillNtupleDColumn(0, 1, pos.getX() / CLHEP::cm);
    analysis->FillNtupleDColumn(0, 2, pos.getY() / CLHEP::cm);
    analysis->FillNtupleDColumn(0, 3, pos.getZ() / CLHEP::cm); */
  /*   analysis->FillNtupleDColumn(0, 4, vel.getX());
    analysis->FillNtupleDColumn(0, 5, vel.getY());
    analysis->FillNtupleDColumn(0, 6, vel.getZ()); */
    analysis->FillNtupleDColumn(0, 1, energy / CLHEP::MeV);
    analysis->AddNtupleRow(0);


  /*   analysis->FillNtupleSColumn(0, 0, particle_name);
    analysis->FillNtupleDColumn(0, 1, pos.getX() / CLHEP::cm);
    analysis->FillNtupleDColumn(0, 2, pos.getY() / CLHEP::cm);
    analysis->FillNtupleDColumn(0, 3, pos.getZ() / CLHEP::cm);
    analysis->FillNtupleDColumn(0, 4, vel.getX());
    analysis->FillNtupleDColumn(0, 5, vel.getY());
    analysis->FillNtupleDColumn(0, 6, vel.getZ());
    analysis->FillNtupleDColumn(0, 7, energy / CLHEP::MeV);
    analysis->AddNtupleRow(0); */


}
