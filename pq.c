// C code to implement Priority Queue
// using Linked List
#include <stdio.h>
#include <stdlib.h>
#include "pq.h"
 
// Node
// typedef struct node {
//     int data;
 
//     // Lower values indicate higher priority
//     int priority;
 
//     struct node* next;
 
// } Node;
 
// Function to Create A New Node
Nodepq* newNode(int src,int dest, int p)
{
    Nodepq* temp = (Nodepq*)malloc(sizeof(Nodepq));
    char *inf = temp->data;
    inf[0]=src;
    inf[1]=dest;
    temp->priority = p;
    temp->next = NULL;
 
    return temp;
}
 
// Return the value at head
Nodepq* peek(Nodepq** head)
{
    return (*head);
}
 
// Removes the element with the
// highest priority form the list
void pop(Nodepq** head)
{
    // Nodepq* temp = *head;
    (*head) = (*head)->next;
    // free(temp);
}
 
// Function to push according to priority
void push(Nodepq** head,int src ,int dest, int p)
{
    Nodepq* start = (*head);
 
    // Create new Node
    Nodepq* temp = newNode(src,dest, p);
    if(*head== NULL)
    {
        (*head) = temp;
        return;
    }
 
    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if ((*head)->priority > p) {
 
        // Insert New Node before head
        temp->next = *head;
        (*head) = temp;
    }
    else {
 
        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL &&
            start->next->priority < p) {
            start = start->next;
        }
 
        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;
    }
}
 
// Function to check is list is empty
int isEmpty(Nodepq** head)
{
    return (*head) == NULL;
}
 
// int Dijsktra(pnode *head,int src,int dest)
// Driver code
// int main()
// {
//     // Create a Priority Queue
//     // 7->4->5->6
//     Node* pq = newNode(4, 1);
//     push(&pq, 5, 2);
//     push(&pq, 6, 3);
//     push(&pq, 7, 0);
 
//     while (!isEmpty(&pq)) {
//         printf("%d ", peek(&pq));
//         pop(&pq);
//     }
 
//     return 0;
// }