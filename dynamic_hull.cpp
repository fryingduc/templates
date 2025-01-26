// add + check query

#include "bits/stdc++.h"
using namespace std;

#define int long long

struct pt{
  int x, y;
  
  pt() : x(0), y(0) {}
  pt(int _x, int _y) : x(_x), y(_y) {}
  bool operator==(const pt o) const{
    return x == o.x and y == o.y; 
  }
  bool operator<(const pt o) const{
    return (x != o.x ? x < o.x : y < o.y);
  }
  pt operator-(const pt &o) const{
    return {x - o.x, y - o.y};
  }
  long long operator*(const pt &o) const{
    return x * o.y - y * o.x;
  }
};
int cross(const pt &a, const pt &b, const pt &c){
  return (b - a) * (c - b);
}
bool ccw(const pt &a, const pt &b, const pt &c){
  return cross(a, b, c) > 0;
}
struct upper {
  set<pt> se;
  set<pt>::iterator it;

  int is_under(pt p) { // 1 -> inside ; 2 -> border
    it = se.lower_bound(p);
  	if (it == se.end()) return 0;
  	if (it == se.begin()) return p == *it ? 2 : 0;
  	if (ccw(p, *it, *prev(it))) return 1;
  	return ccw(p, *prev(it), *it) ? 0 : 2;
  }
  void insert(pt p) {
  	if (is_under(p)) return;
  
  	if (it != se.end()) while (next(it) != se.end() and !ccw(*next(it), *it, p))
  		it = se.erase(it);
  	if (it != se.begin()) while (--it != se.begin() and !ccw(p, *it, *prev(it)))
  		it = se.erase(it);
  
  	se.insert(p);
  }
};
struct dynamic_convex_hull {
  upper U, L;

  int is_inside(pt p) {
  	int u = U.is_under(p), l = L.is_under({-p.x, -p.y});
  	if (!u or !l) return 0;
  	return max(u, l);
  }
  void add(pt p) {
  	U.insert(p);
  	L.insert({-p.x, -p.y});
  }
  int size() {
  	int ans = U.se.size() + L.se.size();
  	return ans <= 2 ? ans/2 : ans-2;
  }
};

int q;
void solve(){
  cin >> q;
  dynamic_convex_hull hull;
  while(q--){
      int op; cin >> op;
      if(op == 1){
        pt x; cin >> x.x >> x.y;
        hull.add(x);
      }
      else{
        pt x; cin >> x.x >> x.y;
        cout << (hull.is_inside(x) ? "YES" : "NO") << '\n';
      }
  }
}
signed main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int test = 1;
  // cin >> test;
  for(int i = 1; i <= test; i++){
    // cout << "Case " << "#" << i << ": "; 
    solve();
  }

  return 0;
}
