
#include "MyBOXRunAction.hh"

#include "MyBOXPrimaryGeneratorAction.hh"
#include "MyBOXRun.hh"
#include "G4Run.hh"

#include "Randomize.hh"
#include "MyBOXDetectorConstruction.hh"

#include "HistoManager.hh"

//root staff
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

////////////////// metodi per accere da altri file ///////////////////////////////////////////////////////////////////////////////////////////////////////
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyBOXRunAction* MyBOXRunAction::fgInstance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyBOXRunAction* MyBOXRunAction::Instance()
{
// Static acces function via G4RunManager

  return fgInstance;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



MyBOXRunAction::MyBOXRunAction(MyBOXDetectorConstruction* det, MyBOXPrimaryGeneratorAction* prim)
:   G4UserRunAction(),
    fMyBOXDetector(det),
    fMyBOXPrimary(prim),
    fMyBOXRun(nullptr) {

	fgInstance = this;   // metodo per accedere da altri file

}

MyBOXRunAction::~MyBOXRunAction() {
	fgInstance = 0;   // metodo per accedere da altri file
}


G4Run* MyBOXRunAction::GenerateRun() {
	fMyBOXRun = new MyBOXRun(fMyBOXDetector, fMyBOXPrimary);
	return fMyBOXRun;
}


void MyBOXRunAction::BeginOfRunAction(const G4Run* /*run*/) {
    // Show Rndm status (only for the Master thread)
    //if ( IsMaster() ) G4Random::showEngineStatus();
    //
    // Make sure that the Gun position is correct: the user can change the target
    // thickness between construction of objects and start of the run.  
    // note: primary generator is set in the CTR only for the Worker threads in the 
    //       ActionInitialization (left null for Master in the BuildForMaster())
    if ( fMyBOXPrimary ) {
       fMyBOXPrimary->UpdatePosition();
    }

    HistoManager::Instance()->book();

}


void MyBOXRunAction::EndOfRunAction(const G4Run*) {
    // Print Run summary (only for the Master thread)
    if ( IsMaster() ) { 
    	fMyBOXRun->EndOfRunSummary();
    }
    //
    // Show Rndm status (only for the Master thread)
//    if ( IsMaster() ) G4Random::showEngineStatus();
	//
	// G4AnalysisManager* analysisManager Write and CloseFile
}

