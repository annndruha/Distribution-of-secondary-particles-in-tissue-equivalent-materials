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
/// \file B1PrimaryGeneratorAction.cc
/// \brief Implementation of the B1PrimaryGeneratorAction class

#include "B1PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SingleParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4Neutron.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::B1PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),
  fEnvelopeBox(0)
{
    CircleSource = new G4SingleParticleSource();
    CircleSource->SetParticleDefinition(G4Electron::Definition());

    G4SPSEneDistribution* energy = CircleSource->GetEneDist();
    //energy->SetEnergyDisType("Gauss");
    //energy->SetBeamSigmaInE(0.5 *MeV);
    energy->SetMonoEnergy(23.5 *MeV);

    G4SPSPosDistribution* position = CircleSource->GetPosDist();
    position->SetPosDisType("Plane");
    position->SetPosDisShape("Rectangle");
    position->SetHalfX(0.5*cm);
    position->SetHalfY(0.5*cm);
    position->SetCentreCoords(G4ThreeVector(0*cm,0*cm,-2                                           *cm));

    G4SPSAngDistribution* angular = CircleSource->GetAngDist();
    angular->SetParticleMomentumDirection(G4ThreeVector(0.0,0.0,1.0));

  /*fParticleGun = new G4ParticleGun(1);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
  fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, -2 * cm));*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
{
    delete CircleSource;
    //delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    CircleSource->GeneratePrimaryVertex(anEvent);
    //fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
