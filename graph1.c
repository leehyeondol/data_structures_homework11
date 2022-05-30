#include <stdio.h>
#include <stdlib.h>


#define MAX_VERTEX 10

typedef struct Vertex {
   int num;
   struct Vertex* link;
} Vertex;

typedef struct VertexHead {
   Vertex* head;
} VertexHead;

typedef struct Graph {
   VertexHead* vlist;
} Graph;


void createGraph(Graph** g);
void insertVertex(VertexHead* vh);
void insertEdge(VertexHead* vh);
int depthFS(VertexHead* vh);
int breadthFS(VertexHead* vh);
void printGraph(VertexHead* vh);
void printmenu();

void push(int* stack, int* top, int num);
void pop(int* top);
void enQueue(int* Queue, int* front, int rear, int num);
int deQueue(int* Queue, int front, int* rear);


void destoryGraph(Graph** g);

int main()
{
    Graph *mygraph;
    mygraph = NULL;

    int delete_v;
    char command;

    do {
        printf("\n\n");
        printf("-----------------[2019038085] [lee hyeondo]----------------------\n");
        printf("                       Graph Searches                            \n");
        printf("-----------------------------------------------------------------\n");
        printf(" Initialize Graph = z                                            \n");
        printf(" Insert Vertex = v              Insert Edge = e                  \n");
        printf(" Depth First Search = d         Breath First Search = b          \n");
        printf(" Print Graph =  p               Quit = q                         \n");
        
        printf("Command = ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'z': case 'Z':
            createGraph(&mygraph);
            break;
        case 'v': case 'V':
            if (mygraph != NULL)
                insertVertex(mygraph->vlist);
            else
                printf("\ncreateGraph first!");
            break;
        case 'e': case 'E':
            if (mygraph != NULL)
                insertEdge(mygraph->vlist);
            else
                printf("\ncreateGraph first!");
            break;
        case 'p': case 'P':
            if (mygraph != NULL)
                printGraph(mygraph->vlist);
            break;
        case 'd': case 'D':
            if (mygraph != NULL)
                depthFS(mygraph->vlist);
            else
                printf("\ncreateGraph first!");
            break;
        case 'b': case 'B':
            if (mygraph != NULL)
                breadthFS(mygraph->vlist);
            else
                printf("\ncreateGraph first!");
            break;
        case 'q': case 'Q':
                break;
        default:
            printf("\nchoose correct menu!");
            break;
        }
    } while (command != 'q' && command != 'Q');

    return 1;
}


void createGraph(Graph** g)
{
   if (*g != NULL)
      destoryGraph(g);
   *g = (Graph*)malloc(sizeof(Graph));
   (*g)->vlist = (VertexHead*)malloc(sizeof(VertexHead)*MAX_VERTEX);
   for (int i = 0; i < MAX_VERTEX; i++)
      (*g)->vlist[i].head = NULL;
}

void destoryGraph(Graph** g)
{
   int i;
   for (i = 0; i < MAX_VERTEX; i++)
      if ((*g)->vlist[i].head != NULL)
         (*g)->vlist[i].head = NULL;
   free((*g)->vlist);
   free(*g);
   *g = NULL;
}



void enQueue(int* Queue, int* front, int rear, int num)
{
   if ((*front + 1) % MAX_VERTEX + 1 != rear)  
   {
      *front = (*front + 1) % MAX_VERTEX;
      Queue[*front] = num;
   }
   else
      printf("\n\nQueue is full!\n");
}


int deQueue(int* Queue, int front, int* rear)
{
   int key;
   if (front != *rear)
   {
      *rear = (*rear + 1) % MAX_VERTEX;
      key = Queue[(*rear)];
      printf("%d ", key);
      return key;
   }
   else
      printf("\n\nQueue is empty!\n");
   return -1;
}



void push(int* stack, int* top, int num)
{
   printf("%d ", num); 
   stack[++(*top)] = num;
}


void pop(int* top)
{
   (*top)--;
}



void printGraph(VertexHead* vh)
{
   int i;
   Vertex* temp;
   for (i = 0; i < MAX_VERTEX; i++)
   {
      if (vh[i].head != NULL)
      {
         printf("\nindex[%d]: %d  -  ", i, vh[i].head->num);
         temp = vh[i].head->link;
         while (temp != NULL)
         {
            printf(" - %d ", temp->num);
            temp = temp->link;
         }
      }
   }
}


void insertEdge(VertexHead* vh)
{

}


void insertVertex(VertexHead* vh)
{

}



int breadthFS(VertexHead* vh)
{

}


int depthFS(VertexHead* vh)
{

}

