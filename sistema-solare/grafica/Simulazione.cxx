// File di evoluzione del sistema solare

#include "SistemaSolare.h"   
#include <iostream>
#include <vector>

//>>>>>>>>> INIZIO BLOCCO AGGIUNTIVO PER LA GRAFICA >>>>>>>>>>>>>>
#include <TApplication.h>
//<<<<<<<<< FINE BLOCCO AGGIUNTIVO PER LA GRAFICA <<<<<<<<<<<<<<<<


int main(int argc, char** argv)
{ 
  // Variabili per definire l'intervallo temporale in unità leggibili
  unsigned long long hour = 3600;
  unsigned long long day  = hour*24;
  unsigned long long year = day*356;

//>>>>>>>>> INIZIO BLOCCO AGGIUNTIVO PER LA GRAFICA >>>>>>>>>>>>>>
  //Inizializzo l'interfaccia con root (e' necessario)
  TApplication myApp("App", &argc, argv);
//<<<<<<<<< FINE BLOCCO AGGIUNTIVO PER LA GRAFICA <<<<<<<<<<<<<<<<

  // Creazione oggetto della classe SistemaSolare con granularità di simulazione di un'ora
  SistemaSolare s(6*hour);

  // Aggiunta corpi:        nome        massa     Posizione          Velocita' tangenziale
  s.Add( new CorpoCeleste ("Sole",     1.98e30, Vettore(      0 ,0), Vettore(0,     0 ) ) );
  s.Add( new CorpoCeleste ("Mercurio", 3.30e23, Vettore( 57.8E9, 0), Vettore(0, 47873 ) ) );
  s.Add( new CorpoCeleste ("Venere",   4.87e24, Vettore(108.2E9, 0), Vettore(0, 35021 ) ) );
  s.Add( new CorpoCeleste ("Terra",    5.97e24, Vettore(149.6E9, 0), Vettore(0, 29786 ) ) );
  s.Add( new CorpoCeleste ("Marte",    6.42e23, Vettore(227.9E9, 0), Vettore(0, 24131 ) ) );
  s.Add( new CorpoCeleste ("Giove",    1.90e27, Vettore(778.4E9, 0), Vettore(0, 13070 ) ) );
  
  // Evoluzione per 10 anni
  s.evolvi(10*year);

  return 0;
}
