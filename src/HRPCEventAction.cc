
#include "G4RunManager.hh"

#include "HRPCEventAction.hh"

#include "HistoManager.hh"
#include "HRPCRun.hh"
#include "HRPCSteppingAction.hh"


////////////////// metodi per accere da altri file ///////////////////////////////////////////////////////////////////////////////////////////////////////
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HRPCEventAction* HRPCEventAction::fgInstance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HRPCEventAction* HRPCEventAction::Instance()
{
// Static acces function via G4RunManager

  return fgInstance;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


HRPCEventAction::HRPCEventAction()
: G4UserEventAction(),
  fPrintModulo(100000),

  //fEnergyGap1(0.), fEnergyGap2(0.),
  //fTrackLGap1(0.), fTrackLGap2(0.)
  n_incidenti(0),
  n_incidenti_top(0),
  n_incidenti_bot(0),

  n_cariche(0),
  n_cariche_gap1(0),
  n_cariche_gap2(0){

  fgInstance = this;   // metodo per accedere da altri file
}


HRPCEventAction::~HRPCEventAction() {
  fgInstance = 0;   // metodo per accedere da altri file
}


// Beore each event: reset per-event variables 
void HRPCEventAction::BeginOfEventAction(const G4Event* /*anEvent*/) {
  HRPCSteppingAction::Instance()->Reset();	// resetta valori

  // initialisation per event
  //fEnergyGap1 = fEnergyGap2 = 0.;
  //fTrackLGap1 = fTrackLGap2 = 0.;
}


// After each event:
// fill the data collected for this event into the Run global (thread local)
// data Run data object (i.e. into YourRun)  
void HRPCEventAction::EndOfEventAction(const G4Event* /*anEvent*/) {

	////    CONTATORE  PARTICELLE INCIDENTI     //////////// modif += x =
	n_incidenti = HRPCSteppingAction::Instance()->GetIncident();	//CONTATORE particelle incidenti o fake TOP o fake BOT  (somma varibile di stepping presa tramite metodo GetIncident, la somma alla varibile del file event)

	n_incidenti_top = HRPCSteppingAction::Instance()->GetIncident_top();	//CONTATORE particelle incidenti  TOP
	n_incidenti_bot = HRPCSteppingAction::Instance()->GetIncident_bot();	//CONTATORE particelle incidenti  BOT


	//////////   CONTATORE PARTICELLE CARICHE IN GAS GAP    //////////
	n_cariche = HRPCSteppingAction::Instance()->GetP_charged();	//CONTATORE  p cariche sia in gap1 che gap 2 (somma varibile di stepping presa tramite metodo GetP_charged, la somma alla varibile del file event)

	n_cariche_gap1 = HRPCSteppingAction::Instance()->GetP_charged_gap1();	//CONTATORE p cariche solo in GAP1
	n_cariche_gap2 = HRPCSteppingAction::Instance()->GetP_charged_gap2();	//CONTATORE p cariche solo in GAP2

	// get the current Run object and cast it to HRPCRun (because for sure this is its type)
	HRPCRun* currentRun = static_cast< HRPCRun* > ( G4RunManager::GetRunManager()->GetNonConstCurrentRun() );
    // add the quantities to the (thread local) run global YourRun object 
	// add the quantities to the (thread local) run global YourRun object
    currentRun->AddTotalParticleInPerEvent( n_incidenti );
	currentRun->AddParticleInTopPerEvent( n_incidenti_top );
	currentRun->AddParticleInBotPerEvent ( n_incidenti_bot );
	currentRun->AddTotalChargePerEvent( n_cariche );
	currentRun->AddGap1ChargePerEvent( n_cariche_gap1 );
	currentRun->AddGap2ChargePerEvent( n_cariche_gap2 );

	//fill histograms
	//
	//HistoManager::Instance()->FillHisto(0, fEnergyGap1);
	//HistoManager::Instance()->FillHisto(1, fEnergyGap2);
	//HistoManager::Instance()->FillHisto(2, fTrackLGap1);
	//HistoManager::Instance()->FillHisto(3, fTrackLGap2);

	//fill ntuple
	 //
	//HistoManager::Instance()->FillNtuple(fEnergyGap1, fEnergyGap2, fTrackLGap1, fTrackLGap2);

}

