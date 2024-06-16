#include "StudenteTriennale.h"
#include "StudenteMagistrale.h"
#include <iostream>


int main() 
{
  StudenteTriennale a("AAAA", 12345678, 2004);
  a.esameSuperato(28);
  a.esameSuperato(28);
  a.esameSuperato(30);
  a.changeMatr(87654321);
  std::cout << a << std::endl;  
  
  StudenteMagistrale b("AAAA", 12345678, 2004, "Materia");
  b.esameSuperato(28);
  b.esameSuperato(28);
  b.esameSuperato(30);
  b.changeMatr(87654321);
  std::cout << b << std::endl;
  return 0;  
} 
