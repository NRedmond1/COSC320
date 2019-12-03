Read Me


Nathan Redmond
COSC 320
Lab 12
Created: 02 May 2019
Modified: 09 May 2019


Running command:
	make clean		//cleans out .o files and executable
	make			//creates .o and executable to run
	./Lab12		//runs the program.


Approach:
	Followed Dr. Anderson’s outline on how to set up the Graph class. Implemented the functions following pseudo code for Edge Cover. I created one map for holding the vertex to vector. This will allow for me to store an adjacency list of my vertices and their neighbors. For my main file, I created a menu to better display all my functions and usability for the user, this includes bringing in an adjacency list from a text file. 

Time Complexity:
	Add vertex:	most O(1)

	Add edge:	most O(1)

//prints every node and every node has an edge to every other node. 
	Print: 		most O(n*n-1)	
			Best O(n)

	Vertex Cover:	O( |v| + |E| )

	Brute Force:	O(2^n)

Input Data File:
	My input file is set up as it takes in the vertex first the bypasses a character “|” and then takes in the rest as a string to parse into separate integers. 
Ex:
	1 | 2 3
	2 | 1 3
	3 | 1 2

Specific Graphs:
	The flower pedal graph can push the approx. vertex cover away from the minimal set. With the more pedals you add to the flower the more vertices could be wrongly chosen.

 	    2	      5
    /	  \   /	  \	
	1	      4	      7
	  \	  /   \	  /
	    3	      6

Graph Structure:
	I was thinking maybe the best case for the approx. vertex cover would be a tree format where there is a top node and branches going down leading to a leaf node. Other ideas would be where two nodes are connected and each node has a hundred edges going off of it but only to one unique node. This would end in worse case picking 4 nodes out of 202 nodes. 
		  \ | /	    \ | /
	----  1  -----  2 ----
		  / | \	    / | \

Random testing:
	When testing the Random vertex cover verses non-random cover, the vertex cover is roughly the same. However, there was chances where the random vertex cover chose the minimal set or the closest to it. One example is a straight line. The random or non-random will never get the minimal set of vertices to cover every edge.

Code improvement:
	I guess one improvement could be giving the user the option to select a vertex then be able to select multiple vertices at once to connect edges to. The way my menu is set up you can choose how many edges you want to create and then select a “from” and “to” vertex to create the edge.  The code also does not give errors for duplicating. It just doesn’t put one in if it already exists.

