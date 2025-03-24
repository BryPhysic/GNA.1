#include "MySensitiveDetector.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4TouchableHistory.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4RunManager.hh"

MySensitiveDetector::MySensitiveDetector(const G4String& name)
    : G4VSensitiveDetector(name) {}

G4bool MySensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    G4double edep = step->GetTotalEnergyDeposit();

    if (edep == 0.) return false;

    // Obtener el volumen donde ocurrió el depósito de energía
    G4TouchableHandle touchable = step->GetPreStepPoint()->GetTouchableHandle();
    G4String volumeName = touchable->GetVolume()->GetLogicalVolume()->GetName();

    G4cout 
        << "🟡 Energía depositada en " << volumeName
        << ": " << edep / keV << " keV" << G4endl;

    return true;
}