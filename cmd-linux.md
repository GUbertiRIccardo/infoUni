# Appunti
# Comandi importanti
 - `tar czf ilbackup.tgz tesi` per zippare con tar
 - `tar -xvf ciao.tgz` per unzippare con tar
 - `chmod +x ciao.sh` per rendere eseguibili i file
 - `ssh studente@pcatl01.pv.infn.it` per collegarsi a un pc, dopo va inserita la password
 - `scp studente@pcatl01.pv.infn.it:/etc/passwd .` Copia il file /etc/passwd dal nodo remoto, alla directory corrente del nodo locale “.”
 - `scp dati.txt studente@pcatl01.pv.infn.it:.` Copia il file dati.txt dal computer locale, alla home directory di studente sul nodo remoto
 - `g++ -o hello HelloWorld.cxx` per compilare un file c++
 - `g++ main.cxx potenza.cxx` per compilare un file e la sua libreria

# ERRORI FREQUENTI SSH/SCP
```
Dimenticare il “:”
– Senza “:” significa “destinazione locale”, quindi viene
creato in locale un file il cui nome sarà il 2° parametro
● Dimenticare l’utente
– Il sistema assume che lo username di destinazione
sia uguale a quello corrente (fisica in questo caso)
● Dimenticare il parametro di destinazione
– Qui manca il parametro di destinazione! Per es.
potrebbe essere un “.” per indicare la dir corrente

[fisica@linux]$ scp dati.txt studente@pcatl01.pv.infn.it
[fisica@linux]$ scp dati.txt pcatl01.pv.infn.it:.
[fisica@linux]$ scp studente@xxx.unipv.it:/etc/passwd
```

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

# PICCOLO APPUNTO SU I PERMESSI
What number is -rw-r--r-- Linux?

    4 = r (Read)
    2 = w (Write)
    1 = x (eXecute)

It is 644.

There are 10 dashes. First dash represents if it is a file or a directory, next 9 dashes are divided into 3 group ie (owner,group,others).

In your case, rw- read and write permission for the owner.

Next three represents the permission for the group r-- readonly permission for group. User who are part of this group will have readonly permission

Last three dash represents the permission for other users who is not owner of the file or part of the group.

File permission can be changed by file owner by executing chmod command with the combination of above numbers

Eg

#chmod 755 filename (rwxr-xr-x)

#chmod 777 filename (rxwrwxrwx)

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
 - `file --mime-type ciao` per identificare il tipo di file
```bash
1. find . -name thisfile.txt

If you need to know how to trovare a file in Linux called thisfile.txt, it will look for it in current and sub-directories.

2. find /home -name *.jpg

Cerca tutti i .jpg files in the /home and directories below it.

3. find . -type f -empty

Look for an empty file inside the current directory.

4. find /home -user randomperson-mtime 6 -iname ".db"

Look for all .db files (ignoring text case) that have been changed in the preceding 6 days by a user called randomperson.
```
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
– E possibile aggiungere elif ed else
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
Esempio quanta gente connessa alla rete
```bash
BASE=192.168.1. # Rete da esplorare
for i in `seq 1 254` # loop per i che va da 1 a 254
do
 IND=$BASE$i # indirizzo, es: 192.168.1.7
 ping -c 1 -W 1 $IND > /dev/null # esegue ping
 # buttando via l'output
 if [ $? -eq 0 ] # se ping ritorna OK (0)
 then echo "$IND usato" # scrive: 192.168.1.x usato
 else echo "$IND" # oppure scrive: 192.168.1.x
 fi
done
```
# Network
> L'ip è visibile tramite `ifconfig` oppure `ip addr` o meglio per vedere IPV4 pubblico `curl ifconfig.me`
```
lo: loopback, il nodo stesso
eth: scheda ethernet (cavo)
wlan: schema wireless
```
- `host 193.204.35.100` o `host www.infn.it` ti danno a chi sono mappati i siti o gli ip
- `ping info.cern.ch` per verificare se un nodo è attivo
- `tracepath www.infn.it` per tracciare da dove viene un pacchetto dati
- `telnet info.cern.ch 80` ti connette a mano alle porte di quel nodo
- `telnet smtp.mioserver.it 25` si può anche mandare una mail...
- `netstat -t` mostra l'elenco delle connessioni aperte
- `lsof` mostra anche i file aperti
- I file in `/var/log` mostrano i log di sistema
- `nmap -A -T4 192.168.1.1` scopre le porte aperte su un host, con l'indirizzo del router LAN
- `nmap 192.168.1.1-255` scan completo della rete locale
- `uptime` per vedere quanto è up un server
- `tcpdump -i eth0` Traffico dati visto dalla scheda di rete ethernet in mezzo secondo su una rete del dipartimento.
- `arp -a` per vedere quali computer sono connessi alla tua sottorete
```bash
# Sniff di tutti i pacchetti visti dall'interfaccia ethernet
[root@linux]$ tcpdump -i eth0
...
# Sniff di tutti i pacchetti verso un host specifico
[root@linux]$ tcpdump -i eth0 host un.nodo.it
...
# Sniff di tutti i pacchetti dal nodo A al nodo B
[root@linux]$ tcpdump -i eth0 src nodoA.it dst nodoB.it
...
# Sniff del solo traffico www
[root@linux]$ tcpdump -i eth0 port 80
```
