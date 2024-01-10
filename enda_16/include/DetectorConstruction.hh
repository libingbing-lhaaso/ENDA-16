#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include<globals.hh>
#include<G4VUserDetectorConstruction.hh>
#include<G4VSolid.hh>
#include<G4LogicalVolume.hh>
#include<G4VPhysicalVolume.hh>
#include<G4Material.hh>
#include "Globals.hh"




class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
    virtual ~DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
    
  protected:
};

#endif
