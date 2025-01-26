struct point_t {
  int x, y;
  bool operator==(const point_t &o) {
    return (x == o.x and y == o.y);
  }
  bool operator<(const point_t &o) {
    return (x != o.x ? x < o.x : y < o.y);
  }
  point_t operator-(const point_t &o) const {
    return {x - o.x, y - o.y};
  }
  long long operator*(const point_t &o) {
    return 1ll * x * o.y - 1ll * y * o.x;
  }
} a[maxn];
long long cross(const point_t &a, const point_t &b, const point_t &c) {
  return (b - a) * (c - b);
}
bool ccw(const point_t &a, const point_t &b, const point_t &c) {
  return cross(a, b, c) >= 0;
}
bool cw(const point_t &a, const point_t &b, const point_t &c) {
  return cross(a, b, c) < 0;
}
long long dot(const point_t &a, const point_t &b, const point_t &c) {
    return 1LL * (b.x - a.x) * (c.x - a.x) + 1LL * (b.y - a.y) * (c.y - a.y);
}
vector<point_t> convex_hull(vector<point_t> a) {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  int n = a.size();
  if(n < 3) return a;
  point_t dak = a[0], mim = a[n - 1];
  vector<point_t> up, down;
  up.push_back(dak);
  down.push_back(dak);
  for(int i = 1; i < n; ++i){
    if(i == n - 1 || cw(dak, a[i], mim)) {
      while(up.size() >= 2 and !cw(up[up.size() - 2], up.back(), a[i])) up.pop_back();
      up.push_back(a[i]);
    }
    if(i == n - 1 || ccw(dak, a[i], mim)) {
      while(down.size() >= 2 and !ccw(down[down.size() - 2], down.back(), a[i])) down.pop_back();
      down.push_back(a[i]);
    }
  }
  a.clear();
  for(int i = 0; i < (int)up.size(); ++i) a.push_back(up[i]);
  int gg = down.size();
  for(int i = gg - 2; i >= 1; --i) a.push_back(down[i]);
  return a;
}
long long dist(const point_t &a, const point_t &b) {
  return 1ll * (a.x - b.x) * (a.x - b.x) + 1ll * (a.y - b.y) * (a.y - b.y);
}
