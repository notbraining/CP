struct segtree{
    int n;
    vector<int>t;
    segtree(int n_){
        n = n_;
        t = vector<int>(4 * n + 20, -INF);
        update(0, 0);
    }
    void update(int tl, int tr, int node, int upos, int x){

        //cout << tl << " " << tr << " " << node << " " << upos << " " << x << endl;
        //cout << n << endl;
        if(upos < tl || tr < upos){
            return;
        }
        if(tl == upos && tr == upos){
            //you are ok
            cout << node << endl;
            t[node] = x;
            return;
        }
        int mid = (tl + tr) / 2;
        update(tl, mid, node * 2, upos, x);
        update(mid + 1, tr, node * 2 + 1, upos, x);
        t[node] = max(t[node * 2], t[node * 2 + 1]);
    }
    void update(int upos, int x){
        update(0, n, 1, upos, x);
    }
    int query(int tl, int tr, int node, int ql, int qr){
        if(tr < ql || qr < tl){
            return -INF;
        }
        if(ql <= tl && tr <= qr){
            cout << "node: " << node << endl;
            cout << t[node] << endl;
            return t[node];
        }
        int mid = (tl + tr) / 2;
        return max(query(tl, mid, node * 2, ql, qr), query(mid + 1, tr, node * 2 + 1, ql, qr));
    }
    int query(int ql, int qr){
        return query(0, n, 1, ql, qr);
    }
};
