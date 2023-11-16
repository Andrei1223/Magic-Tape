/*TIMOFTE Andrei-Ioan - 315CC*/

/* definire lista simplu inlantuita pentru coada 
cu pointeri la functii si un caracter*/
typedef struct node
{
    void (* comm)(Lista *, Lista *, char, FILE *);
    char caract;
    struct node *next;
}Node, *ListaSimp;

// initializare coada - lista simplu inlantuita cu doua capete
void init_coada(ListaSimp *coada, ListaSimp *final)
{
    *coada = (ListaSimp)malloc(sizeof(Node));
    *final = (ListaSimp)malloc(sizeof(Node));

    // seteaza la NULL
    (*final)->next = NULL;
    (*coada)->next = NULL;
}

// adauga la finalul cozii un pointer la o functie
void enq(void (* funct)(Lista *, Lista *, char, FILE *), ListaSimp *coada, char car, ListaSimp *fin)
{
    ListaSimp nou = (ListaSimp)malloc(sizeof(Node));
    // se copiaza valorile
    nou->comm = funct;
    nou->caract = car;
    nou->next = NULL;
    
    // daca este primul element din coada
    if ((*coada)->next == NULL)
    {
        (*coada)->next = nou;
        (*fin)->next = nou;
        return ;
    }

    // se fac legaturile
    (*fin)->next->next = nou;
    (*fin)->next = nou;
}

// scoate primul element din coada
void deq(ListaSimp *coada, void (** funct)(Lista *, Lista *, char, FILE *), char *car, ListaSimp *fin)
{
    ListaSimp aux = (*coada)->next;

    // se copiaza valorile
    *funct = aux->comm;
    *car = aux->caract;

    // cazul cu un singur element in coada
    if ((*coada)->next == (*fin)->next)
    {
        (*fin)->next = NULL;
        (*coada)->next = NULL;
        free(aux);
        return ;
    }

    (*coada)->next = aux->next;
    aux->next = NULL;
    
    // se sterge nodul
    free(aux);
}