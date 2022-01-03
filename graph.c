#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <stdbool.h>
#include "pq.h"

void build_graph_cmd(pnode *head)
{
    // this will deleat the graph to create a new one
    deleteGraph_cmd(head);
    int size = 0;
    scanf("%d", &size);
    char input = ' ';
    // this print will catch the space 
    scanf("%c", &input);
    for(int i =0;i < size;i++)
    {
        scanf("%c", &input);
        if(input == 'n')
        {
            insert_node_cmd(head);
        }
    }
}
// help function for insert_node_cmd
bool isin(pnode *head, int id)
{
    pnode cur = *head;
    while (cur != NULL)
    {
        if(cur->node_num == id)
        {
            return true;
        }
        cur = cur->next;
    }
    return false;   
}

void insert_node_cmd(pnode *head)
{
    int new_Node_id = -1;
    pnode Node = NULL;
    scanf("%d", &new_Node_id);
    // the way i add here is at the begining if i have a head Node
    // my new Node will point to it 
    // then the name of the pointer *head will point to my new node
    if(isin(head,new_Node_id) == false)
    {
        Node = (pnode)malloc(sizeof(node));
        Node->node_num = new_Node_id;
        Node->edges=NULL;
        Node->next = *head;
        *head = Node;
        // head = Node;????
    }
    // else = the node already exists in the Graph
    else
    {
        // this will get me the NOde in to cur
        pnode cur = *head;
        while (cur != NULL)
        {
            if(cur->node_num == new_Node_id)
            {
                break;
            }
            cur = cur->next;
        }
        pedge Edge = cur->edges;
        // this will free all the Edges the node cur has
        while (Edge != NULL)
        {
            pedge temp = Edge->next;//move to next
            Edge = temp;//save next
            free(temp);//free it
        }
        cur->edges=NULL;//reset it
        Node = cur;
    }
    // now we need to add the Now Edges to the updated Node
    pedge *add_Edge = &(Node->edges);
    int dest = -1;
    // when scanf will scan "n" it will return 0 and not scan the "n"
    while (scanf("%d",&dest) != 0)
    {
        if(dest == -1)
        {
            return;
        }
        pnode dest_Node=NULL;
        // if the dest dose not exist we create it with only its id
        // then when we get to in from the input we will right over the temp creation
        if(isin(head , dest) == false)
        {
            dest_Node = (pnode)malloc(sizeof(node));
            dest_Node->node_num = dest;
            dest_Node->edges = NULL;
            dest_Node->next = *head;
            *head = dest_Node;
            // head = dest_Node????
        }
        // if the dest exist we need to find it and get it 
        pnode cur = *head;
        while (cur != NULL)
        {
            if(cur->node_num == dest)
            {
                break;
            }
            cur = cur->next;
        }
        dest_Node = cur;

        int weight = -1;
        scanf("%d",&weight);
        *add_Edge = (pedge)malloc(sizeof(edge));
        (*add_Edge)->endpoint = dest_Node;
        (*add_Edge)->weight = weight;
        (*add_Edge)->next = NULL;
        // add Edge will pont to the null and when the loop starts 
        // the null will be recreated 
        add_Edge = &((*add_Edge)->next); 
    }
}

void delete_node_cmd(pnode *head)
{
    int delete = -1;
    scanf("%d",&delete);
    pnode temp = *head;

    // first we pass over all of the Nodes using temp and delete all the Edges that go in to the eleted Node
    // we will egnor the actual node to delete and deal with it later 
    while (temp != NULL)
    {
        if(temp->node_num == delete)
        {
            temp = temp->next;
            if(temp == NULL)
            {
                break;
            }
        }
        pedge to_free = NULL;
        pedge prev_edge = NULL;
        pedge Edges = temp->edges;
        // if the first Edge is going to delete
        while (Edges != NULL)
        {
            if(Edges->endpoint->node_num == delete)
            {
                if(prev_edge == NULL)
                {
                    to_free = Edges;
                    Edges = Edges->next;
                    free(to_free);
                    temp->edges = Edges;
                }
                else
                {
                    to_free = Edges;
                    prev_edge->next = Edges->next;
                    Edges = Edges->next;
                    free(to_free);
                }
            }
            else
            {
                prev_edge = Edges;
                Edges = Edges->next;
            }
        }
        temp = temp->next;
    }
     // this is just to find prev 
    pnode prev_node = *head;
    if(prev_node->node_num == delete) {
        pedge Edges = prev_node->edges;
        while (Edges != NULL)
        {
            pedge temp = Edges->next;//move to next
            Edges = temp;//save next
            free(temp);//free it
        }
        prev_node->edges=NULL;//reset it

        pnode to_free = prev_node;
        prev_node = prev_node->next;
        free(to_free);
        *head = prev_node;
    }
    else
    {
        while (prev_node->next != NULL && prev_node->next->node_num != delete)
        {
            if(prev_node->next == NULL)
            {
                return;
            } 
            prev_node = prev_node->next;
        }
        // now we deall wih the Node to delete
        pnode Node_to_free = prev_node->next;
        pedge Edge = Node_to_free->edges;
        // this will free all the Edges the node cur has
        while (Edge != NULL)
        {
            pedge temp = Edge->next;//move to next
            Edge = temp;//save next
            free(temp);//free it
        }
        Node_to_free->edges=NULL;//reset it
        // and finaly delete it
        prev_node->next = Node_to_free->next;
        free(Node_to_free);
    }
}
    
void printGraph_cmd(pnode head)
{
    pnode cur = head;
    while (cur != NULL)
    {
        printf("Node %d:\n", cur->node_num);
        pedge Edges = cur->edges;
        while (Edges != NULL)
        {
            printf("src = %d , dest = %d , weight = %d\n",cur->node_num,Edges->endpoint->node_num,Edges->weight);
            Edges = Edges->next;
        }
        printf("\n");
        cur = cur->next;
    }
}

void deleteGraph_cmd(pnode *head)
{
    pnode cur = *head;
    while (cur != NULL)
    {
        pedge cur_edges = cur->edges;
        while (cur_edges != NULL)
        {
            pedge temp = cur_edges;
            cur_edges = cur_edges->next;
            free(temp);
        }
        pnode temp = cur;
        cur = cur->next;
        free(temp);
    }
    *head = NULL;
}

pnode GetNode(pnode head, int id)
{
    pnode cur = head;
    while (cur != NULL)
    {
        if(cur->node_num == id)
        {
            return cur;
        }
        cur = cur->next;
    }
    return false;   
}

int shortsPath_cmd(pnode head,int src,int end_dest)
{
    Nodepq *queue = NULL;
    if(queue == NULL)
    {
        // now we set the weight of all the Nodes in the graph
        pnode cur = head;
        while (cur != NULL)
        {
            // this is not realy max value but good enofe
            if(cur->node_num == src)
            {
                cur->tag =0;
                cur->weight = 0;
            }
            else
            {
                cur ->tag = -1;
                cur->weight=100000;
            }
            cur = cur->next;
        }
        // this will start the queue with the first Node
        cur = GetNode(head,src);
        pedge Edges = cur->edges;
        if(Edges == NULL)
        {
            return -1;
        }
        queue = newNode(cur->node_num,Edges->endpoint->node_num,Edges->weight);
        Edges->endpoint->weight = Edges->weight;
        Edges->endpoint->tag = src;
        Edges = Edges->next;
        while (Edges != NULL)
        {
            push(&queue,cur->node_num,Edges->endpoint->node_num,Edges->weight);
            // this is the first start so we can just set the weight of the node dest to the weight of the Edge
            Edges->endpoint->weight=Edges->weight;
            Edges->endpoint->tag = src;
            Edges = Edges->next;
        }
    }
    while (!isEmpty(&queue))
    {
        Nodepq *queue_node = peek(&queue);
        pop(&queue);
        // we get the node we go to the dest of the Edge
        int s = queue_node->data[0];
        int d = queue_node->data[1];
        free(queue_node);
        pnode src = GetNode(head,s);
        pnode dest = GetNode(head,d);
        pedge Edges_dest=NULL;
        if(dest->edges != NULL)
        {
            Edges_dest = dest->edges;
        }
        while (Edges_dest != NULL)
        {
            // this is the weight of the dest of the Edge
            double Edges_dest_weighi = Edges_dest->endpoint->weight;
            // this is the weight of the Edge and the src ledding to the dest
            double Edges_weight_plus_Edge_src = Edges_dest->weight+dest->weight;
            // the curent weight is more then the new Edge leeding up to it 
            if(Edges_dest_weighi > Edges_weight_plus_Edge_src && Edges_dest->endpoint->node_num != src->node_num)
            {
                Edges_dest->endpoint->weight = Edges_weight_plus_Edge_src;
                Edges_dest->endpoint->tag = d;
                push(&queue,dest->node_num,Edges_dest->endpoint->node_num,Edges_weight_plus_Edge_src);
            }
            Edges_dest = Edges_dest->next;
            
        }
        if(d == end_dest)
        {
            break;
        }
    }
    pnode temp = GetNode(head,end_dest);
    // printf("the cost is = %d\n",temp->weight);
    return temp->weight;
}

// void path(pnode head,int src,int dest)
// {
//     pnode temp = GetNode(head,dest);
//     // this is not full prof but good enofe
//     shortsPath_cmd(head,src,dest);
//     char path[100];
//     int id;
//     int i = 0;
//     while(id != src && i < 100)
//     {
//         id = temp->tag;
//         path[i] = id;
//         i = i + 1;
//         temp = GetNode(head,id);
//     }
//     if(i == 99)
//     {
//         printf("%d",-1);
//     }
//     else
//     {
//         while (i >= 0)
//         {
//             printf(" %d ->",path[i]);
//             i = i-1;
//         }
//     }
// }

void TSP_cmd(pnode head)
{
    int final_sum =__INT_MAX__;
    int sum = 0;
    int size;
    scanf("%d",&size);
    int* citys = (int*)malloc(size *(sizeof(int)));
    int* copy = (int*)malloc(size *(sizeof(int)));
    for (int i = 0; i < size; i++)
    {
        scanf("%d",&citys[i]);
        copy[i] = citys[i];
    }
    // for (int j = 0; j < size-1; j++)
    // {
    //     sum += shortsPath_cmd(head,citys[j],citys[j+1]);
    // }

    int min_dist = __INT_MAX__;
    int location = -1;
    // bool indicator = false;
    for(int k = 0; k < size; k++)
    {
        pnode cur = GetNode(head,citys[k]);
        for(int j = 0; j < size-1; j++)
        {
            for (int i = 0; i < size; i++)
            {
                pnode city_node = GetNode(head,citys[i]);
                if(citys[i] != -1 && city_node->node_num != cur->node_num)
                {
                    // printf("src = %d dest = %d \n",cur->node_num,city_node->node_num);
                    int temp = shortsPath_cmd(head, cur->node_num, city_node->node_num);
                    // printf("temp = %d\n",temp);
                    if(temp == -1)
                    {
                        temp = __INT_MAX__;
                    }
                    if(min_dist > temp)
                    {
                        min_dist = temp;
                        location = i;
                    }
                }
            }
            cur = GetNode(head,citys[location]);
            if(min_dist != __INT_MAX__ && sum != __INT_MAX__)
            {
                // printf("min_dist = %d\n",min_dist);
                sum += min_dist;
            }
            else
            {
                sum = __INT_MAX__;
            }
            if(location != -1)
            {
                citys[location] = -1;
            }
            min_dist = __INT_MAX__;
            location = -1;
        }
        for (int e = 0; e < size; e++)
        {
            citys[e] = copy[e];
        }
        // printf("sum = %d\n",sum);
        if(final_sum>sum)
        {
            final_sum = sum;
        }
        // printf("final_sum = %d\n",final_sum);
        sum = 0;
    }
    if(final_sum == __INT_MAX__)
    {
        final_sum = -1;
    }
    printf("TSP shortest path: %d \n",final_sum);
}