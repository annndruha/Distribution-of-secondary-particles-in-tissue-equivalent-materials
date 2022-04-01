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
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1RunAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "G4FTFPNeutronBuilder.hh"
#include "G4HETCNeutron.hh"
#include "G4Neutron.hh"

#include "analysis.hh"

#include "globals.hh"

G4double E_tot = 0;
G4double Et = 0;
G4double E_n = 0;
G4int nn=0;
G4double brems[200] = {0};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction, B1RunAction *runAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fRunAction(runAction),
  fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) {
    const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

    fScoringVolume = detectorConstruction->GetScoringVolume();
  }

  // get volume of the current step
  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

  auto volname = volume->GetName();

  // check if we are in scoring volume
  if (volname != "phantoml")
  {
       return;
  }

  auto track = step->GetTrack();
  auto particle = track->GetDynamicParticle()->GetParticleDefinition();
  auto pname = particle->GetParticleName();

  auto dE  = step->GetTotalEnergyDeposit();
  auto E = track->GetKineticEnergy();
  auto pos = step->GetPreStepPoint()->GetPosition();

  if (pname != "gamma")
  {
       return;
  }



  // G4cout << pname << G4endl;

  E_tot += dE;
  Et += E;
  nn++;

  track->SetTrackStatus(fStopAndKill);



  auto analysis = G4AnalysisManager::Instance();

  analysis->FillNtupleDColumn(0, 0, dE / CLHEP:: joule);
  analysis->FillNtupleDColumn(0, 1, pos.getX() / CLHEP::cm);
  analysis->FillNtupleDColumn(0, 2, pos.getY() / CLHEP::cm);
  analysis->FillNtupleDColumn(0, 3, pos.getZ() / CLHEP::cm);
  analysis->FillNtupleDColumn(0, 4, E / CLHEP::MeV);
  analysis->AddNtupleRow(0);
/*
  if(pname == "neutron"){
    //G4cout << "dE = "<< dE << G4endl;
    //G4cout << "E = "<< E << G4endl;
    E_n+=dE;
    analysis->FillNtupleDColumn(1, 0, dE / CLHEP::joule);
    analysis->FillNtupleDColumn(1, 1, pos.getX() / CLHEP::cm);
    analysis->FillNtupleDColumn(1, 2, pos.getY() / CLHEP::cm);
    analysis->FillNtupleDColumn(1, 3, pos.getZ() / CLHEP::cm);
    analysis->FillNtupleDColumn(1, 4, E / CLHEP::MeV);
    analysis->AddNtupleRow(1);
  }*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
