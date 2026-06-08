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
using namespace std;
#define int long long
#define pii pair<int,int>
int big = 5e7;
int tot, totdiff, st, rev, lz;
deque<pii>v; //stores length of segment, slope of this
//when reverse is true, the actual slope is the negative of (lz+element.second)
void reverse(int pos){ //does CUT and FLIP
    pii lst = {67, 67};
    if(!rev){
        //need to be global

        while(tot > pos){
            //cout << "RAN\n";
            lst = v.back();
            int m = lz + lst.second;
            tot -= lst.first;
            totdiff -= m * lst.first;
            v.pop_back();
        }
        v.push_back({pos - tot, lst.second});
        totdiff += ((pos - tot) * (lst.second + lz));
        tot = pos;
        //completed cut operation,

        /*

        rev = 1;
        st = st + totdiff;
        totdiff = -totdiff;


        //add some really long stuff
        int extend = big - tot;
        v.push_front({extend, -lz});

        */
        //now we sort of reverse the erange
        st = st + totdiff;
        totdiff = -totdiff;
        auto owo = v;
        v.clear();
        while(!owo.empty()){
            auto x = owo.front();
            v.push_front({x.first, -x.second - 2 * lz});
            owo.pop_front();
        }
        v.push_back({big, -lz});
        tot += big;


    } else{

        while(tot > pos){
            lst = v.front();
            int m = -lz - lst.second;
            tot -= lst.first;
            totdiff -= m * lst.first;
            v.pop_front();
        }
        v.push_front({pos - tot, lst.second + lz});
        totdiff += (pos - tot) * (-lst.second - lz);


        rev = 0;
        st = st + totdiff;
        totdiff = -totdiff;



        //add some really long stuff
        int extend = big - tot;
        v.push_back({extend, lz});


    }


}

//pops elements from the beginning until the slope positive
void suffmin(){
    if(!rev){
        int lensum = 0;
        while((v.front().second + lz) < 0){ //keep popping out elements as long as the front one has a decreasing slope
            lensum += v.front().first;
            tot -= v.front().first;
            totdiff -= (v.front().second + lz) * v.front().first;
            st += (v.front().second + lz) * v.front().first;
            v.pop_front();
        }
        v.push_front({lensum, -lz});
        tot += lensum;
    } else{
        int lensum = 0;
        while((-lz - v.back().second) < 0){ //keep popping out elements as long as the front one has a decreasing slope
            lensum += v.back().first;
            tot -= v.back().first;
            totdiff -= (-v.back().second - lz) * v.back().first;
            int realslope = (-v.back().second - lz);
            st += (-v.back().second - lz) * v.back().first;
            v.pop_back();
        }
        // cout << "lz: " << lz << endl;
        v.push_back({lensum, -lz});

    }
}
void add(int val){
    totdiff += tot * val;
    if(!rev){
        lz += val;
    } else{
        lz -= val;
    }
}
int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<int>w(n), c(n);
    for(int i = 0; i < n; ++i){
        cin >> w[i];
    }
    for(int i = 0; i < n - 1; ++i){
        cin >> c[i];
    }

    auto p = [&](){
        cout << "st: " << st << "\n";
        cout << "totdiff: " << totdiff << endl;
        cout << "tot: " << tot << endl;
        auto owo = v;
        while(!owo.empty()){
            cout << owo.front().first << " " << owo.front().second << endl; owo.pop_front();
        }
        cout << "end of line\n\n";
        };


    tot = big;
    totdiff = big * big;
    v.push_back({big, big});
    reverse(w[0]);

    //p();


    for(int i = 1; i < n; ++i){
        add(c[i - 1]);
        // p();
        suffmin();
        //p();

        reverse(w[i]);
        cout << st << "\n";
        //p();
    }



}
