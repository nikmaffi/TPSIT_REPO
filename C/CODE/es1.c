#include <stdio.h>
#include <stdlib.h>

typedef struct node_t //Tipo node -> rappresenta una cella della coda
{
    int value; //Valore del nodo
    struct node_t *next; //Puntatore del nodo successivo
}node;

typedef struct queue_t //Tipo coda
{
    node* tail; //Puntatore all'ultima cella della coda
    node* head; //Puntatore alla prima cella della coda
}queue;

short enqueue(queue *q, int value)
{
    node *tmp = NULL; //Puntatore di supporto

    if(q == NULL) //Controllo della validità del puntatore alla coda
        return 0;

    tmp = (node *)calloc(1, sizeof(node)); //Creazione di un nuovo nodo
    tmp->value = value; //Impostazione del valore del nodo

    if(q->tail != NULL) //Se tail non è null (non è la prima operazione di accodamento) *
        q->tail->next = tmp; //* viene collegato il nodo precedente a quello nuovo

    q->tail = tmp; //tail ora punta al nuovo nodo (la coda si estende)

    if(q->head == NULL) //Se head è null (è la prima operazione di accodamento) *
        q->head = q->tail; //head punta alla stessa cella puntata da tail

    return 1;
}

short dequeue(queue *q, int *value)
{
    node *tmp = NULL; //Puntatore di supporto

    //Controllo della validità dei puntatori passati come parametri
    //Se il il puntatore head è nullo la coda è vuota -> non si può effettuare l'estrazione
    if(q == NULL || value == NULL || q->head == NULL)
        return 0;

    tmp = q->head;
    *value = q->head->value; //Impostazione del valore che restituirà l'estrazione
    q->head = q->head->next; //Il puntatore head ora punta al nodo successivo (la coda si riduce)
    free(tmp); //Deallocazione del nodo sulla cima della coda

    if(q->head == NULL) //Se head è nullo (ultima operazione di estrazione possibile) *
        q->tail = q->head; //* head punta alla stessa cella puntata da tail

    return 1;
}

queue initqueue()
{
    queue q;

    q.head = NULL; //Il puntatore alla base della coda è nullo per l'inizializzazione
    q.tail = NULL; //Il puntatore alla cima della coda è nullo per l'inizializzazione

    return q;
}

int main()
{
    int num = 0;
    queue q = initqueue();

    printf("CODA DI NUMERI\n\n");

    printf("Inserire i numeri in serie (inserire un carattere per terminare):\n");
    while(scanf("%d", &num) > 0)
        enqueue(&q, num);

    printf("\nContenuto della coda: ");
    while(dequeue(&q, &num))
        printf("[%d]", num);

    return 0;
}