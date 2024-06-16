// Implementazione metodi della classe base

#include <string>
#include <iostream>
#include <vector>
#include "StudenteTriennale.h"

StudenteTriennale::StudenteTriennale(std::string nome, int matr, int anno){
m_nome = nome;
m_matricola = matr;
m_anno = anno;
}


void  StudenteTriennale::esameSuperato(int voto)
{
  m_voti.push_back(voto);
}

float StudenteTriennale::getAvg(){
	float s=0.;
	for (int i=0 ; i < m_voti.size(); i++){
		s += float(m_voti[i]);
	}
	return (s/float(m_voti.size()));
}

void StudenteTriennale::changeMatr(int matr){
	m_matricola = matr;
}


// Overloading dell'operatore di inserimento con parametro della classe StudenteTriennale
std::ostream& operator<<(std::ostream& o, StudenteTriennale& stud)
{
  o << stud.getNome() << " #" << stud.getMatr() << " Avg: " << stud.getAvg() ;
  return o;
}

