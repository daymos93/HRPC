
#ifndef HRPCBOXRUN_HH
#define HRPCBOXRUN_HH

#include "G4Run.hh"

#include "HistoManager.hh"

// forward declarations
class HRPCDetectorConstruction;
class HRPCPrimaryGeneratorAction;

//root class

class TFile;
class TH1D;
class TH2D;
class TH3D;
class TTree;
class TNtuple;
class TGraph;

class HRPCRun : public G4Run {

  // Method declaration:
  public:
    
    // CTR: 
	HRPCRun(HRPCDetectorConstruction* det, HRPCPrimaryGeneratorAction* prim);
    virtual ~HRPCRun();

    // Virtual method to be implemented to define the way of merging the underlying 
    // (thread local) Run global data structures into one global instance.
    virtual void Merge(const G4Run*);

   
    // Method to be called by the Master to compute final quantities using the 
    // its run global Run object into which all thread local run global run 
    // object instance has already been merged
    void  EndOfRunSummary();



    void AddTotalParticleInPerEvent( G4int n_incidenti_final)   {
    	fn_incidenti_final  += n_incidenti_final;
        }

    void AddParticleInTopPerEvent( G4int n_incidenti_top_final)   {
    	fn_incidenti_top_final  += n_incidenti_top_final;
            }

    void AddParticleInBotPerEvent( G4int n_incidenti_bot_final)   {
    	fn_incidenti_bot_final  += n_incidenti_bot_final;
            }

    void AddTotalChargePerEvent( G4int n_cariche_final)   {
    	fn_cariche_final  += n_cariche_final;
                }

    void AddGap1ChargePerEvent( G4int n_cariche_gap1_final)   {
    	fn_cariche_gap1_final  += n_cariche_gap1_final;
                }

    void AddGap2ChargePerEvent( G4int n_cariche_gap2_final)   {
        	fn_cariche_gap2_final  += n_cariche_gap2_final;
                    }


  // Data member declarations:
  private:
    
    	//G4long fTime;				//conta tempo per eseguire run

        G4int     fn_incidenti_final;				// contatore particelle incidenti bot + top
        G4int     fn_incidenti_top_final;			// contatore particelle incidenti top
        G4int     fn_incidenti_bot_final;			// contatore particelle incidenti bot

        G4int     fn_cariche_final;					// contatore particelle cariche in gap 1 + gap2
        G4int  	  fn_cariche_gap1_final;			// contatore particelle cariche in gap1
        G4int     fn_cariche_gap2_final;			// contatore particelle cariche in gap2


        HRPCDetectorConstruction*	fHRPCDetector;
        HRPCPrimaryGeneratorAction*	fHRPCPrimary;

        G4long	fTime;

        //HistoManager* fEdepHistogram;

};

#endif

