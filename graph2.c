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
   int n1, n2;
   Vertex* find;
   Vertex* v1;
   Vertex* v2;

   printf("연결할 Vertex1: ");
   scanf("%d", &n1);
   printf("연결할 Vertex2: ");
   scanf("%d", &n2);

 
   if (vh[n1].head != NULL && vh[n2].head != NULL)   
   {
      v1 = (Vertex*)malloc(sizeof(Vertex));
      v1->num = n2;
      v1->link = NULL;

      v2 = (Vertex*)malloc(sizeof(Vertex));
      v2->num = n1;
      v2->link = NULL;


      find = vh[n1].head;
      while (find->link != NULL)
         find = find->link;
      find->link = v1;

      find = vh[n2].head;
      while (find->link != NULL)
         find = find->link;
      find->link = v2;
   }
   else
      printf("\nCannot find Vertex");
}


void insertVertex(VertexHead* vh)
{
   int key;

   printf("Vertex: ");
   scanf("%d", &key);

   if (0 <= key && key < 20)
   {
      Vertex *new;
      new = (Vertex*)malloc(sizeof(Vertex));  
      vh[key].head = new;

      vh[key].head->num = key;
      vh[key].head->link = NULL;
   }
   else
      printf("\nInput number in range(0,19)");
}



int breadthFS(VertexHead* vh)
{
   int visited[MAX_VERTEX];   
   int Queue[MAX_VERTEX];
   memset(visited, 0, sizeof(visited)); 

   int v, i, key, front, rear;
   front = -1;
   rear = -1;
   Vertex* temp; 

   printf("First Vertex: ");
   scanf("%d", &v); 

   if (vh[v].head == NULL)
   {
      printf("First vertex[%d] doesn't exist", v);
      return 0;
   }

   printf("\nBreath First Search: ");
   temp = vh[v].head;
   visited[temp->num] = 1;
   enQueue(Queue, &front, rear, temp->num); 

   do {
      key = deQueue(Queue, front, &rear);
      if (key == -1)
         return 0;
      temp = vh[key].head->link;
      while (temp != NULL)
      {
         if (visited[temp->num] == 0)
         {
            visited[temp->num] = 1;
            enQueue(Queue, &front, rear, temp->num);
         }
         temp = temp->link;
      }
   } while (front != rear);
}


int depthFS(VertexHead* vh)
{
   int visited[MAX_VERTEX]; 
   int stack[MAX_VERTEX];
   memset(visited, 0, sizeof(visited)); 

   int v, i, top;
   top = -1;
   Vertex* temp;  
   Vertex* temp2;  
   
   printf("First Vertex: ");  
   scanf("%d", &v);

  
   if (vh[v].head == NULL)
   {
      printf("First vertex[%d] doesn't exist", v);
      return 0;
   }

   printf("\nDepth First Search: ");
   temp = vh[v].head;
   do
   {
      if (visited[temp->num] == 0)   
      {
         push(stack, &top, temp->num);
         visited[temp->num] = 1;  
         temp2 = temp->link;
         while (temp2 != NULL) 
         {
            if (visited[temp2->num] == 0)
            {
               temp = vh[temp2->num].head;
               break;
            }
            temp2 = temp2->link;
         }
         if (temp2 == NULL) 
         {
            pop(&top); 
            temp = vh[stack[top]].head;
         }
      }
      else
      {  
         temp2 = temp->link;
         while (temp2 != NULL) 
         {
            if (visited[temp2->num] == 0)
            {
               temp = vh[temp2->num].head;
               break;
            }
            temp2 = temp2->link;
         }
         if (temp2 == NULL)
         {
            pop(&top);
            if (top != -1)
               temp = vh[stack[top]].head;
         }
      }
   } while (top != -1);

   return 0;
}

