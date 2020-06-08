// A UI messenger class that implements our own UI commands to manipulate some 
// properties (thickness, material) of the detector Target. An object from this 
// class must be created and stored in the coresponding YourDetectorConstruction
// object on which the implemented/defined commands will act.
#ifndef HRPCDETECTORMESSENGER_HH
#define HRPCDETECTORMESSENGER_HH

#include "G4UImessenger.hh"

// forward declarations
class HRPCDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4String;

class HRPCDetectorMessenger : public G4UImessenger {

  // Method declaration:
  public:

    // CTR & DTR 
	HRPCDetectorMessenger(HRPCDetectorConstruction* det);
   ~HRPCDetectorMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);
  

  // Data member declarations  
  private:

    HRPCDetectorConstruction*  fHRPCDetector;
    
    G4UIdirectory*             fDirCMD;
    G4UIcmdWithADoubleAndUnit* fgasGapThicknessCMD;
    G4UIcmdWithADoubleAndUnit* ftrdRPositionCMD;
    G4UIcmdWithADoubleAndUnit* ftrdThetaPositionCMD;



};

#endif
