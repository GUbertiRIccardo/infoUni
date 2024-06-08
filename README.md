# appunti-metodi
# Variabili
 - `a=http://www.comuni-italiani.it/province.html` puoi assegnare anche così
 - `links2 -dump $a` per usarla
 - 
# Comandi Linux non noti
 - `df -h` stampa i filesystems montati e l'utilizzo
 - `df -hT` stampa i dischi montati e l'utilizzo
 - `mount` monta una partizione
 - `unmount` smonta una partizione
 - `cat /proc/cpuinfo` è dove si trovano le info di sistema `cat /proc/meminfo `
 - `ps -ef` mostra i processi in esecuzione per vedere di più `ls -1 /proc/8854`
 - `bc` è la calcolatrice
 - `tr ":" "\n"` sostituisce tutti i : con \n
 - `sort listaNomi | uniq` sorta un file e toglie i doppioni
 - `paste nazionale82 nazionale06` affianca due file
 - `seq 1 4 21` genera una sequenza da 1 a 21 con step = 4
 - `basename /bin/date` basename rimuove le directory dall'indirizzo assoluto di un file
 - `basename -s` rimuove il suffisso dal nome di un file
 - `watch -n 5 ls -l` watch mostra l'output di uno stesso comando ogni n secondi
 - `grep cpu /proc/cpuinfo` prende solo le linee del file che presentano la stringa cpu
  - `-v` prende quelle che NON
  - `-i` case insensitive
  - `^c` significa: la linea iniziaper “c”. Mentre “xx$” significa finisce per “xx"
  - `-n` prende il numero di linea
 - `head` legge le prime righe
 - `tail` legge le ultime
 - `links2 -dump http://www.comuni-italiani.it/province.html` browser testuale -dump toglie l'interattività
 - ` > ` reindirizzo a file ` >> ` reindirizzo e sovrascrivo
 - `column -t pWeb2.txt` per formattare l'output in colonne
 - `sed -e 's/testo/altro_testo/g' pWeb2.txt` si usa per le regex
  - -e: esegui il comando seguente
  - s: sostituisci
  - /: separatore
  - g: per ogni occorrenza
  - ': inizio-fine dello script
 - `awk '{print $2, $5}' pWeb2.txt` $num seleziona la colonna desiderata, si usa per selezionare
  - `awk '!/Resid/ {print $2, $5, $6/$7}' pWeb3.txt` Solo le linee che non (!) contengono stringa “Resid”,Divisione tra colonne
  - `awk '{n=n+1; s=s+$3} END{print "Media " s/n}' pWeb3.txt` fa la media di una colonna
    Stampa il prodotto delle colonne 2 e 4 se la riga contiene “MHz”
    [fisica@linux]$ awk '/MHz/ {print "prodotto= " $2*$4 }' file
    ...
    Stampa solo le righe con il valore della colonna 4 maggiore di 42
    [fisica@linux]$ awk '$4 > 42' file
    ...
    Stampa solo le righe con il valore della colonna 4 maggiore di 42
    e il valore della colonna 2 minore di 7
    [fisica@linux]$ awk '$4 > 42 && $2 < 7' file
    ...
    Stampa solo le righe con più di 72 caratteri
    [fisica@linux]$ awk 'length > 72' file
    ...
    Stampa la colonna 3 se la colonna 1 è uguale a “energy”
    [fisica@linux]$ awk '$1=="energy" {print $3}' file
    ...
    Stampa solo le righe comprese tra la parola inizio e quella fine
    [fisica@linux]$ awk '/inizio/,/fine/' file
