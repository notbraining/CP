
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
const int N = 505;
int cap[N][N];
int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<vector<int>>adj(n + 1);
    for(int i = 0; i < m; ++i){
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back(b);
        adj[b].push_back(a);
        cap[a][b] += c;
    }

    vector<int>par(n + 1, -1);
    auto can_reach = [&](){
        queue<int>q;
        q.push(1);
        par[1] = 1;
        while(!q.empty()){
            int cur = q.front();
            q.pop();
            for(int i : adj[cur]){
                if(cap[cur][i] <= 0 || par[i] != -1)continue;
                par[i] = cur;
                q.push(i);
            }
        }

        return par[n] != -1;
        };
    int ans = 0;
    while(can_reach()){

        int cur = n;
        int curflow = INF;
        while(cur != 1){
            curflow = min(curflow, cap[par[cur]][cur]);
            cur = par[cur];
        }
        cur = n;
        while(cur != 1){
            cap[par[cur]][cur] -= curflow;
            cap[cur][par[cur]] += curflow;
            cur = par[cur];
        }
        ans += curflow;
        par = vector<int>(n + 1, -1);
    }
    cout << ans;

}
