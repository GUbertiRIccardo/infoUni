# Appunti
# Comandi importanti
 - `tar czf ilbackup.tgz tesi` per zippare con tar
 - `chmod +x ciao.sh` per rendere eseguibili i file
# Variabili
Le variabili sono
 – assegnate con l’operatore =
 - NB: Occhio a non lasciare spazi intorno all’=
 – accedute anteponendo il simbolo $
 - `a=http://www.comuni-italiani.it/province.html` puoi assegnare anche così
 - `links2 -dump $a` per usarla
 - Si usa command substitution per:
 - Assegnare ad una variabile l’output di un comando ```A=`date` B=$(date)```
 - Popolare i parametri di un comando
```bash
shell> echo sono `whoami` e oggi è $(date +%A)
sono negri e oggi è sabato
for i in `seq 1 7`; do echo cap$i; done
for i in $(seq 1 7); do echo cap$i; done
```

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
```bash
Sostituisci Tizio con Caio
[fisica@linux]$ sed -e 's/Tizio/Caio/g' file
...
Se la stringa da sostituire contiene "/" si può usare "|" come
carattere di delimitazione. Es: cambia /usr/bin con /usr/local/bin
[fisica@linux]$ sed 's|/usr/bin|/usr/local/bin|g' file
...
Stampa solo le righe tra 7 e 42
[fisica@linux]$ sed -n -e 7,42p file
...
Stampa solo le righe tra le stringhe "inizio" e "fine"
[fisica@linux]$ sed -n -e '/inizio/,/fine/p' file
...
Rimuovi tutte le righe contenenti la parola "windows"
[fisica@linux]$ sed -e /windows/d file
...
Aggiungi spazi all'inizio di ogni linea (simbolo ^)
[fisica@linux]$ sed -e 's/^/ /' file
```
 - `awk '{print $2, $5}' pWeb2.txt` $num seleziona la colonna desiderata, si usa per selezionare
	- `awk '!/Resid/ {print $2, $5, $6/$7}' pWeb3.txt` Solo le linee che non (!) contengono stringa “Resid”,Divisione tra colonne
	- `awk '{n=n+1; s=s+$3} END{print "Media " s/n}' pWeb3.txt` fa la media di una colonna
```bash
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
```
Per i file csv usare:
`awk 'FS= "," {print $7}' myDataset.csv`
# Script
Esempio backup tesi:
```bash
FIL=ilbackup.`date "+%y%m%d-%H%M"`.tgz
DIR=tesi
echo "Sto facendo il backup di $DIR"
tar czf $FIL $DIR
echo "Ho fatto il backup di $DIR, il file di archivio e': "
ls -l $FIL
```
Esempio di for e while:
```bash
for y in 1800 1900 2000 # Per gli anni nella lista
do # Inizio operazione
 cal 4 $y # Stampa il calendario di aprile
done # Fine operazione

for f in *.data; do mv $f $f.old; done
for i in {0..7}; do touch $i.txt; done
for i in `seq 0 7`; do touch $i.txt; done

while true; do date; sleep 3; done 
```
Esempio di if:
```bash
Il costrutto if-then-else in bash
– Inizia con if e termina con fi (dettagli qui)
– La comparazione è tra [ ] e seguita da then
● NB: gli spazi attorno a “[“ e “]” sono necessari!!
– Gli operatori sono: -gt, -eq, -ne, -lt (dettagli qui)
– E' possibile aggiungere elif ed else
if [ $X -gt 42 ] # Se la variabile X è maggiore di 42
then
 # Fai una determinata operazione
elif [ $X -eq 42 ] # Se invece la variabile X è uguale a 42
then
 # Fai un'altra operazione
else # Se nessuna delle precedenti
 # Fai un altro tipo di operazione
fi # Chiusura dell'if
```
Esempio di parametri inline:
```bash
#!/bin/bash
echo "Numero di parametri: $#"
echo "Nome dello script : $0"
echo "Primo parametro : $1"
echo "Tutti i parametri : $@"
for p in $@; do echo "Par = $p"; done
```
Esempio cambio suffisso:
```bash
#!/bin/bash
OLDSUFF=$1
NEWSUFF=$2
for OLDNAME in *$OLDSUFF
do
 BASE=`basename $OLDNAME $OLDSUFF`

 NEWNAME=$BASE$NEWSUFF

 mv -v $OLDNAME $NEWNAME
done
```
