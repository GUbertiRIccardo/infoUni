#ifndef STUDENTE_MAG_H
#define STUDENTE_MAG_H

#include <string>
#include <iostream>
#include <vector>
#include "StudenteTriennale.h"

// Classe derivata
class StudenteMagistrale: public StudenteTriennale{
	public:
		StudenteMagistrale(std::string nome, int matr, int anno, std::string curriculum);
		std::string getCurr(){return m_curriculum ;}

	private:
		std::string m_curriculum;
};

std::ostream& operator<<(std::ostream& o, StudenteMagistrale& stud);


#endif
