Read Me


Nathan Redmond and Mason Kimbell
Computer Science 320 
Final Project – Connecting of Partial Order
Modified: 12 May 2019


Running command:
	make clean		//cleans out .o files and executable
	make			//creates .o and executable to run
	./proj3			//runs the program.


Approach:

	For our approach to this project, we had to do a lot of research about strongly connected components, partial orderings, and random graphs.  It helped that Mason has previously and currently doing research about our project topic. This helped out with most of the understanding of the math behind the project and where we were headed with the research.  We had previously coded the algorithms of BFS and strongly connected components (SCC) of a graph in Labs this year. With the research of random graphs, we could understand how to calculate the probability of all the possible graphs of size n nodes were strongly connected. 
The hardest part of this project would be calculating all the possible graphs we needed to test on and store them into containers. We did this by making a vector of graphs and used the adjacency matrix to input how each graph is connected. Each graph is a directed graph and using a matrix to determine the direction is easy when just looking at the bottom triangle of the matrix. We learned a lot from this research, and we are very pleased with the outcome of this program we have written. 


Design choice: 

	For our design choice we choose to use our pre-existing graph class and matrix class that we made from scratch. We used the matrix class to hold our adjacency matrix for each graph. We had to write some code to run though all the possibilities of the bottom triangle of a nxn matrix, which would be calculated by 2^k  {where n=num nodes,k= ∑▒(n-1)   } possibilities. After having all the graphs stored in a vector<graphs> we could run through all the possible graphs of size n nodes to check if they are strongly connected and how many up arrows each graph had. Our output shows the probability in percentage that with n nodes a random graph is strongly connected. We also output the average number of up arrows out of all possible graphs. However, if you would like there is some user interaction as well, this includes having the choice to print out all the strongly connected graphs out of all possibilities. Also choosing how many nodes you want in the graph that is being calculated on. 


Deficiencies:

	None that come to mind!


Improvements: 
	One problem we have is the calculation of graphs bigger than 7 nodes will crash due to having to calculate so much. One way we would like to try and fix this is having an algorithm that runs at O ( 2^n ). The algorithm we have runs at O ( 2^k ), where n = number of nodes and k= ∑▒〖(n-1)〗



