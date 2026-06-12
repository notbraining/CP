
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
#include <print>
using namespace std;
#define int long long
#define pii pair<int,int>
int INF = 1e18;
//#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) cerr << #X << ": " << (X) << '\n'
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
/*
    if you fix the first row, S.T> theres only 1 pair of adjacent + , there will result at most 2 answers (they will still need to satisfy the contraints to be considered as valid)




    problem reduces down to each column has:
    either a "red" range that means the line MUST go through there and nowhere else
    or it has a "green" range: the line CANNOT go through here

    -ReflectioN: Unforntuaely, didn't consider diagonals nor did I consider two possible diagonals going int he same direcitons

*/
int solve(){
    int r, c, x; cin >> r >> c >> x;
    vector<pii>v;
    for(int i = 0; i < x; ++i){
        char c; cin >> c;
        int a, b; cin >> a >> b;
        if(c == '+'){
            v.push_back({max(a, b), 1});
        } else{
            v.push_back({max(a, b), -1});
        }
    }
    int L = max(c, r);
    sort(v.begin(), v.end());
    if(x == 0){
        return L + 1;
    }

    //consider all pairs
    int ans = 1; bool seen = false;
    for(int i = 0; i < x - 1; ++i){
        int d = v[i + 1].first - v[i].first;

        if(d % 2){
            //odd distance
            if(v[i + 1].second != v[i].second)continue;
            if(seen){
                return 0;
            } else{

                seen = true;


                if(v[i].second == 1){
                    ans = (d + 1) / 2;
                } else{
                    ans = (d - 1) / 2;
                }

            }
        } else{
            if(v[i + 1].second == v[i].second)continue;
            if(seen){
                return 0;
            } else{
                seen = true;
                ans = (d) / 2;
            }
        }
    }


    if(seen == false){
        if(v.front().second == 1){
            ans += v.front().first / 2;
        } else{
            ans += (v.front().first + 1) / 2 - 1;
        }
        if(v.back().second == 1){
            ans += (L - v.back().first + 1) / 2;
        } else{
            ans += (L - v.back().first + 2) / 2 - 1;
        }

    }
    return ans;



}
int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while(t--){
        cout << solve() << "\n";
    }

}
