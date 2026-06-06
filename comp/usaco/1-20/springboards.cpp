
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
const int big = 1e12;
//range min, point add
struct segtree{
    vector<int>t, lazy;
    int n;
    segtree(int n_){
        n = n_;
        t = vector<int>(4 * n + 10, INF);
        lazy = vector<int>(4 * n + 10, 0);
    }


    void push(int node){
        t[node * 2] += lazy[node];
        t[node * 2 + 1] += lazy[node];
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        lazy[node] = 0;
    }
    void add(int node, int tl, int tr, int ql, int qr, int x){
        if(tr < ql || qr < tl){
            return;
        }

        if(ql <= tl && tr <= qr){
            t[node] += x;
            lazy[node] += x;
            return;
        }
        push(node);
        int mid = (tl + tr) / 2;
        add(node * 2, tl, mid, ql, qr, x);
        add(node * 2 + 1, mid + 1, tr, ql, qr, x);
        t[node] = min(t[node * 2], t[node * 2 + 1]);
    }

    void upd(int node, int tl, int tr, int pos, int x){
        if(tl == tr && pos == tl){
            t[node] = x;
            return;
        }
        push(node);
        int mid = (tl + tr) / 2;
        if(pos <= mid){
            upd(node * 2, tl, mid, pos, x);
        } else{
            upd(node * 2 + 1, mid + 1, tr, pos, x);
        }
        t[node] = min(t[node * 2], t[node * 2 + 1]);
    }
    int query(int node, int tl, int tr, int ql, int qr){
        if(tr < ql || qr < tl){
            return INF;
        }



        if(ql <= tl && tr <= qr){
            return t[node];
        }
        push(node);
        int mid = (tl + tr) / 2;
        return min(query(node * 2, tl, mid, ql, qr), query(node * 2 + 1, mid + 1, tr, ql, qr));
    }
    void upd(int pos, int x){
        upd(1, 0, n, pos, x);
    }
    int query(int ql, int qr){
        return query(1, 0, n, ql, qr);
    }
    void add(int ql, int qr, int x){
        add(1, 0, n, ql, qr, x);
    }

};
int32_t main(){
    freopen("boards.in", "r", stdin);
    // the following line creates/overwrites the output file
    freopen("boards.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    int N, p; cin >> N >> p;
    vector<int>coord; coord.push_back(N);
    vector<pair<pii, pii>>eoi;
    for(int i = 1; i <= p; ++i){
        int a, b, x, y; cin >> a >> b >> x >> y;
        if(a > N || b > N || x > N || y > N){
            continue;
        }
        coord.push_back(b);
        coord.push_back(y);
        eoi.push_back({{x, y}, {1, i}});
        eoi.push_back({{a, b}, {0, i}});
    }
    sort(coord.begin(), coord.end());
    auto la = unique(coord.begin(), coord.end());
    coord.erase(la, coord.end());




    int m = coord.size() + 1;
    segtree seg(m);


    vector<int>u_val(p + 2);
    u_val[0] = 0; //u_val stores the REAL value to get there, one without the +hi
    eoi.push_back({{0, 0}, {1, 0}});
    eoi.push_back({{N, N}, {67, 67}});

    sort(eoi.begin(), eoi.end());
    int last = 0;
    for(auto e : eoi){
        auto [x, y] = e.first;
        auto [t, ind] = e.second;
        seg.add(0, m, x - last);

        last = x;

        int c = lower_bound(coord.begin(), coord.end(), y) - coord.begin();


        int bestval = seg.query(0, c);
        seg.upd(c, bestval);

        if(t == 0){
            //you are updating
            u_val[ind] = bestval - (big - y);
        }
        if(t == 1){
            //you are taking the upd
            seg.upd(c, min(bestval, u_val[ind] + big - y));
        }

    }

    int cn = lower_bound(coord.begin(), coord.end(), N) - coord.begin();
    cout << seg.query(cn, cn) - (big - N);


}
