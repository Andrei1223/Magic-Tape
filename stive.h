/*TIMOFTE Andrei-Ioan - 315CC*/

// definire stiva ca lista simplu inlantuita
typedef struct nodstiv
{
    // pointer la un nod din banda
    Lista elem; 
    struct nodstiv *next;
}Nodstiv, *Stiv;


// initializare stiva
void init_stiva(Stiv *stack)
{
    *stack = (Stiv) malloc(sizeof(Nodstiv));
    (*stack)->next = NULL; 
}

// adaugare la inceputul stivei un pointer la un nod din banda
void adaugare_stiva(Stiv *stack, Lista poz)
{
    // alocare memorie element nou
    Stiv nou = (Stiv) malloc(sizeof(Nodstiv));
    
    // copiere valoare
    nou->elem = poz;

    nou->next = (*stack)->next;
    (*stack)->next = nou;
} 

// se sterge primul element din stiva
void scoatere_stiva(Stiv *stack, Lista *poz)
{
    Stiv aux;
    // se verifica daca stiva este goala
    if ((*stack)->next == NULL)
        return ;
    
    aux = (*stack)->next;
    *poz = aux->elem;
    (*stack)->next = aux->next;
    // se elibereaza memoria
    free(aux);
}

// se elibereaza memoria din stiva
void eliberare_stiva(Stiv *stack)
{
    Stiv aux;
    // se parcurg toate nodurile si se elibereaza
    while ((*stack)->next != NULL)
    {
        aux = *stack;
        *stack = (*stack)->next;
        free(aux);
    }
}