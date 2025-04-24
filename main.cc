// main.cc
#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "FTFP_BERT.hh"  // ✅ Lista de física disponible por defecto
#include "MyDetectorConstruction.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

int main(int argc, char** argv) {
    // Run manager
    auto* runManager = new G4RunManager();

    // Geometría del detector
    runManager->SetUserInitialization(new MyDetectorConstruction());

    // ✅ Lista de física (FTFP_BERT es completa y robusta)
    runManager->SetUserInitialization(new FTFP_BERT());

    // Inicializar todo
    runManager->Initialize();

    // Visualización
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    // Interfaz de usuario
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    G4UIExecutive* ui = nullptr;

    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv, "Qt");
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    } else {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    // Limpieza
    delete visManager;
    delete runManager;

    return 0;
}