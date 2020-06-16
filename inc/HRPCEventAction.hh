
#ifndef HRPCEVENTACTION_HH
#define HRPCEVENTACTION_HH

#include "G4UserEventAction.hh"

#include "globals.hh"



class HRPCEventAction : public G4UserEventAction {

  // Method declaration:
  public:
    
    // CTR: 
	HRPCEventAction();
    virtual ~HRPCEventAction();

    // static access method  (per accere da altri file)
    static HRPCEventAction* Instance();

    // Two virtual method called at the beginning and at the end of each event 
    virtual void BeginOfEventAction(const G4Event* anEvent);
    virtual void EndOfEventAction(const G4Event* anEvent);

    //void AddGap1(G4double de, G4double dl) {fEnergyGap1 += de; fTrackLGap1 += dl;};
    //void AddGap2(G4double de, G4double dl) {fEnergyGap2 += de; fTrackLGap2 += dl;};



    // funzioni per prendere valori da event

    G4int GetIncident_final() const { return n_incidenti; }
    G4int GetIncident_top_final() const { return n_incidenti_top; }
    G4int GetIncident_bot_final() const { return n_incidenti_bot; }

    G4int GetP_charged_final() const { return n_cariche; }
    G4int GetP_charged_gap1_final() const { return n_cariche_gap1; }
    G4int GetP_charged_gap2_final() const { return n_cariche_gap2; }

  // Data member declarations:
  private:
    
    static HRPCEventAction* fgInstance;  // per accere da altri file

    G4int     fPrintModulo;

    //G4double  fEnergyGap1, fEnergyGap2;
    //G4double  fTrackLGap1, fTrackLGap2;


    G4int     n_incidenti;				// contatore particelle incidenti bot + top
    G4int     n_incidenti_top;			// contatore particelle incidenti top
    G4int     n_incidenti_bot;			// contatore particelle incidenti bot

    G4int     n_cariche;				// contatore particelle cariche in gap 1 + gap2
    G4int     n_cariche_gap1;			// contatore particelle cariche in gap1
    G4int     n_cariche_gap2;			// contatore particelle cariche in gap2

};

#endif
