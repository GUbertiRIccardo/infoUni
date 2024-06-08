#include "Complesso.h"
#include <iostream>

int main()
{
  Complesso a(0, 4);
  Complesso b(3, 0);


  Complesso c = a + b;  // Complesso c = a.operator+(b);

  std::cout << "a+b= " << c << std::endl;

  std::cout << "a-b= " << a -b  << std::endl;

  Complesso z = a*b;
  std::cout << "a*b= " << z  << std::endl;
  
  std::cout << "Fase di a = " << a.Fase()  << std::endl;

  return 0;
}

