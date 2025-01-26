#include "bits/stdc++.h"
using namespace std;

#ifdef duc_debug
#include "bits/debug.h"
#else
#define debug(...)
#endif

const int maxn = 2e5 + 5;
const int LG = 19;
int n, q;
pair<int, int> a[maxn];
int id[maxn];
vector<pair<int, int>> g[maxn];

bool cmp(const int &i, const int &j) {
  return a[i].first + a[i].second < a[j].first + a[j].second;
}
int dist(int x, int y) {
  return abs(a[x].first - a[y].first) + abs(a[x].second - a[y].second);
}
int lab[maxn];
struct dsu {
  int n; 
  dsu() {}
  dsu(int n) : n(n) {
    memset(lab, -1, sizeof(lab));
  }
  int find(int u) {
    return lab[u] < 0 ? u : lab[u] = find(lab[u]);
  }
  bool is_joined(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) {
      return 1;
    }
    if(lab[u] > lab[v]) swap(u, v);
    lab[u] += lab[v];
    lab[v] = u;
    return 0;
  }
} ds;
void solve() {
  cin >> n;
  for(int i = 1; i <= n; ++i){
    cin >> a[i].first >> a[i].second;
  }
  vector<pair<int, int>> edges;
  iota(id, id + n + 1, 0);
  for(int s = 0; s < 2; ++s) {
    for(int t = 0; t < 2; ++t) {
      sort(id + 1, id + n + 1, cmp);
      map<int, int> sweep;
      for(int i = 1; i <= n; ++i) {
        int dak = id[i];
        auto it = sweep.lower_bound(-a[dak].second);
        while(it != sweep.end()) {
          int j = it->second;
          if(a[dak].first - a[j].first < a[dak].second - a[j].second) break;
          edges.emplace_back(min(j, dak), max(j, dak));
          it = sweep.erase(it);
        }
        sweep[-a[dak].second] = dak;
      }
      for(int i = 1; i <= n; ++i) swap(a[i].first, a[i].second);
    }
    for(int i = 1; i <= n; ++i) {
      a[i].first = -a[i].first;
    }
  }
  sort(edges.begin(), edges.end(), [&](const pair<int, int> &x, const pair<int, int> &y) -> bool {
    return dist(x.first, x.second) < dist(y.first, y.second);
  });
  edges.erase(unique(edges.begin(), edges.end()), edges.end());
  
  ds = dsu(n);
  for(auto &e:edges) {
    int w = dist(e.first, e.second);
    if(!ds.is_joined(e.first, e.second)) {
      g[e.first].emplace_back(e.second, w);
      g[e.second].emplace_back(e.first, w);
    }
  }
}
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  solve();

  return 0;
}



