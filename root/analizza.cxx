#include <iostream> 
#include <iomanip>
#include <stdlib.h>

// Include per ROOT
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1I.h>
#include <TH1F.h>
#include <fstream>   

// Programma che riempie un istogramma
int main(int argc, char **argv)
{
  // Inizializzo l'interfaccia con root (e' necessario)
  TApplication myApp("App", &argc, argv);

  // Creazione dello screen
  TCanvas *screen = new TCanvas("screen", "Funzione", 0, 0, 800, 600);

  // Creazione, per allocazione dinamica, di un oggetto della classe TH1I:
  // istogramma monodimensionale con canali a contenuto intero
  TH1I *h = new TH1I("h", "Dati", 37, 80., 170.);

  // Creazione oggetto ifstream e apertura file
  std::ifstream in("Higgs4l.dat");
  
  // Legge i dati fintanto che il file e' valido
  while(1)
  {
    float x;
    in >> x;            // Lettura dato
    std::cout <<  x << std::endl;  // Scrittura tanto per ...
    if (!in.good())     // Se il file e' finito esce dal loop
      break;
    h->Fill( x );       // Aggiunta dato all'istogramma
  }

// ----> Aggiungere qui altre operazioni
  std::cout << "Entrate: " << h->GetEntries() << std::endl;
  std::cout << "Media: " << h->GetMean() << std::endl;
  std::cout << "Massimo: " << h->GetMaximum() << std::endl;
  h->SetTitle("Higgs oson"); // Titolo del grafico
  h->GetXaxis()->SetTitle("massa (GeV)");

  for (int i=1; i <= h->GetNbinsX(); i++){
	  std::cout << i << "  " << h->GetBinContent(i) << std::endl;
  }

  h->Fit("gaus", "", "", 110, 140);
// <---- Aggiungere qui altre operazioni

  // Rappresentazione grafica
  h->SetFillColor(42);  // Colore dell'istogramma
  h->Draw();            // Disegno
  myApp.Run();          // Passaggio del controllo a root  

  return 0;   
} 
