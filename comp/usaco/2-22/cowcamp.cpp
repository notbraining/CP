
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
long double big = 1e20;
long double eps = 1e-9;
int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    int T, K; cin >> T >> K;
    --T; //remember to add 1 to the answer
    vector<long double>P(T + 1);
    P[0] = 0.5;
    for(int i = 1; i < T; ++i){
        P[0] = P[0] * 0.5;
    }
    for(int i = 1; i <= T; ++i){
        P[i] = P[i - 1] * (T - i + 1) / i;

    }

    auto check = [&](long double a, long double x, long double y, int n)->long double{
        //find x^n
        long double xn = 1;
        long double b = x;
        for(int i = 0; i < 33; ++i){
            if((1LL << i) & n){
                xn = xn * b;
            }
            b = b * b;
        }
        long double ret = a * xn + y * ((xn - 1.000) / (x - 1.0000));
        return ret;



        };


    vector<long double>dp(T + 1);
    //just you because you have no tries left
    long double y = 0;
    for(int i = 0; i <= T; ++i){
        dp[i] = i;
        y += i * P[i];
    }
    long double x = 0;
    int used = 0;
    long double a = 0;



    for(int i = 0; i <= T; ++i){
        int l = 0;
        int r = K - used;
        if(check(a, x, y, r) < i){
            //spend everyting
            a = check(a, x, y, r);
            break;
        }
        while(l <= r){
            int mid = (l + r) / 2;
            if(check(a, x, y, mid) >= i){
                r = mid - 1;
            } else{
                l = mid + 1;
            }
        }
        //l will make it fine!
        a = check(a, x, y, l);

        used += l;
        y -= i * P[i];
        x += P[i];

        //cout << "at the end: " << i << endl;
        //cout << setprecision(20) << x << " " << y << " " << a << " " << used << endl;
    }

    cout << (setprecision(20)) << a + 1;





}
