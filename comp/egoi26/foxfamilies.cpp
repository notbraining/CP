
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<iomanip>
#include <cassert>
#include<algorithm>
#include<queue>
#include <array>
#include<queue>
#include <bitset>
#include<numeric>
#include<random>
#include<cstring>
#include<chrono>
using namespace std;
#define int long long
#define pii pair<int,int>
int INF = 1e18;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) cerr << #X << ": " << (X) << '\n'
#endif
/*
solution sketch: need to keep track of minL, maxL, minR, maxR for each family

*/
#define P pair<pii,pii>
int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    multiset<P>s;
    auto can_uni = [&](P i, P j){ //if 
        if(i.first.second < j.first.first && i.second.second < j.second.first){
            return false;
        }
        if(j.first.second < i.first.first && j.second.second < i.second.first){
            return false;
        }
        return true;
        };
    auto merge = [&](P i, P j){
        return P{{min(i.first.first, j.first.first), max(i.first.second, j.first.second)}, {min(i.second.first, j.second.first), max(i.second.second, j.second.second)}};
        };
    for(int i = 0; i < n; ++i){
        int l, r; cin >> l >> r;
        P x = {{l, l}, {r, r}};
        P y = {{l, -1}, {-1, -1}};
        while(true){
            auto it = s.lower_bound(y);
            if(it == s.end())break;
            if(can_uni(*it, x)){
                x = merge(x, *it);
                s.erase(it);
            } else{
                break;
            }
        }
        while(true){
            auto it = s.upper_bound(y);
            if(it == s.begin()){
                break;
            }
            it = prev(it);

            if(can_uni(*it, x)){
                x = merge(x, *it);
                s.erase(it);
            } else{
                break;
            }

        }
        s.insert(x);
        cout << s.size() << "\n";
    }

}
