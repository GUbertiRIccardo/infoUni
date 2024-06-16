#include "Vettore.h"
#include <iostream>

int main()
{
  Vettore v(1,1);
  Vettore b(1,4);
  std::cout << v.modulo() << std::endl;
  Vettore c = v + b;
  std::cout << c << std::endl;
  return 0;
}
