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

List * createList() 
{
    List * list = (List *)malloc(sizeof(List));
    assert(list != NULL);
    list->head = list->tail = list->current = NULL;
    return list;
}

void * firstList(List * list) 

{
    if (list == NULL || list->head == NULL) 
    {
        return NULL;
    }
    list->current = list->head;
    return list->head->data;
}

void * nextList(List * list) 
{
    if (list == NULL || list->head == NULL) 
    {
        return NULL;
    }
    if (list->current != NULL) 
    {
       list->current = list->current->next; 
    }
    if (list->current != NULL)
    {
        return list->current->data;
    }
    return NULL;
}
void * lastList(List * list) 
{
    list->current = list->tail;
    return list->current->data;
    return NULL;
}

void * prevList(List * list) 
{
    if (list->current != NULL)
        list->current = list->current->prev;
    if(list->current != NULL)
        return list->current->data;
    return NULL;
}

void pushFront(List * list, void * data) 
{
    Node * nodo = createNode(data);
    if(list->head == NULL)
    {
        list->head = list->tail = nodo;
    }
    else
    {
        nodo->next = list->head;
        list->head->prev = nodo;
        list->head = nodo;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
    Node* nodo = createNode(data);
    if(list->current != NULL)
    {
        if(list->current->next == NULL)
        {
            nodo->prev = list->current;
            list->current->next = nodo;
            list->tail = nodo;
        }
        else
        {
            nodo->next = list->current->next;
            list->current->next->prev = nodo;
            nodo->prev = list->current;
            list->current->next = nodo;
        }
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

void * popCurrent(List * list) 
{
    if(list->current->prev == NULL)
    {
        list->head = list->current->next;
        list->current->next = NULL;
        list->current = NULL;
    }
    else if(list->current->next == NULL)
    {
        list->tail = list->current->prev;
        list->current->prev = NULL;
        list->current = NULL;
    }
    else
    {
        list->current->prev->next = list->current->next;
        list->current->next->prev = list->current->prev;
        list->current->next = NULL;
        list->current->prev = NULL;
        list->current = NULL;
    }
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}