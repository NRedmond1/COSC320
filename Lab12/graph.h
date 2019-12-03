#include <iostream>
using namespace std;
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <queue>
#include <map>

/**************************************
 *  Nathan Redmond                    *
 *  COSC 320 Lab 012                  *
 *  modified: 09 May 2019             *
 **************************************/

class edgeCover{
private:
    map<int, vector<int>> verticies;
public:
    void addVertex(int vert){
        auto iter = verticies.find(vert);
        if( iter == verticies.end() ){
          vector<int> newVector;
          verticies.insert(pair<int, vector<int>> (vert, newVector));
        }
    }

    void addEdge(int vert1, int vert2){
      addVertex(vert1);
      addVertex(vert2);
      if( vert1 == vert2 ){
        for( auto it = verticies[vert1].begin(); it < verticies[vert1].end(); it++ ){
          if( *it == vert1 )
              return;
        }
        verticies[vert1].push_back(vert1);
      }
      else{
        for( auto it = verticies[vert1].begin(); it < verticies[vert1].end(); it++ ){
          if( *it == vert2 )
              return;
        }
        verticies[vert1].push_back(vert2);
        verticies[vert2].push_back(vert1);
      }

    }

    void print(){
        for( auto it = verticies.begin(); it != verticies.end(); it++ ){
          cout << "Vertex[" << it->first << "] = ";
          for( auto iterat = it->second.begin(); iterat < it->second.end(); iterat++ ){
            cout << *iterat << "  ";
          }
          cout << endl;
        }
    }


    void findEdgeCover(){
      map<int, vector<int>> edges;
      edges = verticies;
      vector<int> COVER;
      int temp1, temp2;
      bool emp = false;
      while( !emp )
      {
        for( auto t = edges.begin(); t != edges.end(); t++ ){
          if( !t->second.empty() ){
            temp1 = t->first;
            temp2 = t->second[0];
          }
        }
        COVER.push_back(temp1);
        COVER.push_back(temp2);
        for( auto it = COVER.begin(); it < COVER.end(); it++ ){
          for( auto iter = edges.begin(); iter != edges.end(); iter++ ){
            for( auto iter2 = edges[iter->first].begin(); iter2 < edges[iter->first].end(); iter2++ ){
              if( *iter2 == *it )
                edges[iter->first].erase(iter2);
              if( iter->first == *it )
                edges[iter->first].clear();
            }
          }
        }
        emp = true;
        for( auto travers = edges.begin(); travers != edges.end(); travers++ ){
          if( !travers->second.empty() )
            emp = false;
        }
      }

      cout << "The Approx Cover w/o Random is: " << endl << "\t";
      for( auto it = COVER.begin(); it < COVER.end(); it++ ){
        cout << *it << " ";
      }

    }

    void findRandEdgeCover(){
      map<int, vector<int>> edges;
      edges = verticies;
      vector<int> COVER;
      int temp1, temp2, ran, ran2;
      bool emp = false, choose;
      srand (time(NULL));
      while( !emp )
      {
        choose = true;
        while(choose){
          auto count = edges.begin();
          ran = rand();
          ran = (ran*ran) % edges.size();
          for(int i = 0; i < ran; i++){
            count++;
          }
          if( !count->second.empty() ){
            ran2 = rand();
            ran2 = (ran2*ran2)%count->second.size();
            temp1 = count->first;
            temp2 = count->second[ran2];
            choose = false;
          }
        }
        COVER.push_back(temp1);
        COVER.push_back(temp2);
        for( auto it = COVER.begin(); it < COVER.end(); it++ ){
          for( auto iter = edges.begin(); iter != edges.end(); iter++ ){
            for( auto iter2 = edges[iter->first].begin(); iter2 < edges[iter->first].end(); iter2++ ){
              if( *iter2 == *it )
                edges[iter->first].erase(iter2);
              if( iter->first == *it )
                edges[iter->first].clear();
            }
          }
        }

        emp = true;
        for( auto travers = edges.begin(); travers != edges.end(); travers++ ){
          if( !travers->second.empty() )
            emp = false;
        }
      }

      cout << "The Approx Cover w/ Random is: " << endl << "\t";
      for( auto it = COVER.begin(); it < COVER.end(); it++ ){
        cout << *it << " ";
      }
    }

    void pruteForce(){
        //took to much time to try and find the subsets.
    }
};
