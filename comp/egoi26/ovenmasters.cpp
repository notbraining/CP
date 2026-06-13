#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<queue>
#include<cassert>
using namespace std;
#define int long long
int32_t main(){
    int n, m; cin >> n >> m;
    vector<vector<int>>tables(m);
    vector<vector<int>>adj(n);
    vector<int>indeg(n);
    vector<int>lastone(n);
    set<int>mad;
    vector<int>og_ord(m);
    for(int i = 0; i < n;++i){
        mad.insert(i);
    }
    for(int i = 0; i < m; ++i){
        int t; cin >> t;
        tables[i] = vector<int>(t);
        for(int j = 0; j < t; ++j){
            cin >> tables[i][j];
            if(!j){
                og_ord[i] = tables[i][j];
            }
            mad.erase(tables[i][j]);
            if(j){
                if(tables[i][j] < tables[i][j - 1]){
                    cout << "NO\n";
                    return 0;
                }
            }
        }
    }
    sort(tables.begin(), tables.end()); //if this TLE then change
    for(int i = 0; i < m - 1; ++i){
        for(int j = 1; j < tables[i].size(); ++j){
            auto it = lower_bound(tables[i + 1].begin(), tables[i + 1].end(), tables[i][j]);
            if(it == tables[i + 1].end()){
                cout << "NO\n"; return 0;
            }
            // this one = tables[i][j], next one = tables[i + 1][it - tables[i + 1].begin()];
            int cur = tables[i][j];
            int nx = tables[i + 1][it - tables[i + 1].begin()];
            indeg[cur] += 2;

            adj[nx].push_back(cur);
            adj[tables[i][j - 1]].push_back(cur);

            lastone[cur] = tables[i][j - 1];
        }
    }
    for(int j = 1; j < tables[m - 1].size(); ++j){
        int cur = tables[m - 1][j];
        int last = tables[m - 1][j - 1];
        adj[last].push_back(cur);
        indeg[cur]++;
        lastone[cur] = last;
    }
    if(mad.size()){
        for(int i = 0; i < m; ++i){
            if(tables[i].back() < *mad.rbegin()){
                cout << "NO\n";
                return 0;
            }
        }
    }



    /*
        for(int i = 0; i < n; ++i){
            cout << "node " << i << " ";
            for(int j : adj[i]){
                cout << j << " ";
            }
            cout << endl;
        }

    */

    priority_queue<int, vector<int>, greater<int>> pq;
    cout << "YES\n";
    set<int>currstate;
    for(int i : og_ord){
        // pq.push(tables[i][0]);
        cout << i << " ";
        currstate.insert(i);
        for(int j : adj[i]){
            indeg[j]--;
            if(indeg[j] == 0){
                pq.push(j);

            }
        }
    }
    while(!pq.empty() || !mad.empty()){
        while(!mad.empty() && *currstate.begin() > *mad.begin()){
            cout << *mad.begin() << " ";
            mad.erase(mad.begin());
        }
        if(pq.empty())break;
        int cur = pq.top(); pq.pop();
        currstate.erase(lastone[cur]);
        currstate.insert(cur);
        cout << cur << " ";
        for(int j : adj[cur]){
            indeg[j]--;
            if(indeg[j] == 0)pq.push(j);
        }

    }


    assert(mad.size() == 0);




}
