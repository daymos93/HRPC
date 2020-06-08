
#ifndef MYBOXACTIONINITIALIZATION_HH
#define MYBOXACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"


// forward declarations
class MyBOXDetectorConstruction;


class MyBOXActionInitialization : public G4VUserActionInitialization {

  // Method declaration:
  public:
    
    // CTR & DTR (you will need to talk to your detector to find out the GUN pos.)
	MyBOXActionInitialization(MyBOXDetectorConstruction* det);
    virtual ~MyBOXActionInitialization();

    // (Pure) Virtual method to be implemented by the user to instantiate 
    // User Action class objects
    virtual void Build() const;

    // Virtual method to be implemented by the user to instantiate User RunAction
    // class object to be used by G4MTRunManager. THIS METHOD IS NOT INVOKED IN
    // THE SEQUENTIAL MODE! The user should not use this method to instantiate
    // user action classes rather than user RunAction.
    virtual void BuildForMaster() const;


  // Data member declarations:
  private:

    MyBOXDetectorConstruction* fMyBOXDetector;
};

#endif
