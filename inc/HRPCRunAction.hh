
#ifndef HRPCRUNACTION_HH
#define HRPCRUNACTION_HH

#include "G4UserRunAction.hh"

#include "G4String.hh"

// forward declarations
class HRPCDetectorConstruction;
class HRPCPrimaryGeneratorAction;
class HRPCDetectorConstruction;
class G4Run;
class HRPCRun;


class HRPCRunAction : public G4UserRunAction {

  // Method declaration:
  public:
    
    // CTR: 
    //  - detector construction object is used in the stepping action to check target
    //  - primary generator is used to re-set position for workers and to get E0 (set only for workers)
	HRPCRunAction(HRPCDetectorConstruction* det, HRPCPrimaryGeneratorAction* prim = nullptr);
    virtual ~HRPCRunAction();

    // static access method  (per accere da altri file)
    static HRPCRunAction* Instance();
    
    // Virtual method to generate YourRun for each Worker threads
    virtual G4Run* GenerateRun();    

    // Virtial method that is called by the RunManager before the first event starts
    virtual void   BeginOfRunAction(const G4Run*);

    // Virtual method that is called by the RunManager after the last event finished
    virtual void   EndOfRunAction(const G4Run* aRun);


  // Data member declarations:
  private:

  	HRPCDetectorConstruction*    fHRPCDetector;

  	HRPCPrimaryGeneratorAction*  fHRPCPrimary;

    HRPCRun*                     fHRPCRun;
    
    static HRPCRunAction* fgInstance;  // per accere da altri file

    G4long fTime;				//conta tempo per eseguire run
    
};

#endif
