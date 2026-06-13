
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
const int N = 100002;
int dp[4 * N][51];
int a[N];
void build(int node, int tl, int tr){
    if(tl == tr){
        //leaf node
        for(int j = 0; j <= 50; ++j){
            dp[node][j] = abs(a[tl] - j);
        }
        return;
    }
    int mid = (tl + tr) / 2;
    build(node * 2, tl, mid);
    build(node * 2 + 1, mid + 1, tr);
    for(int j = 0; j <= 50; ++j){
        int x = dp[node * 2 + 1][j];
        dp[node][j] = dp[node * 2][x];
    }

}
void upd(int node, int tl, int tr, int pos, int x){
    if(tl == tr){
        a[tl] = x;
        for(int j = 0; j <= 50; ++j){
            dp[node][j] = abs(a[tl] - j);
        }
        return;
    }
    int mid = (tl + tr) / 2;
    if(mid < pos){
        upd(node * 2 + 1, mid + 1, tr, pos, x);
    } else{
        upd(node * 2, tl, mid, pos, x);
    }
    for(int j = 0; j <= 50; ++j){
        int w = dp[node * 2 + 1][j];
        dp[node][j] = dp[node * 2][w];
    }
}
int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    int sum = 0;
    for(int i = 0; i < n; ++i){
        cin >> a[i];
        sum += a[i];
    }

    build(1, 0, n - 1);
    auto ans = [&](){
        int x = dp[1][0];
        //cout << sum << endl;
        cout << abs(sum - x) / 2 << "\n";
        };
    ans();
    for(int i = 0; i < q; ++i){
        int p, x; cin >> p >> x;
        sum += (x - a[p]);
        upd(1, 0, n - 1, p, x);
        ans();
    }



}
