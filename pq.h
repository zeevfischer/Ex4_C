
#ifndef pq
#define pq
typedef struct nodepq {
    char data[2];
 
    // Lower values indicate higher priority
    int priority;
 
    struct nodepq* next;
 
} Nodepq;

int isEmpty(Nodepq** head);
void push(Nodepq** head,int src, int dest, int p);
void pop(Nodepq** head);
Nodepq* peek(Nodepq** head);
Nodepq* newNode(int src,int dest, int p);
#endif