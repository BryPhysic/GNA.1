#ifndef MYDETECTORCONSTRUCTION_HH
#define MYDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"


class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;

class MyDetectorConstruction : public G4VUserDetectorConstruction {
public:

    MyDetectorConstruction();
    virtual ~MyDetectorConstruction() = default;

    virtual G4VPhysicalVolume* Construct();
    void ConstructSDandField();
    void DefineMaterials();

private:
    G4double worldSize;
    G4double waterRadius;
    G4double gnpRadius;

    G4LogicalVolume* logicWorld;
    G4Material* matWorld;

    G4LogicalVolume* logicWater;
    G4Material* matWater;

    G4LogicalVolume* logicGNP;
    G4Material* matGNP;
};

#endif