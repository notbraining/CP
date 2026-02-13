struct segtree{
    int n;
    vector<int>t;
    vector<int>lazy;
    segtree(int n_){
        n = n_;
        t = vector<int>(4 * n + 2, 0);
        lazy = vector<int>(4 * n + 2, 0);
    }
    void push(int tl, int tr, int node){
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        int mid = (tl + tr) / 2;
        t[node * 2] += lazy[node] * (mid - tl + 1);
        t[node * 2 + 1] += lazy[node] * (tr - mid);

        lazy[node] = 0;
    }
    void update(int tl, int tr, int node, int ul, int ur, int x){

        if(ur < tl || tr < ul){
            return;
        }
        if(ul <= tl && tr <= ur){
            t[node] += (tr - tl + 1) * x;
            lazy[node] += x;
            return;
        }
        push(tl, tr, node);
        int mid = (tl + tr) / 2;
        update(tl, mid, node * 2, ul, ur, x);
        update(mid + 1, tr, node * 2 + 1, ul, ur, x);
        t[node] = t[node * 2] + t[node * 2 + 1];
    }
    void update(int l, int r, int x){
        update(1, n, 1, l, r, x);
    }
    int query(int tl, int tr, int node, int ql, int qr){
        if(tr < ql || qr < tl){
            return 0;
        }
        if(ql <= tl && tr <= qr){
            return t[node];
        }
        push(tl, tr, node);
        int mid = (tl + tr) / 2;
        return query(tl, mid, node * 2, ql, qr) + query(mid + 1, tr, node * 2 + 1, ql, qr);
    }
    int query(int ql, int qr){
        return query(1, n, 1, ql, qr);
    }
};
