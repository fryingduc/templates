#include "bits/stdc++.h"
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif

using ll = long long;
using pii = pair<int, int>;

#define F first
#define S second
#define sz(x) (int)((x).size())
#define all(x) (x).begin(), (x).end()

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll get_rand(ll l, ll r) {
    assert(l <= r);
    return uniform_int_distribution<ll> (l, r)(rng);
}

struct Line{
    ll a, b;
    Line() : a(0), b(0) {}
    Line(ll _a, ll _b) : a(_a), b(_b) {}
    Line(Line &x, Line &y){
        a = x.a + y.a;
        b = x.b + y.b;
    }
    ll get(ll x){ return a * x + b; }
};

struct SlopeTrickableFunction{
    Line rightmost;
    multiset<ll> st;

    SlopeTrickableFunction(){}

    SlopeTrickableFunction(ll _xabs){
        rightmost = Line(1, -_xabs);
        st.insert(_xabs);
        st.insert(_xabs);
    }

    SlopeTrickableFunction(SlopeTrickableFunction &x, SlopeTrickableFunction &y){
        // debug(x.rightmost.a, y.rightmost.a);
        rightmost = Line(x.rightmost, y.rightmost);
        st = x.st;
        for(ll s : y.st)
            st.insert(s);
    }
};

void solve(){
    int n;
    cin >> n;
    vector<ll> a(n), b(n);

    SlopeTrickableFunction f;

    ll pre = 0;

    for(ll i = 0; i < n; ++i){
        ll x;
        cin >> x;
        a[i] = x;
        x -= i;

        debug(x);

        SlopeTrickableFunction cur(x);
        SlopeTrickableFunction g = SlopeTrickableFunction(f, cur);

        // debug(g.rightmost.a);

        // debug(g.st, g.rightmost.a, g.rightmost.b);

        f = g;

        while(f.rightmost.a > 0){
            ll last = *f.st.rbegin();
            f.st.erase(f.st.find(last));
            f.rightmost.b = f.rightmost.get(last) - last * (f.rightmost.a - 1);
            --f.rightmost.a;
        }
        debug(f.st, f.rightmost.a, f.rightmost.b);
        pre = f.rightmost.b;
        b[i] = *f.st.rbegin();
        // debug(f.rightmost.a, f.rightmost.b);
    }

    debug(b);

    debug(f.rightmost.a, f.rightmost.b);

    int last = b.back();
    ll total = 0;
    for(int i = n - 1; i >= 0; --i){
        b[i] += i;
        if(i < n - 1)
            b[i] = min(b[i], b[i + 1] - 1);
        total += abs(a[i] - b[i]);
    }

    debug(b);

    assert(total == f.rightmost.b);

    cout << f.rightmost.b << '\n';
    for(int i = 0; i < n; ++i)
        cout << b[i] << " \n"[i == n - 1];
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(0);
    #define task "troll"
    if(fopen(task".inp", "r")){
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    int test = 1;
//    cin >> test;
    for(int i = 1; i <= test; ++i){
//        cout << "Case #" << i << ": ";
        solve();
    }
    #ifdef LOCAL
        cerr << "\n[Time]: " << 1000.0 * clock() / CLOCKS_PER_SEC << " ms.\n";
    #endif
    return 0;
}

