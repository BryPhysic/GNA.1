#include "MyDetectorConstruction.hh" // lib necesaria para. construcción de detector
#include "G4NistManager.hh"     // lib necesaria para definir materiales 
#include "G4Sphere.hh"             // lib necesaria para gepmetroa sferica
#include "G4Box.hh"                // lib necesaria para geometria cúbica
#include "G4LogicalVolume.hh"   // lib para declarar volúmenes lógicos
#include "G4Material.hh"

#include "G4PVPlacement.hh"     // lib necesaria para colocar los volúmenes lógicos en el mundo
#include "G4SystemOfUnits.hh" 

#include "CLHEP/Units/SystemOfUnits.h"
///
#include "MySensitiveDetector.hh"

#include "G4SDManager.hh"

// 
MyDetectorConstruction::MyDetectorConstruction()
    : worldSize(205 * cm), //, worldSizeY(20 * cm), worldSizeZ(100 * cm),
     waterRadius(200.0 * cm), // esto es para la esfera de agua
     gnpRadius( 100 * cm ),
     logicWorld(nullptr),matWorld(nullptr),
     logicWater(nullptr),matWater(nullptr), 
     logicGNP(nullptr), matGNP(nullptr) {}
     
// Metodo para definir los materiales 
void MyDetectorConstruction::DefineMaterials() {
        G4NistManager* nist = G4NistManager::Instance();
        matWorld = nist->FindOrBuildMaterial("G4_AIR");
        matWater = nist->FindOrBuildMaterial("G4_WATER");
        matGNP = nist->FindOrBuildMaterial("G4_GOLD");
    }

// Método para construir el detector sensible
void MyDetectorConstruction::ConstructSDandField() {
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    // Crear el detector sensible y registrar el detector en el SDManager para GNP 
    MySensitiveDetector* gnpSD = new MySensitiveDetector("GNP_SD");  
    sdManager->AddNewDetector(gnpSD); // Agregar detector al SDManager
    if (logicGNP) {
        logicGNP->SetSensitiveDetector(gnpSD); // Asignar detector a un volumen lógico
        G4cout << "Detector GNP creado" << G4endl;
    }

    // Crear el detector sensible y registrar el detector en el SDManager para agua
    MySensitiveDetector* waterSD = new MySensitiveDetector("Water_SD");
    sdManager->AddNewDetector(waterSD); 
    if (logicWater) {
        logicWater->SetSensitiveDetector(waterSD); 
        G4cout << "Detector de agua creado" << G4endl;
    }
    
}



// Método para construir el detector
G4VPhysicalVolume* MyDetectorConstruction::Construct() {
    DefineMaterials(); 
    
    // World - caja
    G4Box* solidWorld = new G4Box("World", 2.05 * m, 2.05 * m, 2.05 * m);
    logicWorld = new G4LogicalVolume(solidWorld, matWorld, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(
        nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0
    );

    // Water - esfera dentro del mundo
    G4Sphere* solidWater = new G4Sphere("Water", 0., waterRadius, 0., 2 * CLHEP::pi, 0., CLHEP::pi);
    logicWater = new G4LogicalVolume(solidWater, matWater, "Water");
    new G4PVPlacement(
        nullptr, G4ThreeVector(), logicWater, "Water", logicWorld, false, 0
    );

    // GNP - dentro del agua
    G4Sphere* solidGNP = new G4Sphere("GNP", 0., gnpRadius, 0., 2 * CLHEP::pi, 0., CLHEP::pi);
    logicGNP = new G4LogicalVolume(solidGNP, matGNP, "GNP");
    new G4PVPlacement(
        nullptr, G4ThreeVector(), logicGNP, "GNP", logicWater, false, 0
    );

    ConstructSDandField();
    return physWorld;
}



