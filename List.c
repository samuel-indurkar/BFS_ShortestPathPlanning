//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//
// sindurka 1644073 pa3
//
//-----------------------------------------------------------------------------



#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include "List.h"


// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   data_type data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj {
   NodeObj* frontNode;
   NodeObj* backNode;
   NodeObj* cursorNode;
   int cursor;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
NodeObj* newNode(data_type data)
{
   NodeObj* N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN)
{
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void)
{
   List Q;
   Q = malloc(sizeof(ListObj));
   Q->cursorNode = Q->frontNode = Q->backNode = NULL;
   Q->cursor = -1;
   return(Q);
}


// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.S
void freeList(List* pQ)
{
    
    List L = *pQ;

    if(pQ!=NULL && *pQ!=NULL) {  
            while( length( L )   > 0) { 
                if (length(L) == 1) {
                    L->backNode = NULL;
                    L->cursorNode= NULL;
                    freeNode(&L->frontNode);
                    L->frontNode = NULL;
                }
                else{
                    deleteBack(*pQ);
                }
            }

        free(*pQ);
        *pQ = NULL;
   }
}


// Access functions -----------------------------------------------------------
int length(List L)
{ // Returns the number of elements in L.
    int count = 0; 
    NodeObj* N = L->frontNode;
    if( N == NULL) return 0;
    while ( N != NULL){
        count++;
        N = N->next; 
    }
    return count; 
}

int my_index(List L)
{ // Returns my_index of cursor element if defined, -1 otherwise.
    return L->cursor;
}

data_type front(List L)
{ // Returns front element of L. Pre: length()>0
    if( length(L) > 0){
        return L->frontNode->data;
    }
    printf("ERROR: you called command: Front on a list which is empty\n");
    exit(1);
}

data_type back(List L)
{ // Returns back element of L. Pre: length()>0
    if(length(L) > 0) return L->backNode->data;
    printf("ERROR: you called command: Back on a list which is empty\n");
    exit(1);
}

data_type get(List L)
{ // Returns cursor element of L. Pre: length()>0, my_index()>=0
    if(length(L) < 0){
        printf("ERROR: you are trying to get an element of an empty list\n");
        exit(1); 
    }
    if(my_index(L) < 0){
        printf("ERROR: you are trying to get the element at "
                "pos. cursor which is undef.\n");
        exit(1); 
    }
    L->cursorNode = L->frontNode; 
    for(int i = 0; i<my_index(L); i++){
        L->cursorNode = L->cursorNode->next;
    }
    return L->cursorNode->data; 
}

int equals(List A, List B)
{
    return listCompare(A, B);
}

int listCompare(List A, List B)
{ // Returns true (1) iff Lists A and B are in same
 // state, and returns false (0) otherwise.
    NodeObj* AQ = A->frontNode; 
    NodeObj* BQ = B->frontNode; 
    if( length(A) != length(B)) return 0;
    for (int i =0 ; i < length(A); i++){
        if (AQ->data != BQ->data) return 0;
        AQ = AQ->next;
        BQ = BQ->next;
    }
    return 1;
}
        

// Manipulation procedures ----------------------------------------------------
void clear(List L)
{ // Resets L to its original empty state.
    //NodeObj* N = L->backNode;
    //while(N->prev != NULL){
        //L->backNOde = N->prev;
        //free(N); 
        //if(L->backNode->data == L->frontNode->data){ //PROBLEM here List: [1,1] front data = back data but list isn't down to just one element. 
            //N = L->frontNode; 
            //free(N); 
            //L->frontNode = L->backNode = NULL;
    //}
    freeList(&L);
    L = newList();
}
void moveFront(List L)
{ // If L is non-empty, sets cursor under the front element,
    if(length(L) != 0){
        L->cursor = 0;
        L->cursorNode = L->frontNode; 
    }
    else{
        printf("you called 'moveFront' on an empty list\n");
        exit(1); 
    }
}

 // otherwise does nothing.
void moveBack(List L)
{ // If L is non-empty, sets cursor under the back element,
    if(length(L) != 0){
        L->cursor = length(L)-1;
        L->cursorNode = L->backNode; 
    }
    else{
        
        printf("you called 'moveBack' on an empty list\n");
        exit(1); 
    }
}
 // otherwise does nothing.
void movePrev(List L)
{ // If cursor is defined and not at front, move cursor one
    if(L->cursor == -1){
        printf("you called 'movePrev' but cursor is undef.\n");
        exit(1); 
    }
    if(L->cursor >0 ){  //if cursor is not at the front
        L->cursor--;
        L->cursorNode = L->cursorNode->prev;
    }
    else{ //it is at the front
        L->cursor = -1; 
        L->cursorNode = NULL;
    }



/************************************
 * broken fuction doesn't work
    if(L->cursor > 0){
        L->cursor--;
        L->cursorNode = L->cursorNode->prev;
    }
    else{
        
        printf("you called 'movePrev' on an empty list or cursor is already at front\n");
        exit(1); 
    }
    **************************************************/
}
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L)
{ // If cursor is defined and not at back, move cursor one
    if(L->cursor == -1){
        printf("you called 'moveNext' but cursor is undef.\n");
        exit(1); 
    }
    if(L->cursor != length(L)-1){  //if cursor is not at the back
        L->cursor++;
        L->cursorNode = L->cursorNode->next;
    }
    else{ //it is at the back
        L->cursor = -1; 
        L->cursorNode = NULL;
    }
    
    
    
   /***************************************************** 
    * broken function doesn't work 
    *
    if(L->cursor != length(L)-1){
        L->cursor++;
        L->cursorNode = L->cursorNode->next;
    }
    if(L->cursorNode == L->backNode){
        L->cursor = -1; 
        L->cursorNode = NULL;
    }
    else{
        printf("you called 'moveNext' but cursor is undef.\n");
        exit(1); 
    }
    *******************************************************************/
}
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void prepend(List L, data_type data)
{ // Insert new element into L. If L is non-empty,
    if(L == NULL){
        printf("Queue Error: calling prepend() on a NULL Queue reference\n");
        exit(1);
    }
    NodeObj* Q = newNode(data);
    if(length(L) == 0){
        L->frontNode = L->backNode = Q;
    }
    else{
        Q->next = L->frontNode;
        L->frontNode->prev = Q;
        L->frontNode = Q;
    }
    if ( L->cursor != -1 ) L->cursor++;
}
 // insertion takes place before front element.
void append(List L, data_type data)
{ // Insert new element into L. If L is non-empty,
    if (L == NULL){
        printf("Queue Error: calling Append() on a NULL reference\n");
        exit(1); 
    }
    NodeObj* Q = newNode(data);
    if(length(L) == 0){
        L->frontNode = L->backNode = Q;
    }
    else{
        Q->prev = L->backNode;
        L->backNode->next=Q;
        L->backNode = Q;
    }
}


void insertInOrder(List L, data_type data) //Insert new element in order
{
    if ( length(L)<=0) {
        append(L, data); 
        return; 
    }
    //do function to figure out its position
    int key = data;
    moveFront(L);
    bool inserted = false;
    while ( !inserted ) {
        if (  get(L) >= key ) {
            insertBefore(L, key);
            inserted = true;
        }
        else {
            moveNext(L);
            if (my_index(L) == -1 ) {
                append(L, key);
                inserted = true;
            }
        }
    }
 

}


 // insertion takes place after back element.
void insertBefore(List L, data_type data)
{ // Insert new element before cursor.
    if(my_index(L)<0){
        printf("ERROR: you are calling insertBefore but the cursor is undef.\n");
        exit(1);
    }
    if(length(L)<0){
        printf("ERROR: you are calling insertBefore on an empty list.\n");
        exit(1);
    }
    if (L->cursor == 0) {
        prepend(L, data);
        return; 
    }
    NodeObj* N=newNode(data);
    NodeObj* P=L->cursorNode->prev;
    N->prev = P;
    P->next = N; 
    N->next = L->cursorNode;
    L->cursorNode->prev = N;
    L->cursor++;

}
 // Pre: length()>0, my_index()>=0
void insertAfter(List L, data_type data)
{ // Insert new element after cursor.
    
    if(my_index(L)<0){
        printf("ERROR: you are calling insertAfter but the cursor is undef.\n");
        exit(1);
    }
    if(length(L)<0){
        printf("ERROR: you are calling insertAfter on an empty list.\n");
        exit(1);
    }
    NodeObj* N = newNode(data);
    NodeObj* P = L->cursorNode->next;
    N->prev = L->cursorNode;
    L->cursorNode->next = N;
    N->next = P; 
    if ( P ) P->prev = N;
    if ( L->backNode == N->prev )  L->backNode = N;
}
 // Pre: length()>0, my_index()>=0
void deleteFront(List L)
{ // Delete the front element. Pre: length()>0
    
    if(length(L)<0){
        printf("ERROR: you are calling deleteFront on an empty list.\n");
        exit(1);
    }
    NodeObj* N = L->frontNode;
    L->frontNode = L->frontNode->next;
    if (  L->frontNode ) {   //if frontNOde exists then set its prev to NULL
        L->frontNode->prev = NULL;
    } else {
        L->backNode = NULL; 
        L->cursorNode = NULL; 
        L->cursor = -1;
    }
    free(N);
    N = NULL;
    if ( L->cursor != -1 ) L->cursor--;
}
void deleteBack(List L)
{ // Delete the back element. Pre: length()>0
    
    if(length(L)<0){
        printf("ERROR: you are calling deleteBack on an empty list.\n");
        exit(1);
    }
    NodeObj* N = L->backNode;
    L->backNode = L->backNode->prev;
    if (  L->backNode ) {   //if backtNOde exists then set its next to NULL
        L->backNode->next = NULL;
    } else {
        L->frontNode = NULL; 
        L->cursorNode = NULL; 
        L->cursor = -1;
    }
    if ( L->cursorNode == N ) {
        L->cursorNode = NULL; 
        L->cursor = -1;
    }
    free(N);
    N = NULL;
}
void delete(List L)
{ // Delete cursor element, making cursor undefined.
    
    if(length(L)<0){
        printf("ERROR: you are calling delete on an empty list.\n");
        exit(1);
    }
    NodeObj* P = L->cursorNode->prev;
    NodeObj* N = L->cursorNode->next;
    free(L->cursorNode);
    L->cursorNode = NULL;
    L->cursor = -1; 

    if (P) { P->next = N;  }
    else { L->frontNode = N; }

    if (N) { N->prev = P;  }
    else { L->backNode = P; }
}
 // Pre: length()>0, my_index()>=0

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L)
{ // Prints to the file pointed to by out, a

    if( out==NULL ){
      printf("Unable to open file for writing\n");
      exit(1);
    }

    if(L->frontNode == NULL){
        printf("Error: trying to print an empty list\n");
        exit(1);
    }
    moveFront(L);
    for(int i=0; i<length(L); i++){
        fprintf(out, "%d ", L->cursorNode->data); 
        moveNext(L);
    }
}

//prints the list from the back for BigInteger
void printListBack(FILE* out, List L)
{ // Prints to the file pointed to by out, a

    if( out==NULL ){
      printf("Unable to open file for writing\n");
      exit(1);
    }

    if(L->frontNode == NULL){
        printf("Error: trying to print an empty list\n");
        exit(1);
    }
    moveBack(L);
    while ( my_index(L) >=0 )
    {
        fprintf(out, "%d", L->cursorNode->data);
        movePrev(L);
    }
}



 // string representation of L consisting
 // of a space separated sequence of integers,
// with front on left.
List copyList(List L)
{ // Returns a new List representing the same integer
    
    if(length(L)<0){
        printf("ERROR: you are calling copyList on an empty list.\n");
        exit(1);
    }
    List list_copy = newList();
    NodeObj* N = L->frontNode; 
    while(N != NULL){
        //extract data to copy from orig list
        data_type copy_data = N->data;
        //NodeObj* Q = newNode(copyData); 
        append(list_copy, copy_data);
        N = N->next; 
    }
    return list_copy;
}
 // sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.

// set()
// Overwrites the cursor element with x. Pre: length()>0, my_index()>=0
void set(List L, long x)
{
    if ( length(L) <= 0 ) {
        printf("ERROR: you are calling set on an empty list.\n");
        exit(1);
    }
    if ( my_index(L) < 0 ) {
        printf("ERROR: you are calling my_index on an empty list.\n");
        exit(1);
    }
    L->cursorNode->data = x; 
}
