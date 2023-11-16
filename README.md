# TEMA 1

# -----------------------INTRODUCERE-----------------------------

Codul a fost impartit in 4 fisiere, 3 fiind headere care contin functii
grupate in functie de utilizarea lor. In fisierul principal, numit "banda.c",
se afla 2 subprograme ce vizeaza initializarea listei dublu inlantuite cu 
santinela si eliberarea memoriei din aceasta la finalul programului. 

# -----------------------IMPLEMENTARE-----------------------------

Informatiile primite de program provin din fisierul de input numit
"tema1.in", unde se afla pe fiecare rand cate o comanda care 
trebuie se fie prelucrata, iar apoi sa fie afisate rezultatele in fisierul
"tema1.out".

Pentru realizarea operatiilor cerute au fost create 4 structuri:

1. o lista dublu inlantuita cu santinela care reprezenta banda din
enunt
2. o structura care contine head-ul listei prezedente si, totodata,
pointer-ul la nodul la care arata degetul
3. o lista simplu inlantuita care are 2 pointeri (unul la inceputul
listei, respectiv la finalul listei), avand ca scop simularea unei cozi
(coada care contine pointer la functiile care necesita comanda EXECUTE
pentru a fi executate)
4. o lista simplu inlantuita care are un pointer la inceputul listei,
avand ca scop simularea stivelor de undo/redo.

Initial, se citeste numarul de operatii care se afla in fisierul de input,
apoi ,pe rand, fiecare comanda. In cazul comenziilor "SHOW" si "SHOW_CURRENT"
acestea vor avea efect imediat si vor afisa, in fisierul "tema1.out",
elementele din banda sau elementul de pe pozitia curenta. 

Functiile de tipul UPDATE, care necesita comanda EXECUTE pentru a fi executate,
sunt adaugate in coada pentru EXECUTE. (se adauga pointerul la functie alaturi
de un caracter in cazul in care functia era precedata de un caracter
ex:"INSERT_RIGHT"). Se tot adauga in coada pana se intalneste comanda EXECUTE,
caz in care se scoate primul element din acesta, si se executa functia scoasa.
Din cauza utiliza pointerilor la functii a fost nevoie ca toate operatiile sa 
aiba acelasi antet, astfel fiecare functie primeste ca parametru un pointer 
la fisier si un caracter chiar daca nu afiseaza nimic sau nu a fost citit
niciun caracter.

O data cu scoaterea unei functii din coada de EXECUTE, se adauga in stiva undo
pozitia degetului in lista dublu inlantuita inainte de a se efectua comanda. 
Daca pozitia este neschimbata (adica operatia nu a fost efectuata cu succes
ex:MOVE_LEFT pe prima pozitie din banda), atunci nu este adaugata in stiva undo

Daca este intalnita comanda UNDO se scoate primul pointer la un nod in banda
si se adauga in stiva redo, apoi se schimba pozitia degetului la cea scoasa din
stiva. Preocesul este similar pentru comanda REDO, unde se scoate primul
element din stiva redo,se adauga in stiva undo si se modifica pozitia degetului

Cele doua stive sunt golite atunci cand se intalneste comanda "WRITE", intrucat
este garantat faptul ca operatiile "UNDO" si "REDO" se dau doar pentru operatii
care schimba pozitia pointerului.(s a stabilit ca doar pentru functiile
MOVE_RIGHT si MOVE_LEFT) Astfel, astea sunt singurele functii care au un impact
asupra stivelor undo/redo.

In final, dupa ce se iese din bucla for, se elibereaza toate listele folosite,
alaturi de toti pointerii la acestea si apoi se inchid fisierele folosite
pentru input/output.

# ---------------------------PRECIZARI------------------------------

1. Se presupune faptul ca se va da ca input numarul corect de comenzi
"EXECUTE" pentru a goli coada. Astfel, nu exista un subprogram pentru 
eliberarea memoriei din coada la finalul programului, deci pot aparea
pierderi de memorie daca nu este respectata conditia.

2. Se presupune faptul ca comenzile "UNDO" si "REDO" nu sunt date inainte
de a se fi executat vreo comanda "MOVE_LEFT" sau "MOVE_RIGHT". Astfel, nu
exista o verificare daca stivele sunt goale, inainte de a se incerca extragerea
unui element din acestea, deci ar putea aparea SEGFAULT.

3. Pentru functiile de adaugare si scoatere de elemente din coada de pointeri
la functii, s au folosit denumiri prescurtate avand rolul de a economisi 
spatiu. In general, functiile sunt numite "enqueue" si "dequeue", insa eu am 
optat pentru "enq" si "deq", intrucat pronuntia este aceeasi chiar daca lipsesc
ultimele 4 litere.

4. De a lungul rularii programului, nu se verifica in niciun fel daca fisierele
au fost deschise cu succes sau daca memoria a fost alocata cu succes.

# --------------------------FISIERE------------------------------

Pentru rezolvarea cerintei am facut 2 headere separat care contin functiile de
adaugare si eliminare specifice structurii lor. Totodata, mai exista un fisier
care contine doar implementarea comenzilor date in enunt.

1. operatii.h

Astfel, in fisierul "operatii.h" se afla doar functiile cerute in enunt
precum MOVE_RIGHT, WRITE <CHAR> etc. Este important de precizat faptul
ca toate functiile din acest fisier au acelasi antet, intrucat este usor
de a implementa coada EXECUTE ca o lista de pointeri la functii.
Astfel, voi descrie functionalitatea operatiilor din acest header:

-->move_right - realizeaza mutarea la dreapta fata de pozitia curenta a
                degetului. Nu este conditionata in niciun fel deplasarea la 
                dreapta adaugandu se noduri noi daca s a ajuns la finalul 
                listei, caz in care este adaugat automat caracterul '#' in
                noul nod creat.

-->move_left - realizeaza mutarea la stanga fata de pozitia curenta a degetului
               Aceasta operatie nu poate fi realizatat daca degetul se afla pe
               prima pozitie din lista, si astfel pozitia degetului va ramane
               neschimbata (fara a se afisa vreun mesaj de eroare).

-->move_left_char - realizeaza mutarea la stanga a degetului, pe pozitia pe
                    care se afla caracterul dat. Daca acesta nu este gasit se 
                    afiseaza mesajul "ERROR" si pozitia ramane neschimbata.

-->move_right_char - realizeaza mutarea la dreapta a degetului, pe pozitia pe 
                     care se afla caracterul dat. Daca acesta nu este gasit, 
                     se adauga un nod nou la finalul listei si degetul ramane
                     pe aceasta pozitie.

-->insert_left - realizeaza adaugarea la stanga pozitiei curente a degetului,
                 a unei casute in care pune caracterul citit din fisier. Daca
                 degetul arata spre prima pozitie din banda, va fi afisat
                 mesajul "ERROR" fara a se efectua vreo modificare.

-->insert_right - realizeaza adaugarea la dreapta pozitiei curente a degetului,
                  a unei casute in care pune caracterul citit din fisier. Daca
                  degetul arata spre ultima pozitie din banda, se va adauga un
                  nou nod la final care contine caracterul citit.

-->show - realizeaza afisarea continutului listei si este evidentiata pozitia
          degetului prin utilizarea caracterului '|' pentru a inconjura nodul
          indicat de catre deget.
        
-->show_current - realizeaza afisarea doar a caracterului din lista spre care
                  arata degetul.

-->write - modifica caracterul de pe pozitia la care indica degetul.

2. stive.h

In fisierul "stive.h" se afla atat definirea structurii si a unui subprogram
pentru initializarea listei simplu inlantuite, cat si 3 subprograme care permit
folosirea acestei structuri. Stiva functioneaza pe principiul LIFO, astfel 
adaugarea unui nou element in aceasta se va realiza la inceputul listei, iar 
eliminarea se va face tot la inceput.

-->adaugare_stiva - adauga la inceputul stivei un pointer la un nod din lista
                    dublu inlantuita

-->scoatere_stiva - scoate din lista primul nod

-->eliberare_stiva - are rolul de a elibera stiva, astfel eliberand toata
                     memoria alocata

3. coada.h

In fisierul "coada.h" se afla atat definirea structurii si a unui subprogram
pentru initializarea listei simplu inlantuite (care are 2 pointeri : unul care
arata la inceputul listei si un al doilea care arata la ultimul nod din
aceasta), cat si 3 subprograme care permit folosirea acestei structuri. Coada
functioneaza pe principiul FIFO, astfel adaugarea unui nou element in aceasta
se va realiza la finalul listei(realizandu se in timp constant datorita 
pointerului de la final), iar eliminarea se va face la inceput.

-->enq - adauga la finalul cozii un nou element, folosindu se de
         pointerul spre final

-->deq - are rolul de a adauga un nou element la inceputul cozii