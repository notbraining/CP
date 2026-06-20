
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
#define pii pair<int,int>
#define ll long long
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) cerr << #X << ": " << (X) << '\n'
#endif

vector<long long> mosaic(
    vector<int> X, vector<int> Y,
    vector<int> T, vector<int> B,
    vector<int> L, vector<int> R){
    int n = X.size(); int q = T.size();
    int M = min(n, 3);
    vector<vector<ll>>v(n);
    vector<ll>ret(q);
    for(int i = 0; i < n; ++i){
        if(i < M){
            v[i].resize(n);
        } else{
            v[i].resize(M);
        }
    }
    for(int i = 0; i < n; ++i){
        v[0][i] = X[i];
        v[i][0] = Y[i];
    }
    for(int i = 1; i < n; ++i){
        for(int j = 1; j < v[i].size(); ++j){
            if(v[i][j - 1] + v[i - 1][j] == 0){
                v[i][j] = 1;
            } else{
                v[i][j] = 0;
            }
        }
    }
    auto psum = v;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < v[i].size(); ++j){
            psum[i][j] = (i ? psum[i - 1][j] : 0) + (j ? psum[i][j - 1] : 0) - (i && j ? psum[i - 1][j - 1] : 0) + v[i][j];
        }
    }


    auto solve_rect = [&](int t, int b, int l, int r){
        return psum[b][r] - (l ? psum[b][l - 1] : 0) - (t ? psum[t - 1][r] : 0) + ((t && l) ? psum[t - 1][l - 1] : 0);
        };

    vector<ll>sum1(n - M), sum2(n - M), sum3(n - M), sum4(n - M);


    for(int i = M; i < n; ++i){
        sum1[i - M] = ((i - M) ? sum1[i - M - 1] : 0) + v[i - 1][M - 1];
        sum3[i - M] = ((i - M) ? sum3[i - M - 1] : 0) + v[i - 1][M - 1] * (n - i);
    }
    for(int i = M; i < n; ++i){
        sum2[i - M] = ((i - M) ? sum2[i - M - 1] : 0) + v[M - 1][i - 1];
        sum4[i - M] = ((i - M) ? sum4[i - M - 1] : 0) + v[M - 1][i - 1] * (n - i);
    }



    /*
        for(int i = 0; i < n - M; ++i){
        cout << sum1[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < n - M; ++i){
        cout << sum2[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < n - M; ++i){
        cout << sum3[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < n - M; ++i){
        cout << sum4[i] << " ";
    }
    cout << endl;
    */




    auto hardwork = [&](int b, int r){
        if(b < 0 || r < 0)return 0LL;
        ll ans = 0;
        ll peak = min(b, r) + 1;

        //cout << "add: " << sum3[b] - ((b - peak >= 0) ? sum3[b - peak] : 0) << endl;
        //cout << "subtract: " << ((sum1[b] - ((b - peak >= 0) ? sum1[b - peak] : 0)) * (n - M - b - 1)) << endl;
        ans += sum3[b] - ((b - peak >= 0) ? sum3[b - peak] : 0) - ((sum1[b] - ((b - peak >= 0) ? sum1[b - peak] : 0)) * (n - M - b - 1));
        ans += sum4[r] - ((r - peak >= 0) ? sum4[r - peak] : 0) - ((sum2[r] - ((r - peak >= 0) ? sum2[r - peak] : 0)) * (n - M - r - 1));

        //cout << "sum4: " << sum4[r] - ((r - peak >= 0) ? sum4[r - peak] : 0) << endl;

        //cout << "curans: " << ans << endl;
        if(r > b){
            //have some more sum2
            ans += sum2[r - b - 1] * (peak);
        }
        if(b > r){
            ans += sum1[b - r - 1] * (peak);
        }
        ans -= v[M - 1][M - 1] * peak;
        return ans;
        } ;
    for(int i = 0; i < q; ++i){
        int t = T[i]; int b = B[i]; int l = L[i]; int r = R[i];
        if(r < M){
            //just need one
            ret[i] = solve_rect(t, b, l, r); continue;
        }
        if(b < M){
            ret[i] = solve_rect(t, b, l, r); continue;
        }


        if(l < M && t < M){
            ret[i] = solve_rect(t, b, l, M - 1) ;
            ret[i] += solve_rect(t, min(M - 1, b), M, r);
        }


        if(l < M && t >= M){
            ret[i] += solve_rect(t, b, l, M - 1);
        }
        if(l >= M && t < M){
            // cout << "LL";
            ret[i] += solve_rect(t, M - 1, l, r);
        }



        // cout << "curr_ret: " << ret[i] << endl;
        if(b < M)continue;
        // cout << b - M << " " << r - M << endl;
        //cout << hardwork(b - M, r - M) << endl;

        ret[i] += hardwork(b - M, r - M) - hardwork(t - 1 - M, r - M) - hardwork(b - M, l - 1 - M) + hardwork(t - 1 - M, l - 1 - M);

    }
    return ret;
}
