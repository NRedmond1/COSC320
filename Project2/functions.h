#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
using namespace std;
#include <vector>
#include <sstream>
#include "hash.h"
#include "termcolor.hpp"

//Functions HERE
class HashTable{
  private:
    int bucketSize;

    struct Node{
      Node* next = NULL;
      string input;
      int value;
      Node(string x, int y) : input(x), value(y) {}
    };

    typedef struct Node* Nodeptr;
    Nodeptr* bucket;


  public:
    HashTable(int size){
      bucketSize = size;
      bucket = new Nodeptr[bucketSize];
      for(int i = 0; i < bucketSize; i++)
          bucket[i] = NULL;
    }
    ~HashTable(){
      Nodeptr curr;
      Nodeptr prev;
      for(int i = 0; i < bucketSize; i++)
      {
        if(bucket[i] != NULL)
        {
        curr = bucket[i];
          while(curr != NULL)
          {
              prev = curr;
              curr = curr->next;
              delete prev;
          }
        }
      }
    }

    bool searchHashTable(string search, int key)
    {
      Nodeptr curr = bucket[key];
      while(curr != NULL)
      {
        if( curr->input == search )
        {
          return true;
        }
        else
          curr = curr->next;
      }
      return false;
    }

    void addItem(string word, int hashingVal)
    {
        Nodeptr newNode = new Node( word, hashingVal );
        if( bucket[hashingVal] == NULL )
        {
          bucket[hashingVal] = newNode;
        }
        else{
          Nodeptr Temp = bucket[hashingVal];
          while( Temp->next != NULL ){
            Temp = Temp->next;
          }
          Temp->next = newNode;
        }
    }

    void printTable()
    {
      Nodeptr temp;
      cout << "Hashing Table" << endl;
      cout << "-------------------------------------" << endl;
      for( int x = 0; x < bucketSize; x++ )
      {
        temp = bucket[x];
        cout << temp->value << "  -->  ";
        while( temp != NULL )
        {
          cout << temp->input << "  ";
          temp = temp->next;
        }
        cout << endl << endl;
      }
    }

    void findBucketMaxMin(int& max, int& min){
      Nodeptr cursor;
      int sum = 0;
      for( int i = 0; i < bucketSize; i++ )
      {
        cursor = bucket[i];
        while( cursor != NULL )
        {
          sum++;
          cursor = cursor->next;
        }
        if( sum > max )
          max = sum;
        if( sum < min )
          min = sum;

        sum = 0;
      }
    }

    int usedBuckets()
    {
      int used = 0;
      Nodeptr curr;
      for( int x = 0; x < bucketSize; x++ )
      {
        curr = bucket[x];
        if( curr != NULL )
          used++;
      }
      return used;
    }

    void wordsInOneEdit(string misspelled, int bucketNum, int &suggestionCounter, vector<string> &correctWords)
    {
      correctWords.erase(correctWords.begin(), correctWords.end());

      string tempReplce, tempInsert, tempDelete, tempSwap;
      int tempHashReplace = 0, tempHashInsert = 0, tempHashDelete = 0, tempHashSwap = 0;
      bool SearchedReplace = false, SearchedInsert = false, SearchedDelete = false, SearchedSwap = false;
       for( int x = 0; x < misspelled.size(); x++ )
       {
          tempReplce = misspelled;
          tempInsert = misspelled;
          tempDelete = misspelled;
          tempSwap = misspelled;
          for( char c = 'a'; c <= 122; c++ )
          {
             tempReplce.replace(x, 1, 1, c);
             tempHashReplace = hashS(tempReplce)%bucketNum;
             SearchedReplace = searchHashTable(tempReplce, tempHashReplace);
             if( SearchedReplace == true )
             {
                suggestionCounter++;
                correctWords.push_back(tempReplce);
             }
          }
    //-------------------------------------------------------------------------
          for( char c = 'a'; c <= 122; c++ )
          {
             tempInsert = misspelled;
             tempInsert.insert(x, 1, c);
             tempHashInsert = hashS(tempInsert)%bucketNum;
             SearchedInsert = searchHashTable(tempInsert, tempHashInsert);
             if( SearchedInsert == true )
             {
                suggestionCounter++;
                correctWords.push_back(tempInsert);
             }
          }
    //-------------------------------------------------------------------------
             tempDelete.erase(x,1);
             tempHashDelete = hashS(tempDelete)%bucketNum;
             SearchedDelete = searchHashTable(tempDelete, tempHashDelete);
             if( SearchedDelete == true )
             {
                suggestionCounter++;
                correctWords.push_back(tempDelete);
             }
    //-------------------------------------------------------------------------
          for( int i = 0; i < tempSwap.size(); i++ )
          {
            tempSwap = misspelled;
            if( x != i )
            {
              swap(tempSwap[x], tempSwap[i]);

              tempHashSwap = hashS(tempSwap)%bucketNum;
              SearchedSwap = searchHashTable(tempSwap, tempHashSwap);
              if( SearchedSwap == true )
              {
                suggestionCounter++;
                correctWords.push_back(tempSwap);
              }
            }
          }
    //-------------------------------------------------------------------------

       }
       if( correctWords.empty() )
          cout << "\tThere are no one edit suggestions at this time..." << endl;
       for( int x = 0; x < correctWords.size(); x++ )
       {
         for( int y = x+1; y < correctWords.size(); y++ )
         {
            if( correctWords[x] == correctWords[y] ){
                correctWords.erase(correctWords.begin()+y-1);
                suggestionCounter--;
              }
         }
         cout << termcolor::green << " *" << correctWords[x] << "* " << termcolor::reset;
       }
       cout << endl << "-------------------------------------------------------" << endl;
    }


    void wordsInTwoEdit(vector<string> correctWords, int bucketNum, int &suggestionCounter, vector<string> &correctWordsTwo)
    {
      correctWordsTwo.erase(correctWordsTwo.begin(), correctWordsTwo.end());

      for( int k = 0; k < correctWords.size(); k++ )
      {
      string tempReplce, tempInsert, tempDelete, tempSwap;
      int tempHashReplace = 0, tempHashInsert = 0, tempHashDelete = 0, tempHashSwap = 0;
      bool SearchedReplace = false, SearchedInsert = false, SearchedDelete = false, SearchedSwap = false;
       for( int x = 0; x < correctWords[k].size(); x++ )
       {
          tempReplce = correctWords[k];
          tempInsert = correctWords[k];
          tempDelete = correctWords[k];
          tempSwap = correctWords[k];
          for( char c = 'a'; c <= 122; c++ )
          {
             tempReplce.replace(x, 1, 1, c);
             tempHashReplace = hashS(tempReplce)%bucketNum;
             SearchedReplace = searchHashTable(tempReplce, tempHashReplace);
             if( SearchedReplace == true )
             {
                suggestionCounter++;
                correctWordsTwo.push_back(tempReplce);
             }
          }
    //-------------------------------------------------------------------------
          for( char c = 'a'; c <= 122; c++ )
          {
            tempInsert = correctWords[k];
             tempInsert.insert(x, 1, c);
             tempHashInsert = hashS(tempInsert)%bucketNum;
             SearchedInsert = searchHashTable(tempInsert, tempHashInsert);
             if( SearchedInsert == true )
             {
                suggestionCounter++;
                correctWordsTwo.push_back(tempInsert);
             }
          }
    //-------------------------------------------------------------------------
             tempDelete.erase(x,1);
             tempHashDelete = hashS(tempDelete)%bucketNum;
             SearchedDelete = searchHashTable(tempDelete, tempHashDelete);
             if( SearchedDelete == true )
             {
                suggestionCounter++;
                correctWordsTwo.push_back(tempDelete);
             }
    //-------------------------------------------------------------------------
          for( int i = 0; i < tempSwap.size(); i++ )
          {
            tempSwap = correctWords[k];
            if( x != i )
            {
              swap(tempSwap[x], tempSwap[i]);

              tempHashSwap = hashS(tempSwap)%bucketNum;
              SearchedSwap = searchHashTable(tempSwap, tempHashSwap);
              if( SearchedSwap == true )
              {
                suggestionCounter++;
                correctWordsTwo.push_back(tempSwap);
              }
            }
          }
    //-------------------------------------------------------------------------

       }

     }
        vector<string> temp;
       int y;
       for( int x = 0; x < correctWordsTwo.size()-1; x++ )
       {
         y = x+1;
         while (y < correctWordsTwo.size())
         {
            if( correctWordsTwo[x] == correctWordsTwo[y] ){
                correctWordsTwo.erase(correctWordsTwo.begin() + y);
                suggestionCounter--;
              }
            else
              y++;
         }
         temp.push_back(correctWordsTwo[x]);
       }

       int t;
       for( int s = 0; s < temp.size(); s++ )
       {
         t = 0;
         while (t < correctWords.size())
         {
            if( temp[s] == correctWords[t] ){
                temp.erase(temp.begin() + s);
                suggestionCounter--;
              }
            else
              t++;
         }
       }

       for( int g = 0; g < temp.size(); g++ )
       {
         if(temp[g] != "")
            cout << termcolor::green << " *" << temp[g] << "* " << termcolor::reset;
       }

       cout << endl << "-------------------------------------------------------" << endl;

    }

};

void removeWords(string str, vector<string> &vect)
{
  istringstream ss(str);

  do{
    string word;
    ss >> word;
    char c;
    for(int x = 0; x < word.size(); x++ )
    {
      c = word[x];
      if( c == '.' || c == ',' || c == '\n' || c == '!' || c == '?' || c == '"' || c == '-' )
        word.erase(x);
    }
    vect.push_back(word);

  } while (ss);
}


#endif
