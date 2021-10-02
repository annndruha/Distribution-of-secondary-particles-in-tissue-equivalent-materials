#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "g4csv.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) {
    const DetectorConstruction* detectorConstruction
      = static_cast<const DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();
  }

  // get volume of the current step
  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

  // check if we are in scoring volume
  // G4cout << volume->GetName() << G4endl;
  if (volume->GetName() != "Phantom") return;

  auto edep = step->GetTotalEnergyDeposit();

  if(edep == 0) return;

  // G4cout << step->GetTrack()->GetDynamicParticle() << '\t'
  //        << "Is first: " << step->IsFirstStepInVolume() << '\t'
  //        <<

  auto pos = step->GetPreStepPoint()->GetPosition();

  auto analysis = G4AnalysisManager::Instance();
  analysis->FillNtupleDColumn(0, 0, edep);
  analysis->FillNtupleDColumn(0, 1, pos.getX() / CLHEP::mm);
  analysis->FillNtupleDColumn(0, 2, pos.getY() / CLHEP::mm);
  analysis->FillNtupleDColumn(0, 3, pos.getZ() / CLHEP::mm);
  analysis->AddNtupleRow(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
