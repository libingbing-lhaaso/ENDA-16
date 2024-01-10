#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
//#include "G4NeutronHPThermalScatteringNames.hh"
#include "G4SystemOfUnits.hh"
#include "Globals.hh"
#define M_PI 3.14159
#include <fstream>
#include <iostream>

#include "G4AssemblyVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
using namespace std;

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{ }

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();

//---------------------------------------------MATERIALS-------------------------------------------------

  G4double density, fractionmass;
  G4int ncomp, natoms;

  G4Element* elO  = nist->FindOrBuildElement("O");
  G4Element* elC  = nist->FindOrBuildElement("C");
  G4Element* elH  = nist->FindOrBuildElement("H");

  G4Element* elSi = nist->FindOrBuildElement("Si");
  G4Element* elZn = nist->FindOrBuildElement("Zn");
  G4Element* elS = nist->FindOrBuildElement("S");
  G4Element* elB = nist->FindOrBuildElement("B");
  G4Element* elNa = nist->FindOrBuildElement("Na");
  G4Element* elMg = nist->FindOrBuildElement("Mg");
  G4Element* elAl = nist->FindOrBuildElement("Al");
  G4Element* elK = nist->FindOrBuildElement("K");
  G4Element* elTi = nist->FindOrBuildElement("Ti");
  G4Element* elCa = nist->FindOrBuildElement("Ca");
  G4Element* elFe = nist->FindOrBuildElement("Fe");
  

  G4Material* ZnS=new G4Material("CinkSulfide",density=4.09*g/cm3,ncomp=2);
  ZnS->AddElement(elZn, natoms=1);
  ZnS->AddElement(elS, natoms=1);

  G4Material* B2O3=new G4Material("BoronOxid",density=1.85*g/cm3,ncomp=2);
  B2O3->AddElement(elB, natoms=2);
  B2O3->AddElement(elO, natoms=3);

  G4Material* Silicon = new G4Material("Silicon", density=1*g/cm3, ncomp=4);
  Silicon->AddElement(elSi, natoms=1);
  Silicon->AddElement(elO, natoms=1);
  Silicon->AddElement(elC, natoms=2);
  Silicon->AddElement(elH, natoms=6);

  G4Material* LRB2 = new G4Material("BoronSc", density=3.3*g/cm3, ncomp=2);
  LRB2->AddMaterial(ZnS, fractionmass=65.0*perCent);
  LRB2->AddMaterial(B2O3, fractionmass=35.0*perCent);

  G4Material* Soil_ybj = new G4Material("Soil", density=4.45*g/cm3, ncomp=9);
  Soil_ybj->AddElement(elO,  fractionmass=0.6288); //density from Yangfan
  Soil_ybj->AddElement(elNa, fractionmass=0.0104);
  Soil_ybj->AddElement(elMg, fractionmass=0.0057);
  Soil_ybj->AddElement(elAl, fractionmass=0.0695);
  Soil_ybj->AddElement(elSi, fractionmass=0.2274);
  Soil_ybj->AddElement(elK,  fractionmass=0.0236);
  Soil_ybj->AddElement(elCa, fractionmass=0.0067);
  Soil_ybj->AddElement(elTi, fractionmass=0.0027);
  Soil_ybj->AddElement(elFe, fractionmass=0.0252);

  G4Material* Air = nist->BuildMaterialWithNewDensity("Air_YBJ","G4_AIR",0.8*mg/cm3);
  G4Material* Concrete = nist->FindOrBuildMaterial("G4_CONCRETE");
  G4Material* Dry_Soil_Haizi = nist->BuildMaterialWithNewDensity("Soil_YBJ","G4_CONCRETE",1.8*g/cm3);
  G4Material* PE = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material* Water = nist->FindOrBuildMaterial("G4_WATER");

  G4Material* Wet_Soil_Haizi = new G4Material("GND with Water", \
             density=(Dry_Soil_Haizi->GetDensity() + waterfraction*0.02*g/cm3), ncomp=2);
  Wet_Soil_Haizi->AddMaterial(Dry_Soil_Haizi, fractionmass=(100 - waterfraction)*perCent);
  Wet_Soil_Haizi->AddMaterial(Water, fractionmass=waterfraction*perCent);


  G4Material* scintillator = LRB2;

  //-------------------------------SIZES-------------------------------------------------------

  G4double world_sizeX = 100*m;
  G4double world_sizeY = 100*m;
  G4double world_sizeZ = 50*m;
  G4double soil_thickness = 10*m;
  G4double SciThick = 1.5*mm;
  G4double BrlSize_Z = 70*cm;
  G4double BrlSize_XY = 80*cm;
  G4double BrlThick = PEthick*mm;
  G4double SiliconThick = 3*mm;
  G4double ScintSize_XY = 69*cm;
  G4double dy=0*m;
  G4double dx=0*m;
  G4double dz=(0.05*m+0.5*BrlSize_Z+BrlThick);
  G4ThreeVector D=G4ThreeVector(dx,dy,dz);

  G4bool checkOverlaps = true;

  //-------------------------------VOLUMES-----------------------------------------------------

  G4Box *solidWorld = new G4Box("World", world_sizeX, world_sizeY, world_sizeZ);
  G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, Air, "World");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0, checkOverlaps);

  G4Box *solidFloor = new G4Box("Ground", world_sizeX, world_sizeY, soil_thickness/2);
  G4LogicalVolume *logicFloor = new G4LogicalVolume(solidFloor, Soil_ybj ,"Ground");
  //G4LogicalVolume *logicFloor = new G4LogicalVolume(solidFloor, Concrete, "Ground");
  new G4PVPlacement(nullptr,	G4ThreeVector(0*m, 0*m, -soil_thickness/2), logicFloor, "Ground", logicWorld, false, 0, checkOverlaps);

  G4Tubs* solidDec[16];
  G4LogicalVolume* logicDec[16];

  G4Tubs* solidDecAir[16];
  G4LogicalVolume* logicDecAir[16];

  G4Tubs* solidDet[16];
  G4LogicalVolume* logicDet[16];

  G4Tubs* solidSil[16];
  G4LogicalVolume* logicSil[16];
 
  G4double xrand=0., yrand=0., detx, dety;
  G4int detID;
  cin>> xrand >> yrand;
  G4cout<< xrand <<" " <<yrand<<G4endl;
  for(int i=0;i<16;i++){
   if(fdet.is_open()){
     fdet >> detID >> detx >> dety;
     //G4double placex=-7.5+5*(i%4)+xrand;
     //G4double placey=-7.5+5*int(i/4)+yrand;
     G4double placex=detx+xrand;
     G4double placey=dety+yrand;
     G4cout<<detID<<" "<<placex<<" "<<placey<<endl;
     G4ThreeVector place = G4ThreeVector(placex*m, placey*m, dz);
     G4String name = "Detector"+std::to_string(i);
     solidDec[i] = new G4Tubs("Brl", 0, (0.5*BrlSize_XY+BrlThick), (0.5*BrlSize_Z+BrlThick), 0., 2*M_PI*rad); //solid
     logicDec[i] = new G4LogicalVolume(solidDec[i], PE, "Brl");
     new G4PVPlacement(nullptr,place,logicDec[i],"Brl",logicWorld,false,0, checkOverlaps);

     solidDecAir[i] = new G4Tubs("Air", 0, (0.5*BrlSize_XY), (0.5*BrlSize_Z), 0., 2*M_PI*rad); //solid
     logicDecAir[i] = new G4LogicalVolume(solidDecAir[i], Air, "Air");
     new G4PVPlacement(nullptr, G4ThreeVector(0*m, 0*m, 0*m), logicDecAir[i], "Air", logicDec[i], false, 0, checkOverlaps);

     solidSil[i] = new G4Tubs("Sil", 0, (0.5*ScintSize_XY), 0.5*SiliconThick, 0., 2*M_PI*rad); //solid
     logicSil[i] = new G4LogicalVolume(solidSil[i], Silicon, "Sil");
     new G4PVPlacement(nullptr, G4ThreeVector(0*m, 0*m, -0.5*BrlSize_Z + 2*cm), logicSil[i], "Sil", logicDecAir[i], false, 0, checkOverlaps);

     solidDet[i] = new G4Tubs(name, 0, (0.5*ScintSize_XY), 0.5*SciThick, 0., 2*M_PI*rad); //solid
     logicDet[i] = new G4LogicalVolume(solidDet[i], scintillator, name);
     new G4PVPlacement(nullptr, G4ThreeVector(0*m, 0*m, 0*cm), logicDet[i], name, logicSil[i], false, 0, checkOverlaps);
   }
  }

  return physWorld;
}
