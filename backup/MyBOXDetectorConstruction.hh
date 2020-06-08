// This class is mandatory: descriptin of the detector
#ifndef MYBOXDETECTORCONTRUCTION_HH
#define MYBOXDETECTORCONTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

// forward declaration
class MyBOXDetectorMessenger;
class G4Material;
class G4String;
class G4LogicalVolume;

class MyBOXDetectorConstruction : public G4VUserDetectorConstruction {

  // Method declaration:
  public:

    // CTR & DTR 
    MyBOXDetectorConstruction();
    virtual ~MyBOXDetectorConstruction();

    // The base class has the (only one) pure virtual method Construct() which
    // is invoked by the G4RunManager when it's Initialize() method is invoked.
    // The Construct() method must return the G4VPhysicalVolume pointer which 
    // represents the world volume.
    // Your detector description must be implemented here in this method.
    virtual G4VPhysicalVolume* Construct();

    // Note: other (not pure) virtual methods are available in the base class 
    // for SD and FIELD construction. See G4VUserDetectorConstruction for more 
    // details.

    //
    // Further (custom) methods implemnted by the user for this application:

    // Public methods to set/get the target thickness: i.e. the (full) x-size
    // ( the YZ size will be set to 1.25x the x-size automatically) 
    // NOTE: that the RUnManager will need to be informed that the geometry has 
    //       been modified. Since we compute several things here in the 
    //       Construct method, we will need to re-construct the geometry so
    //       /run/reinitializeGeometry ( /run/geometryModified is not enough)
    void     SetTargetThickness(const G4double thick) { fTargetThickness = thick; }
    G4double GetTargetThickness() const               { return fTargetThickness;  }

    // Public methods to set/get the target material: G4 NIST materials
    void              SetTargetMaterial(const G4String& matName);
    const G4Material* GetTargetMaterial() const  { return fTargetMaterial; }

    // Public method to obtain the proper gun-position depending on the detector
    G4double GetGunXPosition() { return fGunXPosition; }

    // Public method to get the target logical volume pointer (used for scoring)
    const G4VPhysicalVolume* GetTargetPhysicalVolume() const { 
        return fTargetPhysicalVolume; 
    } 
    


  // Data member declaration
  private:

    // The detector messenger pointer: to set the target thickness
    MyBOXDetectorMessenger* fDetMessenger;

    // Target material 
    G4Material*            fTargetMaterial;

    // Target logical volume pointer
    G4VPhysicalVolume*     fTargetPhysicalVolume;

    // The target thickness i.e. its (full) x-size (YZ size will be set 10x this)
    G4double               fTargetThickness;
    
    // The midpoint between the target and the world on the negative x-side
    G4double               fGunXPosition;
};

#endif   
