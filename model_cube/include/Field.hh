#ifndef ExN04Field_H
#define ExN04Field_H 1

#include "G4MagneticField.hh"
#include "globals.hh"

class ExN04Field : public G4MagneticField
{
public:
  ExN04Field();
  ~ExN04Field();

  virtual void GetFieldValue(const double Point[3], double *Bfield) const;

private:
  G4double fBz;
  G4double frmax_sq;
  G4double fzmax;
};

#endif