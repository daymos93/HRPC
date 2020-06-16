
#include "HRPCPrimaryGeneratorAction.hh"

#include "G4Material.hh"
#include "HRPCDetectorConstruction.hh"
#include "HRPCRun.hh"
#include "HRPCEventAction.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4ParticleGun.hh"

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
#include "HistoManager.hh"

HRPCRun::HRPCRun(HRPCDetectorConstruction* det, HRPCPrimaryGeneratorAction* prim)
:   G4Run(),
    fHRPCDetector(det),
    fHRPCPrimary(prim) {

	// init data members
	fn_incidenti_final = 0;				// contatore particelle incidenti bot + top
	fn_incidenti_top_final = 0;			// contatore particelle incidenti top
	fn_incidenti_bot_final = 0;			// contatore particelle incidenti bot

	fn_cariche_final = 0;				// contatore particelle cariche in gap 1 + gap2
	fn_cariche_gap1_final = 0;			// contatore particelle cariche in gap1
	fn_cariche_gap2_final = 0;

	HistoManager::Instance()->book();
}

HRPCRun::~HRPCRun() {

}

// This method will be called by the master RunManager by passing each theard 
// local run (YourRun) pointers as argument. Therefore, here you define how to
// merge each thread local Run global data structures (all thread local Run-s
// will be merged to the master Run data). 
void HRPCRun::Merge(const G4Run* run) {
	// Cast the (theard local) G4Run (base) pointer to YourRun pointer (it will 
	// be YourRun since the RunManager will call YourRunAction::GenerateRun 
	// interface method to generate the Run-s)
	const HRPCRun* localRun = static_cast<const HRPCRun*>(run);
	//
	// Then you can define how to sum up the individual YourRun data members
	fn_incidenti_final				+= localRun->fn_incidenti_final;
	fn_incidenti_top_final          += localRun->fn_incidenti_top_final;
	fn_incidenti_bot_final			+= localRun->fn_incidenti_top_final;

	fn_cariche_final  				+= localRun->fn_cariche_final;
	fn_cariche_gap1_final 			+= localRun->fn_cariche_gap1_final;
	fn_cariche_gap2_final 			+= localRun->fn_cariche_gap2_final;

	// add our histograms: note, since the Hist object is not a primitive type,
	// the addition of such objects needs to be defined (see the Hist::Add()
	// method for more details).
	//fEdepHistogram->Add(localRun->fEdepHistogram);

	// This is just to have one PrimaryGeneratorAction object at the end (because)
	// here we are merging the worker threads run objects into the master thread
	// run object but the master's RunAction do not have the PrimaryGenerator set.)
	fHRPCPrimary = localRun->fHRPCPrimary;

	// Call the base class Merge method at the end to merge the base class members
	G4Run::Merge(run);
}


// Called only for the Master's RunAction at the end after all thread local runs
// have been merged.
void  HRPCRun::EndOfRunSummary() {
    // Get number of events simulated from the base G4Run object (number of 
    // events processed by each worker thread has already been merged at the end 
    // of the Merge method when calling the base class Merge method).

    G4int nbEvents = GetNumberOfEvent();			//prende numero eventi
    if (nbEvents == 0) return;


    	//fTime = time(NULL) - fTime;				//conta tempo impiegato per eseguire run completo

    // Run conditions: modello con sorgente fgun
      const G4ParticleGun* particleGun  = HRPCPrimaryGeneratorAction::Instance()->GetParticleGun();
      G4String primary_particleName = particleGun->GetParticleDefinition()->GetParticleName();
      G4double primary_particleEnergy = particleGun->GetParticleEnergy();

     // G4cout << "\n--------------------End of Run: "<< run->GetRunID() << "  tooks: " << fTime << " seconds     ------------------------------ \n";
      G4cout << "\n ======================== run summary ======================\n";
      G4cout << "\n The run was " << nbEvents <<" events of " << primary_particleName << " having energy: " << G4BestUnit(primary_particleEnergy,"Energy")  <<"\n";
      G4cout << "\n-----------------------------------------------\n";


      //HistoManager::Instance()->Get_EventNumber_histo(nbEvents);		//passa numero eventi richiesti per plot histo
      //HistoManager::Instance()->Fill_final_histograms();		// crea file finali composti ///problema gordo!!!!
   	  //HistoManager::Instance()->save();				// salva tutto nel root file

   	  //G4double sensitivity_from_histo= HistoManager::Instance()-> GetSensitivity();

    // stampa il numero finale prendendo valori da event

    G4cout << "\n" <<"N INCIDENTI     " << fn_incidenti_final << "\n";
    G4cout <<"N INCIDENTI TOP " << fn_incidenti_top_final << "\n";
    G4cout <<"N INCIDENTI BOT " << fn_incidenti_bot_final << "\n";
    G4cout <<"N CARICHE       " << fn_cariche_final << "\n";
    G4cout <<"N CARICHE GAP1  " << fn_cariche_gap1_final << "\n";
    G4cout <<"N CARICHE GAP2  " << fn_cariche_gap2_final << "\n";
    //G4cout <<"Sensitivity     " << sensitivity_from_histo << "\n";


}
