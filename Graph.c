//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//
// sindurka 1644073 pa3
//
//-----------------------------------------------------------------------------



#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Graph.h"


// structs --------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj{
    int order; //number of vertices
    int size; // number of edges
    int source; //label (index) of the last used source vertex
    List* adj_list;
    char* color;
    int* parent;
    int* dist;
} GraphObj;

// private Graph type
typedef GraphObj* Graph;

// Constructors-Destructors ---------------------------------------------------
// newGraph()
// Returns a reference to a new Graph object in the zero state.
Graph newGraph( int n)
{
    Graph N = malloc(sizeof(GraphObj));
    N->order = n; //number of vertices
    N->size = 0; // number of edges
    N->source = NIL; //label (index) of the last used source vertex

    N->adj_list = malloc(  sizeof( List) * (n+1) );
    //initialize the array of newLists
    for ( int i = 1 ; i <=N->order; i++ ) {
        N->adj_list[i] = newList();
    }

    N->color = malloc(  sizeof( char ) * (n+1) );
    //intialize the color array to all white
    for ( int i = 1 ; i<=N->order; i++ ) {
        N->color[i] = 'w';
    }

    N->parent = malloc(  sizeof( int ) * (n+1) );
    //intialize the parent array to all NIL
    for ( int i = 1 ; i<=N->order; i++ ) {
        N->parent[i] = NIL;
    }

    N->dist = malloc(  sizeof( int ) * (n+1) );
    //intialize the dist array to all INF
    for ( int i = 1 ; i<=N->order; i++ ) {
        N->dist[i] = INF;
    }
    return N;
}

// freeGraph()
// Frees heap memory associated with *pG, sets *pG to NULL.
void freeGraph(Graph* pG)
{

    Graph N = *pG;
    if ((pG != NULL) && (*pG != NULL)) {
        //initialize the array of newLists
        for ( int i = 1 ; i <=N->order; i++ ) {
            freeList( & N->adj_list[i]);
        }
        free(*pG); 
        *pG = NULL; 
    }
}


/*** Access functions ***/
int getOrder(Graph G)
{
    return G->order;
}


int getSize(Graph G)
{
    return G->size;
}


int getSource(Graph G)
{
    return G->source; 
}


int getParent(Graph G, int u)
{
    if ( u > getOrder(G) || u <= 0 ) {
        printf("ERROR: called getParent with invalid index %d, order = %d\n", u, G->order);
        exit(1);
    }
    return G->parent[u]; 
}


int getDist(Graph G, int u)
{
    if ( u > getOrder(G) || u <= 0 ) {
        printf("ERROR: called getDist with invalid index %d, order = %d\n", u, G->order);
        exit(1);
    }
    return G->dist[u];
}


void getPath(List L, Graph G, int u)
{
    if ( u > getOrder(G) || u <= 0 ) {
        printf("ERROR: called getPath with invalid index %d, order = %d\n", u, G->order);
        exit(1);
    }
    if ( getSource(G) == NIL ) {
        printf("ERROR: called getPath before calling BFS\n");
        exit(1);
    }
    if ( G->source == 'w' ) {
        printf("ERROR: calling getpath but BFS not ran on %d\n", G->source); 
        exit(1); 
    }
    if (u == G->source ) {
        append(L, G->source); 
    }
    else if (G->parent[u] == NIL ) {
        append( L, NIL); 
        G->dist[u] = INF;
    }
    else {
        getPath(L, G, G->parent[u]);
        append(L, u); 
    }
    return;
}


/*** Manipulation procedures ***/
void makeNull(Graph G)
{
    
    //empty the array of Lists
    for ( int i = 1 ; i <=G->order; i++ ) {
        clear(G->adj_list[i]);
    }
    G->size = 0; 
    return;

}



void addEdge(Graph G, int u, int v)
{
    if ( u > getOrder(G) || u <= 0 ) {
        printf("ERROR: called addEdge with invalid index u %d, order = %d\n", u, G->order);
        exit(1);
    }
    if ( v > getOrder(G) || v <= 0 ) {
        printf("ERROR: called addEdge with invalid index v %d, order = %d\n", v, G->order);
        exit(1);
    }
    G->size++;
    //add u to v's list
    insertInOrder( G->adj_list[v], u);
    //add v to u's list
    insertInOrder( G->adj_list[u], v);
    return;

}


void addArc(Graph G, int u, int v)
{
    if ( u > getOrder(G) || u <= 0 ) {
        printf("ERROR: called getPath with invalid index %d, order = %d\n", u, G->order);
        exit(1);
    }
    if ( v > getOrder(G) || v <= 0 ) {
        printf("ERROR: called getPath with invalid index %d, order = %d\n", v, G->order);
        exit(1);
    }
    G->size++;
    //add v to u's list
    insertInOrder( G->adj_list[u], v);
    return;
}


void BFS(Graph G, int s)
{
    G->source = s;
    for ( int i = 1; i <= G->order; i++ ) {
        if ( i == s) continue; 

        G->color[i] = 'w'; 
        G->dist[i] = INF; 
        G->parent[i] = NIL; 
    }

    G->color[s] = 'g'; 
    G->dist[s] = 0; 
    G->parent[s] = NIL; 
    List Q = newList(); 
    append(Q, s);
    while ( length(Q) > 0 ) {
        int x = front(Q); 
        //printf("%d\n\n", x);   // to print out the Q
        deleteFront(Q); 
        //for each element in x's adj list
        if ( length(G->adj_list[x]) != 0  ) {
            moveFront(G->adj_list[x]); 
            for ( int i = 0; i < length(G->adj_list[x]) ; i++ ) {
                int y = get(G->adj_list[x]);
                if ( G->color[y] == 'w' ) {
                    G->color[y] = 'g'; 
                    G->dist[y] = G->dist[x] + 1; 
                    G->parent[y] = x;
                    append(Q, y); 
                }
                moveNext(G->adj_list[x]);
            }
            G->color[x] = 'b'; 
        }
    }
    freeList(&Q); 
    return;

}


/*** Other operations ***/
void printGraph(FILE* out, Graph G)
{
    for ( int i = 1; i<=G->order; i++ ) {
        fprintf(out, "%d: ", i);
        if ( length(G->adj_list[i]) > 0) {
            printList(out, G->adj_list[i]);
        }
        fprintf(out, "\n");
    }
    return;

}



// EOF
//
//



