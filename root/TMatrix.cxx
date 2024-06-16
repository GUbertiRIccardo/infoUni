#include <iostream> 
#include <stdlib.h>
#include <time.h>

#include <TMatrix.h>

// Esercizio sulla classe TMatrixF.
// L'interfaccia della classe e' disponibile online nelle pagine di documentazione
// della classe TMatrixF e della sua class base TMatrixTBase (cioe' i metodi pubblici
// della classe base sono ovviamente metodi anche della classe derivata):
//  - https://root.cern.ch/root/html/TMatrixT_float_.html
//  - https://root.cern.ch/root/html/TMatrixTBase_float_.html

int main(int argc, char **argv)
{
  // Creazione matrice TMatrixF (F=float) di dimensione 3x3
  TMatrixF m(3,3);  

  // Riempimento matrice tramite operator(float i, float j)
  m(0,0)=1.;  m(0,1)=2.;   m(0,2)=3.;
  m(1,0)=0.;  m(1,1)=1.;   m(1,2)=4.;
  m(2,0)=5.;  m(2,1)=6.;   m(2,2)=0.;

  // Stampa della matrice su terminale
  m.Print();  

  // 1. Stampare il determinante della matrice 
	std::cout << "Determinante: " << m.Determinant() << std::endl;
  // 2. Creare la matrice n, copia di m
	TMatrixF n=m;
	n.Print();
  // 3. Invertire la matrice m
  	m.Invert();
  	m.Print();

  // 4. Creare una matrice k, prodotto delle matrici precedenti
	TMatrixF k(3,3);
	k.Mult(m,n);
	k.Print(); 
  // 5. Verificare che la risultate sia simmetrica (usare il metodo apposito)
	std::cout << k.IsSymmetric();
  // 6. Modificare m in modo che ogni elemento sia uguale al suo quadrato
  	m.Sqr();
  	m.Print();
  
  // 7. "Trovare" una matrice di elementi compresi tra 0 e 10 ed avente determinante 
  // maggiore di 100. Suggerimento: le linee seguenti randomizzano la matrice x 
  // con numeri compresi tra 0 e 1 e con seme uguale a 7
       TMatrixF x(3, 3);
       double s = time(NULL);
       x.Randomize( 0, 10, s);
      while(x.Determinant() < 100){
       x.Zero();
       x.Randomize( 0, 10, s);
       }
     
     x.Print();
     std::cout << x.Determinant();

  return 0;   
} 
