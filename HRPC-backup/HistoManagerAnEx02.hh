
#ifndef HISTOMANAGER_HH
#define HISTOMANAGER_HH
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TFile;
class TTree;
class TH1D;

const G4int kMaxHisto = 4;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoManager
{
  public:
    HistoManager();
   ~HistoManager();
   
    static HistoManager* Instance();   // static access method (per accedere a stepping da altri file)

    void Book();
    void Save();

    void FillHisto(G4int id, G4double bin, G4double weight = 1.0);
    void Normalize(G4int id, G4double fac);    

    void FillNtuple(G4double energyGap1, G4double energyGap2,
                    G4double trackLGap1, G4double trackLGap2);
    
    void PrintStatistic();
        
  private:

    static HistoManager* fgInstance;

    TFile*   fRootFile;
    TH1D*    fHisto[kMaxHisto];            
    TTree*   fNtuple1;    
    TTree*   fNtuple2;    

    G4double fEgap1;
    G4double fEgap2;
    G4double fLgap1;
    G4double fLgap2;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

