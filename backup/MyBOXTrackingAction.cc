#include "MyBOXTrackingAction.hh"

#include "MyBOXDetectorConstruction.hh"
#include "MyBOXRun.hh"
//#include "HistoManager.hh"

#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4Proton.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyBOXTrackingAction::MyBOXTrackingAction(MyBOXDetectorConstruction* det)
:G4UserTrackingAction(),fMyBOXDetector(det)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyBOXTrackingAction::PostUserTrackingAction(const G4Track* track)
{
 G4int trackID = track->GetTrackID();

 //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
 MyBOXRun* run
   = static_cast<MyBOXRun*>(
       G4RunManager::GetRunManager()->GetNonConstCurrentRun());



 //status of primary particle : absorbed, transmited, reflected ?
 //
 if (trackID == 1) {
  G4int status = 0;
  if (!track->GetNextVolume()) {
    if (track->GetMomentumDirection().x() > 0.) status = 1;
    else                                        status = 2;
  }
  run->AddTrackStatus(status);
 }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

