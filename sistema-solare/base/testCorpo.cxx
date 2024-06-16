// File di validazione della classe CorpoCeleste
// Si crea Sole e Terra nelle opportune posizioni iniziali
// e si verifica che il moto abbia il periodo corretto

#include "Vettore.h"
#include "CorpoCeleste.h"   
#include <iostream>
#include <vector>
#include <stdint.h>

int main()
{  
  // Creazione del Sole nell'origine e la Terra a 149 di km sull'asse x 
  // e velocita' orbitale in direzione tangenziale (asse y)
  CorpoCeleste s("Sole",  1.98e30, Vettore(0      , 0), Vettore(0,      0) );
  CorpoCeleste t("Terra", 5.97e24, Vettore(149.6E9, 0), Vettore(0, 29.8E3) );
 
  // Container di puntatori a CorpoCeleste
  std::vector<CorpoCeleste*> corpi;
  corpi.push_back(&s); // Aggiunge l'indirizzo dell'oggetto s al container 
  corpi.push_back(&t); // Aggiunge l'indirizzo dell'oggetto t al container 

  // Evoluzione del sistema per un'anno con un deltaT di un'ora
  uint32_t hour = 3600;
  uint32_t day  = hour*24;
  uint32_t year = day*365;
  for(uint32_t i=0; i < year; i+=hour)
  {
    t.evolviDeltaT(hour, corpi);  // Evoluzione lineare dell'oggetto Terra per un'ora
    if( i % (day*7) == 0 )          // Stampa della posizione ogni settimana
      std::cout << i/day << " gg\t" << t << std::endl;
  }
  return 0;
}
