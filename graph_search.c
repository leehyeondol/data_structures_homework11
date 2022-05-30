#include <stdio.h>
#include <stdlib.h>
#include <string.h>//memset함수를 사용하기 위한 string 헤더

#define MAX_VERTEX 10//최대 벌텍스 크기 10

typedef struct Vertex {//벌텍스 구조체 생성
   int num;//정수형 변수 생성
   struct Vertex* link;//벌텍스형 포인터 링크 생성
} Vertex;//별명

typedef struct VertexHead {//구조체 벌텍스 해드 생성
   Vertex* head;//벌텍스형 해드 생성
} VHead;//별명

typedef struct Graph {//그래프 구조체 생성
   VHead* vlist;//벌택스 해드형 vlist 생성
} Graph;//별명

void initializegraph(Graph** g);//초기화 함수
void insertVer(VHead* vh);//벌텍스 입력함수
void insertEd(VHead* vh);//간선 입력함수
int depthFirstSearch(VHead* vh);//깊이우선탐색 함수
int breadthFirstSearch(VHead* vh);//너비 우선탐색 함수
void printGraph(VHead* vh);//그래프 출력 함수

void push(int* stack, int* top, int num);//스택에 푸시 함수
void pop(int* top);//스택의 팝 함수
void enQueue(int* Queue, int* front, int rear, int num);//큐의 입력 함수
int deQueue(int* Queue, int front, int* rear);//큐의 삭제 함수

void freeGraph(Graph** g);//그래프 메모리 삭제 함수

int main()
{
    Graph *mgraph;//그래프 변수 생성
    mgraph = NULL;//그래프 초기화
    char command;//커멘드 변수 생성
    do {//while의 조건에 따라 반복
        printf("\n\n");//메뉴 출력
        printf("-----------------[2019038085] [lee hyeondo]----------------------\n");
        printf("                       Graph Searches                            \n");
        printf("-----------------------------------------------------------------\n");
        printf(" Initialize Graph = z                                            \n");
        printf(" Insert Vertex = v              Insert Edge = e                  \n");
        printf(" Depth First Search = d         Breath First Search = b          \n");
        printf(" Print Graph =  p               Quit = q                         \n");
        printf("-----------------------------------------------------------------\n");
        
        printf("Command = ");
        scanf(" %c", &command);//커멘드 입력

        switch (command)//커면드에 따라 선택 됨
        {
        case 'z': case 'Z'://z면
            initializegraph(&mgraph);//그래프 초기화
            break;
        case 'v': case 'V'://v면
            if (mgraph != NULL)//그래프가 존재하면
                insertVer(mgraph->vlist);//벌텍스 입력함수 호출
            else
                printf("\n Do not initialize");
            break;
        case 'e': case 'E'://e면
            if (mgraph != NULL)//그래프가 존재하면
                insertEd(mgraph->vlist);//간선 입력함수 호출
            else
                printf("\nDo not initialize");
            break;
        case 'p': case 'P'://p면
            if (mgraph != NULL)//그래프가 존재하면
                printGraph(mgraph->vlist);//그래프 출력함수 호출
            break;
        case 'd': case 'D'://d면
            if (mgraph != NULL)//그래프가 존재하면
                depthFirstSearch(mgraph->vlist);//깊이우선탐색함수 호출
            else
                printf("\nDo not initialize");
            break;
        case 'b': case 'B'://b면
            if (mgraph != NULL)//그래프가 존재하면
               breadthFirstSearch(mgraph->vlist);//너비우선탐색함수 호출
            else
               printf("\nDo not initialize");
            break;
        case 'q': case 'Q'://q면
            if(mgraph!=NULL)//그래프가 존재하면
               freeGraph(&mgraph);//메모리 삭제 함수 호출
            else
               printf("\nDo not initialize");
            break;
        default://지정된 커멘드가 아니면
            printf("\n >>>>>   Concentration!!   <<<<< ");//집중! 호출
            break;
        }
    } while (command != 'q' && command != 'Q');//q거나 Q면 반복 종료

    return 1;
}


//그래프를 만드는 함수.다른 명령어들 사용전에 필수적으로 제일먼저 사용해야함

void initializegraph(Graph** g)//초기화 함수
{
    if (*g != NULL)//g가 비어있지않으면
        freeGraph(g);//그래프 초기화
    *g = (Graph*)malloc(sizeof(Graph));//동적할당
    (*g)->vlist = (VHead*)malloc(sizeof(VHead)*MAX_VERTEX);//맥스벌텍스 크기만큼 동적할당
    for (int i = 0; i < MAX_VERTEX; i++)//멕스 벌텍스 크기만큼 반복
        (*g)->vlist[i].head = NULL;//모두 NULL
}

void freeGraph(Graph** g)//그래프 삭제 함수
{
    int i;
    for (i = 0; i < MAX_VERTEX; i++)//멕스 벌텍스 크기만큼 반복
        if ((*g)->vlist[i].head != NULL)//헤드가 NULL이 아니면
            (*g)->vlist[i].head = NULL;//헤드 NULL로 초기화
    free((*g)->vlist);//동적할당 해제
    free(*g);//동적할당 해제
    *g = NULL;
}




void enQueue(int* Queue, int* front, int rear, int num)//큐 입력함수
{
    if ((*front + 1) % MAX_VERTEX + 1 != rear)   //순환 큐 구현 및 큐가 가득 차있는지 확인
    {
        *front = (*front + 1) % MAX_VERTEX;//다음 칸으로 이동
        Queue[*front] = num;//입력
    }
    else
        printf("\n\n full! \n");
}


int deQueue(int* Queue, int front, int* rear)//큐 삭제 함수
{
    int key;
    if (front != *rear)//순환 큐 구현 및 큐가 비어있는지 확인
    {
        *rear = (*rear + 1) % MAX_VERTEX;//다음칸으로 이동
        key = Queue[(*rear)];//이동된 값 키에 입력
        printf("%d ", key);
        return key;
    }
    else
        printf("\n\n empty! \n");
    return -1;
}


void push(int* stack, int* top, int num)//push함수
{
    printf("%d ", num);//트리의 preorder과 비슷하기에 push할 때 출력
    stack[++(*top)] = num;// 탑 +1에 num입력
}


void pop(int* top)//pop 함수
{
    (*top)--;//탑 값 -1
}


void printGraph(VHead* vh)//그래프 출력 함수
{
    int i;
    Vertex* p;//temp 역할 수행할 벌텍스
    for (i = 0; i < MAX_VERTEX; i++)//맥스 벌텍스 만큼 반복
    {
        if (vh[i].head != NULL)//벌텍스 해드가 NULL이 아닌동안
        {
            printf("\nindex[%d]: %d  ", i, vh[i].head->num);//그래프 출력
            p = vh[i].head->link;//한칸이동
            while (p != NULL)//p가 NULL될때까지
            {
                printf(" - %d ", p->num);//다음 값에 num 출력
                p = p->link;//한칸 이동
            }
        }
    }
}


void insertEd(VHead* vh)//Edge를 생성하여 Vertex를 연결하는 함수
{
    int n1, n2;
    Vertex* p;
    Vertex* v1;
    Vertex* v2;

    printf("link Vertex1: ");
    scanf("%d", &n1);
    printf("link Vertex2: ");
    scanf("%d", &n2);

    if (vh[n1].head != NULL && vh[n2].head != NULL)//둘 다 선언된 Vertex이면
    {
        v1 = (Vertex*)malloc(sizeof(Vertex));//동적할당 및 초기화
        v1->num = n2;//v1에 n2 입력
        v1->link = NULL;

        v2 = (Vertex*)malloc(sizeof(Vertex));//동적할당 및 초기화
        v2->num = n1;//v2에 n1 입력
        v2->link = NULL;


        p = vh[n1].head;
        while (p->link != NULL)//p의 링크가 NULL일때까지
            p = p->link;//마지막 값까지 이동
        p->link = v1;//마지막에 초기화한 v1입력

        p = vh[n2].head;
        while (p->link != NULL)//p의 링크가 NULL일때까지
            p = p->link;//마지막 값까지 이동
        p->link = v2;//마지막에 초기화한 v2입력
    }
    else
        printf("\nCannot find Vertex");
}


/*
Vertex를 제작할 때 연결된 노드를 하나 만들고
해당 노드의 num은 Vertex와 동일하게 만듬
즉, Vertex생성시 하나의 노드가 같이 생성되고
이것을 Vertex가 사용여부를 판단함 
*/

void insertVer(VHead* vh)//Vertex를 생성 함수
{
    int key;

    printf("Vertex(0~9): ");
    scanf("%d", &key);// 키 입력받음 

    if (0 <= key && key < 10)//키가 0부터 9사이 값이면
    {
        Vertex *new;//벌택스 new 생성
        new = (Vertex*)malloc(sizeof(Vertex));//index, 즉 Vertex를 나타낼 노드생성
        vh[key].head = new;//생성된 new 값 입력

        vh[key].head->num = key;//키값 입력된 벌텍스.해드의 num에 키 입력
        vh[key].head->link = NULL;//링크는 NULL로 초기화
    }
    else
        printf("\n Input num(0~9)");
}


int breadthFirstSearch(VHead* vh)//너비 우선 탐색 함수. iterative 방식
{
    int visited[MAX_VERTEX];//방분기록을 저장할 배열(0이면 미방문, 1이면 방문했음)
    int Queue[MAX_VERTEX];//큐 생성
    memset(visited, 0, sizeof(visited));//memset 함수를 이용하여 방문기록 초기화

    int v, i, key, front, rear;
    front = -1;
    rear = -1;
    Vertex* temp;//Vertex 탐색을 위한 포인터

    printf("First Vertex: ");
    scanf("%d", &v);//처음 탐색을 시작할 노드 입력

    if (vh[v].head == NULL)//입력한 벌택스가 없으면
    {
        printf("First Vertex[%d] not found", v);//없음을 출력
        return 0;
    }

    printf("\nBreath First Search: ");
    temp = vh[v].head;//입력받은 벌텍스의 헤드 값 temp에 입력
    visited[temp->num] = 1;//시작 노드의 방문기록을 저장
    enQueue(Queue, &front, rear, temp->num);//시작 노드를 큐에 저장

    do {//반복
        key = deQueue(Queue, front, &rear);//큐에 있는 노드를 출력하여 key에 입력
        if (key == -1)//큐가 비어 있으면
            return 0;//종료
        temp = vh[key].head->link;//temp에 다음 노드 입력
        while (temp != NULL)//temp가 NULL이 될때까지 반복
        {
            if (visited[temp->num] == 0)//방문전적이 없는 경우
            {
                visited[temp->num] = 1;//방문 했음을 입력
                enQueue(Queue, &front, rear, temp->num);//방문한 노드값 큐에 입력
            }
            temp = temp->link;//다음 인접 노드를 탐색
        }
    } while (front != rear);//큐가 빌 때까지 반복
}



int depthFirstSearch(VHead* vh)//깊이 우선 탐색 함수. iterative 방식
{
    int visited[MAX_VERTEX];//방분기록을 저장할 배열(0이면 미방문, 1이면 방문)
    int stack[MAX_VERTEX];//스택 배열
    memset(visited, 0, sizeof(visited));//방문기록 초기화. memset함수 이용

    int v, i, top;
    top = -1;
    Vertex* temp;//Vertex를 탐색하기 위한 포인터
    Vertex* temp2;//인접 노드를 탐색하기 위한 포인터
    
    printf("First Vertex: ");//처음 탐색을 시작할 벌택스 입력
    scanf("%d", &v);//입력

    
    //벌택스가 선언되어 있는지 확인 
    if (vh[v].head == NULL)//입력받은 벌택스의 헤드가 없으면
    {
        printf("First Vertex[%d] not found", v);//없음을 출력
        return 0;
    }

    printf("\nDepth First Search: ");
    temp = vh[v].head;//입력받은 벌텍스의 해드를 temmp에 입력
    do//반복
    {
        if (visited[temp->num] == 0)//방문전적이 없는 경우
        {
            push(stack, &top, temp->num);//스택에 num 푸시
            visited[temp->num] = 1;//방문기록을 1로 수정
            temp2 = temp->link;//다음으로 이동
            while (temp2 != NULL)//인접노드들 탐색
            {
                if (visited[temp2->num] == 0)//방문한적 없느경우
                {
                temp = vh[temp2->num].head;//temp에 방문한적 없는 벌텍스 입력
                break;//while문 빠져나오기
                }
                temp2 = temp2->link;//방문한적 있었으면 다음으로 이동
            }
            if (temp2 == NULL)//인접노드들이 존재하지 않거나 전부 다 방문했을 경우
            {
                pop(&top);//벌텍스를 pop
                temp = vh[stack[top]].head;//방문여부 확인
            }
        }
        else//벌텍스를 이미 방문한 경우
        {   
            temp2 = temp->link;//temp2에 temp의 다음 입력
            while (temp2 != NULL)//인접노드를 탐색
            {
                if (visited[temp2->num] == 0)//방문한적 없는 경우
                {
                temp = vh[temp2->num].head;//temp에 방문한적 없는 벌텍스 입력
                break;//반복문 탈출
                }
                temp2 = temp2->link;//방문한적 있었으면 다음으로 이동
            }
            if (temp2 == NULL)   //인접노드들이 존재하지 않거나 전부 다 방문했을 경우
            {
                pop(&top);//벌텍스를 pop
                if (top != -1)//만약 top이 -1 이면
                    temp = vh[stack[top]].head;//방문 여부 확인
            }
        }
    } while (top != -1);//top이 -1 일때까지. 스택이 전부 빌때까지.

    return 0;
}

