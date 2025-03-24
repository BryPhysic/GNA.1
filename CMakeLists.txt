cmake_minimum_required(VERSION 3.10)

project(MyGNPsim)

# Habilita C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Busca Geant4
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
# Archivos fuente
set(SOURCES
    main.cc
    MyDetectorConstruction.cc
    MySensitiveDetector.cc
)

# Ejecutable
add_executable(MyGNPsim ${SOURCES})

# Enlaza bibliotecas de Geant4
target_link_libraries(MyGNPsim ${Geant4_LIBRARIES})

# Incluye los directorios necesarios
target_include_directories(MyGNPsim PRIVATE ${Geant4_INCLUDE_DIRS})