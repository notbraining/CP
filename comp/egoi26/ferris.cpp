#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define int long long
int32_t main(){
    int n; string s; cin >> n >> s;
    vector<int>p;
    vector<int>m;
    for(int i = 0; i < n; ++i){
        if(s[i] == '+'){
            p.push_back(i);
        } else{
            m.push_back(i);
        }
    }
    sort(p.begin(), p.end());
    sort(m.begin(), m.end(), greater<int>());
    if(p.size() == 0 || m.size() == 0 || p[0] != 0 || m[0] != n - 1){
        cout << "NO\n"; return 0;
    }
    cout << "YES\n";
    for(int i : p){
        cout << i << " ";
    }
    for(int i : m){
        cout << i << " ";
    }


}
