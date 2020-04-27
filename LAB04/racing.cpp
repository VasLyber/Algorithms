#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define BSIZE 1<<15
long int K , L ,cnt;
long int  *time ; 
int * city,*aux;

struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode* next;
};
 

struct AdjList
{
    struct AdjListNode *head;  
};
 

struct Graph
{
    int V;
    struct AdjList* array;
};
 
struct AdjListNode* newAdjListNode(int dest, int weight)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
 

struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
int i ;
    graph->V = V;
 
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
    for  (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 int compare(const void *a, const void *b)
{
    const long int *ia = (const long int *)a; 
    const long int *ib = (const long int *)b;
    if (*ia > *ib)
        return 1 ;
    else
        return (*ia < *ib) ? -1:0 ;
}

void addEdge(struct Graph* graph, int src, int dest, int weight)
{

    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
 
struct MinHeapNode
{
    int  v;
    int dist;
};
 
struct MinHeap
{
    int size;     
    int capacity;  
    int *pos;    
    struct MinHeapNode **array;
};
 
struct MinHeapNode* newMinHeapNode(int v, int dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
char buffer[BSIZE];
long bpos = 0L, bsize = 0L;

long readLong() 
{
	long d = 0L, x = 0L;
	char c;

	while (1)  {
		if (bpos >= bsize) {
			bpos = 0;
			if (feof(stdin)) return x;
			bsize = fread(buffer, 1, BSIZE, stdin);
		}
		c = buffer[bpos++];
		if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
		else if (d == 1) return x;
	}
	return -1;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
void minHeapify(struct MinHeap * minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if ((left < minHeap->size) && (minHeap->array[left]->dist < minHeap->array[smallest]->dist))
      smallest = left;
 
    if ((right < minHeap->size) && (minHeap->array[right]->dist < minHeap->array[smallest]->dist))
      smallest = right;
 
    if (smallest != idx)
    {
        struct MinHeapNode * smallestNode = minHeap->array[smallest];
        struct MinHeapNode * idxNode = minHeap->array[idx];
 
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}
 
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
    struct MinHeapNode* root = minHeap->array[0];
 
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 

void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    int i = minHeap->pos[v];
 
    minHeap->array[i]->dist = dist;
 

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {

        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
 

        i = (i - 1) / 2;
    }
}
 
int isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return 1;
   return 0;
}
 

void printArr(int dist[], int n)
{
	int i ;
    printf("Vertex   Distance from Source\n");
    for (i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
 

void dijkstra(struct Graph* graph, int B)
{
    int V = graph->V;
    int dist[V];      
    int i,v ;
    int next,curr,remain,done;
    int A ; 
    long int total;

    struct MinHeap* minHeap = createMinHeap(V);
    struct AdjListNode* tmp ;

    for ( v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
    for (i=0 ; i < B ; i++){
        A = readLong(); 
        dist[A] = 0;
    	decreaseKey(minHeap, A, 0);
    }
        
    minHeap->size = V;
 

    while (!isEmpty(minHeap))
    {

        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        if (aux[u] == 1){
            time[cnt] = dist[u];
            cnt++;
        }

        struct AdjListNode* ptr = graph->array[u].head;
        while (ptr != NULL)
        {
            int v = ptr->dest;
 
            if ((isInMinHeap(minHeap, v)) && (ptr->weight + dist[u] < dist[v]))
            {
                dist[v] = dist[u] + ptr->weight;
                
                decreaseKey(minHeap, v, dist[v]);
            }
            ptr = ptr->next;
        }
    }
 	total = 0 ; 
    for (i=0 ; i < L;i++){
        total += time[i];
    }    
    remain = 1 ;
    done = 0 ; 
    next = city[0];
     
    while (remain <= K){
        curr = next ;
        next = city[remain];
        
        tmp = graph->array[curr].head;
        
        while ((tmp)&&(!done)){
            if (tmp->dest == next){
                total += tmp->weight;
                done = 1 ;
            }
            tmp = tmp->next;
        }
        remain++;
        done = 0 ;
    }
    printf("%lu\n",total);

}

int main()
{

    int V,M,B,i,src,dst,weight,A;
	V = readLong()+1;
    
    struct Graph* graph = createGraph(V);
    M = readLong();
    K = readLong();	    
    L = readLong();
    B = readLong();
    city = (int*) malloc(K*sizeof(int));
    aux = (int*) malloc(V*sizeof(int));
    for (i=0 ; i < V  ; i++){
        aux[i] = 0 ;
    }

    for (i=0 ; i< M ; i++){
        src = readLong();
        dst = readLong();
        weight = readLong();
        addEdge(graph,src,dst,weight);
    }
    A = readLong();
    city[0] = A ; 
    for (i=1 ; i < K-1 ; i++){
        A = readLong();
        aux[A] = 1 ;
        city[i]= A ; 
    }
    A = readLong();
    city[K-1] = A ; 
    cnt = 0 ; 
    time = (long int*) malloc (K * sizeof(long int ));
    dijkstra(graph, B);
    
    return 0;
}

