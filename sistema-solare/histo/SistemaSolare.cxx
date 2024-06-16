#include "SistemaSolare.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>

// Nel costruttore i dati membro possono essere anche inizializzati con la sintassi 
// mostrata: cioè un ":" seguito da una lista di espressioni del tipo X(Y), che 
// equivalgono ad assegnare Y a X. Cioe' l'espessione m_dT(dt) e' equivalente a m_dT = dt
SistemaSolare::SistemaSolare(uint32_t dT, std::string inputFile, uint32_t mode)
   : m_dT(dT), m_file(inputFile), m_t(0)
{
  std::cout << "Costruttore di SistemaSolare" << std::endl;
  CorpoCeleste::setMode(mode);
  std::cout << "Settato modo = " << mode << std::endl;
  readConfigFile();
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
  uint64_t y = m_t/(3600*24*365);
  uint64_t d = m_t/(3600*24);
  std::cout << "Year " << y << "\tDay " << d%365 << std::endl;
  for (int i=0; i < m_corpi.size(); i++) 
  { 
    std::cout << *m_corpi[i] << std::endl; 
  }
}  


TH1I* SistemaSolare::getThisHisto(std::string nomeCorpo, uint32_t indice)
{
  nomeCorpo = nomeCorpo.substr(0,3); // Cerchiamo solo le prime 3 lettere
  for(auto p : m_corpi)
    if (p->nome().find(nomeCorpo)==0)
      return p->getHisto(indice);
  return NULL;
}

void SistemaSolare::PrintHistos()
{
  uint32_t idx=nCorpi()-1;
  CorpoCeleste *p = m_corpi[1];
  std::cout << std::noshowpos;
  for(int i=0; i<p->numHistos(); i++)
    std::cout << "\t" << i << "\t-> " << p->getHisto(i)->GetName() << std::endl;
}

void SistemaSolare::readConfigFile()
{
  std::ifstream in(m_file);
  if( in.fail() )
  {
    std::cerr << "File " << m_file << " non trovato\n";
    exit(3);
  }
  
	std::string line;
  while (std::getline(in, line))
  {
    std::cout << line << std::endl;

		// Skip comment and empty lines
    if( line.find("#") == 0 ) continue;
    if( line.size()    == 0 ) continue;

    std::istringstream iss(line);
    std::string n;
    float m, x, y, vx, vy;
    iss >> n >> m >> x >> y >> vx >> vy;
    Add( new CorpoCeleste (n, m, Vettore( x, y ), Vettore( vx, vy ) ) );
  }
  in.close();
}
