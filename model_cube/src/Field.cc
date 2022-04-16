#include "G4SystemOfUnits.hh"
#include "Field.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ExN04Field::ExN04Field()
 : G4MagneticField()
{
  fBz = 0.001*tesla;
  frmax_sq = sqr(1000.*cm);
  fzmax = 20.*cm;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ExN04Field::~ExN04Field()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ExN04Field::GetFieldValue(const double Point[3],double *Bfield) const
{
  Bfield[0] = 0.;
  Bfield[1] = fBz;
  Bfield[2] = 0.;
  
/*   if (std::abs(Point[1]) < fzmax && (sqr(Point[0])+sqr(Point[2])) < frmax_sq ) {
    Bfield[1] = fBz;
  } else {
    Bfield[1] = 0.;
  } */
}


// Paste into DetectorConstruction.cc
/* 
  ExN04Field* myField = new ExN04Field;
  G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager()-> GetFieldManager();
  fieldMgr-> SetDetectorField(myField);
  fieldMgr-> CreateChordFinder(myField);
  auto field = new ExN04Field;
  auto manager = new G4FieldManager(field);
  logicWorld -> SetFieldManager(manager, true);
*/