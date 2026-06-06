
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
#define pii pair<int,int>
const int N = 752;
int a[N][N];
int f[N][N];
int dp[N][N][2];
int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 2; i <= n; ++i){
        for(int j = 1; j < i; ++j){
            cin >> a[i][j];
            a[j][i] = a[i][j];
        }
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            for(int k = j; k <= n; ++k){
                if(a[i][k] < 0)
                    f[i][j] += -a[i][k];
            }
        }
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            a[i][j] = max(0, a[i][j]);
        }
    }
    //iterate in order of r-l+1
    for(int len = 1; len <= n; ++len){
        for(int l = 1; l <= n; ++l){
            int r = l + len - 1;
            if(r > n)continue;
            for(int b = 0; b < 2; ++b){
                if(len == 1){
                    dp[l][r][b] = 0;
                } else{
                    dp[l][r][b] = 1e9;
                }


                for(int k = l + 1; k <= r; ++k){
                    dp[l][r][b] = min(dp[l][k - 1][0] + dp[k][r][1] + a[l][k], dp[l][r][b]);
                }
                if(b == 1){
                    dp[l][r][b] += f[l][r + 1];
                }
            }
        }
    }
    cout << dp[1][n][1];
}
