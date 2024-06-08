#include <iostream>
#include <stdlib.h> // Per random()
#include <unistd.h> // Per getpid() e usleep()
int main()
{
 int s = getpid(); // Ritorna il process ID
 srandom(s); // Setta il seme con tale ID
 int pos = 30; // Posizione iniziale
 for( ; ; ) // Loop infinito
 { // Estrazione random
 if(random()%2 == 0) pos=pos-1; // Se pari step a sx
 else pos=pos+1; // Altrim. step a dx
 // Ora disegno "pos" spazi e poi una X
 for(int i=0; i<pos; i++) // "pos" spazi
 std::cout << " ";
 std::cout << "X" << std::endl;// e poi una X
 // Ritardo 100ms con microsleep (man 3 usleep)
 usleep(100*1E3);
 }
 return 0;
}
