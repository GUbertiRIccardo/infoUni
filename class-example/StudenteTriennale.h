#ifndef STUDENTE_TRI_H
#define STUDENTE_TRI_H

#include <string>
#include <iostream>
#include <vector>

// Classe base
class StudenteTriennale
{
  public:
    // Costruttori
    StudenteTriennale(std::string nome, int matr, int anno);
    
  
  
    // Metodi di accesso in lettura ai dati membro
    std::string  	getNome()  { return m_nome; }
    int     		getMatr()  { return m_matricola; }
    float    		getAvg();
    	
    // Metodo che inserisce un nupvo voto nella lista dei voti (m_voti) 
    void  	esameSuperato(int voto);
    void 	changeMatr(int matr); 

  protected:
    std::string      	m_nome;      // Cognome dello studente       
    int              	m_matricola; // Numero di matricola
    int              	m_anno;      // Anno di corso
    std::vector<int> 	m_voti;      // Voti
};

std::ostream& operator<<(std::ostream& o, StudenteTriennale& stud);
#endif

