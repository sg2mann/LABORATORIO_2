#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

// 1. Programe la función List* createList(), la cual retorna el puntero del tipo de dato List con sus valores inicializados en NULL.
// Recuerda reservar memoria al puntero usando malloc o calloc.

List * createList() {
    List * lista = (List *) malloc(sizeof(List));
    if (lista == NULL) return NULL;
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    return lista;
}

// 2. Programe las funciones void * firstList(List * list) y void * nextList(List * list).
//   - La primera retorna el dato del primer nodo de la lista (head) y actualiza el current para que apunte a ese nodo.
//   - La segunda función retorna el dato del nodo a continuación del current y actualiza el current para que apunte a ese nodo.

void * firstList(List * lista) {
    if (lista == NULL || lista->head == NULL) return NULL;
    lista->current = lista->head;
    return lista->current->data;
}

void * nextList(List * lista) {
    if(lista == NULL || lista->current == NULL) return NULL;
    if(lista->current->next == NULL) return NULL;
    lista->current = lista->current->next;
    return lista->current->data;
}

// 3. Programe las funciones void * lastList(List * list) y void * prevList(List * list).
//   - La primera retorna el dato del último elemento en la lista y actualiza el current al nodo correspondiente.
//   - La segunda función retorna el dato del nodo anterior a current y actualiza el current para que apunte a ese nodo.

void * lastList(List * list) {
    return NULL;
}

void * prevList(List * list) {
    return NULL;
}

// 4. Programe la función void pushFront(List * list, void * data), la cual agrega un dato al comienzo de la lista.
// Puede utilizar la función Node* createNode(void * data) la cual crea, incializa y retorna un nodo con el dato correspondiente.

void pushFront(List * lista, void * data) {
    Node * nuevoNodo = createNode(data);
    if(lista->head == NULL)
    {
        lista->head = nuevoNodo;
        lista->tail = nuevoNodo;
    }
    else
    {
        nuevoNodo->next = lista->head;
        lista->head->prev = nuevoNodo;
        lista->head = nuevoNodo;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

// 5. Programe la función void pushCurrent(List * list, void* data), la cual agrega un dato a continuación del nodo apuntado por list->current.

void pushCurrent(List * lista, void * data) {
    if(lista == NULL || lista->current == NULL) return;
    
    Node * nuevoNodo = createNode(data);
    Node * izq = lista->current;
    Node * der = lista->current->next;

    nuevoNodo->prev = izq;
    nuevoNodo->next = der;

    izq->next = nuevoNodo;

    if (der != NULL)
    {
        der->prev = nuevoNodo;
    }
    else
    {
        lista->tail = nuevoNodo;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

// 6. Programe la función void* popCurrent(List * list), la cual elimina el nodo que está en la posición del current de la lista enlazada, y además retorna el dato del nodo eliminado.
// Nota: El current debe quedar apuntando al nodo siguiente del eliminado.

void * popCurrent(List * list) {
    if(list->current == NULL) return NULL; // si la lsita esta vacia no hay current
    Node* aux = list->current; // nodo auxiliar
    Node* izq = aux->prev; // nodo izquierdo al current
    Node* der = aux->next; // nodo derecho al current

    void* dato = aux->data; // guardamos el dato para despues mostrarlo

    if (izq != NULL) // si el de la izqueierda es distinto de vacio
    {
        izq->next = der;  // el next del nodo izquierdo apunta al nodo derecho
    }
    else  // sino
    {
        list->head = der; // la cabeza ahora sera el nodo derecho
    }
    if (der != NULL) // si el de la derecha esta no esta vacio
    {
        der->prev = izq; // el anterior de la derecha apunta al nodo de la izquierda
    }
    else // sino
    {
        list->tail = izq; // el ultimo sera el nodo izquierdo
    }

    list->current = der; // el nuevo current pasa a ser el siguiente dato del nodo
    free(aux); // liberamos
    return dato; //retornamos el dato del current eliminado
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}