#include "Complesso.h"
#include <iostream>
Complesso::Complesso(float re, float im){
	std::cout << "Costruttore di [" << re << ","
	<< im << "i]" << std::endl;
	m_re = re; // Assegnazione di re ad m_re
	m_im = im; // Assegnazione di im ad m_im
}

Complesso::~Complesso(){
	std::cout << "Distruttore di [" << m_re << ","
	<< m_im << "i]" << std::endl;
} 
