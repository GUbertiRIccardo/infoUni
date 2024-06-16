// File di evoluzione del sistema solare

#include "SistemaSolare.h"   
#include <iostream>
#include <vector>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  // Variabili per definire l'intervallo temporale in unità leggibili
  const uint64_t hour = 3600;
  const uint64_t day  = hour*24;
  const uint64_t year = day*365;

  // Creazione oggetto della classe SistemaSolare con granularità di simulazione di un'ora
  SistemaSolare s(hour);

  // Aggiunta corpi al sistema solare, utilizzando l'allocazione dinamica
  //                        nome      massa kg  Posizione m           Velocita' tangenz. m/s
  s.Add( new CorpoCeleste ("Sole",     1.98e30, Vettore(       0 ,0), Vettore(0,     0 ) ) );
  s.Add( new CorpoCeleste ("Mercurio", 3.30e23, Vettore(  57.8E9, 0), Vettore(0, 47873 ) ) );
  s.Add( new CorpoCeleste ("Venere",   4.87e24, Vettore( 108.2E9, 0), Vettore(0, 35021 ) ) );
  s.Add( new CorpoCeleste ("Terra",    5.97e24, Vettore( 149.6E9, 0), Vettore(0, 29786 ) ) );
  s.Add( new CorpoCeleste ("Marte",    6.42e23, Vettore( 227.9E9, 0), Vettore(0, 24131 ) ) );
  s.Add( new CorpoCeleste ("Giove",    1.90e27, Vettore( 778.4E9, 0), Vettore(0, 13070 ) ) );
  s.Add( new CorpoCeleste ("Saturno",  5.69e26, Vettore(1427.4E9, 0), Vettore(0,  9672 ) ) );
  s.Add( new CorpoCeleste ("Urano",    8.68e25, Vettore(2871.0E9, 0), Vettore(0,  6836 ) ) );
  s.Add( new CorpoCeleste ("Nettuno",  1.02e26, Vettore(4498.3E9, 0), Vettore(0,  5478 ) ) );

  
  // Evoluzione per n anni
  s.evolvi(10*year);

  return 0;
}
