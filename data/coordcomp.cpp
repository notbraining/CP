vector<int> coord_comp(vector<int>v){
    auto x = v;
    sort(x.begin(), x.end());
    for(int i = 0; i < v.size(); ++i){
        v[i] = lower_bound(x.begin(), x.end(), v[i]) - v.begin();
    }
    return x;
}
