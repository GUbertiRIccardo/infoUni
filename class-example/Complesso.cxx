#include "Complesso.h"
#include <iostream>

Complesso::Complesso(float r, float i)
{
  //std::cout << "Sono il costruttore con " << r << " e " << i << std::endl;
  m_re = r;
  m_im = i;
}

Complesso::~Complesso()
{
  //std::cout << "Sono il distruttore con " <<  m_re << " e " << m_im << std::endl;
}

Complesso  Complesso::Con()
{
  Complesso t(m_re, - m_im);
  return t;
}

Complesso Complesso::operator+(Complesso h)
{
  float r = m_re + h.m_re;
  float i = m_im + h.Im();
  Complesso t(r, i);
  return   t;
}

Complesso Complesso::operator-(Complesso h)
{
  return Complesso(m_re - h.m_re,  m_im - h.m_im);
}

Complesso Complesso::operator*(Complesso h)
{
  float r = m_re * h.m_re - m_im * h.m_im ;
  float i = m_im * h.m_re + m_re * h.m_im ;
  return Complesso(r, i);
}

float Complesso::Fase()
{
  if(m_re>0) 
    return atan(m_im/m_re);  // NB: se passa qui, non prosegue sotto
  if(m_re<0)
    return atan(m_im/m_re) + M_PI;

  // Se siamo qui vuol dire che a==0  
  return M_PI_2;  
}

std::ostream &operator<<(std::ostream &stream, Complesso c)
{
  stream << "[" << c.Re() << ", " << c.Im() << "i]";
  return stream;
}

