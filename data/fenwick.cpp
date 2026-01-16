struct fenwick{
    vector<int>v;
    int size;
    fenwick(int sz){
        sz+=10;
        size = sz;
        v = vector<int>(sz + 1);
    }


    int query(int l, int r){
        if(l>r)
            return 0;
        return (prefix_query(r) - prefix_query(l - 1)+MOD)%MOD;
    }
    void update(int pos, int val){
        while(pos < v.size()){
            v[pos] += val;
            v[pos]%=MOD;
            //v[pos] %= MOD;
            pos += pos & (-pos);
        }
    }
// INF loop if pos = 0,all inputs msust between 1 and n
    int prefix_query(int pos){
        int ans = 0;
        while(pos > 0){
            ans += v[pos];
            ans%=MOD;
            //ans %= MOD;
            pos -= pos & (-pos);
        }
        return ans;
    }
};
