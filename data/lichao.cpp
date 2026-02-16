#define ll long long
ll INF = 1e18;
struct Line{
    ll m, b;
    Line(){
        //worst possible line 
        m = 0; b = -INF;
    }
    Line(ll x, ll y){
        m = x;
        b = y;
    }
    ll eval(ll x) const{
        return m * x + b;
    }
    bool better(const Line& other, ll L, ll R) const{
        return eval(L) >= other.eval(L) && eval(R) >= other.eval(R);
    }
};
struct LCT{
    LCT* children[2];
    Line bestline;
    const ll MAXN = 1e9;
    LCT(){
        children[0] = children[1] = nullptr;
        bestline = Line();
    }
    ~LCT(){
        if(children[0]) delete children[0];
        if(children[1]) delete children[1];
    }
    void makechild(ll ind){
        if(!children[ind]){
            children[ind] = new LCT();
        }
    }
    ll query(ll x, ll L, ll R){
        ll ans = bestline.eval(x);
        ll mid = L + (R - L) / 2;
        if(L == R) return ans; //leaf
        if(x <= mid){
            if(children[0]){
                ans = max(ans, children[0]->query(x, L, mid));
            }
        } else{
            if(children[1]){
                ans = max(ans, children[1]->query(x, mid + 1, R));
            }
        }
        return ans;
    }
    void add(Line newline, ll L, ll R){
        if(newline.better(bestline, L, R)){
            swap(newline, bestline);
        }
        if(bestline.better(newline, L, R))
            return;
        if(bestline.eval(L) < newline.eval(L))
            swap(newline, bestline);
        ll mid = L + (R - L) / 2;
        if(newline.eval(mid) >= bestline.eval(mid)){
            swap(newline, bestline);
            makechild(0);
            children[0]->add(newline, L, mid);
        } else{
            makechild(1);
            children[1]->add(newline, mid + 1, R);
        }
    }
    ll query(ll x){
        return query(x, -MAXN, MAXN);
    }
    void add(Line newline){
        add(newline, -MAXN, MAXN);
    }
    void update_range(Line newline, ll ul, ll ur, ll tl, ll tr){
        if(tr < ul || ur < tl) return;
        if(ul <= tl && tr <= ur){
            add(newline, tl, tr);
            return;
        }
        ll mid = tl + (tr - tl) / 2;
        makechild(0);
        makechild(1);
        children[0]->update_range(newline, ul, ur, tl, mid);
        children[1]->update_range(newline, ul, ur, mid + 1, tr);
    }
    void update_range(Line newline, ll ul, ll ur){
        update_range(newline, ul, ur, -MAXN, MAXN);
    }
};
int main(){
    cin.tie(0)->sync_with_stdio(0);
    LCT* lichao = new LCT();
}
