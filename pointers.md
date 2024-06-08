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
