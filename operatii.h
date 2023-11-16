/*TIMOFTE Andrei-Ioan - 315CC*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definire lista dublu inlantuita
typedef struct nod
{
    char elem;
    struct nod *next;
    struct nod *prev;
}Nod, *Lista;

// definire structura pointeri ls lista si poz curenta
typedef struct pozitii
{
    Lista head;
    Lista deget;
}Pointeri;

// muta la dreapta degetul si daca este cazul creeaza inca un nod
void move_right(Lista *lst, Lista *deget, char caract, FILE *fw)
{
    // se adauga inca un nod
    if ((*deget)->next == NULL)
    {
        Lista nou = (Lista)malloc(sizeof(Nod));
        nou->next = NULL;
        nou->prev = *deget;
        (*deget)->next = nou;

        // adaugare caracter special
        nou->elem = '#';
    }

    // mutare pozitie deget
    *deget = (*deget)->next;
}

// muta la stanga degetul daca este posibil
void move_left(Lista *lst, Lista *deget, char caract, FILE *fw)
{
    // verifica daca este pe prima pozitie
    if ((*deget)->prev == *lst)
        return;
    (*deget) = (*deget)->prev;
}

// muta la stanga pe pozitia caracterului dorit daca exista
void move_left_char(Lista *lst, Lista *deget, char caract, FILE *fw)
{
    int gasit = 0;
    Lista pozInit = *deget; // de verificat daca ramane nemodificat
    while (*lst != *deget)
    {
        // se verifica daca s a gasit caracterul
        if ((*deget)->elem == caract)
        {
            gasit = 1;
            break;
        }
        // se parcurge mai departe lista
        *deget = (*deget)->prev;
    }

    // daca nu a fost gasit
    if (gasit == 0)
    {
        fprintf(fw, "ERROR\n");
        // pozitia ramane neschimbata
        *deget = pozInit;
    }
}

/* muta la dreapta pe pozitia caracterului dorit 
daca nu exista creaza un nod nou si muta pozitia degetului*/
void move_right_char(Lista *lst, Lista *deget, char caract, FILE *fw)
{
    int gasit = 0;
    // parcurge pana la penultimul caracter
    while ((*deget)->next != NULL)
    {
        // se verifica daca s a gasit caracterul
        if ((*deget)->elem == caract)
        {
            gasit = 1;
            break;
        }
        *deget = (*deget)->next;
    }
    // verifica daca ultimul element este caracterul cautat
    if ((*deget)->elem == caract)
        gasit = 1;

    // mai adauga un nod
    if (gasit == 0)
    {
        move_right(lst, deget, caract, fw);
    }
}

// afiseaza caracterul curent
void show_current(Lista *lst, Lista *deget, char caract, FILE *fw)
{
    fprintf(fw, "%c\n", (*deget)->elem);
}

// afiseaza banda
void show(Lista *lst, Lista *deget, char caract, FILE *fw)
{
    // se sare peste santinela
    *lst = (*lst)->next;
    while (*lst != NULL)
    {
        // verifica daca a ajuns pe pozitia degetului
        if (*lst == *deget)
            fprintf(fw, "|%c|", (*lst)->elem);
        else
            fprintf(fw, "%c", (*lst)->elem);
        *lst = (*lst)->next;
    }
    fprintf(fw, "\n");
}

// functie de modificare caracter
void write(Lista *lst, Lista *deget, char caract, FILE *fw)
{
    (*deget)->elem = caract;
}

/* adauga pe orice pozitie din banda un nod
se primeste pointerul la nodul inaintea caruia se doreste adaugarea*/
void add_mijloc(Lista *deget, char caract)
{
    // alocare memorie
    Lista nou = (Lista)malloc(sizeof(Nod));
    nou->elem = caract;

    nou->next = *deget;
    nou->prev = (*deget)->prev;
    (*deget)->prev->next = nou;
    (*deget)->prev = nou;
}

// functie de inserare la dreapta
void insert_right(Lista *lst, Lista *deget, char caract, FILE *fw)
{
    // se verifica daca se afla pe ultima pozitie
    if ((*deget)->next == NULL)
    {
        // se adauga un nod la final
        move_right(lst, deget, caract, fw);
        write(lst, deget, caract, fw);
        return ;
    }

    *deget = (*deget)->next;
    add_mijloc(deget, caract);
    *deget = (*deget)->prev;
}

// functie de inserare la stanga
void insert_left(Lista *lst, Lista *deget, char caract, FILE *fw)
{
    // se verifica daca se afla pe prima pozitie
    if ((*deget)->prev == *lst)
    {
        fprintf(fw, "ERROR\n");
        return ;
    }

    add_mijloc(deget, caract);
    *deget = (*deget)->prev;
}