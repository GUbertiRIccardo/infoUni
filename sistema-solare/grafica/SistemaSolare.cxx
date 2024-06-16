#include "SistemaSolare.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>

//>>>>>>>>> INIZIO BLOCCO AGGIUNTIVO PER LA GRAFICA >>>>>>>>>>>>>>
#include <TCanvas.h>
#include <TView.h>
#include <TMarker.h>
#include <time.h>
//<<<<<<<<< FINE BLOCCO AGGIUNTIVO PER LA GRAFICA <<<<<<<<<<<<<<<<


// Nel costruttore i dati membro possono essere anche inizializzati con la sintassi 
// mostrata: cioè un ":" seguito da una lista di espressioni del tipo X(Y), che 
// equivalgono ad assegnare Y a X. Cioe' l'espessione m_dT(dt) e' equivalente a m_dT = dt
SistemaSolare::SistemaSolare(unsigned int dT) 
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

void SistemaSolare::evolvi(unsigned long long t)
{

//>>>>>>>>> INIZIO BLOCCO AGGIUNTIVO PER LA GRAFICA >>>>>>>>>>>>>>
  // In prima approssimazione aggiungiamo tutta la grafica all'interno del metodo evolvi()
  // In una seconda fase potrebbe essere opportuno creare dei dati membro (es: per screen
  // e il vettore di TMarker) e spostare le inizializzazioni del costruttore

  // Creazione del canvas per disegnare i pianeti
  TCanvas *screen = new TCanvas("c1", "My Solar System", 0, 0, 800, 800);
  screen->SetFillColor(1);                    // Background nero
  TView *view = TView::CreateView();          // Creo la proiezione
  view->SetRange(-400,-400,-400,400,400,400); // Definisco il range (x0,y0,z0) --> (x1,y1,z1)
 
  // Creazione di un TMarker per ogni CorpoCeleste.
  // Sara' ospitato in un vettore di TMarker gemello di m_corpi
  std::vector<TMarker*> markers;

  // Loop sui CorpoCeleste della classe
  //   - Creazione di un nuovo Marker per ogni CorpoCeleste
  //   - Inizializzazione di colore e dimensione
  //   - Indentificazione del pianeta più lontano (massima distanza dall'origine)
  float massimo = 0.;
  for( int i=0; i<m_corpi.size(); i++ )
  {
    TMarker *m = new TMarker;
    m->SetMarkerStyle(20);   // 20 == Cerchio
    m->SetMarkerColor(2+i);  // Colore diverso per ogni CorpoCeleste (NB 1==nero)

    // Associo una ragionevole dimensione grafica al marker di ogni Corpo
    float dim = 0.2*( log10( m_corpi[i]->massa()) -20 );
    if (dim <0) dim = .5; 
    m->SetMarkerSize(dim);

    m->Draw();             // Poniamo il marker sulla tela
    markers.push_back(m);  // Aggiungiamo il marker al vettore di markers

    // Indentificazione della massima distanza iniziale
    Vettore p = m_corpi[i]->pos();
    if( p.x() > massimo) massimo = p.x();
    if( p.y() > massimo) massimo = p.y();
  }
//<<<<<<<<< FINE BLOCCO AGGIUNTIVO PER LA GRAFICA <<<<<<<<<<<<<<<<


  // Loop principale del programma. Chiama ripetutamente il metodo di 
  // evoluzione linearizzata fino a che non finisce il tempo programmato.
  // Eventualmente stampa la posizione dei pianeti ogni tot passi
  // E' all'interno di questo loop che va chiamata l'eventuale libreria grafica
  for(unsigned long long s=0; s < t; s += m_dT)
  {
    evolviDeltaT();

    if(s % (m_dT*100) == 0 )
      Print();

//>>>>>>>>> INIZIO BLOCCO AGGIUNTIVO PER LA GRAFICA >>>>>>>>>>>>>>
    // Per ogni corpo:
    //  - prendo le coordinate x,y
    //  - aggiorno la posizione del Marker corrispondente
    //    tenendo presente che le coordinate grafiche vanno da -1 a 1
    //    e quindi occorre riscalare le distanze sulla distanza massima
    //    in gioco (variabile massimo calcolata in precedenza)
    for(int i=0; i < m_corpi.size(); i++)
    {
      Vettore pos = m_corpi[i]->pos();
      float x = 0.8 * pos.x() / massimo; // Lo 0.8 e' per avere un po' di margine
      float y = 0.8 * pos.y() / massimo;
      markers[i]->SetX(x);
      markers[i]->SetY(y);
    }

    // Spostati i punti occorre aggiornare il disegno
    screen->Modified();     // notifico la modifica
    screen->Update();       // ridisegno
   
    // Ritardo il tutto di qualche ms per non impallare il PC
    struct timespec ts = { 0, 10000000 }; // Seconds, nanoseconds
    struct timespec tsrem;
    nanosleep(&ts, &tsrem);
//<<<<<<<<< FINE BLOCCO AGGIUNTIVO PER LA GRAFICA <<<<<<<<<<<<<<<<

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



