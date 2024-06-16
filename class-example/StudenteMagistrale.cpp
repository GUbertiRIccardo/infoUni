#include <string>
#include <iostream>
#include <vector>
#include "StudenteTriennale.h"
#include "StudenteMagistrale.h"

StudenteMagistrale::StudenteMagistrale(std::string nome, int matr, int anno, std::string curriculum) : StudenteTriennale(nome, matr, anno){
m_nome = nome;
m_matricola = matr;
m_anno = anno;
m_curriculum = curriculum;
}

std::ostream& operator<<(std::ostream& o, StudenteMagistrale& stud)
{
  o << stud.getNome() << " #" << stud.getMatr() << " Avg: " << stud.getAvg() << " Curriculum: " << stud.getCurr() ;
  return o;
}
