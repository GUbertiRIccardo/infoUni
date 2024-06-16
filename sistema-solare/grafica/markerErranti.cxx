#include <iostream> 
#include <sstream>
#include <math.h>  // Per sin e cos
#include <time.h>  // Per nanosleep

// Include per ROOT
#include <TROOT.h>
#include <TApplication.h>
#include <TView.h>
#include <TCanvas.h>
#include <TMarker.h>
#include <TText.h>

// Questo programma usa ROOT der disegnare le traiettorie 
// di un pallino e un quadratino erranti 
int main(int argc, char **argv)
{
  // Inizializzo l'interfaccia con root (e' necessario)
  TApplication myApp("App", &argc, argv);

  // Inizializzo la "tela"
  TCanvas *screen =                           // Creo una "tela" di dimensioni 800x800 
      new TCanvas("c1", "My Solar System", 0, 0, 800, 800);
  screen->SetFillColor(0);                    // Faccio lo sfondo bianco
  TView *view = TView::CreateView();          // Creo la proiezione
  view->SetRange(-400,-400,-400,400,400,400); // Definisco il range (x0,y0,z0) --> (x1,y1,z1)

  // Mi creo un TMarker e ne definisco le proprieta'
  // E' una classe che definisce makers: cerchi, triangoli, quadrati ecc
  TMarker cerchio;
  cerchio.SetMarkerStyle(20); // 20 == Cerchio
  cerchio.SetMarkerColor(2);  // 2 == Rosso
  cerchio.SetMarkerSize(2);   // Dimensione    
  cerchio.Draw();             // Lo disegno

  // Mi creo un secondo TMarker
  TMarker quad;
  quad.SetMarkerStyle(21);    // 21 == Quadratino
  quad.SetMarkerColor(3);     // 3 == Rosso
  quad.SetMarkerSize(2);      // Dimensione    
  quad.Draw();                // Lo disegno

  // Stampa di servizio
  std::cout << "Premere CTRL+C per uscire" << std::endl;

  // Per rendere visibile il movimento delle figure occorre rallentarle, 
  // per esempio aggiungendo un ritardo di 1 ms ad ogni aggiornamento 
  // Le due struct qui sotto servono come input alla funzione nanosleep()
  // utilizzata dentro il loop seguente
  // NB: le struct sono classi con tutto public  
  struct timespec ts = { 0, 10000000 }; // Seconds, nanoseconds
  struct timespec tsrem;

  float scale = 0.7;   // Fattore di scala che servira' per centrare gli oggetti

  // Faccio il loop e disegno; NB: le coordinate vanno da -1 a +1 (!!!)
  for(int i=1; ; i++) 
  {
    // Uso il metodo TPolyMarker::SetPoint(0, x, y) per definire la posizione ad ogni loop
    // Facciamo muovere il quad su una circonferenza
    quad.SetX( scale*cos(i/180.) ); 
    quad.SetY( scale*sin(i/180.) );        

    // Il cerchio su una traiettoria piu' particolare
    cerchio.SetX( scale*cos(i/90.)*sin(i/180.) );  
    cerchio.SetY( scale* sin(i/200.) ); 

    // Spostati i punti occorre aggiornare il disegno
    screen->Modified();     // notifico la modifica
    screen->Update();       // ridisegno

    nanosleep(&ts, &tsrem); // Per ridurre la velocita' dei pallini
  }  

  return 0;   
} 
