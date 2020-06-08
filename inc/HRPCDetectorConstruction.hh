// This class is mandatory: descriptin of the detector
#ifndef HRPCDETECTORCONTRUCTION_HH
#define HRPCDETECTORCONTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"


// forward declaration
class HRPCDetectorMessenger;
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4String;

// Standard includes
#include <list>
#include <string>
#include <cmath>

//G4 includes
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4ProductionCuts.hh"
#include "G4Region.hh"
#include "G4Trd.hh"
#include "G4Box.hh"



/// Detector construction class to define materials and geometry.
///
/// Crystals are positioned in Ring, with an appropriate rotation matrix. 
/// Several copies of Ring are placed in the full detector.

class HRPCDetectorConstruction : public G4VUserDetectorConstruction{

	// Method declaration:
	public:

		// CTR & DTR
		HRPCDetectorConstruction();
		virtual ~HRPCDetectorConstruction();

		// The base class has the (only one) pure virtual method Construct() which
	    // is invoked by the G4RunManager when it's Initialize() method is invoked.
	    // The Construct() method must return the G4VPhysicalVolume pointer which
	    // represents the world volume.
	    // Your detector description must be implemented here in this method.
	    virtual G4VPhysicalVolume* Construct();

	    //
	    // Further (custom) methods implemnted by the user for this application:

	    // Public methods to set/get the gas-gap thickness: i.e. the (full) x-size
	    // ( the YZ size will be set to 1.25x the x-size automatically)
	    // NOTE: that the RUnManager will need to be informed that the geometry has
	    //       been modified. Since we compute several things here in the
	    //       Construct method, we will need to re-construct the geometry so
	    //       /run/reinitializeGeometry ( /run/geometryModified is not enough)
	    void     SetGasGapThickness(const G4double thick) { fgasGapThickness = thick; }
	    G4double GetGasGapThickness() const               { return fgasGapThickness;  }

	    // Public methods to set/get the detector distance to (0,0,0)
	    void     SetDetectorDistance(const G4double distance) { ftrdRPosition = distance; }
	    G4double GetDectorDistance() const               { return ftrdRPosition;  }

	    // Public methods to set/get the detector angle
	    void     SetDetectorAngle(const G4double angle) { ftrdThetaPosition = angle; }
	    G4double GetDetectorAngle() const               { return ftrdThetaPosition;  }

	    // Public method to obtain the proper gun-position depending on the detector
	    G4double GetGunXPosition() { return fGunXPosition; }

	// Data member declaration
	private:

	    // The detector messenger pointer: to set the target thickness
	    HRPCDetectorMessenger* 		fDetMessenger;
    
	    G4double minorBase; 		//dimensioni trapezio camera (area effettiva)
	    G4double majorBase;
	    G4double Height;

	    // Logical volumes
	    G4LogicalVolume* worldLog;		//volume logico world

        std::vector<G4Trd*>           trdCollection ;			//collezione del nome dei volumi
        std::vector<G4LogicalVolume*> trdLogCollection ;		//collezione dei volumi logici

 
        // Physical volumes
        G4VPhysicalVolume* worldPhys;		//volume fisico world

        //per controllare che nessun volume sia sovrapposto ad un altro
        G4bool  fCheckOverlaps;

        // The midpoint between the target and the world on the negative x-side
        G4double               fGunXPosition;

        G4double   			   ftrdRPosition;

        G4double 			   ftrdThetaPosition;

        G4double			   fgasGapThickness;

};

#endif


