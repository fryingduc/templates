#define F first
#define S second
typedef long long ll;
typedef long double ld;
struct line_container {
  deque<pair<ld, ld> > dq;

  ld value(pair<ld, ld> l, ld x) {
    return l.F * x + l.S;
  }
  bool better(pair<ld, ld> L, pair<ld, ld> L1, pair<ld, ld> L2) {
    return (L2.S - L.S) * (L1.F - L2.F) <= (L.F - L2.F) * (L2.S - L1.S);
  }
  void init() {
    dq.clear();
    dq.push_back({0, 0});
  }
  void add(ld m, ld b) {
    while((int)dq.size() >= 2 && better({m, b}, dq[dq.size() - 1], dq[dq.size() - 2])) dq.pop_back();
    dq.push_back({m, b});
  }
  ld get(ld x) {
    while((int)dq.size() >= 2 && value(dq[0], x) < value(dq[1], x)) dq.pop_front();
    return value(dq.front(), x);
  }
  void clear() {
    dq.clear();
  }
} cht[maxn / B + 5];