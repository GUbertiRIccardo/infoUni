// Classe che descrive un Vettore in due dimensioni
// Servira' nella simulazione del sistema solare (in 2D), dove verra' utilizzato 
// per descrivere posizione e velocita' del pianeta e per calcolare la forza 
// gravitazionale. A tale scopo e' necessario poter eseguire le seguenti operazioni:
//  - calcolo del modulo   (calcolo attrazione gravitazionale)
//  - calcolo del versore  (calcolo attrazione gravitazionale)
//  - somma e sottrazione di Vettori (calcolo della risultate delle forze)
//  - prodotto e divisione di un Vettore per un numero (calcolo attrazione gravitazionale)


// Le istruzioni di precompilazione seguenti sono necessarie quando in un progetto con piu'
// file la catena di #include dovesse portare ad includere piu' volte lo stesso header 
// durante la compilazione di un file sorgente (.cxx). In tal caso il compilatore potrebbe
// vedere piu' volte la dichiarazione di una stessa funzione o classe e darebbe errore.
// Le istruzioni seguenti servono ad assicurarsi che il compilatore passi solo una volta
// da questo file header. Infatti la prima volta che il preprocessore ci passa l'etichetta
// CORPOCELESTE_H non e' definita (#ifndef == if not defined) e quindi continua processando
// le righe seguenti fino ad #endif. Ora l'instruzione #define definisce l'etichetta
// CORPOCELESTE_H e quindi in caso di una seconda inclusione il blocco #ifndef-#endif 
// saltato. 


// Le istruzioni di precompilazione seguenti sono necessarie per assicurarsi che il compilatore
// non processi piu' volte le stesse dichiarazioni, eventualita' che porterebbe ad un errore
// del tipo "redefinition of function ....". La deinizione dell'etichetta CORPOCELESTE_H
// assicura che le istruzione contenute tra #ifndef ed #endif siano incluso una volta sola
#ifndef VETTORE_H   // NB: deve essere chiuso da un corrispettivo #endif!! Vedi sotto
#define VETTORE_H

#include <math.h>    // per sqrt()
#include <iostream>  

// Classe che descrive un Vettore in due dimensioni
class Vettore
{
  public:
    Vettore();                   // Costuttore che crea Vettore (0,0)
    Vettore(double x, double y); // Costuttore che crea Vettore (x,y)

    double x() { return m_x; }   // Ritorna la coordinata x
    double y() { return m_y; }   // Ritorna la coordinata y

    double modulo()              // Ritorna il modulo del Vettore
       { return sqrt(m_x * m_x + m_y * m_y); }

    Vettore operator+(const Vettore& v); // Somma di vettori 
    Vettore operator-(const Vettore& v); // Differenza di vettori
    Vettore operator*(const double c);   // Prodotto di un Vettore per un numero
    Vettore operator/(const double c);   // Divisione di un Vettore per un numero

  private:
    double m_x;  // Dato membro che rappresenta la prima coordinata
    double m_y;  // Dato membro che rappresenta la seconda coordinata
};

// Funzione non membro: inseritore
std::ostream& operator<<(std::ostream& o, Vettore& v);

#endif
