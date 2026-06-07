
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
const int K = 201;
int dp[K + 1];
int suffmin[K + 1];
int dp2[K + 1];
int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<int>w(n + 1), c(n + 1);
    for(int i = 1; i <= n; ++i){
        cin >> w[i];
    }
    for(int i = 1; i < n; ++i){
        cin >> c[i];
    }
    /*
    suffmin[K] = INF;
    //dp is all 0 because satifiying only 0 is cost 0
    //pull DP
    for(int i = 1; i <= K; ++i){
        suffmin[i] = INF;
    }
    suffmin[0] = 0;
    for(int i = 2; i <= n; ++i){
        for(int k = K - 1 ; k >= 0; --k){
            dp[k] = c[i - 1] * k + suffmin[max(0LL, w[i - 1] - k)];

        }
        for(int k = K - 1; k >= 0; --k){
            suffmin[k] = min(dp[k], suffmin[k + 1]);
        }
        cout << suffmin[w[i]] << "\n";
    }
    */

    vector<pii>hull;
    int b = 0;
    hull.push_back({0, 1e6});
    for(int i = 2; i <= n; ++i){
        //reverse at poistion w[i-1]
        int revpos = w[i - 1];
        while(hull.back().first > revpos){
            hull.pop_back();
        }
        //now reverse everything
        int newb = b;
        int currm = 0; int lastx = 0;
        for(auto [posx, md] : hull){
            newb += currm * (posx - lastx);
            lastx = posx;
            currm += md;
        }
        newb += currm * (revpos - hull.back().first);

        hull.push_back({revpos, c[i - 1]});
        reverse(hull.begin(), hull.end());
        for(int i = 0; i < hull.size(); ++i){
            hull[i].first = revpos - hull[i].first;
        }
        int sum = -currm;

        lastx = 0;
        //there might be a bug here 
        int ind = 0;
        int add = 0;
        while(true){
            newb += (hull[0].first - lastx) * sum;
            sum += hull[0].second;

            lastx = hull[0].first;
            if(sum >= 0){
                break;
            }
            add += hull[0].second;
            hull.erase(hull.begin());

        }

        hull.begin()->second = sum;
        b = newb;

        //now compute the value at w[i]
        int ans = b;
        for(auto [pos, deltam] : hull){
            if(pos >= w[i])continue;
            ans += deltam * (w[i] - pos);
        }
        cout << ans << "\n";
    }



}
