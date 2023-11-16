/*TIMOFTE Andrei-Ioan - 315CC*/

#include "operatii.h"
#include "stive.h"
#include "coada.h"

// initializare lista 
void init_lista(Lista *lst, Lista *deget)
{
    *lst = (Lista)malloc(sizeof(Nod));
    (*lst)->prev = NULL;

    // intializare deget
    *deget = (Lista)malloc(sizeof(Nod));
    (*lst)->next = *deget;
    (*deget)->next = NULL;
    (*deget)->prev = *lst;

    // adaugare caracter
    (*deget)->elem = '#';
}

// elibereaza lista dublu inlantuita
void eliberare_lista(Lista *lst, Lista *deget)
{
    // parcurgere lista
    while (*lst != NULL)
    {
        *deget = *lst;
        *lst = (*lst)->next;
        free(*deget);
    }
}

int main()
{
    Pointeri lista;

    ListaSimp coada, final;

    Stiv undo, redo;

    // initializare stive undo/redo
    init_stiva(&undo);
    init_stiva(&redo);

    // initializare lista cu santinela
    init_lista(&(lista.head), &(lista.deget));

    // initializare coada
    init_coada(&coada, &final);

    // deschidere fisiere fr - read fw - write
    FILE *fr, *fw; 
    fr = fopen("tema1.in", "r");
    fw = fopen("tema1.out", "w");
    
    // citire comenzi
    int nrComenzi, i;
    fscanf(fr, "%d", &nrComenzi);
    Lista santinela = lista.head;

    for (i = 1; i <= nrComenzi; i++)
    {
        
        void (* funct)(Lista *, Lista *, char, FILE *);
        char caract = '\0', comanda[30];
        fscanf(fr, "%s", comanda);
        
        // prelucrare comenzi
        if (strcmp(comanda, "SHOW") == 0)
        {
            show(&(lista.head), &(lista.deget), caract, fw);
        }
        else if (strcmp(comanda, "SHOW_CURRENT") == 0)
        {
            show_current(&(lista.head), &(lista.deget), caract, fw);
        }
        else if (strcmp(comanda, "EXECUTE") == 0)
        {
            void (* auxiliar)(Lista *, Lista *, char, FILE *);
            // se scoate din coada pentru a fi executat
            deq(&coada, &auxiliar, &caract, &final);
            Lista poz = lista.deget;

            // apelare functie
            (* auxiliar)(&(lista.head), &(lista.deget), caract, fw);

            // se adauga in stiva de undo daca este o operatie de mutat
            if (auxiliar == &move_left || auxiliar == &move_right)
            {
                // se adauga doar daca s a modificat pozitia degetului
                if (poz !=  lista.deget)
                    adaugare_stiva(&undo, poz);
            }
            // golire stive la intalnirea functiei "write"
            if (auxiliar == &write)
            {
                // se elibereaza cele 2 stive
                eliberare_stiva(&undo);
                eliberare_stiva(&redo);
            }
        }
        else if (strcmp(comanda, "MOVE_RIGHT") == 0)
        {
            // se adauga in coada EXECUTE
            funct = &move_right;
            enq(funct, &coada, caract, &final);
        }
        else if (strcmp(comanda, "MOVE_LEFT") == 0)
        {
            // se adauga in coada EXECUTE
            funct = &move_left;
            enq(funct, &coada, caract, &final);
        }  
        else if (strcmp(comanda, "MOVE_LEFT_CHAR") == 0)
        {
            // se adauga in coada EXECUTE
            funct = &move_left_char;
            fgetc(fr);

            // se citeste caracterul
            fscanf(fr, "%c", &caract);
            enq(funct, &coada, caract, &final);
        }
        else if (strcmp(comanda, "MOVE_RIGHT_CHAR") == 0)
        {
            // se adauga in coada EXECUTE
            funct = &move_right_char;
            fgetc(fr);
            // se citeste caracterul
            fscanf(fr, "%c", &caract);
            enq(funct, &coada, caract, &final);
        }
        else if (strcmp(comanda, "WRITE") == 0)
        {
            // se adauga in coada EXECUTE
            funct = &write;
            fgetc(fr);
            // se citeste caracterul
            fscanf(fr, "%c", &caract);
            enq(funct, &coada, caract, &final);
        }
        else if (strcmp(comanda, "INSERT_RIGHT") == 0)
        {
            // se adauga in coada EXECUTE
            funct = &insert_right;
            fgetc(fr);

            // se citeste caracterul
            fscanf(fr, "%c", &caract);
            enq(funct, &coada, caract, &final);
        }
        else if (strcmp(comanda, "INSERT_LEFT") == 0)
        {
            // se adauga in coada EXECUTE
            funct = &insert_left;
            fgetc(fr);
            // se citeste caracterul
            fscanf(fr, "%c", &caract);
            enq(funct, &coada, caract, &final);
        }
        else if (strcmp(comanda, "UNDO") == 0)
        {
            Lista pozitie = lista.deget;

            // se scoate primul pointer din stiva UNDO
            scoatere_stiva(&undo, &pozitie);

            // se adauga in stiva redo pozitia curenta
            adaugare_stiva(&redo, lista.deget);
            // se schimba pozitie curenta
            lista.deget = pozitie;
        }
        else if (strcmp(comanda, "REDO") == 0)
        {
            Lista pozitie = lista.deget;

            // se scoate primul pointer din stiva REDO
            scoatere_stiva(&redo, &pozitie);

            // se adauga in stiva de undo pozitia curenta
            adaugare_stiva(&undo, lista.deget);

            // se schimba pozitia curenta
            lista.deget = pozitie;
        }
        // revine pointerul la pozitia initiala
        lista.head = santinela;
    }

    // eliberare memorie coada
    free(coada);
    free(final);

    // eliberare memorie stive
    eliberare_stiva(&undo);
    eliberare_stiva(&redo);
    free(undo);
    free(redo);

    // eliberare memorie lista dublu inlantuita
    eliberare_lista(&(lista.head), &(lista.deget));
    free(lista.head);


    // inchidere fisiere
    fclose(fr);
    fclose(fw);

    return 0;
}