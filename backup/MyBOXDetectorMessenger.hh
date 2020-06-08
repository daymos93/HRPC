// A UI messenger class that implements our own UI commands to manipulate some 
// properties (thickness, material) of the detector Target. An object from this 
// class must be created and stored in the coresponding YourDetectorConstruction
// object on which the implemented/defined commands will act.
#ifndef MYBOXDETECTORMESSENGER_HH
#define MYBOXDETECTORMESSENGER_HH

#include "G4UImessenger.hh"

// forward declarations
class MyBOXDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4String;

class MyBOXDetectorMessenger : public G4UImessenger {

  // Method declaration:
  public:

    // CTR & DTR 
	MyBOXDetectorMessenger(MyBOXDetectorConstruction* det);
   ~MyBOXDetectorMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);
  

  // Data member declarations  
  private:

    MyBOXDetectorConstruction*  fMyBOXDetector;
    
    G4UIdirectory*             fDirCMD;
    G4UIcmdWithADoubleAndUnit* fTargetThicknessCMD;
    G4UIcmdWithAString*        fTargetMaterialCMD;

};

#endif
