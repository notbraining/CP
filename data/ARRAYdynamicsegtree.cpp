struct Node {
    ll freq = 0;
    int lazy = 0;
    int left = -1;
    int right = -1;
};

struct dyn_segtree {
    int root = 0;
    Node t[16999990];
    ll sz;
    int ind = 0;
    inline void make_Nodes(int curr){
        ind++;
        t[curr].left = ind;
        ind++;
        t[curr].right = ind;
    }
    void push_lazy(int curr, ll len){
        t[curr].lazy = 1 - t[curr].lazy;
        t[curr].freq = len - t[curr].freq;
    }
    void push_down(int curr, ll l, ll r) {
        if(l == r) return;
        ll mid = l + (r - l) / 2;
        if(t[curr].left == -1)  make_Nodes(curr);
        if(t[curr].lazy == 0)
            return;
        push_lazy(t[curr].left, mid - l + 1);
        push_lazy(t[curr].right, r - mid);
        t[curr].lazy = 0;
    }

    ll query(int curr, ll l, ll r, ll ql, ll qr){
        if(qr < l || r < ql){
            return 0;
        }
        if(ql <= l && r <= qr){
            return t[curr].freq;
        }
        //partial intersection, must vis children
        ll mid = (l + r) / 2;
        push_down(curr, l, r);
        return query(t[curr].left, l, mid, ql, qr) + query(t[curr].right, mid + 1, r, ql, qr);
    }
    void update(int curr, ll l, ll r, ll ul, ll ur){

        if(ur < l || r < ul){
            return;
        }
        //cout << "update: " << l << " " << r << endl;
        if(ul <= l && r <= ur){
            t[curr].freq = (r - l + 1) - t[curr].freq;
            t[curr].lazy = 1 - t[curr].lazy;
            return;
        }
        ll mid = (l + r) / 2;
        push_down(curr, l, r);
        update(t[curr].left, l, mid, ul, ur);
        update(t[curr].right, mid + 1, r, ul, ur);
        t[curr].freq = t[t[curr].left].freq + t[t[curr].right].freq;
    }
    dyn_segtree(ll n) : sz(n) {}
    void update(ll l, ll r) { update(root, 0, sz - 1, l, r); }
    ll query(ll l, ll r) { return query(root, 0, sz - 1, l, r); }
};
