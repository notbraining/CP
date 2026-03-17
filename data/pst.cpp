struct pst{
    static const int LIMIT = 8e6 + 10;
    static const int sz = 2e5 + 10;
    int lr[LIMIT][2];
    ll t[LIMIT];
    ll lazy[LIMIT];
    vector<int>roots;
    int freenode = 1;
    int copynode(int cur){
        freenode++;
        t[freenode] = t[cur];
        lazy[freenode] = lazy[cur];
        for(int i = 0; i < 2; ++i){
            lr[freenode][i] = lr[cur][i];
        }
        return freenode;
    }
    void push(int node, int tl, int tr){
        if(!lazy[node]) return;
        lr[node][0] = copynode(lr[node][0]);
        lr[node][1] = copynode(lr[node][1]);
        int leftchild = lr[node][0]; int rightchild = lr[node][1];
        int mid = tl + (tr - tl) / 2;
        t[leftchild] += (mid - tl + 1) * lazy[node];
        t[rightchild] += (tr - mid) * lazy[node];
        lazy[leftchild] += lazy[node]; lazy[rightchild] += lazy[node];
        lazy[node] = 0;
    }
    ll query(int node, int tl, int tr, int ql, int qr, ll add = 0){
        if(tr < ql || qr < tl){
            return 0;
        }
        if(ql <= tl && tr <= qr){
            return t[node] + (tr - tl + 1) * add;
        }
        add += lazy[node];
        //push(node, tl, tr, false);

        int mid = tl + (tr - tl) / 2;
        return query(lr[node][0], tl, mid, ql, qr, add) + query(lr[node][1], mid + 1, tr, ql, qr, add);
    }
    int update(int node, int tl, int tr, int ul, int ur, ll x){
        if(tr < ul || ur < tl)return node;
        int newnode = copynode(node);
        if(ul <= tl && tr <= ur){
            lazy[newnode] += x;
            t[newnode] += (tr - tl + 1) * x;
            return newnode;
        }
        int mid = tl + (tr - tl) / 2;
        push(newnode, tl, tr);
        lr[newnode][0] = update(lr[newnode][0], tl, mid, ul, ur, x);
        lr[newnode][1] = update(lr[newnode][1], mid + 1, tr, ul, ur, x);
        t[newnode] = t[lr[newnode][0]] + t[lr[newnode][1]];
        return newnode;
    }
    int build(vector<int>& v, int tl, int tr){
        int node = freenode++;
        if(tl == tr){
            if(tr >= v.size()){
                t[node] = 0;
            } else{
                t[node] = v[tl];
            }
            return node;
        }
        int mid = tl + (tr - tl) / 2;
        lr[node][0] = build(v, tl, mid);
        lr[node][1] = build(v, mid + 1, tr);
        t[node] = t[lr[node][0]] + t[lr[node][1]];
        return node;
    }
    void build(vector<int>& v){
        roots.push_back(build(v, 0, sz - 1));
    }
    ll query(int ver, int ql, int qr){
        return query(roots[ver], 0, sz - 1, ql, qr);
    }
    int update(int ver, int ul, int ur, int x){
        return (update(roots[ver], 0, sz - 1, ul, ur, x));
    }
};
pst seg;
int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int>v(n);
    for(int i = 0; i < n; ++i){
        cin >> v[i];
    }
    seg.build(v);

    for(int i = 0; i < q; ++i){
        int t; cin >> t;
        if(t == 1){
            int ver, ind, x; cin >> ver >> ind >> x;--ind;
            --ver;
            int val = seg.query(ver, ind, ind);
            int delta = x - val;

            int r = seg.update(ver, ind, ind, delta);
            seg.roots[ver] = r;
        }
        if(t == 2){
            int k, a, b; cin >> k >> a >> b; --k;
            --a;--b;
            cout << seg.query(k, a, b) << "\n";
        }
        if(t == 3){
            int k; cin >> k; --k;
            seg.roots.push_back(seg.roots[k]);
        }
    }
}
