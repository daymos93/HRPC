#include "HRPCDetectorConstruction.hh"
#include "HRPCDetectorMessenger.hh"

// for geometry definitions
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

// for material definitions
#include "G4NistManager.hh"

#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"


#include "G4SDManager.hh"
#include "G4VisAttributes.hh"

#include "G4GDMLParser.hh"
#include "G4LogicalVolumeStore.hh"


// Standard includes
#include <list>
#include <string>
#include <string.h>
#include <cmath>
//


// Geant4 includes
#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4ProductionCuts.hh"
#include "G4Region.hh"
#include "G4Trd.hh"
#include "G4Box.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4GeometryManager.hh"
#include "G4UnitsTable.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// CTR
HRPCDetectorConstruction::HRPCDetectorConstruction()
:	G4VUserDetectorConstruction(),
	//fCheckOverlaps(true)
	minorBase(0), majorBase(0), Height(0),ftrdRPosition(0),ftrdThetaPosition(0),fgasGapThickness(0)			// dimensioni trapezio camera (area effettiva)

{  	majorBase	=	584.1*mm;				//definizione valori dimensioni trapezio camera
   	minorBase	=	866.3*mm;
   	Height	=	1613.0*mm;

   	ftrdRPosition	=	1000.0*mm;			//distancia detector to origin

   	ftrdThetaPosition	=	90.0*deg;			//theta position of RPC in grads in ZY plane

   	fgasGapThickness = 1.4*mm;

   	// create detector messenger object (for your own detector UI commands)
   	fDetMessenger    = new HRPCDetectorMessenger(this);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// DTR
HRPCDetectorConstruction::~HRPCDetectorConstruction(){
	delete fDetMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* HRPCDetectorConstruction::Construct()
{ 

//+++++++++++++++++++++++++++++++++++ RIVELATORE KODEL ++++++++++++++++++++++++++++++++++++++

 //------------------------------------------------------ materials


  G4NistManager* manager = G4NistManager::Instance() ;		//inizializza tabella materiali standard


  // define Elements
   G4Element* elO  = manager->FindOrBuildElement("O");
   G4Element* elC  = manager->FindOrBuildElement("C");		//per: isobutano, etc
   G4Element* elH  = manager->FindOrBuildElement("H");

   G4Element* elF  = manager->FindOrBuildElement("F");		
   G4Element* elS  = manager->FindOrBuildElement("S");



//-------- MATERIALI

// inzializzazione costanti per creare elementi e materiali 

  //G4double a;  // atomic mass
  //G4double z;  // atomic number

   G4int numel(0), natoms(0) ;		//numero elementi, numero atomi
   G4double density(0.), temperature(0.), pressure(0.), fractionMass(0.)  ;
   G4String name, symbol ;


  // materiali da Nist
 
   G4Material *Al = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al") ;
   G4Material *Cu = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu") ;
   G4Material *Graphite = G4NistManager::Instance()->FindOrBuildMaterial("G4_GRAPHITE") ;


   // gases at STP conditions 

   G4Material* empty = manager->FindOrBuildMaterial("G4_Galactic");
 

//nuovi materiali a partire da NIST
// Aluminum core (per honeycomb core) alluminio con densità inferiore
   density=0.5*g/cm3;
   G4Material* AlCore = G4NistManager::Instance()->BuildMaterialWithNewDensity("AlCore","G4_Al",density);




// materiali composti


   //Air   
   G4Material* Air = new G4Material(name = "Air", density= 1.29*mg/cm3, numel=2);
    Air->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_N"), fractionMass = 70.*perCent);
    Air->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_O"), fractionMass = 30.*perCent);


   //paper (cellulosa)

   density = 0.3*g/cm3;
   G4Material* paper = new G4Material("paper" , density, numel=3);
   paper->AddElement(elC, natoms=6);
   paper->AddElement(elH, natoms=10);
   paper->AddElement(elO, natoms=5);


   //PET

   density = 1.37*g/cm3;
   G4Material* PET = new G4Material("PET" , density, numel=3);
   PET->AddElement(elC, natoms=10);
   PET->AddElement(elH, natoms=8);
   PET->AddElement(elO, natoms=4);


   //High Pressure Laminate HPL   
   G4Material* HPL = new G4Material(name = "HPL", density= 1.4*g/cm3, numel=3);
   HPL->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_H"), fractionMass = 5.74*perCent);
   HPL->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_C"), fractionMass = 77.46*perCent);
   HPL->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_O"), fractionMass = 16.8*perCent);



   //EVA (Etilene vinil acetato)

//-Etilene
   G4Material* etylene = new G4Material(name = "etylene", density= 1.2612*g/cm3, numel=2);
   etylene->AddElement(elC, natoms=2);
   etylene->AddElement(elH, natoms=4);

// vinyl acetato
   G4Material* vinyl_acetato = new G4Material(name = "vinyl_acetato", density= 0.93*g/cm3, numel=3);
   vinyl_acetato->AddElement(elC, natoms=4);
   vinyl_acetato->AddElement(elH, natoms=6);
   vinyl_acetato->AddElement(elO, natoms=2);

//EVA
   G4Material* EVA = new G4Material(name = "EVA", density= 0.934*g/cm3, numel=2);
   EVA->AddMaterial(etylene,fractionMass = 10* perCent);
   EVA->AddMaterial(vinyl_acetato,fractionMass = 90* perCent);




  // RPC mixture gas components

   // iso-Butane (methylpropane), STP
   density = 2.67*mg/cm3;
   G4Material* isobutane = new G4Material(name = "isoC4H10", density, numel=2) ;
   isobutane->AddElement(elC,4);
   isobutane->AddElement(elH,10);

   // Freon
   density = 4.55*mg/cm3;
   G4Material* C2H2F4 = new G4Material(name = "Freon", density, numel=3) ;
   C2H2F4->AddElement(elC, natoms=2);
   C2H2F4->AddElement(elH, natoms=2);
   C2H2F4->AddElement(elF, natoms=4);
 
   // esafluoruro di zolfo SF6
   density = 6.14*mg/cm3;
   G4Material* SF6 = new G4Material(name = "SF6", density, numel=2) ;
   SF6->AddElement(elS, natoms=1);
   SF6->AddElement(elF, natoms=6);

   //miscela RPC
   density = 3.569*mg/cm3;
   G4Material* RPCgas = new G4Material(name = "RPCGas", density, numel=3) ;
   RPCgas->AddMaterial(isobutane, fractionMass = 4.5* perCent) ;
   RPCgas->AddMaterial(C2H2F4, fractionMass = 95.2* perCent) ;
   RPCgas->AddMaterial(SF6, fractionMass = 0.3* perCent) ;




	// Print materials
	G4cout << *(G4Material::GetMaterialTable()) << G4endl; 



//----- VISUALIZZAZIONE ATTRIBUTI (colore layer)

  // Visual attributes
   G4VisAttributes *electrodeAttributes = new G4VisAttributes(G4Color::Grey()) ;
   //cathodeAttributes->SetForceWireframe(true) ;
   G4VisAttributes *gasAttributes = new G4VisAttributes(G4Color::White()) ;
   //g10Attributes->SetForceWireframe(true) ;
   G4VisAttributes *petAttributes = new G4VisAttributes(G4Color::Blue()) ;
   //gasAttributes->SetForceWireframe(true) ;
   G4VisAttributes *evaAttributes = new G4VisAttributes(G4Color::Red()) ;
   //gemAttributes->SetForceWireframe(true) ;
   G4VisAttributes *cuAttributes = new G4VisAttributes(G4Color::Yellow()) ;
  //insAttributes->SetForceWireframe(true) ;
   G4VisAttributes *honeyAttributes = new G4VisAttributes(G4Color::Green()) ;
  //insAttributes->SetForceWireframe(true) ;
   G4VisAttributes *graphiteAttributes = new G4VisAttributes(G4Color::Magenta()) ;
  //insAttributes->SetForceWireframe(true) ;
   G4VisAttributes *fakeAttributes = new G4VisAttributes(G4Color::Cyan()) ;
  //insAttributes->SetForceWireframe(true) ;


  //------------------------------------------------------ volumes

// Rotation Matrix for layers   (ruota elementi disegnati)
G4RotationMatrix* rotationPlacement = new G4RotationMatrix() ;
//rotationPlacement->rotateX((ftrdThetaPosition+90)*M_PI / 180) ;		//rotazione asse x, per avere asse trapezio verticale
//rotationPlacement->rotateY(0*M_PI / 180) ;		//ruota asse y, per avere x larghezza e z spessore
//rotationPlacement->rotateZ(90*M_PI / 180) ;

rotationPlacement->rotateX(ftrdThetaPosition+90*deg) ;		//rotazione asse x, per avere asse trapezio verticale
rotationPlacement->rotateY(0*deg) ;		//ruota asse y, per avere x larghezza e z spessore
rotationPlacement->rotateZ(90*deg) ;



//----  WORLD----

   G4double worldSizeX = 6.*m;				// MEZZE dimensioni world 
   G4double worldSizeY = 6.*m;
   G4double worldSizeZ = 6.*m;

   G4Box* worldBox = new G4Box("WorldBox", worldSizeX, worldSizeY, worldSizeZ) ;			//crea box world
   G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, Air, "WorldLog") ;		//crea volume logico world

   G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLog, "WorldSpace", 0, false, fCheckOverlaps) ;	//posiziona volume world
  

 // Set visual attributes
   G4VisAttributes *worldAttributes = new G4VisAttributes ;		//rende non visibile il volume world
   worldAttributes->SetVisibility(false) ;
   worldLog->SetVisAttributes(worldAttributes) ;



//----- VOLUMI TRAPEZI CAMERA (UNO DI SEGUITO ALL'ALTRO),   RE4-2 KODEL DG 1.4 1.4


#define Nstrati 41						//costante per definire NUMERO DI STRATI (con int non funziona)

	//CONTINOUS MATERIALS
		std::string NomeStrati[Nstrati]= 					//array nome strati
		{  

		"fakeTop",  								//falso layer di aria
		"Honeycomb_skin1_1", "Honeycomb_core1","Honeycomb_skin1_2",		//honeycomb panel  TOP
		"PET_insulationTOP",							//pet insulation TOP
		"paper",								//layer paper

		"Copper1_1", "PET1_1","PET1_2", "EVA1_1","graphite1_1","HPL1_1",	//HPL1_1
		"GasGap1",								//GASGAP 1
		"HPL1_2","graphite1_2", "EVA1_2", "PET1_3","PET1_4","Copper1_2",	// HPL1_2

		"PETstrip1","Copper_Strip", "PETstrip2",					//STRIP

		"Copper2_1", "PET2_1","PET2_2", "EVA2_1","graphite2_1","HPL2_1",	//HPL2_1
		"GasGap2",								//GASGAP 2
		"HPL2_2","graphite2_2", "EVA2_2", "PET2_3","PET2_4","Copper2_2",	// HPL2_2
		
		"PET_insulationBOT",							//pet insulation BOT
		"Bakelite",								//bakelite layer
		"Honeycomb_skin2_1", "Honeycomb_core2","Honeycomb_skin2_2",		//honeycomb panel BOTTOM
		"fakeBottom",								//falso layer di aria
		
		};



		std::string NomeStratiLog[Nstrati];				//ciclo per aggiungere Log a nome strati
		
		for(size_t A=0; A<Nstrati; A++) { 
		    NomeStratiLog[A]=NomeStrati[A]+"Log";
		    }



		G4Material* MatStrati[Nstrati] =				//array materiali 
		{
		
		Air,  								//falso layer di aria
		Al, AlCore ,Al,								//honeycomb panel  TOP
		PET,								//pet insulation TOP
		paper,								//layer paper

		Cu, PET,PET, EVA, Graphite, HPL,				//"Copper1_1", "PET1_1","PET1_2", "EVA1_1","graphite1_1","HPL1_1"
		RPCgas,								//GASGAP 1
		HPL, Graphite, EVA, PET, PET, Cu,				//"HPL1_2","graphite1_2", "EVA1_2", "PET1_3","PET1_4","Copper1_2"

		PET, Cu, PET,							//"PETstrip1","CuStrip", "PETstrip2"		

		Cu, PET, PET, EVA, Graphite, HPL,				//"Copper2_1", "PET2_1","PET2_2", "EVA2_1","graphite2_1","HPL2_1"		
		RPCgas,								//GASGAP 2
		HPL, Graphite, EVA, PET, PET, Cu,				// HPL2_2
		
		PET,								//pet insulation BOT
		HPL,								//bakelite layer
		Al, AlCore, Al,								//honeycomb panel BOTTOM
		Air,								//falso layer di aria

		};



		G4double spessoreStrati[Nstrati]=				//array spessori
		{

		0.01*mm,								//falso layer di aria
		0.5*mm,	5.0*mm, 0.5*mm,						//"Honeycomb_skin1_1", "Honeycomb_core1","Honeycomb_skin1_2"
		0.188*mm,							//pet insulation TOP
		1.0*mm,								//layer paper

		0.38*mm, 0.18*mm, 0.18*mm, 0.15*mm, 0.001*mm, 1.35*mm,	      	//"Copper1_1", "PET1_1","PET1_2", "EVA1_1","graphite1_1","HPL1_1"		
		fgasGapThickness,								//GASGAP 1
		1.35*mm, 0.001*mm, 0.15*mm, 0.18*mm, 0.18*mm,0.38*mm,		//"HPL1_2","graphite1_2", "EVA1_2", "PET1_3","PET1_4","Copper1_2"		

		0.2*mm, 0.17*mm, 0.2*mm,					//"PETstrip1","CuStrip", "PETstrip2"					
		
		0.38*mm, 0.18*mm, 0.18*mm, 0.15*mm, 0.001*mm, 1.35*mm,		//"Copper2_1", "PET2_1","PET2_2", "EVA2_1","graphite2_1","HPL2_1"		
		fgasGapThickness,								//GASGAP 2
		1.35*mm, 0.001*mm, 0.15*mm, 0.18*mm, 0.18*mm,0.38*mm,		//"HPL2_2","graphite2_2", "EVA2_2", "PET2_3","PET2_4","Copper2_2"		
		
		0.188*mm,							//pet insulation BOT
		2.0*mm,								//bakelite layer
		0.5*mm,	5.0*mm, 0.5*mm,						//"Honeycomb_skin2_1", "Honeycomb_core2","Honeycomb_skin2_2"
		0.01*mm,							//falso layer di aria
		
		};

		

		//volumi LOGICI
		
		std::string HPLstring="HPL";					//stringhe per controllo e assegnazione colore a volumi
		std::string Bakelitestring="Bakelite";
		std::string GasGapstring="GasGap";
		std::string PETstring="PET";
		std::string EVAstring="EVA";
		std::string Copperstring="Copper";
		std::string Honeycombstring="Honeycomb";
		std::string Graphitestring="graphite";
		std::string Fakestring="fake";



		for(G4int lyr=0;lyr<Nstrati;lyr++){				//loop per assegnare a ogni nome strato il proprio volume logico e forma e spessore

			G4Trd* strato= new G4Trd(NomeStrati[lyr],spessoreStrati[lyr]/2, spessoreStrati[lyr]/2,majorBase/2, majorBase/2, Height/2); //per invertire posizione base maggiore e minore basta invertirli nell'inserimento
			//G4Box* strato= new G4Box(NomeStrati[lyr],spessoreStrati[lyr]/2, minorBase/2,Height/2);
			G4LogicalVolume* logicStrato = new G4LogicalVolume(strato, MatStrati[lyr], NomeStratiLog[lyr]) ;


			
			if (NomeStrati[lyr].find(HPLstring)==0 or NomeStrati[lyr].find(Bakelitestring)==0) {  		//ciclo per settare colore volumi
				logicStrato->SetVisAttributes(new G4VisAttributes(*electrodeAttributes));}

			
			else if (NomeStrati[lyr].find(GasGapstring)==0) {
				logicStrato->SetVisAttributes(new G4VisAttributes(*gasAttributes));}


			else if (NomeStrati[lyr].find(PETstring)==0) {
				logicStrato->SetVisAttributes(new G4VisAttributes(*petAttributes));}


			else if (NomeStrati[lyr].find(EVAstring)==0) {
				logicStrato->SetVisAttributes(new G4VisAttributes(*evaAttributes));}


			else if (NomeStrati[lyr].find(Copperstring)==0) {
				logicStrato->SetVisAttributes(new G4VisAttributes(*cuAttributes));}

			
			else if (NomeStrati[lyr].find(Honeycombstring)==0) {
				logicStrato->SetVisAttributes(new G4VisAttributes(*honeyAttributes));}

			
			else if (NomeStrati[lyr].find(Graphitestring)==0) {
				logicStrato->SetVisAttributes(new G4VisAttributes(*graphiteAttributes));}

			
			else if (NomeStrati[lyr].find(Fakestring)==0) {
				logicStrato->SetVisAttributes(new G4VisAttributes(*fakeAttributes));}




			trdCollection.push_back(strato) ;				//mette forma volume nel vettore
		        trdLogCollection.push_back(logicStrato) ;		     	//mette ogni volume logico nel vettore
			}
 



	//VOLUMI FISICI

//-- variabile per shift rispetto a world

G4cout << "----------------------RE4-2 KODEL ------------------------------------" << G4endl ;

//G4double ZTranslation= ftrdRPosition*cos(ftrdThetaPosition*M_PI/180);	//posizione di partenza su asse z da dove posizionare primo layer
//G4double YTranslation= ftrdRPosition*sin(ftrdThetaPosition*M_PI/180);

G4double ZTranslation= ftrdRPosition*cos(ftrdThetaPosition);	//posizione di partenza su asse z da dove posizionare primo layer
G4double YTranslation= ftrdRPosition*sin(ftrdThetaPosition);


G4int cpN=1;		// indice numero strato per stampare a video informazioni

//

    for(size_t i=0 ; i<trdCollection.size() ; i++) {   		// i counts as the copyNo per loop

	ZTranslation += trdCollection.at(i)->GetXHalfLength1() ;//trasla di mezzo spessore(volume posizionato metà prima e metà dopo)(usa il segno - xchè upstream z negativa)
	G4double thickness=trdCollection.at(i)->GetXHalfLength1()*2 ;		//prende spessore del volume per stamparlo a video

      G4cout << "Volume (" << cpN << ") " << trdCollection.at(i)->GetName() << " The thickness is " << thickness << " mm" << " The mean Z position is " << G4BestUnit(ZTranslation,"Length") << " And the start Z thickness position is " << G4BestUnit((ZTranslation-(thickness/2)),"Length") << G4endl ;

      fGunXPosition         = -0.25*( worldSizeX + thickness ); //Xgunposition


      G4VPhysicalVolume* trapezoidalPhysic = new G4PVPlacement(		//crea volume fisico
	  rotationPlacement,							//rotazione
	  G4ThreeVector(0,YTranslation,ZTranslation),					//vettore posizione, varia solo posizione in Z (distanza sorgente)
	  trdLogCollection.at(i),						//nome del volume logico
	  trdCollection.at(i)->GetName(),					//nome volume fisico
	  worldLog,								//volume madre in cui posizionare
	  false,								//pmany
	  cpN,									//copia numero cpN
	  fCheckOverlaps) ;							// controllo overlap (se attivato all'inizio file)	
       
       ZTranslation += trdCollection.at(i)->GetXHalfLength1() ;			// incremento traslazione della seconda metà dello spessore
       cpN++;								//incremento indice layer  (si usa il segno - perchè upstream convenzione z è negativa)
       }

G4cout << "-------------------------------------------------------------------------" << G4endl ;


// Human Phantom
    //Define phantom sizes
	G4double phantomXSize = 30*cm;
	G4double phantomYSize = 60*cm;
	G4double phantomZSize = 50*cm;
	//Define phantom material
	G4Material* materialPhantom = G4NistManager::Instance()->FindOrBuildMaterial("G4_TISSUE_SOFT_ICRP");

    G4Box*              phantomSolid   = new G4Box("solid-Phantom",    // name
    	                                          0.5*phantomXSize,   // half x-size
    	                                          0.5*phantomYSize,  // half y-size
    	                                          0.5*phantomZSize); // half z-size
    G4LogicalVolume*    phantomLogical = new G4LogicalVolume(phantomSolid,    // solid
    													materialPhantom,  // material
                                                           "logic-Phantom"); // name
    G4VPhysicalVolume*  phantomPhyscal = new G4PVPlacement(nullptr,                 // (no) rotation
                                                          G4ThreeVector(0.,0.,0.), // translation
														  phantomLogical,           // its logical volume
                                                          "Phantom",                // its name
                                                          worldLog,            // its mother volume
                                                          false,                   // not used
                                                          0);



  return worldPhys;
}


