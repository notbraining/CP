vector<int> par;
int n;
int get(int x) { return (par[x] < 0 ? x : (par[x] = get(par[x]))); }
void merge(int a, int b) {
  a = get(a);
  b = get(b);
  if (a == b) return;
  if (par[a] < par[b]) {
    swap(a, b);
  }
  par[b] += par[a];
  par[a] = b;
}
