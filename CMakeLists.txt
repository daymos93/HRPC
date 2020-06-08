#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(HRPC)


#----------------------------------------------------------------------------
# Find Geant4 package, no UI and Visualization drivers activated
#
## find_package(Geant4 REQUIRED)
#----------------------------------------------------------------------------
# Find Geant4 package, with UI and Visualization drivers activated
#
find_package(Geant4 REQUIRED ui_all vis_all)


#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})


#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/inc
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/*.hh)


#----------------------------------------------------------------------------
# Find ROOT (required package)
#
find_package(ROOT QUIET)
add_definitions(-DG4ANALYSIS_USE_ROOT)
if(NOT ROOT_FOUND)
   message(STATUS "G4 Examples: ROOT package not found. --> 3GEM-G4 example disabled")  
  return()
endif()


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
#include_directories(${ROOT_DIR})
include_directories(${ROOT_INCLUDE_DIRS})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


#----------------------------------------------------------------------------
# Add the executables, and link it to the Geant4 libraries
#
add_executable(HRPC HRPC.cc ${sources} ${headers})
if(ROOT_FOUND)
   target_link_libraries(HRPC ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
else()
   target_link_libraries(HRPC ${Geant4_LIBRARIES})
endif()
