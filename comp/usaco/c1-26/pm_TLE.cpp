
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
//#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) cerr << #X << ": " << (X) << '\n'
#endif

int r, c, x;
int brute(){
    vector<vector<int>>v = {{1, 1, 1, 1}, {1, 1, 1, 0}, {1, 1, 0, 1}, {1, 0, 1, 1}
    , {1, 0, 0, 1}, {0, 1, 1, 1}, {0, 1, 1, 0}};

    vector<int>req(4, -1);
    for(int i = 0; i < x; ++i){
        char k; cin >> k;
        int num;
        if(k == '+'){
            num = 1;
        } else{
            num = 0;
        }
        int a, b; cin >> a >> b; --a; --b;
        req[a * 2 + b] = num;
    }
    int ans = 0;
    for(int i = 0; i < 7; ++i){
        bool ok = true;
        for(int j = 0; j < 4; ++j){
            if(req[j] == -1)continue;
            if(v[i][j] != req[j]) ok = false;
        }
        if(ok)ans++;
    }
    return ans;
}


int solve1(vector<pair<int, pii>>& allreq, bool zerocase){
    vector<vector<bool>>diag(r + c - 1, vector<bool>(2, true));
    for(int i = 0; i < x; ++i){
        int num = allreq[i].first;
        auto [a, b] = allreq[i].second;
        diag[a + b][1 - num] = false;

    }
    int ret = 0;
    auto check = [&](auto&& self, int L, int R, int num){
        if(L > R || L > r + c - 2 || L < 0){
            return true;
        }
        if(!diag[L][num])return false;
        if(L == R)return true;
        return self(self, L + 1, R, 1 - num);
        };
    if(zerocase){
        ret += check(check, 0, r + c - 2, 1);
        ret += check(check, 0, r + c - 2, 0);
    }
    //do one diag case first!

    for(int i = 0; i < r + c - 2; ++i){
        if(diag[i][1] && diag[i + 1][1] && check(check, 0, i - 1, 1 - i % 2) && check(check, i + 2, r + c - 2, 0)){
            ret++;
        }
    }

    for(int i = 0; i < r + c - 2; ++i){
        if(!check(check, 0, i - 1, 1 - i % 2) || !diag[i][1] || !diag[i + 1][1]){
            continue;
        }
        for(int j = i + max(r, c) - 1; j < r + c - 2; ++j){
            if((j - i) % 2 == 1){
                if(check(check, i + 2, j - 1, 0) && check(check, j + 2, r + c - 2, 0) && diag[j][1] && diag[j + 1][1]){
                    ret++;
                    //cout << "doubled down\n";
                }
            }
        }
    }
    return ret;

}

int solve(){
    cin >> r >> c >> x;
    //handle edge case
    if(r == 2 && c == 2){
        return brute();
    }

    vector<pair<int, pii>>allreq(x), allreq2(x);
    //diag, yes or no can be 0 or 1
    for(int i = 0; i < x; ++i){
        char k; cin >> k; int a, b; cin >> a >> b; --a; --b;
        int num = (k == '+') ? 1 : 0;
        allreq[i] = {num, {a, b}};
        allreq2[i] = {num, {a, c - 1 - b}};
    }

    if(min(r, c) == 1){
        return solve1(allreq, 1);
    }
    return solve1(allreq, 0) + solve1(allreq2, 1);
    //check the no diag case
}
int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    while(T--){
        cout << solve() << "\n";
    }
}
