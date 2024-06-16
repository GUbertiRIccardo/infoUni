#include "Vettore.h"
#include <iomanip>  // Per la formattazione di ostream

Vettore::Vettore()
{
  m_x = m_y = 0;
}

Vettore::Vettore(double x, double y)
{
  m_x = x;
  m_y = y;
}

Vettore Vettore::operator+(const Vettore& v) 
{
  return Vettore( m_x + v.m_x, m_y + v.m_y);
}
  
Vettore Vettore::operator-(const Vettore& v) 
{
  return Vettore( m_x - v.m_x, m_y - v.m_y );
}

Vettore Vettore::operator/(const double c) 
{
  return Vettore( m_x/c, m_y/c );
}

Vettore Vettore::operator*(const double c) 
{
  return Vettore( m_x*c, m_y*c);
}


// Funzione non membro inseritore <<
// Per la formattazione Vengono utilizzate le funzioni definite in <iomanip> 
std::ostream& operator<<(std::ostream& o, Vettore& v) 
{
  o.setf(std::ios::showpos);  // Forza la scrittura di + e - davanti ad un numero
  o << std::scientific;       // Scelta della notazione scientifica
  o << std::setprecision(4);  // Definizione della precisione
  o << "(" 
    << std::setw(10) << v.x() << ", "  // Stampa la x su una cella di 10 caratteri
    << std::setw(10) << v.y() << ")";  // Stampa la y su una cella di 10 caratteri
  return o;
}
