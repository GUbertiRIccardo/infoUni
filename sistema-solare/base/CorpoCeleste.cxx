#include "CorpoCeleste.h"
#include "Vettore.h"
#include <iostream> 
#include <iomanip>

CorpoCeleste::CorpoCeleste(std::string nome, double massa, Vettore pos, Vettore vel)
  : m_nome(nome), m_massa(massa), m_pos(pos), m_vel(vel)
{;} 

void CorpoCeleste::evolviDeltaT(double dT, std::vector<CorpoCeleste*> &corpi)
{
  // Verifica dei dati: il vector di input non deve essere vuoto
  if(corpi.size()==0)
  {
    std::cerr << "WARNING: lista vuota" << std::endl;
  }
 
  // Calcolo accelerazione risultate su questo corpo celeste
  Vettore aR(0,0);                       // Vettore risultante
  for (int i=0; i<corpi.size(); i++)     // Loop sui corpi celesti
  {
    Vettore r = corpi[i]->pos() - m_pos; // Vettore distanza dall'i-esimo CorpoCeleste
    double  d = r.modulo();              // Modulo della distanza
    Vettore v = r / r.modulo();          // Versore della distanza
    
    // Protezione per evitare l'autointerazione e quindi la divisione per zero
    if (corpi[i]->nome()==m_nome)     
      continue; // Salta il calcolo e torna all'inizio del loop
    
    // Accelerazione indotta dall'interazione tra questo corpo e 
    // l'i-esimo nella lista: cioe'versore distanza per G per la masse 
    // dell'i-esimo diviso distanza al quadrato
    Vettore a = v * G * corpi[i]->massa() / (d*d);  
    
    // Sommatoria parziale delle forze agenti
    aR = aR + a;
  }
  
  m_vel = m_vel + aR * dT;     // v = v + deltaV, con deltaV = a * dT
  m_pos = m_pos + m_vel * dT;  // x = x + deltaX, con deltaX = v * dT
}

std::ostream& operator<<(std::ostream& o, CorpoCeleste& c)
{
  Vettore p = c.pos()/1.E3; 
  Vettore v = c.vel()/1.E3; 
  o << std::setw(10) << c.nome() << "\t" << p << " km\t" << v << " km/s";
  return o;
}
