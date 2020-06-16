
#include "HRPCRunAction.hh"

#include "HRPCPrimaryGeneratorAction.hh"
#include "HRPCRun.hh"
#include "G4Run.hh"

#include "Randomize.hh"
#include "HRPCDetectorConstruction.hh"

#include "g4root.hh"
#include <TROOT.h>
#include <TFile.h>
#include <TH1D.h>
#include "TH3D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TBranch.h"
#include "TTree.h"
#include <TNtuple.h>
#include "HistoManager.hh"

////////////////// metodi per accere da altri file ///////////////////////////////////////////////////////////////////////////////////////////////////////
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HRPCRunAction* HRPCRunAction::fgInstance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HRPCRunAction* HRPCRunAction::Instance()
{
// Static acces function via G4RunManager

  return fgInstance;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



HRPCRunAction::HRPCRunAction(HRPCDetectorConstruction* det, HRPCPrimaryGeneratorAction* prim)
:   G4UserRunAction(),
    fHRPCDetector(det),
    fHRPCPrimary(prim),
    fHRPCRun(nullptr) {

	fgInstance = this;   // metodo per accedere da altri file

}

HRPCRunAction::~HRPCRunAction() {
	fgInstance = 0;   // metodo per accedere da altri file
}


G4Run* HRPCRunAction::GenerateRun() {
	fHRPCRun = new HRPCRun(fHRPCDetector, fHRPCPrimary);
	return fHRPCRun;
}


void HRPCRunAction::BeginOfRunAction(const G4Run* /*run*/) {
    // Show Rndm status (only for the Master thread)
    //if ( IsMaster() ) G4Random::showEngineStatus();
    //
    // Make sure that the Gun position is correct: the user can change the target
    // thickness between construction of objects and start of the run.  
    // note: primary generator is set in the CTR only for the Worker threads in the 
    //       ActionInitialization (left null for Master in the BuildForMaster())
    if ( fHRPCPrimary ) {
      fHRPCPrimary->UpdatePosition();
    }

	HistoManager::Instance()->book();

}





void HRPCRunAction::EndOfRunAction(const G4Run* run) {
    // Print Run summary (only for the Master thread)
    if ( IsMaster() ) { 
    	fHRPCRun->EndOfRunSummary();
    }
    //
    // Show Rndm status (only for the Master thread)
//    if ( IsMaster() ) G4Random::showEngineStatus();
	//
	// G4AnalysisManager* analysisManager Write and CloseFile
}

