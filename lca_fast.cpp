int tt[maxn], rev_tt[maxn];
int par_t[maxn];
int cur_tt;
void re_define(int u, int prev) {
  tt[u] = ++cur_tt;
  par_t[tt[u]] = tt[prev];
  rev_tt[cur_tt] = u;
  for(auto e:g[u]) {
    int v = e.first;
    if(v == prev) continue;
    re_define(v, u);
  }
}
// RMQ from https://judge.yosupo.jp/submission/177420 + ivdep
template <class T> struct Sparse_Table {
  int n, lg;
  std::vector<std::basic_string<T>> st;
 
  Sparse_Table() {};
 
  void setup(int n) {
    this->n = n;
    lg = 1;
    while ((1 << lg) < n) lg++;
    st.resize(lg);
    st[0].resize(n);
  }
  void build() {
    for (int i = 0; i < (lg - 1); i++) {
      int lim = st[i].size() - (1 << i);
      st[i + 1].resize(lim);
      for (int j = 0; j < lim; j++)
        st[i + 1][j] = std::min(st[i][j], st[i][j + (1 << i)]);
    }
  }
  T prod(int l, int r) const {
    if (l == r) return INT_MAX;
    if (l + 1 == r) return st[0][l];
    int k = __lg(r - l - 1);
    return std::min(st[k][l], st[k][r - (1 << k)]);
  }
};
template <typename T, int LG = 8>
struct Static_Range_Product {
  int n;
  std::vector<T> a, pre, suf;
  Sparse_Table<T> st;
  Static_Range_Product() {}
  Static_Range_Product(int n) {
    this->n = n;
    a.resize(n);
  }
  void build() {
    pre = suf = a;
    constexpr int mask = (1 << LG) - 1;
    for (int i = 1; i < n; ++i)
      if (i & mask)
        pre[i] = std::min(pre[i - 1], a[i]);
    for (int i = n - 1; i >= 0; --i)
      if (i & mask)
        suf[i - 1] = std::min(a[i - 1], suf[i]);
    st.setup(n >> LG);
    for (int i = 0; i < n >> LG; ++i) st.st[0][i] = suf[i << LG];
    st.build();
  }
  T prod(int l, int r) const {
    if (l == r) return INT_MAX;
    r--;
    int x = l >> LG, y = r >> LG;
    if (x < y) return std::min(std::min(suf[l], st.prod(x + 1, y)), pre[r]);
    T t = a[l];
    for (int i = l + 1; i < r + 1; ++i) {
      t = std::min(t, a[i]);
    }
    return t;
  }
};
Static_Range_Product<int> rmq;
int dp[maxn];
inline int lca(int u, int v) {
  if(u == v) return u;
  int l = dp[tt[u] - 1], r = dp[tt[v] - 1];
  if(l > r) swap(l, r);
  return rev_tt[(int)rmq.prod(l, r) + 1];
}

// add this to the solve function
/*
  re_define(1, 0);
  for (int u = n - 1; u > 0; --u) {
    int v = par_t[u + 1] - 1;
    dp[v] += dp[u] + 1;
  }
  for (int u = 1; u < n; ++u) {
    int v = par_t[u + 1] - 1;
    dp[u] = exchange(dp[v], dp[v] - dp[u] - 1);
  } 
  rmq = Static_Range_Product<int>(n);
  for (int i = 1; i < n; ++i) {
    rmq.a[dp[i] - 1] = par_t[i + 1] - 1;
  }
  rmq.build();
*/
