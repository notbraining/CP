
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
using namespace std;
#define int long long
#define pii pair<int,int>
int INF = 1e18;
const int N = 1LL << 18;
int t[N << 1LL];

void build(vector<int>& v){
    for(int i = N; i <= 2 * N - 1; ++i){
        if(i - N >= v.size())break;
        t[i] = v[i - N];
    }
    for(int i = N - 1; i >= 1; --i){
        t[i] = min(t[i << 1], t[i << 1 | 1]);
    }
}
int query(int l, int r){
    //zero index query array
   //turned into inclusive, exclusive
    int small = INF;
    for(l += N, r += N; l < r; l >>= 1, r >>= 1){
        if(l & 1){
            small = min(small, t[l++]);
        }
        if(r & 1){
            small = min(small, t[--r]);
        }
    }
    return small;
}
void upd(int p, int x){
    t[p += N] = x;
    for(; p > 1; p >>= 1){
        t[p >> 1] = min(t[p], t[p ^ 1]);
    }
}

int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q; vector<int>v(n + 1);
    memset(t, 0x3f, sizeof(t));
    for(int i = 1; i <= n; ++i){ cin >> v[i]; }
    build(v);
    while(q--){
        int ty; cin >> ty;
        if(ty == 1){
            int k, u; cin >> k >> u;
            upd(k, u);
        } else{
            int a, b; cin >> a >> b;
            cout << query(a, b + 1) << "\n";
        }
    }

}
