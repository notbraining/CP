void update(int pos, int value, vector<int>& v){
    while(pos < v.size()){
        v[pos] += value;
        pos += ((pos) & (-pos));
    }
}
int query(int pos, vector<int>& v){
    int ans = 0;
    while(pos > 0){
        ans += v[pos];
        pos -= pos & (-pos);
    }
    return ans;
}
int32_t main(){
    int n;
    cin >> n;
    vector<int>v(n + 1, 0);
    for(int i = 1; i <= n; ++i){
        int num;
        cin >> num;
        update(i, num, v);
    }
}
