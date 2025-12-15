struct fenwick{
    vector<int>v;
    int size;
    fenwick(int sz){
        size = sz;
        v = vector<int>(sz + 1);
    }


    int query(int l, int r){
        return (query(r) - query(l - 1)+MOD)%MOD;
    }
    void update(int pos, int val){
        while(pos < v.size()){
            v[pos] += val;
            //v[pos] %= MOD;
            pos += pos & (-pos);
        }
    }
//TIP: update gets INF loop if pos = 0, make sure all inputs are between 1 and n
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
