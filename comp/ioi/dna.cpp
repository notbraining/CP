#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<iomanip>
#include <cassert>
#include<algorithm>
#include<queue>
#include <array>
#include<queue>
#include <bitset>
#include<numeric>
#include<random>
#include<cstring>
#include<chrono>
using namespace std;


map<char, int>mp;
vector<vector<vector<int>>>pre;
int get_distance(int x, int y){
    vector<vector<int>>freq(3, vector<int>(3));
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            freq[i][j] = pre[y][i][j];
            if(x){
                freq[i][j] -= pre[x - 1][i][j];
            }
        }
    }
    bool ok = true;
    if(freq[0][1] + freq[0][2] != freq[1][0] + freq[2][0]) ok = false;
    if(freq[1][0] + freq[1][2] != freq[0][1] + freq[2][1]) ok = false;
    if(freq[2][1] + freq[2][0] != freq[1][2] + freq[0][2]) ok = false;
    if(!ok)return -1;

    int tot = 0;
    int ret = 0;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(i != j){
                tot += freq[i][j];

                if(i > j){
                    ret += min(freq[i][j], freq[j][i]);
                    tot -= 2 * min(freq[i][j], freq[j][i]);
                }

            }
        }
    }
    assert(tot % 3 == 0);
    return ret + tot / 3 * 2;

}
void init(string a, string b){
    mp['A'] = 0;
    mp['T'] = 1;
    mp['C'] = 2;
    int n = a.size();
    pre = vector<vector<vector<int>>>(n + 1, vector<vector<int>>(3, vector<int>(3)));
    for(int i = 0; i < n; ++i){
        int c1 = mp[a[i]];
        int c2 = mp[b[i]];
        if(i){
            for(int j = 0; j < 3; ++j){
                for(int k = 0; k < 3; ++k){
                    pre[i][j][k] = pre[i - 1][j][k];
                }
            }
        }
        pre[i][c1][c2]++;
    }
}

