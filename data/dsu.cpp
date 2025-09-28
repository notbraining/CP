struct DSU{
    vector<int> par;
    vector<int>sz;
    DSU(int _n){
        par = vector<int>(_n + 1);
        sz = vector<int>(_n + 1, 1);
        for(int i = 0; i <= _n; ++i){
            par[i] = i;
        }
    }
    //with path compression
    int get(int x) { return (par[x] == x ? x : (par[x] = find(par[x]))); }
    //small to large merging
    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if(a == b) return;
        if(sz[a] > sz[b]) {
            swap(a, b);
        }
        sz[b] += sz[a];
        par[a] = b;
    }
};
