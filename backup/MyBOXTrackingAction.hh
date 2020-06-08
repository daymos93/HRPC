#ifndef MYBOXTRACKINGACTION_HH
#define MYBOXTRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class MyBOXDetectorConstruction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class MyBOXTrackingAction : public G4UserTrackingAction {

  public:  
	MyBOXTrackingAction(MyBOXDetectorConstruction* det);
   ~MyBOXTrackingAction() {};
   
    virtual void PostUserTrackingAction(const G4Track*);

  private:
    MyBOXDetectorConstruction* fMyBOXDetector;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
