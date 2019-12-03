#include <iostream>
using namespace std;
#include <vector>
#include <math.h>

int main(){
    vector<int> num;
    int n = 5;
    int j = 0;
    for( int i = 0; i <= pow(2, n); i ++ ){
      num[i] = j;
      j = j << 1;
    }
    
    for( auto it = num.begin(); it != num.end(); it++ ){
      cout << *it << endl;
    }
    return 0;
}