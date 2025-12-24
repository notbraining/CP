#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define int long long
#define pii pair<int,int>
int32_t main(){
  ordered_set<int>o;
  o.insert(1);
  o.insert(3);
  o.insert(5);
  cout<<*o.find_by_order(2)<<"\n";
  cout<<o.order_of_key(4)<<"\n";
  /*
  prints 
  5
  2
  order_of_key = number of elements strictly less (<) that the argument
    */
}
