#include <iostream>
using namespace std;
#include <stdio.h>
#include <iomanip>
#include <ctime>
#include "functions.h"
#include "hash.h"
#include <fstream>
#include <math.h>
#include <string>
#include <vector>

/********************************************************
 *                                                      *
 *    Nathan Redmond                                    *
 *    COSC 320 Project 2                                *
 *    Created: 05 April 2019                            *
 *    Modified: 19 April 2019                           *
 *                                                      *
 ********************************************************
 *                                                      *
 *    Running command:                                  *
 *      make clean                                      *
 *      make                                            *
 *      ./Prog2                                         *
 *                                                      *
 ********************************************************/

int main()
{
  srand(time(NULL));
  cout << "Welcome to Spell Checker!" << endl;
  cout << "--------------------------------------------------------" << endl;
  cout << "Loading the database..." << endl;
  cout << "--------------------------------------------------------" << endl << endl;

  double totalTime = 0;
  double _start = double(clock())/(CLOCKS_PER_SEC);
  int wordcount = 0, hashed = 0;
  string word;
  ifstream infile;
  ofstream outfile;

  //infile.open("english.txt", ios::in);
  infile.open("usa2.txt", ios::in);

  while(infile){
    infile >> word;
    wordcount++;
  }

  infile.close();

  int bucketNum = 5*ceil(sqrt(wordcount));
  HashTable A(bucketNum);

  //infile.open("english.txt", ios::in);
  infile.open("usa2.txt", ios::in);
  while(infile){
    infile >> word;
    hashed = hashS(word);
    hashed = hashed%bucketNum;
    A.addItem(word, hashed);
  }

  infile.close();

  int avgNode = int( wordcount/bucketNum );
  int max = 0, min = 10000;
  A.findBucketMaxMin(max, min);

  cout << "Total words = " << wordcount << endl;
  cout << "Biggest bucket size = " << max << endl;
  cout << "Smallest bucket size = " << min << endl;
  cout << "Total number of buckets = " << bucketNum << endl;
  cout << "Number of used buckets = " << A.usedBuckets() << endl;
  cout << "Average number of nodes in each bucket = " << avgNode << endl;
  double _finish = double(clock()) / (CLOCKS_PER_SEC);
  totalTime = _finish - _start;
  cout << "Total time taken = " << fixed << setprecision(6) << totalTime <<  endl;

  cout << "--------------------------------------------------------" << endl << endl;
  cout << "Please enter some text: " << endl;
  cout << "--------------------------------------------------------" << endl;
  string inputstring;
  getline(cin, inputstring);

  int misspelledCounter = 0;
  int suggestionCounter = 0;
  double sugTime = 0;

  vector <string> inputwords;
  vector <string> correctWords;
  vector <string> correctWordsTwo;
  removeWords(inputstring, inputwords);
  int inputhashed = 0;
  double sug_start = double(clock())/(CLOCKS_PER_SEC);
  for( int i = 0; i < inputwords.size()-1; i++ )
  {
    inputhashed = hashS(inputwords[i])%bucketNum;
    bool correct =  A.searchHashTable(inputwords[i], inputhashed);
    if( correct == false )
    {
      misspelledCounter++;
      cout << endl << termcolor::red << inputwords[i] << termcolor::reset << "  is spelled incorrectly." << endl;
      cout << "-------------------------------------------------------" << endl;
      cout << "Here are some options within one edit distance." << endl;
      A.wordsInOneEdit(inputwords[i], bucketNum, suggestionCounter, correctWords);
      cout << "Here are some options within two edit distances." << endl;
      if( !correctWords.empty() )
        A.wordsInTwoEdit(correctWords, bucketNum, suggestionCounter, correctWordsTwo);
      else
        cout << "\tThere are no two edit suggestions at this time..." << endl << endl;
    }
    inputhashed = 0;
  }
  double sug_finish = double(clock())/(CLOCKS_PER_SEC);
  sugTime = sug_finish - sug_start;

  cout << "--------------------------------------------------------" << endl;
  cout << "Summary" << endl;
  cout << "--------------------------------------------------------" << endl;
  cout << "Number of misspelled words = " << misspelledCounter << endl;
  cout << "Number of suggestions = " << suggestionCounter << endl;
  cout << "Time required to find suggestions for all of input = " << fixed << setprecision(6) << sugTime << endl;

  //A.printTable();
}
