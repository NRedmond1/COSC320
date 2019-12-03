#include <iostream>
using namespace std;
#include <vector>
#include <queue>
#include <map>

/**************************************
 *  Nathan Redmond                    *
 *  COSC 320 Lab 11                   *
 *  modified: 25 April 2019           *
 **************************************/

enum color_t{
    BLACK,
    WHITE,
    GRAY
};

class Graph{
private:
    map<int, vector<int>> verticies;
    map<int, vector<int>> transpose;

    map<int, color_t> colors;
    map<int, int> discover;
    map<int, int> finish;
    map<int, int> parent;

    map<int, color_t> colorsT;
    map<int, int> discoverT;
    map<int, int> finishT;
    map<int, int> parentT;

    bool directed;
    bool acyclic = true;
public:
    Graph(bool type)
    {
      directed = type;
    }

    void addVertex(int vert){
        auto iter = verticies.find(vert);
        if( iter == verticies.end() ){
          vector<int> newVector;
          verticies.insert(pair<int, vector<int>> (vert, newVector));
        }
    }

    void addEdge(int vert1, int vert2)
    {
      addVertex(vert1);
      addVertex(vert2);
      if( directed == true )
      {
        if( vert1 == vert2 ){
          return;
        }
        else{
          for( auto it = verticies[vert1].begin(); it < verticies[vert1].end(); it++ ){
            if( *it == vert2 )
                return;
          }
          verticies[vert1].push_back(vert2);
        }
      }
      else
      {
        if( vert1 == vert2 ){
          return;
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

    }

    queue<int> ORDER;
    void TopSort(){
      this->DFS();
      if( directed == true && acyclic == true ){
        int numVert = 0;
        for( auto it = verticies.begin(); it != verticies.end(); it++ ){
          numVert++;
        }
        for( int i = 2*numVert; i > 0; i-- )
        {
          for( auto it = verticies.begin(); it != verticies.end(); it++ ){
            if( finish[it->first] == i ){
              cout << it->first << " ";
              ORDER.push(it->first);
            }
          }
        }
        cout << endl;
      }
      else{
        cout << "Error: " << endl;
        if( directed == false )
          cout << "\tThe graph is undirected." << endl;
        if( acyclic == false )
          cout << "\tThe graph has a cycle." << endl;
      }
    }

    void SCC(){
        this->DFS();
        if( ORDER.empty() ){
        int numVert = 0;
        for( auto it = verticies.begin(); it != verticies.end(); it++ ){
          numVert++;
        }
        for( int i = 2*numVert; i > 0; i-- )
        {
          for( auto it = verticies.begin(); it != verticies.end(); it++ ){
            if( finish[it->first] == i ){
              cout << it->first << " ";
              ORDER.push(it->first);
            }
          }
        }
      }
        for( auto it = verticies.begin(); it != verticies.end(); it++ ){
          vector<int> newVector;
          transpose.insert(pair<int, vector<int>> (it->first, newVector));
        }

        for( auto it = verticies.begin(); it != verticies.end(); it++ ){
          for( auto iterat = it->second.begin(); iterat < it->second.end(); iterat++ ){
            transpose[*iterat].push_back(it->first);
          }
        }
        this->print2();
        this->DFS2();
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

    void print2(){
        for( auto it = transpose.begin(); it != transpose.end(); it++ ){
          cout << "Vertex[" << it->first << "] = ";
          for( auto iterat = it->second.begin(); iterat < it->second.end(); iterat++ ){
            cout << *iterat << "  ";
          }
          cout << endl;
        }
    }

    int time;

    void DFS(){
        for( auto it = verticies.begin(); it != verticies.end(); it++ ){
          colors.insert(pair<int, color_t> (it->first, WHITE));
          discover.insert(pair<int, int> (it->first, -1));
          finish.insert(pair<int, int> (it->first, -1));
          parent.insert(pair<int, int> (it->first, -1));
        }
        time = 0;
        for( auto it = verticies.begin(); it != verticies.end(); it++ ){
          if( colors[it->first] == WHITE )
            DFS_Visit(it->first);
        }
    }

    void DFS_Visit(int node){
      time++;
      discover[node] = time;
      colors[node] = GRAY;
      for( auto it = verticies[node].begin(); it < verticies[node].end(); it++ ){
        if( colors[*it] == WHITE )
        {
          parent[*it] = node;
          DFS_Visit(*it);
        }
        if( colors[*it] == GRAY && directed == false && parent[node] != parent[*it] ){
          acyclic = false;
        }
        if( colors[*it] == GRAY && directed == true ){
          acyclic = false;
        }
      }
      time++;
      colors[node] = BLACK;
      finish[node] = time;
    }

    void printDFS(){
        for( auto it = verticies.begin(); it != verticies.end(); it++ ){
          cout << it->first << ":" << endl;
          cout << "\tdiscover time: " << discover[it->first] << endl;
          cout << "\tfinish time: " << finish[it->first] << endl;
        }
    }

    int counter;
    void DFS2(){
        counter = 1;
        for( auto it = transpose.begin(); it != transpose.end(); it++ ){
          colorsT.insert(pair<int, color_t> (it->first, WHITE));
          discoverT.insert(pair<int, int> (it->first, -1));
          finishT.insert(pair<int, int> (it->first, -1));
          parentT.insert(pair<int, int> (it->first, -1));
        }
        time = 0;
        int pick;
        while( !ORDER.empty() ){
          pick = ORDER.front();
          while( colorsT[pick] == BLACK && !ORDER.empty() ){
            ORDER.pop();
            pick = ORDER.front();
          }
          if( colorsT[pick] == WHITE ){
            cout << "SCC group " << counter << " :" << endl;
            cout << "\t";
            DFS_Visit2(pick);
          }
          counter++;
          cout << endl;
        }
    }

    void DFS_Visit2(int node){
      time++;
      discoverT[node] = time;
      colorsT[node] = GRAY;
      cout << node << " ";
      for( auto it = transpose[node].begin(); it < transpose[node].end(); it++ ){
        if( colorsT[*it] == WHITE )
        {
          parentT[*it] = node;
          DFS_Visit2(*it);
        }
        if( colorsT[*it] == GRAY && directed == false && parentT[node] != parentT[*it] ){
          acyclic = false;
        }
        if( colorsT[*it] == GRAY && directed == true ){
          acyclic = false;
        }
      }
      time++;
      colorsT[node] = BLACK;
      finishT[node] = time;
    }
};
