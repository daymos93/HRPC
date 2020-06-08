
#include "G4RunManager.hh"

#include "MyBOXEventAction.hh"
#include "MyBOXRun.hh"
#include "MyBOXSteppingAction.hh"

////////////////// metodi per accere da altri file ///////////////////////////////////////////////////////////////////////////////////////////////////////
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyBOXEventAction* MyBOXEventAction::fgInstance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyBOXEventAction* MyBOXEventAction::Instance()
{
// Static acces function via G4RunManager

  return fgInstance;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


MyBOXEventAction::MyBOXEventAction()
: G4UserEventAction(),
  fPrintModulo(100000),

  n_incidenti(0),
  n_incidenti_top(0),
  n_incidenti_bot(0),

  n_cariche(0),
  n_cariche_gap1(0),
  n_cariche_gap2(0){

  fgInstance = this;   // metodo per accedere da altri file
}


MyBOXEventAction::~MyBOXEventAction() {
  fgInstance = 0;   // metodo per accedere da altri file
}


// Beore each event: reset per-event variables 
void MyBOXEventAction::BeginOfEventAction(const G4Event* /*anEvent*/) {
  MyBOXSteppingAction::Instance()->Reset();	// resetta valori

}


// After each event:
// fill the data collected for this event into the Run global (thread local)
// data Run data object (i.e. into YourRun)  
void MyBOXEventAction::EndOfEventAction(const G4Event* /*anEvent*/) {

	////    CONTATORE  PARTICELLE INCIDENTI     //////////// modif += x =
	n_incidenti = MyBOXSteppingAction::Instance()->GetIncident();	//CONTATORE particelle incidenti o fake TOP o fake BOT  (somma varibile di stepping presa tramite metodo GetIncident, la somma alla varibile del file event)

	n_incidenti_top = MyBOXSteppingAction::Instance()->GetIncident_top();	//CONTATORE particelle incidenti  TOP
	n_incidenti_bot = MyBOXSteppingAction::Instance()->GetIncident_bot();	//CONTATORE particelle incidenti  BOT


	//////////   CONTATORE PARTICELLE CARICHE IN GAS GAP    //////////
	n_cariche = MyBOXSteppingAction::Instance()->GetP_charged();	//CONTATORE  p cariche sia in gap1 che gap 2 (somma varibile di stepping presa tramite metodo GetP_charged, la somma alla varibile del file event)

	n_cariche_gap1 = MyBOXSteppingAction::Instance()->GetP_charged_gap1();	//CONTATORE p cariche solo in GAP1
	n_cariche_gap2 = MyBOXSteppingAction::Instance()->GetP_charged_gap2();	//CONTATORE p cariche solo in GAP2

	// get the current Run object and cast it to MyBOXRun (because for sure this is its type)
	MyBOXRun* currentRun = static_cast< MyBOXRun* > ( G4RunManager::GetRunManager()->GetNonConstCurrentRun() );
    // add the quantities to the (thread local) run global YourRun object 
	// add the quantities to the (thread local) run global YourRun object
    currentRun->AddTotalParticleInPerEvent( n_incidenti );
	currentRun->AddParticleInTopPerEvent( n_incidenti_top );
	currentRun->AddParticleInBotPerEvent ( n_incidenti_bot );
	currentRun->AddTotalChargePerEvent( n_cariche );
	currentRun->AddGap1ChargePerEvent( n_cariche_gap1 );
	currentRun->AddGap2ChargePerEvent( n_cariche_gap2 );
}

