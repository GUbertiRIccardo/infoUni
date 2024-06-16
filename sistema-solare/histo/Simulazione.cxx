#include "SistemaSolare.h"   
#include <iostream>
#include <vector>
#include <stdint.h>
#include <stdlib.h>
#include <TCanvas.h>
#include <TApplication.h>

// Sporco trucco per pulire lo schermo in terminali unix
#define CLRSCREEN printf("\e[1;1H\e[2J");

int main(int argc, char** argv)
{
  // Controlla la linea di comando
  if(argc<4)
  {
    std::cerr << "Usage: configFile numeroAnni mode\n"; 
    std::cerr << "   configFile: file di configurazione delle condizioni iniziali\n";
    std::cerr << "   numeroAnni: anni di evoluzione\n";
    std::cerr << "   mode:       modalità di evoluzione\n";
    std::cerr << "               0 = standard \n";
    std::cerr << "               1 = con media dell'accelerazione \n";
    return 2;
  }
  char* confFile = argv[1];
  uint32_t nAnni = atoi(argv[2]);
  uint32_t mode  = atoi(argv[3]);

  // Variabili per definire l'intervallo temporale in unità leggibili
  const uint64_t hour = 3600;
  const uint64_t day  = hour*24;
  const uint64_t year = day*365;

  // Creazione oggetto della classe SistemaSolare con granularità di simulazione di un'ora
  SistemaSolare s(hour, confFile, mode);

  // Evoluzione per n anni
  s.evolvi(nAnni*year);
  
  //Inizializzo l'interfaccia con root e creo il TCanvas
  TApplication myApp("App", &argc, argv);
  TCanvas *screen = new TCanvas("c1", "My Solar System", 0, 0, 800, 800);

  // Loop infinito per poter scegliere gli istogrammi 
  std::string cmd;  // Comando
  int val;          // Valore associato al comando
  TH1I *h;          // Puntatore a istogramma
  CLRSCREEN;
  while(true)
  {
    std::cout << "============================== \n";
    s.Print();
    std::cout << "============================== \n";
    std::cout << "Inserisci: stringa intero \n";
    std::cout << "  Esempi: \n";
    std::cout << "    Pianeta 4   // cioè Pianeta indiceIstogramma \n";
    std::cout << "    list 0      // lista istogrammi disponibili  \n";
    std::cout << "    log  0/1    // scala logaritmica si/no       \n";
    std::cout << "    evo  5      // evolvi per altri 5 anni       \n";
    std::cout << "    exit 0      // per passare a root            \n";
    std::cout << "    quit 0      // Uscire dal programma          \n";
    std::cout << "______\n";
    std::cout << "prompt>";
    
    // Legge i valori
    std::cin >> cmd >> val;

		// Parsing
    if(cmd=="quit"){ break;}
    if(cmd=="log") { screen->SetLogy(val); CLRSCREEN; continue; }
    if(cmd=="list"){ CLRSCREEN; s.PrintHistos();      continue; }
    if(cmd=="evo") { s.evolvi(val*year);   CLRSCREEN; continue; }
    if(cmd=="exit"){
      std::cout << "\n\n\t\t --> Comando alla finestra di root\n";
      std::cout << "    \t\t     File->Quit per tornare al terminale\n";        
      myApp.Run(kTRUE);
      CLRSCREEN;
      std::cout << "Uscito dalla finestra di root\n";
      continue; 
    }
    
		TH1I *h = s.getThisHisto(cmd, val);
    if(h==NULL)
      { std::cerr << "Pianeta non riconosciuto\n"; continue; }

    h->SetFillColor(41);
    h->Draw();
    screen->Modified();    
    screen->Update();
    CLRSCREEN;
  }

	std::cout << "Ciao, alla prossima" << std::endl;
  return 0;
}
