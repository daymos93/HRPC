
#include "../inc/MyBOXActionInitialization.hh"
#include "../inc/MyBOXDetectorConstruction.hh"
#include "../inc/MyBOXPrimaryGeneratorAction.hh"

#include "MyBOXRunAction.hh"
#include "MyBOXEventAction.hh"
#include "MyBOXSteppingAction.hh"



MyBOXActionInitialization::MyBOXActionInitialization(MyBOXDetectorConstruction* det)
:   G4VUserActionInitialization(),
    fMyBOXDetector(det) { }
    

MyBOXActionInitialization::~MyBOXActionInitialization() {}

// NOT CALLED IN SEQUENTIAL MODE i.e. ONLY FOR MT: 
// - ONLY FOR creating RunAction for the Master thread
// - (will be invoked immediately by the only one G4MTRunManager 
//   when the ActionInitialization object is registered in it in the main)
// - this RunAction might be or not the same as for worker threads below
// - see more under the G4VUserActionInitialization class section at 
//   https://twiki.cern.ch/twiki/bin/view/Geant4/QuickMigrationGuideForGeant4V10
void MyBOXActionInitialization::BuildForMaster() const {
	// we will use the same for the Master as for the Workers (IsMaster() can be 
	// used to see if a given RunAction object is the one that belongs to the 
	// Master thread or not: see for example YourRunAction::EndOfRunAction
	// method for an example of doing something only for the Master RunAction 
	// object but not for the Worker RunAction objects)
	//
	// the primary-generator not used in the master RunAction only for the workers
    SetUserAction(new MyBOXRunAction(fMyBOXDetector));
}

// Create all User Actions here: 
// - for sequential mode (will be invoked immediately by the only one G4RunManager 
//   when the ActionInitialization object is registered in it in the main)
// - for worker threads (will be invoked later by all worker G4RunManager-s) 
void MyBOXActionInitialization::Build() const {
  // Set UserPrimaryGeneratorAction
  MyBOXPrimaryGeneratorAction* primaryAction = new MyBOXPrimaryGeneratorAction(fMyBOXDetector);
  SetUserAction(primaryAction);
  // Set UserRunAction
  MyBOXRunAction* runAction = new MyBOXRunAction(fMyBOXDetector, primaryAction);
  SetUserAction(runAction);
  // Set UserEventAction
  MyBOXEventAction* eventAction = new MyBOXEventAction();
  SetUserAction(eventAction);
  // Set UserSteppingAction
  SetUserAction( new MyBOXSteppingAction(fMyBOXDetector, eventAction) );

}  
