
#include "HRPCPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4Event.hh" 
#include "G4ParticleTable.hh"
#include "HRPCDetectorConstruction.hh"
#include "Randomize.hh"

HRPCPrimaryGeneratorAction::HRPCPrimaryGeneratorAction(HRPCDetectorConstruction* det)
:   G4VUserPrimaryGeneratorAction(),
    fHRPCDetector(det),
    fParticleGun(nullptr) {
    // create the particle-gun object
    G4int nParticle = 1;
    fParticleGun    = new G4ParticleGun(nParticle);
    SetDefaultKinematic();
}


HRPCPrimaryGeneratorAction::~HRPCPrimaryGeneratorAction() {
    delete fParticleGun;
}


void HRPCPrimaryGeneratorAction::GeneratePrimaries(G4Event* evt) {
	fParticleGun->GeneratePrimaryVertex(evt);
}


void HRPCPrimaryGeneratorAction::SetDefaultKinematic() {
    //
    // default primary particle: 30 [MeV] e- perpendicular to the target
	G4ParticleDefinition* part = G4ParticleTable::GetParticleTable()->FindParticle( "proton" );
    fParticleGun->SetParticleDefinition( part );
    fParticleGun->SetParticleMomentumDirection( G4ThreeVector(1., 0., 0.) );
    fParticleGun->SetParticleEnergy( 30.*CLHEP::MeV );
    UpdatePosition();
}


// needs to be invoked for all workers at the begining of the run: user might
// have changed the target thickness
void HRPCPrimaryGeneratorAction::UpdatePosition() {



    fParticleGun->SetParticlePosition(
        G4ThreeVector( fHRPCDetector->GetGunXPosition(), 0.0, 0.0 ) );
}


const G4String& HRPCPrimaryGeneratorAction::GetParticleName() const {
	return fParticleGun->GetParticleDefinition()->GetParticleName();
}


G4double HRPCPrimaryGeneratorAction::GetParticleEnergy() const {
	return fParticleGun->GetParticleEnergy();
}
