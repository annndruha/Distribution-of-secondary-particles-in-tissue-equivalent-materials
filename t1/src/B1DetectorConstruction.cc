
#include "B1DetectorConstruction.hh"

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
#include "G4Sphere.hh"
#include "G4SubtractionSolid.hh"
#include "G4ProductionCuts.hh"
#include "G4Neutron.hh"
#include "G4Sphere.hh"


B1DetectorConstruction::B1DetectorConstruction(): G4VUserDetectorConstruction(),fScoringVolume(0)
{}

B1DetectorConstruction::~B1DetectorConstruction()
{}

void B1DetectorConstruction::SetJawAperture(G4int idJaw, G4ThreeVector &centre, G4ThreeVector halfSize, G4RotationMatrix *cRotation)
{
    G4double theta, x, y, z, dx, dy, dz;
    x=centre.getX();
    y=centre.getY();
    z=centre.getZ();

    dx=halfSize.getX();
    dy=halfSize.getY();
    dz=halfSize.getZ();

    switch (idJaw)
    {
    case 1: //idJaw1XV2100:
        theta = fabs(atan(10* cm/1000*mm));
        centre.set(z*sin(theta)+dx*cos(theta), y, z*cos(theta)-dx*sin(theta));
        cRotation->rotateY(-theta);
        halfSize.set(fabs(dx*cos(theta)+dz*sin(theta)), fabs(dy), fabs(dz*cos(theta)+dx*sin(theta)));
        break;

    case 2: //idJaw2XV2100:
        theta = fabs(atan(-10*cm/1000*mm));
        centre.set(-(z*sin(theta)+dx*cos(theta)), y, z*cos(theta)-dx*sin(theta));
        cRotation->rotateY(theta);
        halfSize.set(fabs(dx*cos(theta)+dz*sin(theta)), fabs(dy), fabs(dz*cos(theta)+dx*sin(theta)));
        break;

    case 3: //idJaw1YV2100:
        theta = fabs(atan(10*cm/1000*mm));
        centre.set(x, z*sin(theta)+dy*cos(theta), z*cos(theta)-dy*sin(theta));
        cRotation->rotateX(theta);
        halfSize.set(fabs(dx), fabs(dy*cos(theta)+dz*sin(theta)), fabs(dz*cos(theta)+dy*sin(theta)));
        break;

    case 4: //idJaw2YV2100:
        theta = fabs(atan(-10*cm/1000*mm));
        centre.set(x, -(z*sin(theta)+dy*cos(theta)), z*cos(theta)-dy*sin(theta));
        cRotation->rotateX(-theta);
        halfSize.set(fabs(dx), fabs(dy*cos(theta)+dz*sin(theta)), fabs(dz*cos(theta)+dy*sin(theta)));
        break;
    }
}

G4Material * B1DetectorConstruction::otherMaterials(const G4String materialName)
{
    G4Material * material=0;
    G4double A, Z, d;
    G4String name;

   // General elements

    A = 12.011*g/mole;
    G4Element* elC = new G4Element("Carbon","C",Z = 6.,A);

    A = 30.974*g/mole;
    G4Element* elP = new G4Element("Phosphorus","P",Z = 15.,A);

    A = 32.064*g/mole;
    G4Element* elS = new G4Element("Sulfur","S",Z = 16.,A);

    A = 55.85*g/mole;
    G4Element* elFe  = new G4Element("Iron","Fe",Z = 26.,A);

    A = 51.9961*g/mole;
    G4Element* elCr = new G4Element("Cromium","Cr", Z = 24.,A);

    A = 54.94*g/mole;
    G4Element* elMn = new G4Element("Manganese","Mn", Z = 25.,A);

    A =  58.69*g/mole;
    G4Element* elNi = new G4Element("Nickel","Ni", Z = 28.,A);

    A = 28.09*g/mole;
    G4Element* elSi = new G4Element("Silicon","Si", Z = 14.,A);

    A = 183.84*g/mole;
    G4Element* elW = new G4Element("Tungsten","W", Z = 74.,A);

    if (materialName=="steel1")
    {
        d = 7.76 *g/cm3;
        G4Material* steel1 = new G4Material("steel1", d,4);
        steel1 -> AddElement(elFe, 0.935);
        steel1 -> AddElement(elS,0.01);
        steel1 -> AddElement(elMn,0.05);
        steel1 -> AddElement(elC,0.005);
        material=steel1;
    }
    else if (materialName=="steel2")
    {
        d = 8.19*g/cm3;
        G4Material* steel2 = new G4Material("steel2", d,5);
        steel2 -> AddElement(elFe, 0.759);
        steel2 -> AddElement(elNi, 0.11);
        steel2 -> AddElement(elSi,0.01);
        steel2 -> AddElement(elCr,0.12);
        steel2 -> AddElement(elP,0.001);
        material=steel2;
    }
    else if (materialName=="steel3")
    {
        d = 8.19*g/cm3;
        G4Material* steel3 = new G4Material("steel3", d,5);
        steel3 -> AddElement(elFe, 0.69);
        steel3 -> AddElement(elNi, 0.1);
        steel3 -> AddElement(elSi,0.01);
        steel3 -> AddElement(elCr,0.18);
        steel3 -> AddElement(elMn,0.02);
        material=steel3;
    }
    else if (materialName=="EZcut")
    {
        d = 7.9*g/cm3;
        G4Material* EZcut20 = new G4Material("EZcut", d,2);
        EZcut20 -> AddElement(elFe, 0.98);
        EZcut20 -> AddElement(elMn,0.02);
        material=EZcut20;
    }
    else if (materialName=="W")
    {
        d = 15*g/cm3;
        G4Material* W = new G4Material("W", d,1);
        W -> AddElement(elW, 1.);
        material=W;
    }
    return material;
}

G4PVPlacement* ConstructXuy(
  char* name,
  G4ThreeVector sizes,
  G4ThreeVector position,
  G4Material* material,
  G4LogicalVolume* mother_volume)
{
  G4Box* solidXyu = new G4Box(name, sizes.getX(), sizes.getY(), sizes.getZ());
  G4LogicalVolume* logicXyu = new G4LogicalVolume(solidXyu, material, name);
  G4PVPlacement* physXyu = new G4PVPlacement(
    0,               // no rotation
    position,        // its position
    logicXyu,        // its logical volume
    name,            // its name
    mother_volume,   // its mother volume
    false,           // no boolean operation
    0);              // copyNo

  return physXyu;
}

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{
  G4double world_sizeX = 1.5 * m;   // полуразмеры мира
  G4double world_sizeY = 1.5 * m;   // полуразмеры мира
  G4double world_sizeZ = 2. * m;   // полуразмеры мира
  //
  G4double phantom_sizeX = 20 * cm; // полуразмеры фантома
  G4double phantom_sizeY = 20 * cm; // полуразмеры фантома
  G4double phantom_sizeZ = 20 * cm; // полуразмеры фантома

  G4NistManager* nist = G4NistManager::Instance();
  //
  G4Material* water = nist->FindOrBuildMaterial("G4_WATER");
  G4Material* air   = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* Cu    = nist->FindOrBuildMaterial("G4_Cu");
  G4Material* W     = nist->FindOrBuildMaterial("G4_W");
  G4Material* Ta     = nist->FindOrBuildMaterial("G4_Ta");
  G4Material* Fe     = nist->FindOrBuildMaterial("G4_Fe");
  G4Material* Pb     = nist->FindOrBuildMaterial("G4_Pb");
  G4Material* VC = nist->FindOrBuildMaterial("G4_Galactic");

  //
  G4Material* world_mat = VC;

  G4Box* solidWorld = new G4Box("World", world_sizeX, world_sizeY, world_sizeZ);
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
  G4VPhysicalVolume* physWorld = new G4PVPlacement(
    0,               // no rotation
    G4ThreeVector(), // its position
    logicWorld,      // its logical volume
    "World",         // its name
    0,               // its mother volume
    false,           // no boolean operation
    0);              // copyNo

 G4bool checkOverlaps = true;

 G4ThreeVector pos1 = G4ThreeVector(0, 0, 2./2.*mm);

 G4Box* targetW =
   new G4Box("targetW",
   20./2*mm, 20./2*mm, 2./2.*mm);

 G4LogicalVolume* targetWL =
   new G4LogicalVolume(targetW,         //its solid
                       W,               //its material
                       "targetW");      //its name

 new G4PVPlacement(0,                       //no rotation
                   pos1,                    //at position
                   targetWL,             //its logical volume
                   "targetW",                //its name
                   logicWorld,                //its mother  volume
                   false,                   //no boolean operation
                   0,                       //copy number
                   checkOverlaps);          //overlaps checking

 //
 // targetCu
 //
 //G4Material* Cu = nist->FindOrBuildMaterial("G4_Cu");
 G4ThreeVector pos2 = G4ThreeVector(0, 0, 4.5*mm);

 G4Box* targetCu =
   new G4Box("targetCu",
   20./2*mm, 20./2*mm, 5./2*mm);

 G4LogicalVolume* targetCuL =
   new G4LogicalVolume(targetCu,         //its solid
                       Cu,          //its material
                       "targetCu");           //its name

 new G4PVPlacement(0,                       //no rotation
                   pos2,                    //at position
                   targetCuL,             //its logical volume
                   "targetCu",                //its name
                   logicWorld,                //its mother  volume
                   false,                   //no boolean operation
                   0,                       //copy number
                   checkOverlaps);          //overlaps checking


//vacuum window
 G4Material* Be = nist->FindOrBuildMaterial("G4_Be");
   G4Tubs* window = new G4Tubs("Window", 0., 50.*mm, 0.12*mm, 0.*deg, 360.*deg);
   G4LogicalVolume* windowl = new G4LogicalVolume (window, Be, "windowl");
   new G4PVPlacement(0, G4ThreeVector(0,0,80*mm), windowl, "windowp", logicWorld, false, 0, checkOverlaps);

//upper part primary collimator
G4ThreeVector posPC = G4ThreeVector(0, 0, 0);
G4Tubs* PCUW = new G4Tubs("PCUW", 10.*mm, 40.*mm, 20.*mm, 0.*deg, 360.*deg);
G4LogicalVolume* PCUWL =
 new G4LogicalVolume(PCUW,         //its solid
                     W,          //its material
                     "PCUW");  // Trapezoid shape


new G4PVPlacement(0,                       //no rotation
                 posPC,                    //at position
                 PCUWL,             //its logical volume
                 "PCUW",                //its name
                 logicWorld,                //its mother  volume
                 false,                   //no boolean operation
                 0,                       //copy number
                 checkOverlaps);


//lower part primary collimator
posPC = G4ThreeVector(0, 0, 50.*mm);
G4Tubs* PCLW = new G4Tubs("PCLW", 0, 40.*mm, 60./2*mm, 0.*deg, 360.*deg);
G4LogicalVolume* PCLWL = new G4LogicalVolume(PCLW,         //its solid
                                       W,          //its material
                                       "PCLW");  // Trapezoid shape


new G4PVPlacement(0,                       //no rotation
                 posPC,                    //at position
                 PCLWL,             //its logical volume
                 "PCLW",                //its name
                 logicWorld,                //its mother  volume
                 false,                   //no boolean operation
                 0,                       //copy number
                 checkOverlaps);

G4Material* Vacuum = nist->FindOrBuildMaterial("G4_Galactic");
G4Cons* InPCLW = new G4Cons ("InPCLW", 0., 10*mm, 0., (76.*std::tan(14.*deg))*mm, 30.*mm,  0.*deg, 360.*deg);
G4LogicalVolume* InPCLWL = new G4LogicalVolume(InPCLW,         //its solid
                                       Vacuum,          //its material
                                       "InPCLW");


 new G4PVPlacement(0,                       //no rotation
                   posPC,                    //at position
                   InPCLWL,             //its logical volume
                   "InPCLW",                //its name
                   logicWorld,                //its mother  volume
                   false,                   //no boolean operation
                   0,                       //copy number
                   checkOverlaps);



//flattering filter
G4RotationMatrix * nRot = new G4RotationMatrix;
nRot->rotateY(180*deg);

G4Cons * ff1 = new G4Cons ("ff1",0.,20.*mm,0.,50.*mm,2.01*mm,0.*deg,360.*deg);
G4LogicalVolume * ff1l = new G4LogicalVolume (ff1, Fe, "Conelog1");
new G4PVPlacement (nRot,
		   G4ThreeVector(0.,0.,101.005*mm),
		   ff1l,
		   "ff1p",
		   logicWorld,
		   false,
		   0,
		   checkOverlaps);

G4Cons * ff2 = new G4Cons ("ff2",0.,14.*mm,0.,20.*mm,5.21*mm,0.*deg,360.*deg);
G4LogicalVolume * ff2l = new G4LogicalVolume (ff2, Fe, "Conelog1");
new G4PVPlacement (nRot,
                   G4ThreeVector(0.,0.,104.615*mm),
                   ff2l,
                   "ff2p",
                   logicWorld,
                   false,
                   0,
                   checkOverlaps);

G4Cons * ff3 = new G4Cons ("ff3",0.,10.*mm,0.,14.*mm,2.48*mm,0.*deg,360.*deg);
G4LogicalVolume * ff3l = new G4LogicalVolume (ff3, Fe, "Conelog3");
new G4PVPlacement (nRot,
                   G4ThreeVector(0.,0.,108.46*mm),
                   ff3l,
                   "ff3p",
                   logicWorld,
                   false,
                   0,
                   checkOverlaps);

G4Cons * ff4 = new G4Cons ("ff4",0.,6.*mm,0.,10.*mm,1.7*mm,0.*deg,360.*deg);
G4LogicalVolume * ff4l = new G4LogicalVolume (ff4, Fe, "Conelog1");
new G4PVPlacement (nRot,
                   G4ThreeVector(0.,0.,110.55*mm),
                   ff4l,
                   "ff4p",
                   logicWorld,
                   false,
                   0,
                   checkOverlaps);

G4Cons * ff5 = new G4Cons ("ff5",0.,3.*mm,0.,6.*mm,0.7*mm,0.*deg,360.*deg);
G4LogicalVolume * ff5l = new G4LogicalVolume (ff5, Fe, "Conelog1");
new G4PVPlacement (nRot,
                   G4ThreeVector(0.,0.,111.75*mm),
                   ff5l,
                   "ff5p",
                   logicWorld,
                   false,
                   0,
                   checkOverlaps);

G4Cons * ff6 = new G4Cons ("ff6",0.,0.*mm,0.,3.*mm,0.2*mm,0.*deg,360.*deg);
G4LogicalVolume * ff6l = new G4LogicalVolume (ff6, Fe, "Conelog1");
new G4PVPlacement (nRot,
                   G4ThreeVector(0.,0.,112.2*mm),
                   ff6l,
                   "ff6p",
                   logicWorld,
                   false,
                   0,
                   checkOverlaps);

G4ThreeVector centre;
//ionization chamber

 G4Material* KAPTON = nist->FindOrBuildMaterial("G4_KAPTON");
   G4Tubs* ICTubeW = new G4Tubs("ionizationChamberTube", 0., 3.75*2.54*10.*mm, 0.005*25.4*mm, 0.*deg, 360.*deg);
   G4Tubs* ICTubeP = new G4Tubs("ionizationChamberTube", 0., 3.75*2.54*10.*mm, 0.002*25.4*mm, 0.*deg, 360.*deg);


   // W1
   centre= G4ThreeVector(0.,0.,103*mm);
   G4LogicalVolume *PCUTubeW1LV = new G4LogicalVolume(ICTubeW, KAPTON, "ionizationChamberTubeW1LV");
   new G4PVPlacement(0, centre, PCUTubeW1LV,"ionizationChamberTubeW1PV", logicWorld, false, 0, checkOverlaps);
   // P1
   centre= G4ThreeVector(0.,0.,105.38*mm);
   G4LogicalVolume *PCUTubeP1LV = new G4LogicalVolume(ICTubeP, KAPTON, "ionizationChamberTubeP1LV");
   new G4PVPlacement(0, centre, PCUTubeP1LV, "ionizationChamberTubeP1PV", logicWorld, false, 0, checkOverlaps);
   // W2
   centre= G4ThreeVector(0.,0.,110.15*mm);
   G4LogicalVolume *PCUTubeW2LV = new G4LogicalVolume(ICTubeW, KAPTON, "ionizationChamberTubeW2LV");
   new G4PVPlacement(0, centre, PCUTubeW2LV, "ionizationChamberTubeW2PV", logicWorld, false, 0, checkOverlaps);

   // P2
   centre= G4ThreeVector(0.,0.,107.77*mm);
   G4LogicalVolume *PCUTubeP2LV = new G4LogicalVolume(ICTubeP, KAPTON, "ionizationChamberTubeP2LV");
   new G4PVPlacement(0, centre, PCUTubeP2LV, "ionizationChamberTubeP2PV", logicWorld, false, 0, checkOverlaps);

   // W3
   centre= G4ThreeVector(0.,0.,117.3*mm);
   G4LogicalVolume *PCUTubeW3LV = new G4LogicalVolume(ICTubeW, KAPTON, "ionizationChamberTubeW3LV");
   new G4PVPlacement(0, centre, PCUTubeW3LV, "ionizationChamberTubeW3PV", logicWorld, false, 0, checkOverlaps);

   // P3
   centre= G4ThreeVector(0.,0.,112.53*mm);
   G4LogicalVolume *PCUTubeP3LV = new G4LogicalVolume(ICTubeP, KAPTON, "ionizationChamberTubeP3LV");
   new G4PVPlacement(0, centre, PCUTubeP3LV, "ionizationChamberTubeP3PV", logicWorld, false, 0, checkOverlaps);

   // P4
   centre= G4ThreeVector(0.,0.,114.92*mm);
   G4LogicalVolume *PCUTubeP4LV = new G4LogicalVolume(ICTubeP, KAPTON, "ionizationChamberTubeP4LV");
   new G4PVPlacement(0, centre, PCUTubeP4LV, "ionizationChamberTubeP4PV", logicWorld, false, 0, checkOverlaps);


//mirror
 G4Material* MYLAR = nist->FindOrBuildMaterial("G4_MYLAR");
 G4Tubs* mirror = new G4Tubs("mirror", 0., 86.*mm, 1.0*mm, 0.*deg, 360.0*deg);
 G4LogicalVolume *mirrorl = new G4LogicalVolume(mirror, MYLAR, "mirrorl");
 G4RotationMatrix* pr = new 	G4RotationMatrix();
   pr -> rotateY(35.0*deg);
 new G4PVPlacement(pr,
                   G4ThreeVector(0., 0., (117.3+5+49.33)*mm),
                   mirrorl,
                   "mirrorp",
                   logicWorld,
                   false,
                   0,
                   checkOverlaps);


//jaws
//1x
   G4double theta;
 G4double jaw1XAperture = 5*cm;
   G4double jaw2XAperture = -5*cm;
     G4double jaw1YAperture = 5*cm;
       G4double jaw2YAperture = -5*cm;
G4RotationMatrix* cRotation1 = new G4RotationMatrix();
G4RotationMatrix* cRotation2 = new G4RotationMatrix();
G4RotationMatrix* cRotation3 = new G4RotationMatrix();
G4RotationMatrix* cRotation4 = new G4RotationMatrix();
G4double x, y, z, dx, dy; //, dz, top;
G4ThreeVector halfSize, centre1;
//	G4double beta, R;


centre= G4ThreeVector(50.*mm, 0,(117.3+5+2*49.33+25+78/2)*mm);
halfSize= G4ThreeVector(50.*mm, 90.*mm, 78./2.*mm);

x=centre.getX();
y=centre.getY();
z=centre.getZ();
//	top=z-78./2.;
dx=halfSize.getX();
dy=halfSize.getY();

G4Box* box1 = new G4Box("jaw1box", 50.*mm, 90.*mm, 78./2.*mm);
G4LogicalVolume *boxl1 = new G4LogicalVolume (box1, W, "jaw1boxl");



theta=fabs(atan(jaw1XAperture/1000*mm));
       centre1.set(z*sin(theta)+dx*cos(theta), y, z*cos(theta)-dx*sin(theta));
cRotation1->rotateY(-theta);
new G4PVPlacement (cRotation1, centre1, boxl1, "jaw1boxp", logicWorld, false,0, checkOverlaps);

//2x
centre= G4ThreeVector(-50.*mm,0,(117.3+5+2*49.33+25+78/2)*mm);
G4Box* box2 = new G4Box("jaw1box", 50.*mm, 90.*mm, 78./2.*mm);

   halfSize= G4ThreeVector(50.*mm, 90.*mm, 78./2.*mm);

 x=centre.getX();
 y=centre.getY();
 z=centre.getZ();
 //	top=z-78./2.;
 dx=halfSize.getX();
 dy=halfSize.getY();

G4LogicalVolume *boxl2 = new G4LogicalVolume (box2, W, "jaw2boxl");
theta=fabs(atan(jaw2XAperture/1000*mm));
       centre1.set(-(z*sin(theta)+dx*cos(theta)), y, z*cos(theta)-dx*sin(theta));
cRotation2->rotateY(theta);
new G4PVPlacement (cRotation2, centre1, boxl2, "jaw2boxp", logicWorld, false,0, checkOverlaps);

//3y
centre= G4ThreeVector(0, 50.*mm,(117.3+5+2*49.33+25+78/2+90)*mm);
G4Box* box3 = new G4Box("jaw3box",90.*mm, 50.*mm, 78./2.*mm);

   halfSize= G4ThreeVector(90.*mm, 50.*mm, 78./2.*mm);

 x=centre.getX();
 y=centre.getY();
 z=centre.getZ();
 //	top=z-78./2.;
 dx=halfSize.getX();
 dy=halfSize.getY();

G4LogicalVolume *boxl3 = new G4LogicalVolume (box3, W, "jaw3boxl");
theta=fabs(atan(jaw1YAperture/1000*mm));
       centre1.set(x, z*sin(theta)+dy*cos(theta), z*cos(theta)-dy*sin(theta));
cRotation3->rotateX(theta);
new G4PVPlacement (cRotation3, centre1, boxl3, "jaw3boxp", logicWorld, false,0, checkOverlaps);

//4y
centre= G4ThreeVector(0, -50.*mm,( 117.3+5+2*49.33+25+78/2+90)*mm);
G4Box* box4 = new G4Box("jaw4box",90.*mm, 50.*mm, 78./2.*mm);
   halfSize= G4ThreeVector(90.*mm, 50.*mm, 78./2.*mm);

 x=centre.getX();
 y=centre.getY();
 z=centre.getZ();
 //	top=z-78./2.;
 dx=halfSize.getX();
 dy=halfSize.getY();

G4LogicalVolume *boxl4 = new G4LogicalVolume (box4, W, "jaw4boxl");
theta=fabs(atan(jaw2YAperture/1000*mm));
       centre1.set(x, -(z*sin(theta)+dy*cos(theta)), z*cos(theta)-dy*sin(theta));
cRotation4->rotateX(-theta);
new G4PVPlacement (cRotation4, centre1, boxl4, "jaw3boxp", logicWorld, false,0, checkOverlaps);


G4RotationMatrix* cRot = new G4RotationMatrix();
cRot ->rotateX(180*deg);
 G4Sphere* hSphere = new G4Sphere("hSphere",
                                  10.*mm,
                                  40*mm,
                                  0*deg,
                                  360*deg,
                                  0*deg,
                                  90*deg);
 G4LogicalVolume* loghSphere = new G4LogicalVolume(hSphere,
                                                  W,
                                                  "loghSphere",
                                                  0,
                                                  0,
                                                  0,
                                                  true);
 new G4PVPlacement(cRot,                       //no rotation
                   G4ThreeVector(0, 0, -20.*mm),                    //at position
                   loghSphere,             //its logical volume
                   "hSphere",                //its name
                   logicWorld,                //its mother  volume
                   false,                   //no boolean operation
                   0,                       //copy number
                   checkOverlaps);


 G4Sphere* Sphere = new G4Sphere("Sphere", 40.*mm, 110.*mm, 0*deg, 360.*deg, 0*deg, (180-20)*deg);
 G4LogicalVolume* logSphere = new G4LogicalVolume(Sphere,
                                                  Fe,
                                                  "logSphere",
                                                  0,
                                                  0,
                                                  0,
                                                  true);



 new G4PVPlacement(cRot,                       //no rotation
                   G4ThreeVector(0, 0, -20.*mm),                    //at position
                   logSphere,             //its logical volume
                   "Sphere",                //its name
                   logicWorld,                //its mother  volume
                   false,                   //no boolean operation
                   0,                       //copy number
                   checkOverlaps);



 G4Sphere* nSphere = new G4Sphere("nSphere", 111.*mm, 170.*mm, 0*deg, 360.*deg, 0*deg, (180-40)*deg);
 G4LogicalVolume* lognSphere = new G4LogicalVolume(nSphere,
                                                  Pb,
                                                  "lognSphere",
                                                  0,
                                                  0,
                                                  0,
                                                  true);



 new G4PVPlacement(cRot,                       //no rotation
                   G4ThreeVector(0, 0, -20.*mm),                    //at position
                   lognSphere,             //its logical volume
                   "nSphere",                //its name
                   logicWorld,                //its mother  volume
                   false,                   //no boolean operation
                   0,                       //copy number
                   checkOverlaps);


/*G4Box* phantom = new G4Box ("phantom", 20.*cm, 20.*cm, 5*mm);
G4LogicalVolume *phantoml = new G4LogicalVolume (phantom, world_mat, "phantoml");
new G4PVPlacement (0, G4ThreeVector(0,0,(1000+5)*mm), phantoml, "phantomp", logicWorld, false, 0, checkOverlaps);
fScoringVolume = phantoml;*/

 G4Box* phantom = new G4Box ("Phantom",
                            20.*cm,
                            20.*cm,
                            15.*cm);

 G4LogicalVolume* phantoml = new G4LogicalVolume (phantom,
                                              water,
                                              "phantoml");
 new G4PVPlacement (0,
                    G4ThreeVector(0,0,57.*cm), // G4ThreeVector(0,0,105.*cm)
                    phantoml,
                    "phantomp",
                    logicWorld,
                    false,
                    0,
                    checkOverlaps);

 fScoringVolume = phantoml;
  return physWorld;
}
