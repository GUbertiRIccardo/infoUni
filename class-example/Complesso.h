#include <math.h>
#include <iostream>

class Complesso
{
  public:
    Complesso(float r, float i);
   ~Complesso();

    float Re() { return m_re ;}
    float Im() { return m_im ;} 

    float Modulo() { return sqrt( m_re*m_re + m_im*m_im  );   }
    float Fase();

    Complesso  Con();

    void SetRe( float j) { m_re = j  ;}

    Complesso operator+(Complesso h);
    Complesso operator-(Complesso h);
    Complesso operator*(Complesso h);
    Complesso operator/(Complesso h);

  private:
    float m_re;
    float m_im;
}; 

// Dichiarazione dell'overloading della funzione di inserimento su stream
// per la classe complesso
std::ostream &operator<<(std::ostream &stream, Complesso c);
