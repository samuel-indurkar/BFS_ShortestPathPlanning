
//-----------------------------------------------------------------------------
// RobotChallenge.c
//
// Implementation file for  Robot Navigation Challenge
//
// Samuel Indurkar 
// 3/8/2022
//
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
#include"List.h"

#define BFN 1000

int main( int argc, char* argv[])
{
    
    // 1. read input file & open output file
            //determine # of rows and cols
            //determine location of avocado
            //det start location
    // 2. convert input to array
    // 3. convert array to graph
    // 4. shortest_path from start to first avacado
    // 5. repeat till all avacado finished
    // 6. print result
    
    int total_distance=0;
    int ROWS = 0;
    int COLS = 0;
    int row = 0; //iterating variables
    int col = 0; //iterating variables
    int vertex = 0;
    int HASH = '#';
    int OPEN_PATH = '.';
    int AVOCADO = '@';
    int ROBOT = 'x'; 
    int avocCount = 0;
    int currentVertex = 0;

    
    //1. FOPEN FILE and get num rows and cols
    //creating an outfile to write to

    //opening the infile to read it
    FILE* infile;
    FILE* outfile;
    //by default open test_input and SAM_test_output
    char * inFileName = "./test_input.txt";
    char * outFileName = "./SAM_test_output.txt";
    if( argc == 1) {
        printf("Used default test_input.txt and SAM_test_output.txt\n\n");
    }else if ( argc == 2){
        inFileName = argv[1];
        printf("Used default SAM_test_output.txt as outFile\n\n");
    }else if (argc >= 3){  //if test input and output specified
        inFileName = argv[1];
        outFileName = argv[2];
    }
    infile = fopen(inFileName, "r");
    if (infile == NULL){
        printf("unable to open input file %s\n", inFileName);
        exit(1);
    }
    outfile = fopen(outFileName, "w");
    if (outfile == NULL){
        printf("unable to open output file %s\n", outFileName);
        exit(1);
    }

    char buf[BFN];

    //set FilePointer at top
    fseek( infile, 0, SEEK_SET);

    //read File and determine number of ROWS and COLS and count num of avocados
    row = 0;
    col = 0;
    while (fgets(buf, sizeof(buf), infile) != NULL) {
        for ( int k = 0; k <BFN; k++){
            if( (buf[k] == 'X') || (buf[k] == 'x') || (buf[k] == '#') || (buf[k] == '.') || (buf[k] == '@' )) {
                if (row == 0) col++;
                if (buf[k] == '@') avocCount++;
            }else{ break; }
        }
        row++;
        memset( buf, 0, sizeof(buf));
    }

    ROWS = row; 
    COLS = col;
    //array to contain location of all avoc
    int avocLocationArray[avocCount];
    //array to contain location of avoc after being 'picked'
    int avocCollectionArray[avocCount];
    int avocCollectionIndex = 0;
    int avocIndex = 0; 

    //create Array to represent map
    int floorMap [ROWS][COLS];
                
    //set File Pointer at top
    fseek( infile, 0, SEEK_SET);
    row = 0;

    //stuff contents of input file into 2D floorMap Array
    //populate avocLocationArray 
    while (fgets(buf, sizeof(buf), infile) != NULL) {
        for ( int k = 0; k <COLS; k++){
            if( (buf[k] == 'X') || (buf[k] == 'x') || (buf[k] == '#') || (buf[k] == '.') || (buf[k] == '@' )) {
                floorMap[row][k] = buf[k]; 
                if (buf[k] == 'x') {
                    currentVertex = row*COLS + k;
                }
                if ( buf[k] == AVOCADO){
                    avocLocationArray[avocIndex] = row*COLS + k;
                    avocIndex++;
                }
            }else{ break; }
        }
        row++;
        memset( buf, 0, sizeof(buf));
    }
    printf("Starting Location = %d\n\n", currentVertex);

    //print floorMap
    for (row = 0; row < ROWS; row++){
        for (col = 0; col < COLS; col++){
            vertex = row*COLS + col;
            printf("%03d:%c ", vertex, floorMap[row][col]);
        } 
        printf("\n");
    }
    printf("\n");

    /******************************************
    printf("AvocLocationArray\n"); 
    for (int i = 0; i < avocCount; i++){
        printf("%d\n", avocLocationArray[i]);
    }
    ******************************************/

    // 3. convert array to graph
    int up_row = 0;
    int down_row = 0;
    int left_col = 0;
    int right_col = 0;
    int up_vertex = 0;
    int down_vertex = 0;
    int left_vertex = 0;
    int right_vertex = 0;

    Graph floorMapGraph = NULL;
    floorMapGraph = newGraph(ROWS*COLS);
    for (row = 0; row < ROWS; row++){
        for (col = 0; col < COLS; col++){
            if (floorMap[row][col] != HASH){

                vertex = row*COLS + col;
                //UP row
                up_row = row - 1;
                //DOWN row
                down_row = row + 1;
                //LEFT col
                left_col = col - 1;
                //RIGHT col
                right_col = col + 1;

                //checking neighbors and if not hash then add edge with them
                //UP neighbor
                if ( floorMap[up_row][col] != HASH) {
                    up_vertex = up_row*COLS + col;
                    if (up_vertex > 0 && up_vertex < ROWS*COLS) {
                        addEdge( floorMapGraph, vertex, up_vertex);
                    }
                }
                //DOWN Neighbor
                if ( floorMap[down_row][col] != HASH) {
                    down_vertex = down_row*COLS + col;
                    if (down_vertex > 0 && down_vertex < ROWS*COLS) {
                        addEdge( floorMapGraph, vertex, down_vertex);
                    }
                }
                //LEFT 
                if ( floorMap[row][left_col] != HASH) {
                    left_vertex = row*COLS + left_col;
                    if (left_vertex > 0 && left_vertex < ROWS*COLS) {
                        addEdge( floorMapGraph, vertex, left_vertex);
                    }
                }
                //RIGHT 
                if ( floorMap[row][right_col] != HASH) {
                    right_vertex = row*COLS + right_col;
                    if (right_vertex > 0 && right_vertex < ROWS*COLS) {
                        addEdge( floorMapGraph, vertex, right_vertex);
                    }
                }

            }
        } 
    }
                
    //print Graph relationships to stdout
    //printGraph(stdout, floorMapGraph);


    //4. shortest path algo

    List L = newList();
    avocIndex = 0; 
    int src = currentVertex; 
    int dest = 0;
    int dest_row = 0;
    int dest_col = 0;
    //breadth first search on currentVertex
    BFS(floorMapGraph, src);
    //det which is closest avoc
    int minDist = -1;
    int currDist; 
    int minToErase = 0;
    //dest is set to location of closest avocado to src
    for( int i = 0; i < avocCount; i++) {
        if (avocLocationArray[i] != -1){
            currDist = getDist(floorMapGraph, avocLocationArray[i]); 
            if(minDist == -1){
                minDist = currDist; 
                minToErase = i; 
            }else if ( currDist < minDist ){
                minDist = currDist; 
                minToErase = i;
            }
        }
    }
    if (minDist != -1) {
        dest = avocLocationArray[minToErase];
        avocCollectionArray[avocCollectionIndex] = dest; 
        avocCollectionIndex++;
        avocLocationArray[minToErase] = -1;
    }

    while (avocIndex < avocCount){

        if ( src == 0 && dest == 0 ) {
            break; 
        }

        //get path from src to dest having done BST on src
        getPath(L, floorMapGraph, dest); 
        if (getDist(floorMapGraph, dest) != INF ) {
            total_distance += getDist(floorMapGraph, dest);
            dest_row = dest / COLS;
            dest_col = dest % COLS;
            fprintf(stdout, "Avocado Found at(%d,%d) total_distance=%d\n", dest_row, dest_col, total_distance);
            fprintf(stdout, "The distance from %d to %d is %d\n", src, dest, getDist(floorMapGraph,dest));
            fprintf(stdout, "A shortest %d-%d path is: ", src, dest);
            printList(stdout, L);
        }
        else {
            fprintf(stdout, "The distance from %d to %d is infinity\n", src, dest);
            fprintf(stdout, "No %d-%d path exists", src, dest);
    
        }
        fprintf(stdout, "\n");
        fprintf(stdout, "\n");
        clear(L);

        //setting start to current dest and changing dest from current avocado to the next
        minDist = -1;
        src = dest;
        BFS(floorMapGraph, src);
        int minToErase = 0;
        //loop to find next closest avocado
        for( int i = 0; i < avocCount; i++) {
            if (avocLocationArray[i] != -1){
                currDist = getDist(floorMapGraph, avocLocationArray[i]); 
                if(minDist == -1){
                    minDist = currDist; 
                    minToErase = i; 
                }else if ( currDist < minDist ){
                    minDist = currDist; 
                    minToErase = i;
                }
            }
        }
        if (minDist != -1){
            dest = avocLocationArray[minToErase];
            avocCollectionArray[avocCollectionIndex] = dest; 
            avocCollectionIndex++;
            avocLocationArray[minToErase] = -1;
        }
        avocIndex++;

    }

    fprintf(outfile, "%d\n", total_distance);
    for (int i = 0; i < avocCount; i++){
        dest_row = avocCollectionArray[i] / COLS;
        dest_col = avocCollectionArray[i] % COLS;
        fprintf(outfile, "%d, %d\n", dest_row, dest_col);
    }
    printf("Please don't forget to check the output in the output file!\n");

    freeGraph( &floorMapGraph ); 


    fclose (infile);

    fflush( outfile );
    fclose ( outfile);
    
}
