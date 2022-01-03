#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"

int main()
{
    pnode head = NULL;
    pnode *P_head = &head;
    char input = ' ';
    while(scanf("%c", &input) != EOF)
    {
        if (input == 'A')
        {
            build_graph_cmd(P_head);
            // printf("\n");
            // printf("print\n");
            // printGraph_cmd(*P_head);
        }
        else if (input == 'D')
        {
            delete_node_cmd(P_head);
            // printf("\n");
            // printf("print\n");
            // printGraph_cmd(*P_head);
        }
        else if(input == 'B')
        {
            insert_node_cmd(P_head);
            // printf("\n");
            // printf("print\n");
            // printGraph_cmd(*P_head);
        }
        else if(input == 'S') 
        {
            int src = -1;
            int end_dest = -1;
            scanf("%d%d",&src,&end_dest);
            printf("Dijsktra shortest path: %d \n",shortsPath_cmd(*P_head,src,end_dest));
        }
        else if(input == 'T') 
        {
            TSP_cmd(*P_head);
        }
    }
    // printf("\n");
    // printf("print\n");
    // printGraph_cmd(*P_head);
    return 0;
}