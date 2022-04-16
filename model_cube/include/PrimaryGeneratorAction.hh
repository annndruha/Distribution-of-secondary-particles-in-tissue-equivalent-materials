#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"

#include <string>
#include "globals.hh"
#include "CSVReader.hh"

class G4Event;
class G4Box;


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event*);

  private:
    G4GeneralParticleSource* fGPS; // If use mac files and general particle source
    G4ParticleGun*  fParticleGun; // If use custom gun
    CSVReader csv_reader = CSVReader("../csv_particle_source/concat_res.csv", 1);
    std::vector<std::vector<std::string>> data;
};

#endif