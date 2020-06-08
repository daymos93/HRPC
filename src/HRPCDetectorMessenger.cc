
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4String.hh"

#include "../inc/HRPCDetectorMessenger.hh"
#include "HRPCDetectorConstruction.hh"


HRPCDetectorMessenger::HRPCDetectorMessenger(HRPCDetectorConstruction* det)
:   G4UImessenger(), 
    fHRPCDetector(det),
    fDirCMD(nullptr), 
    fgasGapThicknessCMD(nullptr),
	ftrdRPositionCMD(nullptr),
	ftrdThetaPositionCMD(nullptr){
    //
    // create the "det" command directory first then add commands
    fDirCMD = new G4UIdirectory("/HRPC/det/");
    fDirCMD->SetGuidance("UI commands specific to the detector construction of this application");
    //

    // UI command to set the GasGap thickness
    fgasGapThicknessCMD = new G4UIcmdWithADoubleAndUnit("/HRPC/det/setGasGapThickness",this);
    // set the description of the command 
    fgasGapThicknessCMD->SetGuidance("Sets the Thickness of the GasGap.");
    // name = TagetSizeX; omittable=false i.e. user needs to supply a value 
    fgasGapThicknessCMD->SetParameterName("fgasGapThickness",false);
    // set the aceptable range of the parameter value higher than zero
    fgasGapThicknessCMD->SetRange("fgasGapThickness>0.");
    // set the unit category to be length 
    fgasGapThicknessCMD->SetUnitCategory("Length");
    // can be modified at PreInit and Idle state 
    fgasGapThicknessCMD->AvailableForStates(G4State_PreInit, G4State_Idle);
    // in MT mode: do not need to be broadcasted for workers 
    fgasGapThicknessCMD->SetToBeBroadcasted(false);

    // UI command to set the detector distance
    ftrdRPositionCMD = new G4UIcmdWithADoubleAndUnit("/HRPC/det/setDetectorDistance",this);
    // set the description of the command
    ftrdRPositionCMD->SetGuidance("Sets the Distance of the Detector.");
    // name = TagetSizeX; omittable=false i.e. user needs to supply a value
    ftrdRPositionCMD->SetParameterName("ftrdRPosition",false);
    // set the aceptable range of the parameter value higher than zero
    ftrdRPositionCMD->SetRange("ftrdRPosition>0.");
    // set the unit category to be length
    ftrdRPositionCMD->SetUnitCategory("Length");
    // can be modified at PreInit and Idle state
    ftrdRPositionCMD->AvailableForStates(G4State_PreInit, G4State_Idle);
    // in MT mode: do not need to be broadcasted for workers
    ftrdRPositionCMD->SetToBeBroadcasted(false);

    // UI command to set the detector angle position
    ftrdThetaPositionCMD = new G4UIcmdWithADoubleAndUnit("/HRPC/det/setDetectorAngle",this);
    // set the description of the command
    ftrdThetaPositionCMD->SetGuidance("Sets the Angle of the Detector.");
    // name = TagetSizeX; omittable=false i.e. user needs to supply a value
    ftrdThetaPositionCMD->SetParameterName("ftrdThetaPosition",false);
    // set the aceptable range of the parameter value higher than zero
    ftrdThetaPositionCMD->SetRange("90.>=ftrdThetaPosition>=0.");
    // set the unit category to be length
    //ftrdThetaPositionCMD->SetUnitCategory("Length");
    // can be modified at PreInit and Idle state
    ftrdThetaPositionCMD->AvailableForStates(G4State_PreInit, G4State_Idle);
    // in MT mode: do not need to be broadcasted for workers
    ftrdThetaPositionCMD->SetToBeBroadcasted(false);



}


HRPCDetectorMessenger::~HRPCDetectorMessenger() {
	delete fgasGapThicknessCMD;
	delete ftrdRPositionCMD;
	delete ftrdThetaPositionCMD;
  	delete fDirCMD;
}


void HRPCDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
    // set gasgap thickness
    if (command == fgasGapThicknessCMD) {
  	    G4double thickness = fgasGapThicknessCMD->GetNewDoubleValue(newValue);
        fHRPCDetector->SetGasGapThickness(thickness);
    }

    // set detector distance
    if (command == ftrdRPositionCMD) {
  	    G4double distance = ftrdRPositionCMD->GetNewDoubleValue(newValue);
        fHRPCDetector->SetDetectorDistance(distance);
    }

    // set detector angle
    if (command == ftrdThetaPositionCMD) {
     	G4double angle = ftrdThetaPositionCMD->GetNewDoubleValue(newValue);
        fHRPCDetector->SetDetectorAngle(angle);
    }

}


