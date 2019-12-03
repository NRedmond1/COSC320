Read Me


Nathan Redmond
COSC 320
Project 2
Created: 5 April 2019
Modified: 19 April 2019


Running command:
	make clean		//cleans out .o files and executable
	make			//creates .o and executable to run
	./Prog2		//runs the program.


Approach:

	For my approach to this program, I mostly followed Dr. Anderson’s outline. However, drawing out the diagrams for how a hash table works has made the understanding of how the code is all put together much easier. After I understood how to set up the hash table, I was able to set up my bucket size and add the hashed dictionary to the table. Next, I made functions to search the table so I can check if the input Is in the dictionary. I imported my hash.h file that hashes a string or int. I made a function to take the input string and parse each word out separately.  Then finally, I had to make two functions for one edit distance away and two edit distances away from the misspelled word. 
	The hardest part would be setting up the hashtable class and also doing one and two edit distances away while removing duplicates within itself and against the first edit distance.


Design choice: 

	For my hash table design, I wanted it to run the fastest insert on no matter how big the dictionary size is. So, I took the total amount of words in the dictionary and stored into a variable. Then took the ceil(squareroot ( variable NumWords.) ) and multiplied by 5. I chose the number 5 because when I was doing testing with time, the number 5 was faster than 4 and 6. This is just a sweet spot for a bigger array size and smaller linked list in each bucket. 

Improvements:

	Give the user the option to add words into the dictionary that were returned misspelled. Also ask the user which word they want to replace and write out the correct sentence with the words they chose to replace. Another improvement I would like to change is a better hashing algorithm to make my buckets have equally sized linked list in them. 


Strings and keys:

	To change my strings to integers, I followed an algorithm we did in class. I take the variable size = string.length() and run a for loop( from t = size to 0 ) I take the char at position 0 and multiply it by t+1. And then add the product to itself throughout the loop. This is not the best hash there is but if you change any character or the length it will give you a different number. And then I send that number to the hash function for integers. Almost as a double hash but a more uniform hash. 
	For my hash table I wanted a bucket size that is smaller than then total number of words I am inserting. Right before I insert my hash key into the table I mod it by the number of buckets so it will fit in the table. This way when I check the dictionary, all the buckets end up getting used and all are closely related in size. 
The time could be improved even more but I am very happy with the minimal time It takes to insert all of them into the hash table!
