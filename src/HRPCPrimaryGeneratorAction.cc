
#include "../inc/MyBOXPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4Event.hh" 
#include "G4ParticleTable.hh"
#include "MyBOXDetectorConstruction.hh"
#include "Randomize.hh"

MyBOXPrimaryGeneratorAction::MyBOXPrimaryGeneratorAction(MyBOXDetectorConstruction* det)
:   G4VUserPrimaryGeneratorAction(),
    fMyBOXDetector(det),
    fParticleGun(nullptr) {
    // create the particle-gun object
    G4int nParticle = 1;
    fParticleGun    = new G4ParticleGun(nParticle);
    SetDefaultKinematic();
}


MyBOXPrimaryGeneratorAction::~MyBOXPrimaryGeneratorAction() {
    delete fParticleGun;
}


void MyBOXPrimaryGeneratorAction::GeneratePrimaries(G4Event* evt) {
	//set direction
		    /* G4double cosx,cosy;
		     G4double segnoZ;
		     CX=0;CY=0;CZ=0;
		     G4double fracBehind=0.5;   //fraction of particles coming from behind, 50 % di possibilità di particelle dal davanti e dal dietro

		     segnoZ=G4UniformRand();	//genera segno casuale di z (se esce numero da 0 a 0.5 allora è dietro, da 0.5 a 1 davanti)



		     if (segnoZ<fracBehind)  {  // se minore di 0.5 Z viene settato negativo quindi particella viene da dietro, se invece maggiore di 0.5 Z settato positivo particella dal davanti



		// si utilizza metodo HIT OR MISS (si costruisce rettangolo intorno a istogramma, prendendo il valore massimo della y per trovare l'altezza del rettangolo. Se il valore estratto a caso è dentro il rettangolo si tiene, altrimenti si scarta e si ripesca

		        cosx=-1+G4UniformRand()*2;		// genera valore casuale del coseno, tra -1 e 1 (se esce 1 da random -> cosx=-1+1*2=1  + il massimo che può uscir
		        CX = cosx; 					//CX è variabile assegnata nei file .hh

		     while (1){
		        cosy=-1+G4UniformRand()*2;

		         if((cosy*cosy+CX*CX)<1) break;
		      }

		       CY = cosy;
		       CZ = -sqrt(1-CX*CX-CY*CY);		//si calcola il cosZ a partire dagli altri 2. Negativo perchè deve venire da dietro
		 }



		else {						//else, nel caso del segno positivo di Z

		        cosx=-1+G4UniformRand()*2;
		        CX = cosx;


		     while (1){
		        cosy=-1+G4UniformRand()*2;
		         if((cosy*cosy+CX*CX)<1) break;
		       }

		       CY = cosy;
		       CZ = sqrt(1-CX*CX-CY*CY);		//Z POSITIVO
		}



		   fParticleGun->SetParticleMomentumDirection((G4ThreeVector(+CX,+CY,+CZ)));


		//Uniform generation on the detector surface,		scelta casuale della sorgente, ma che deve rientrare nell'area del rivelatore

		 gX =0;						//solo inizializzazione variabili, numeri senza significato
		 gY = 0;
		 gZ = 0;
		 G4double gXtemp=99999;
		 G4double gYtemp=99999;

		 while(1){

		  gYtemp = G4UniformRand()*1613-806.5;					//scelta a caso della coordinata y (la dimensione della camera va da -503.5 a 503.5   messa a metà dell'asse, metà sopra e metà sotto)
		  gXtemp = G4UniformRand()*836.3-418.15;
		   if(fabs(gXtemp)<(gYtemp+3338.6)/11.4316) break; 		// y=mx+q  la variazione di y e x è lineare, quindi si trovano i coefficienti m=11.066 e q=2002.93 in modo che la sorgente quando scende di y e la camera si restringe di larghezza x, ne tiene conto.

		 }
		 gX=gXtemp;
		 gY=gYtemp;


		if(segnoZ<fracBehind){ gZ=29;}			//in base al segno della camera si posiziona la sorgente, appena dietro o appena davanti (29 perchè 28 è spessore rivelatore)
		else {gZ=-1;}

		  //create vertex
		  //
		  fParticleGun->SetParticlePosition(G4ThreeVector(gX,gY,gZ)); */
	fParticleGun->GeneratePrimaryVertex(evt);
}


void MyBOXPrimaryGeneratorAction::SetDefaultKinematic() {
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
void MyBOXPrimaryGeneratorAction::UpdatePosition() {



    fParticleGun->SetParticlePosition(
        G4ThreeVector( fMyBOXDetector->GetGunXPosition(), 0.0, 0.0 ) );
}


const G4String& MyBOXPrimaryGeneratorAction::GetParticleName() const {
	return fParticleGun->GetParticleDefinition()->GetParticleName();
}


G4double MyBOXPrimaryGeneratorAction::GetParticleEnergy() const {
	return fParticleGun->GetParticleEnergy();
}
