#include "SistemaSolare.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>

// Nel costruttore i dati membro possono essere anche inizializzati con la sintassi 
// mostrata: cioè un ":" seguito da una lista di espressioni del tipo X(Y), che 
// equivalgono ad assegnare Y a X. Cioe' l'espessione m_dT(dt) e' equivalente a m_dT = dt
SistemaSolare::SistemaSolare(uint32_t dT) 
   : m_dT(dT), m_t(0)
{
  std::cout << "Costruttore di SistemaSolare" << std::endl;
} 
  
void SistemaSolare::evolviDeltaT()
{
  // Evoluzione di un corpo alla volta per un intervallo dT
  for( int i=0; i < m_corpi.size(); i++ ) 
  {
    m_corpi[i]->evolviDeltaT(m_dT, m_corpi);
  }

  m_t += m_dT;  // Incremento del contatore temporale
}

void SistemaSolare::evolvi(uint64_t t)
{
  // Loop principale del programma. Chiama ripetutamente il metodo di 
  // evoluzione linearizzata fino a che non finisce il tempo programmato.
  // Eventualmente stampa la posizione dei pianeti ogni tot passi
  // E' all'interno di questo loop che va chiamata l'eventuale libreria grafica
  for(uint64_t s=0; s < t; s += m_dT)
  {
    evolviDeltaT();

    // Stampa i dati ogni 1000 volte la granularita'
    if(s % (m_dT*1000) == 0 )
      Print();
  }  
}


void SistemaSolare::Print()
{
  std::cout << "Day " << m_t/(3600*24) << std::endl;
  for (int i=0; i < m_corpi.size(); i++) 
  { 
    std::cout << *m_corpi[i] << std::endl; 
  }
}  
