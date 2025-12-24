/*
Note: segtree with all assocative operations can actually be represented by a fenwick if you represent updates as prefix sums accumulating (differance array)

  */
struct segtree{
    vector<int>t;
    vector<int>lazy;
    int n;
    segtree(int n_){
        n_ += 10;
        n = n_;
        t = vector<int>(4 * n + 20, 0);
        lazy = t;
    }
    void push(int node){
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        t[node * 2] += lazy[node];
        t[node * 2 + 1] += lazy[node];
        lazy[node] = 0;
    }
    int query(int tl, int tr, int node, int ql, int qr){
        if(qr < tl || tr < ql){
            return 0;
        }
        if(ql <= tl && tr <= qr){
            return t[node];
        }
        push(node);
        int mid = (tl + tr) / 2;
        return query(tl, mid, node * 2, ql, qr) + query(mid + 1, tr, node * 2 + 1, ql, qr);
    }
    void update(int tl, int tr, int node, int ul, int ur, int x){
        if(tr < ul || ur < tl){
            return;
        }
        if(ul <= tl && tr <= ur){
            t[node] += x;
            lazy[node] += x;
            return;
        }
        push(node);
        int mid = (tl + tr) / 2;
        update(tl, mid, node * 2, ul, ur, x);
        update(mid + 1, tr, node * 2 + 1, ul, ur, x);
        t[node] = t[node * 2] + t[node * 2 + 1];
    }
    int query(int ql, int qr){
        return query(1, n, 1, ql, qr);
    }
    void update(int ul, int ur, int x){
        update(1, n, 1, ul, ur, x);
    }
};

void dfs(int node, int par){
    tim++;
    ord[tim] = node;
    startingval[node] = tim;
    pos[node] = tim;
    for(int j : adj[node]){
        if(j == par)
            continue;
        dfs(j, node);
    }
    endingval[node] = tim;
}
