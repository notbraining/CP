struct fenwick{
    vector<int>v;
    int size;
    fenwick(int sz){
        size = sz;
        v = vector<int>(sz + 1);
    }

    int query(int l, int r){
        return query(r) - query(l - 1);
    }
    void update(int pos, int val){
        while(pos < v.size()){
            v[pos] += val;
            //v[pos] %= MOD;
            pos += pos & (-pos);
        }
    }
    int query(int pos){
        int ans = 0;
        while(pos > 0){
            ans += v[pos];
            //ans %= MOD;
            pos -= pos & (-pos);
        }
        return ans;
    }
};
