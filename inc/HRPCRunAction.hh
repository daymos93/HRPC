
#ifndef MYBOXRUNACTION_HH
#define MYBOXRUNACTION_HH

#include "G4UserRunAction.hh"

#include "G4String.hh"

// forward declarations
class MyBOXDetectorConstruction;
class MyBOXPrimaryGeneratorAction;
class MyBOXDetectorConstruction;
class G4Run;
class MyBOXRun;


class MyBOXRunAction : public G4UserRunAction {

  // Method declaration:
  public:
    
    // CTR: 
    //  - detector construction object is used in the stepping action to check target
    //  - primary generator is used to re-set position for workers and to get E0 (set only for workers)
	MyBOXRunAction(MyBOXDetectorConstruction* det, MyBOXPrimaryGeneratorAction* prim = nullptr);
    virtual ~MyBOXRunAction();

    // static access method  (per accere da altri file)
    static MyBOXRunAction* Instance();
    
    // Virtual method to generate YourRun for each Worker threads
    virtual G4Run* GenerateRun();    

    // Virtial method that is called by the RunManager before the first event starts
    virtual void   BeginOfRunAction(const G4Run*);

    // Virtual method that is called by the RunManager after the last event finished
    virtual void   EndOfRunAction(const G4Run*);


  // Data member declarations:
  private:

  	MyBOXDetectorConstruction*    fMyBOXDetector;

  	MyBOXPrimaryGeneratorAction*  fMyBOXPrimary;

    MyBOXRun*                     fMyBOXRun;
    
    static MyBOXRunAction* fgInstance;  // per accere da altri file

    G4long fTime;				//conta tempo per eseguire run
    
};

#endif
