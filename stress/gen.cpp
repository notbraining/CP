#pragma GCC optimize("O3")
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
#define pii pair<int, int>
#define LL long long
int rnd(int a, int b) { return a + rand() % (b - a + 1); }
int32_t main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int seed = atoi(argv[1]);
  srand(seed);

  int n= rnd(1,10);
  cout<<n<<"\n";
  for(int i= 0; i<n; ++i){
    cout<<rnd(0,10)<<" ";
  }
  


  
}
