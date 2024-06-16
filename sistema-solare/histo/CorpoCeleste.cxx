#include "CorpoCeleste.h"
#include "Vettore.h"
#include <iostream> 
#include <iomanip>

uint32_t CorpoCeleste::s_mode = 0;

CorpoCeleste::CorpoCeleste(std::string nome, double massa, Vettore pos, Vettore vel)
  : m_nome(nome), m_massa(massa), m_pos(pos), m_vel(vel),
    m_pos0(pos), m_steps(0)
{
  // Il costruttore chiama inizializzazione degli istogrammi
  initializeHistos();
} 


Vettore CorpoCeleste::calcoloAccel(double dT, std::vector<CorpoCeleste*> &corpi, Vettore pos)
{
  Vettore aR(0,0);                       // Vettore risultante
  for (int i=0; i<corpi.size(); i++)     // Loop sui corpi celesti
  {
    Vettore r = corpi[i]->pos() - pos;   // Vettore distanza dall'i-esimo CorpoCeleste
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
  return aR;
}

void CorpoCeleste::evolviDeltaT(double dT, std::vector<CorpoCeleste*> &corpi)
{
  // Verifica dei dati: il vector di input non deve essere vuoto
  if(corpi.size()==0)
  {
    std::cerr << "WARNING: lista vuota" << std::endl;
  }

  // Aggiorna contatore del numero di chiamate
  m_steps++;

  // Salva la distanza da m_pos0 prima dell'update
  float distOld = (m_pos - m_pos0).modulo();

  switch(s_mode)
  {
    case 0:  
    {
      Vettore aR = calcoloAccel(dT, corpi, m_pos);
      m_vel = m_vel + aR * dT;     // v = v + deltaV, con deltaV = a * dT
      m_pos = m_pos + m_vel * dT;  // x = x + deltaX, con deltaX = v * dT
      break;
    }  
    case 1: 
    {
      Vettore vOld = m_vel;
      Vettore aOld = calcoloAccel(dT, corpi, m_pos); 
      Vettore pExp = m_pos + m_vel * dT;
      Vettore aExp = calcoloAccel(dT, corpi, pExp);
      m_vel = m_vel + (aOld + aExp) * 0.5 * dT;
      m_pos = m_pos + (m_vel + vOld) * 0.5 * dT;
      break;
    }
    default:
      std::cerr << "Modo " << s_mode << " non conosciuto. Mi suicido\n";
      exit(2);
  }

  // Calcolo quantita' interessanti per il moto
  CorpoCeleste* sole = corpi[0];   // NB
  if(sole->nome() != "Sole")
    std::cerr << "WARNING: il primo corpo non è il sole, ma " 
              << sole->nome() << std::endl;

  float distDalSole = (m_pos - sole->pos()).modulo();
  float distDaPosIn = (m_pos - m_pos0).modulo(); 

  // Calcolo energia cinetica e potenziale (assumendo m_Sole >> m_Pianeta)
  float Ecin = 0.5*m_massa*m_vel.modulo()*m_vel.modulo(); 
  float Epot = -G * sole->massa() * m_massa / m_pos.modulo();
  float Emec = Ecin + Epot;

  // L = r x mv  -> L/m = r x v
  // Se i due vettori giacciono sul piano x,y, allora
  //   L1 = 0; L2 = 0; L3 = r1*v2 - r2*v1
  float L3_m = m_pos.x()*m_vel.y() -  m_pos.y()*m_vel.x(); 

  double mu = G * 1.989E30;
  double h2  = L3_m*L3_m;
  double num = 2 * h2 * Emec/m_massa;
  double den = mu * mu;
  double e = sqrt(1+num/den);

  // Riempimento degli istogrammi
  m_histos[0]->Fill( m_pos.modulo() );                 // Dist da orig
  m_histos[1]->Fill( distDalSole );                    // Dist dal Sole
  m_histos[2]->Fill( m_pos.x() );                      // X
  m_histos[3]->Fill( m_pos.y() );                      // Y
  m_histos[4]->Fill( distDaPosIn );                    // Dist da pos iniz
  m_histos[5]->Fill( L3_m );                           // Momento angolare
  m_histos[6]->Fill( Emec );                           // Enercia meccanica
  m_histos[7]->Fill( e );                              // Eccentricità
  m_histos[8]->Fill( m_pos.x(), m_pos.y() );           // Traiettoria   
  m_histos[9]->Fill( m_pos.modulo(), m_vel.modulo() ); // Vel vs dist
  m_histos[10]->Fill(m_vel.modulo());                  // Modulo velocità

}



void CorpoCeleste::initializeHistos()
{
  std::cout << "Inizializzo gli istogrammi di " << m_nome << std:: endl;
  int numBins = 400;
  std::string s;
 
  // Variabili utili per riempire gli istogrammi
  float d    = m_pos.modulo();
  float v    = m_vel.modulo();
  float Ecin = 0.5*m_massa*m_vel.modulo()*m_vel.modulo(); 
  float Epot = -G * 1.98e30 * m_massa / m_pos.modulo();    // FIXME
  float Emec = Ecin + Epot;

  // NB: le frazioni usate nei costruttori qui sotto servono per centrare
  //     l'istogramma rispetto al valore atteso

  // Histo 0
  s = m_nome + ": Distanza da (0,0)";
  m_histos.push_back(
    reinterpret_cast<TH1I*> ( new TH1I(s.c_str(), s.c_str(), numBins, d*4/5, d*6/5) ) );
  
  // Histo 1
  s = m_nome + ": Distanza dal Sole";
  m_histos.push_back(
    reinterpret_cast<TH1I*> ( new TH1I(s.c_str(), s.c_str(), numBins, d*4/5, d*6/5) ) );

  // Histo 2
  s = m_nome + ": X";
  m_histos.push_back(
    reinterpret_cast<TH1I*> ( new TH1I(s.c_str(), s.c_str(), numBins, -d*3/2, d*3/2) ) );

  // Histo 3
  s = m_nome + ": Y";
  m_histos.push_back(
    reinterpret_cast<TH1I*> ( new TH1I(s.c_str(), s.c_str(), numBins, -d*3/2, d*3/2) ) );
  
  // Histo 4
  s = m_nome + " dist. pos. iniziale";
  m_histos.push_back(
    reinterpret_cast<TH1I*> ( new TH1I(s.c_str(), s.c_str(), numBins, -d*0.01, 2.1*d) ) );

  // Histo 5
  s = m_nome + ": momento angolare (r x v)";
  float L_att = m_pos.modulo() * m_vel.modulo();
  m_histos.push_back(
    reinterpret_cast<TH1I*> ( new TH1I(s.c_str(), s.c_str(), numBins, L_att*49/50, L_att*51/50) )
  );

  // Histo 6
  s = m_nome + ": energia meccanica"; //NB e' negativa!!!
  m_histos.push_back(
    reinterpret_cast<TH1I*> ( new TH1I(s.c_str(), s.c_str(), numBins, Emec*51/50, Emec*49/50) )
  );
  
  // Histo 7
  s = m_nome + ": eccentricita'"; //NB e' negativa!!!
  m_histos.push_back(
    reinterpret_cast<TH1I*> ( new TH1I(s.c_str(), s.c_str(), numBins, 0, 0.4) )
  );

  // Histo 8
  s = m_nome + ": X vs Y";
  m_histos.push_back( reinterpret_cast<TH1I*>
                        ( new TH2I(s.c_str(), s.c_str(), numBins, -d*3/2, d*3/2,
                                                         numBins, -d*3/2, d*3/2) ) );
  // Histo 9
  s = m_nome + ": |vel| vs |dist|";
  m_histos.push_back( reinterpret_cast<TH1I*>
                        ( new TH2I(s.c_str(), s.c_str(), numBins, d*99/100, d*102/100,
                                                         numBins, v*98/100, v*101/100) ) );
  // Histo 10
  s = m_nome + ": |V|";
  m_histos.push_back(
    reinterpret_cast<TH1I*> ( new TH1I(s.c_str(), s.c_str(), numBins, v*1/2, 2*v) ) );
}


// Ritorna l'istogramma all'indice index del vector
TH1I* CorpoCeleste::getHisto(uint32_t index)
{ 
  if( index >= m_histos.size() ) 
    return NULL;            // Ritorna NULL se l'indice è fuori range
  return m_histos[index];   // Altrimenti l'elemento a indice = index
}




std::ostream& operator<<(std::ostream& o, CorpoCeleste& c)
{
  Vettore p = c.pos()/1.E3; 
  Vettore v = c.vel()/1.E3; 
  o << std::setw(10) << c.nome() << "\t" << p << " km\t" << v << " km/s";
  return o;
}
