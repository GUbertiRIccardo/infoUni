#ifndef CORPOCELESTE_H
#define CORPOCELESTE_H

#include "Vettore.h"
#include <vector>    // Sarebbe piu' corretto usare list ma ...

// Per semplificare il codice non si e' fatto uso del qualificatore const 

const double G = 6.672e-11; // Costante di gravitazione

// Classe che descrive un generico corpo celeste in termini di massa, 
// posizione e velocita' (in 2D).
class CorpoCeleste
{
 public:
  // Costruttore. Con i 4 parametri necessari per inizializzare di dati membro
  CorpoCeleste(std::string nome, double massa, Vettore pos, Vettore vel); 

  Vettore pos()      { return m_pos;  } // Ritorna Vettore posizione del corpo
  Vettore vel()      { return m_vel;  } // Ritorna Vettore velocita' del corpo
  double  massa()    { return m_massa;} // Ritorna la massa del corpo
  std::string nome() { return m_nome; } // Ritorna il nome del corpo

  // Ha lo scopo di far evolvere, in approssimazione lineare, la posizione e 
  // la velocita' del CorpoCeleste. Parametri di input:
  //  - intervallo temporale in secondi
  //  - lista di tutti i CorpiCelesti partecipanti (passato by-reference)
  // NB:
  //  - il metodo e' dichiarato "virtual" per poter supportare il polimorfismo
  //    run-time nel caso venissero create classi derivate da CorpoCeleste (es: Sonda)
  //  - si e' scelto di usare un container di puntatori invece che di oggetti 
  //    al fine di agevolare l'eventuale utilizzo del polimorfismo run-time 
  virtual void evolviDeltaT(double dT, std::vector<CorpoCeleste*> &corpi);

 protected: 
  // I dati membro sono protected invece di private perche' vogliamo che 
  // un'eventuale classe derivata (es: sonda) possa accedervi
  Vettore     m_pos;   // Posizione in m
  Vettore     m_vel;   // Velocita' in m/s
  double      m_massa; // Massa in Kg
  std::string m_nome;  // Nome del CorpoCeleste 
};

// Funzione non membro: inseritore
std::ostream& operator<<(std::ostream& o, CorpoCeleste& c);


#endif

