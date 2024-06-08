# Accenno su teoria dei puntatori
I puntatori sono gestiti attraverso gli operatori * e &
– In fase di dichiarazione, la presenza di * davanti al nome di una variabile indica che questa è un puntatore
` int *p; // La variabile p e' un puntatore ad intero`
– In fase di utilizzo, la presenza di * davanti al nome di una variabile indica l'accesso al valore contenuto nella locazione di memoria a cui essa punta
`int i = *p; // Assegnaz. ad i del valore puntato da p`
- Invece, l'operatore & anteposto ad una variabile ne ritorna l'indirizzo in memoria
```
int n = 42; // Dichiaro variabile n e la inizializzo
p = &n; // Alla variabile puntatore p viene assegnato
// l'indirizzo di memoria di n: 'p punta ad n'
```
Esempio
```cpp
#include <iostream>
int main()
{
 // Dichiarazione variabile: allocazione di uno
 // spazio in memoria per un int con etichetta n
 int n;
 // Assegnazione: 42 e' scritto nella locazione
 // precedentemente etichettata con n
 n = 42;
 // Dichiarazione di variabile puntatore ad int:
 // allocazione di spazio in memoria per un
 // indirizzo ed etichettamento variabile con p
 int *p;
 // Assegnazione del puntatore p all'indirizzo di n. La locazione p
 // ora contiene l'indirizzo di memoria di n. Cioè p punta ad n
 p=&n;
 // Accesso al valore puntato da p
 std::cout << *p << std::endl; // Verra' scritto 42
 *p = 7; // Modifica del valore puntato da p
 std::cout << n << std::endl; // Verra' scritto 7
 return 0;
}
```
Altro esempio:
```cpp
#include <iostream>
int main()
{
 float x = 7; // x e' una variabile di tipo float
 // a cui viene assegnato il valore 7
 float *p = &x; // p e' una variabile di tipo puntatore a float, a
 // cui viene assegnato l'indirizzo della variabile x
 std::cout << "Valore di x: x = " << x << std::endl;
 std::cout << "Indirizzo di x: &x = " << &x << std::endl;
 std::cout << "Valore di p: p = " << p << std::endl;
 std::cout << "Indirizzo di p: &p = " << &p << std::endl;
 std::cout << "Valore puntato *p = " << *p << std::endl;
 return 0;
}
```
Puntatori ed array
```cpp
#include <iostream>
#define LEN 10
int main()
{
 // Allocazione di un array di LEN interi
 int z[LEN] = {1, 2, 3 , 4, 5, 6, 7, 8, 9, 10};
 // Accesso tramite operatore []
 for(int i=0; i<LEN; i++)
 std::cout << z[i] << std::endl
 // Accesso tramite puntatore. Il loop parte facendo puntare p all'
 // inizio dell'array (&z[0]) e incrementando il puntatore fino a che
 // non raggiunge la fine dell'array (z[0]+LEN).
 for(int *p=&z[0]; p < &z[0] + LEN; p++)
 std::cout << *p << std::endl; // Stampa dell'elemento puntato
 return 0;
}
```
Cosa NON fare
```cpp
#include <iostream>
int main()
{
 float x = 7; // x e' una variabile di tipo float a cui viene assegnato 7
 float *p = &x; // p e' una variabile di tipo puntatore a float a
 // cui viene assegnato l'indirizzo della variabile n
 *p = 42; // Assegnazione di 42 alla locazione puntata da p,
 // cioe' la variabile x vale ora 42
 // Provochiamo un crash simulando un'errata gestione di un puntatore
 p = p + 1000000; // p ora punta 4MB sopra alla locazione di x
 // Ora scriviamo nella locazione puntata da p
 // - Se la locazione e' fuori dalla memoria riservata al processo il
 // sistema operativo, per motivi di sicurezza, deve uccidere il
 // processo che morira' con un messaggio "segmentation fault"
 // - Va peggio se la locazione e' all'interno della memoria del processo:
 // ne stiamo corrompendo lo stato ma senza ucciderlo e senza saperlo!
 *p = 137.035; // Qui dovrebbe morire il programma
 // Esercizio: provare cambiare l'offset del puntatore, es: p = &x + 2;
 return 0;
}
```
Allocazione dinamica
```cpp
#include <iostream>
int g = 42; // Variabile globale
int main()
{
 int i = 7; // Allocazione spazio per un int
 { // Nuovo blocco
 float x[10]; // Spazio per 10 float
 } // NB: all'uscita dal blocco la variabile
 // locale x è deallocata in automatico
 // Allocazione dinamica per n interi.
 // NB: non nota a priori!
 std::cout << "Quanto alloco?" << std::endl;
 int n;
 std::cin >> n;
 int *b = new int[n];
 // b punta alla memoria allocata
 // Deallocazione manuale da parte dell'utente
 // quando la memoria non e' piu' necessaria
 // Altrimenti si ha memory leak
 delete[] b;
 return 0;
}
```
Swap coi puntatori
```cpp
#include <iostream>
void swap(int *a, int *b) // NB: ora riceve puntatori!
{ // Scambia il contenuto di 2 variabili usando puntatori
 std::cout << "swap " << *a<< " " << *b<< std::endl;
 int tmp = *a;
 *a = *b;
 *b = tmp;
 std::cout << "swap " << *a<< " " << *b<< std::endl;
}
int main()
{
 int x = 0;
 int y = 7;
 std::cout << "main " << x << " " << y << std::endl;
 swap(&x, &y); // Chiamata di swap
 std::cout << "main " << x << " " << y << std::endl;
 return 0;
} 
```
Swap by ref
```cpp
#include <iostream>
void swap(int &a, int &b)
{ // Scambia il contenuto di 2 variabili
 std::cout << "swap " << a << " " << b << std::endl;
 int tmp = a; // Variabile temporanea per lo scambio
 a = b;
 b = tmp;
 std::cout << "swap " << a << " " << b << std::endl;
}
int main()
{
 int x = 0;
 int y = 7;
 std::cout << "main " << x << " " << y << std::endl;
 swap(x, y); // Chiamata di swap
 std::cout << "main " << x << " " << y << std::endl;
 return 0;
}
```

> `int main(int argc, char* argv[]);`
