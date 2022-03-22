#------------------------------------------------------------------------------
#  Makefile for Graph ADT
#
#  sindurka 1644073 pa3 
#
# Makefile for CSE 101 Programming Assignment 3
#
#       make                  makes Graph
#       make GraphTest        makes GraphTest
#------------------------------------------------------------------------------


all: FindPath  GraphTest 


ListTest : ListTest.o List.o
	gcc -g -o ListTest       ListTest.o List.o

GraphClient : GraphClient.o Graph.o List.o
	gcc -g -o GraphClient     Graph.o   GraphClient.o List.o

FindPath : FindPath.o Graph.o List.o
	gcc -g -o FindPath       FindPath.o Graph.o List.o

GraphTest: GraphTest.o Graph.o List.o
	gcc -g -o  GraphTest       GraphTest.o Graph.o List.o

GraphQuiz: GraphQuiz.o Graph.o List.o
	gcc -g -o  GraphQuiz       GraphQuiz.o Graph.o List.o

RobotChallenge : RobotChallenge.o Graph.o List.o
	gcc -g -o RobotChallenge       RobotChallenge.o Graph.o List.o



########  Make all OBJs

GraphQuiz.o : GraphQuiz.c Graph.h
	gcc -c -g -std=c99 -Wall GraphQuiz.c

GraphTest.o : GraphTest.c Graph.h
	gcc -c -g -std=c99 -Wall GraphTest.c

FindPath.o : FindPath.c Graph.h List.h
	gcc -c -g -std=c99 -Wall FindPath.c

Graph.o : Graph.c Graph.h
	gcc -c -g -std=c99 -Wall Graph.c

ListTest.o : ListTest.c List.h
	gcc -c -g -std=c99 -Wall ListTest.c

GraphClient.o : GraphClient.c 
	gcc -c -g -std=c99 -Wall GraphClient.c

List.o : List.c List.h
	gcc -c -g -std=c99 -Wall List.c

RobotChallenge.o : RobotChallenge.c Graph.h List.h
	gcc -c -g -std=c99 -Wall RobotChallenge.c


clean :
	rm -f RobotChallenge *.o *.exe 
 

