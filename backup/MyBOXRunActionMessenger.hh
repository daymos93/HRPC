
#ifndef MYBOXRUNACTIONMESSENGER_HH
#define MYBOXRUNACTIONMESSENGER_HH

#include "G4UImessenger.hh"

// forward declarations
class MyBOXRunAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4String;

class MyBOXRunActionMessenger : public G4UImessenger {

  // Method declaration:
  public:

    // CTR & DTR 
	MyBOXRunActionMessenger(MyBOXRunAction* runAction);
   ~MyBOXRunActionMessenger();

    // @Override the base class method
    void SetNewValue(G4UIcommand*, G4String);
  

  // Data member declarations  
  private:

    MyBOXRunAction*             fMyBOXRunAction;
    
    G4UIdirectory*             fDirCMD;
    G4UIcmdWithAString*        fEdepHistogramCMD;
};

#endif
