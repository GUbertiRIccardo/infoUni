#include <iostream> 
#include <stdlib.h>

// Include per ROOT
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1I.h>

// Programma che riempie un istogramma
int main(int argc, char **argv)
{
  // Inizializzo l'interfaccia con root (e' necessario)
  TApplication myApp("App", &argc, argv);

  // Creazione dello screen
  TCanvas *screen = new TCanvas("screen", "Funzione", 0, 0, 800, 600);

  // Creazione di un oggetto della classe TFormula
  TH1I *h = new TH1I("h", "Casuali", 10, 0., 100.);
 
  for(int i=0; i< 1000; i++)
    h->Fill( rand()%100 );

  h->SetFillColor(42);  // Colore dell'istogramma
  h->SetMinimum(0);
  h->Draw();            // Disegno

  myApp.Run();  // Passaggio del controllo a root  

  return 0;   
} 
