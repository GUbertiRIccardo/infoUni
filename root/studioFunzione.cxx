#include <iostream> 
#include <iomanip>
#include <stdlib.h>
#include <cstdlib> 

// Include per ROOT
#include <TApplication.h>
#include <TCanvas.h>
#include <TF1.h>
#include <fstream>   

// Programma che riempie un istogramma
int main(int argc, char **argv)
{
  // Inizializzo l'interfaccia con root (e' necessario)
  TApplication myApp("App", &argc, argv);

  // Creazione dello screen
  TCanvas *screen = new TCanvas("screen", "Funzione", 0, 0, 800, 600);

  // Creazione di un oggetto della classe TFI:
  //     http://root.cern.ch/root/html534/TF1.html
  TF1 funz("funz", argv[1], atoi(argv[2]), atoi(argv[3]));
  
  // Chiamata del metodo che disegna la funzione
  funz.Draw();

// ----> Aggiungere qui altre operazioni
std::cout << funz.Eval(3.13, 0, 0) << std::endl;
std::cout << funz.GetMaximum() << std::endl;
std::cout << funz.GetMaximumX(5, 10) << std::endl;

for (int i=0; i<10; i++){
std::cout << funz.GetRandom(-5., 5.) << std::endl;
}

std::cout << funz.Integral(0,10) << std::endl;
//funz.DrawDerivative();
// <---- Aggiungere qui altre operazioni

  // Rappresentazione grafica
  myApp.Run();          // Passaggio del controllo a root  

  return 0;   
} 
