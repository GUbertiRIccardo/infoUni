#ifndef SISTEMASOLARE_H
#define SISTEMASOLARE_H

#include "CorpoCeleste.h"
#include <vector>
#include <stdint.h>

class SistemaSolare
{
 public:
  // Costruttore. I due parametri sono la granularita' e la durata dell'evoluzione. 
  // Il sistema viene creato vuoto, i CorpiCelesti sono inseriti in seguito con il 
  // metodo "Add()".
  SistemaSolare(uint32_t dT);

  // Numero corpi nel sistema
  uint32_t nCorpi() { return m_corpi.size(); }

  // Evoluzione di tutti i corpi del sistema per un intervallo delta T
  void evolviDeltaT();
  
  // Evoluzione del sistema solare per il tempo t in secondi
  // Richiama in loop il metodo evolviDeltaT() 
  void evolvi(uint64_t t);

  // Stampa su terminale della posizione attuale dei corpi celesti
  void Print();

  // Metodo per aggiungere un nuovo CorpoCeleste nel sistema
  void Add(CorpoCeleste *corpo)  { m_corpi.push_back(corpo); };

 private:
  uint32_t                    m_dT;    // Granularita' temporale
  uint64_t                    m_t;     // Contatore del tempo di evoluzione
  std::vector<CorpoCeleste*>  m_corpi; // Container corpi celesti
};

#endif
