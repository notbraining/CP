
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
int INF = 2e18;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int solve(){
    int n; cin >> n;
    vector<int>p(n);
    int big = 0;
    for(int i = 0; i < n; ++i){
        cin >> p[i];
        big = max(big, p[i]);
    }
    if(!big)return 0;
    auto check = [&](int k){
        //first check the middle
        if(n % 2){
            //can only receive n-1 each turn
            if(k * (n / 2) < p[n / 2]){
                return false;
            }
        }
        //find upperbound and lower bound for the amount of A

        int ub = k; int lb = 0;
        for(int i = 0; i < n; ++i){
            if(n % 2 && i == n / 2){
                continue;
            }
            if(i < n / 2){
                //2*i-n+1 is a negative number
                //gives you a upper bound for it
                ub = min(ub, (p[i] - k * (n - 1 - i)) / (2 * i - n + 1));
                if((p[i] - k * (n - 1 - i)) > 0)
                    ub = min(ub, (p[i] - k * (n - 1 - i) - (2 * i - n)) / (2 * i - n + 1));
            } else{
                lb = max(lb, (p[i] - k * (n - 1 - i) + 2 * i - n) / (2 * i - n + 1));
            }
        }
        //if they differ by more than 1, you are cooked
        if(lb <= ub)
            return true;

        if(ub + 1 < lb)
            return false;
        //check set A = lb-1, B = k-A
        int A = lb - 1; int B = k - A - 1;
        vector<int>d(n); vector<int>diffarray(n + 1);

        for(int i = 0; i < n; ++i){
            d[i] = p[i] - A * (i)- B * (n - 1 - i);
            if(d[i] <= 0)continue;
            //everything is bad from i-d[i]+1 to i+d[i]-1;
            int badl = max((0LL), i - d[i] + 1); int badr = min((n - 1), i + d[i] - 1);
            diffarray[badl]++;
            diffarray[badr + 1]--;
        }
        //now check all possible d
        vector<int>val(n);
        val[0] = diffarray[0];
        for(int i = 1; i < n; ++i){
            val[i] = val[i - 1] + diffarray[i];
            if(!val[i] || !val[i - 1]){
                return true;
            }
        }

        return false;

        };


    //you can always win in 2* ceil(big/(n-1))

    int l = 0;
    int r = 2 * big / (n - 1) + 67;

    while(l <= r){
        int mid = (l + r) / 2;
        if(check(mid)){
            r = mid - 1;
        } else{
            l = mid + 1;
        }
    }
    return l;
}
int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while(t--){
        cout << solve() << "\n";
    }

}
