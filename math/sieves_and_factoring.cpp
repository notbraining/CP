const int maxa = 1e7;
vector<int>pdiv(maxa + 1);
//fill each element in pdiv w/ biggest prime divisor
void sieve_max(){
    for(int i = 2; i <= maxa; ++i){
        if(pdiv[i] == 0){
            for(int j = i; j <= maxa; j += i){
                pdiv[j] = i;
            }
        }
    }
}
//fill each element in pdiv w/ smallest prime divisor
void sieve_min(){
    for(int i = 2; i <= maxa; ++i){
        if(pdiv[i] == 0){
            for(int j = i; j <= maxa; j += i){
                if(pdiv[j] == 0)
                    pdiv[j] = i;
            }
        }
    }
}
vector<int> factor_all(int x){
    //find all factors:
    vector<int>v;
    while(x != 1){
        v.push_back(pdiv[x]);
        x /= pdiv[x];
    }
    return v;
}
vector<int> factor_distinct(int x){
    //find all unique factors:
    vector<int>v;
    int lastone = -1;
    while(x != 1){
        if(lastone != pdiv[x])
            v.push_back(pdiv[x]);
        x /= (lastone = pdiv[x]);
    }
    return v;
}
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve_min();
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i){
        int a;
        cin >> a;
        vector<int>factall = factor_all(a);
        vector<int>factdist = factor_distinct(a);
        for(int i : factall){
            cout << i << " ";
        }
        cout << "\n";
        for(int i : factdist){
            cout << i << " ";
        }
        cout << "\n\n\n";
    }
    /*
    try running with input of:
        5
        4
        12
        24
        25
        60
    */

}
