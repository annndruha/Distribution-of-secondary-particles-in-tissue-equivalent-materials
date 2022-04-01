#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4ThreeVector.hh"
#include "G4PhysicalConstants.hh"
#include "iostream"

#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4ProductionCuts.hh"

class G4VPhysicalVolume;

class G4LogicalVolume;

class B1DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    B1DetectorConstruction();

    virtual ~B1DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  protected:
    G4LogicalVolume*  fScoringVolume;

    private:
    G4Material * otherMaterials(const G4String materialName);
    void SetJawAperture(G4int idJaw, G4ThreeVector &centre, G4ThreeVector halfSize, G4RotationMatrix *cRotation);
};

#endif
