
#ifndef MYBOXPRIMARYGENERATORACTION_HH
#define MYBOXPRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "globals.hh"

// forward declaration
class MyBOXDetectorConstruction;
class G4ParticleGun;
class G4Event;
class G4String;


class MyBOXPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {

  // Method declaration:
  public:
    
    // CTR & DTR
	MyBOXPrimaryGeneratorAction(MyBOXDetectorConstruction* det);
    virtual ~MyBOXPrimaryGeneratorAction();

    // (Pure) virtual method to generata primary events
    virtual void   GeneratePrimaries(G4Event*);

    //
    // Additional custom methods: 

    // Public method to obtain the G4ParticleGun object pointer and some other 
    // primary particle realted values
    G4ParticleGun*  GetParticleGun() { return fParticleGun; }

    // Public method to get the primary particle name.
    const G4String& GetParticleName() const;

    // Public method to get the primary particle kinetic energy.
    G4double        GetParticleEnergy() const;

    // Public method to set the default primary particle kinematics
    void            SetDefaultKinematic();

    // Public method to set the position of the particle gun: will be taken for
    // the actual detector construction
    void            UpdatePosition();

    // static access method (per accedere a stepping da altri file)
    static MyBOXPrimaryGeneratorAction* Instance();


  // Data member declarations:
  private:

    // static method (per accere da altri file)
    static MyBOXPrimaryGeneratorAction* fgInstance;

    MyBOXDetectorConstruction* fMyBOXDetector;

  	G4ParticleGun*            fParticleGun; 

    G4double CX;
    G4double CY;
    G4double CZ;
    G4double gX;
    G4double gY;
    G4double gZ;

};

#endif
