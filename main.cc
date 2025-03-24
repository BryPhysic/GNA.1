// main.cc
#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "FTFP_BERT.hh"  // ✅ Lista de física disponible por defecto
#include "MyDetectorConstruction.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

int main(int argc, char** argv) {
    // Modo interactivo si no se pasa macro por línea de comandos
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    // Run manager
    auto* runManager = new G4RunManager();

    // Geometría del detector
    runManager->SetUserInitialization(new MyDetectorConstruction());

    // ✅ Lista de física (FTFP_BERT es completa y robusta)
    runManager->SetUserInitialization(new FTFP_BERT());

    // (Opcional: Generator de partículas - pendiente)

    // Visualización
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    // Inicializar todo
    runManager->Initialize();

    // Comandos
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (ui) {
        UImanager->ApplyCommand("/control/execute ../vis.mac");  // Macro de visualización
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