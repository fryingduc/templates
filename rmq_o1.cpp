// RMQ O(1): 1-indexed
// remember to change the constants, types
using ll = long long;
#define For(i, j, k) for ( int i = (j) ; i <= (k) ; i++ )
#define Fol(i, j, k) for ( int i = (j) ; i >= (k) ; i-- )
namespace RMQ
{
	using T = int; constexpr int N = 2e6 + 6; // change this 
	inline bool cmp(T x, T y) { return x < y; } // change to '>' to query max 
	inline T calc(T x, T y) { return cmp(x, y) ? x : y; }
	T val[N], pre[N], st[__lg(( N >> 5 ) + 9) + 1][( N >> 5 ) + 9]; unsigned f[N];
	__attribute__((target("bmi"  ))) inline int lb(unsigned x) { return __builtin_ctz(x)     ; }
	__attribute__((target("lzcnt"))) inline int hb(unsigned x) { return __builtin_clz(x) ^ 31; }
	inline void build(int n, T *a)
	{
		int m = ( n - 1 ) >> 5, o = hb(m + 1), stk[33]; copy(a + 1, a + n + 1, val);
		For(i, 0, n - 1) pre[i] = i & 31 ? calc(pre[i - 1], val[i]) : val[i];
		For(i, 0, m) st[0][i] = pre[min(n - 1, i << 5 | 31)];
		For(i, 1, o) For(j, 0, m + 1 - ( 1 << i ))
			st[i][j] = calc(st[i - 1][j], st[i - 1][j + ( 1 << ( i - 1 ) )]);
		For(i, 0, n - 1)
			if ( i & 31 )
			{
				f[i] = f[i - 1];
				while ( o && !cmp(val[stk[o]], val[i]) ) f[i] &= ~( 1u << ( stk[o--] & 31 ) );
				f[i] |= 1u << ( ( stk[++o] = i ) & 31 );
			}
			else f[i] = 1u << ( ( stk[o = 1] = i ) & 31 );
	}
	inline T qry(int l, int r)
	{
		if ( ( --l >> 5 ) == ( --r >> 5 ) ) return val[l + lb(f[r] >> ( l & 31 ))];
		T z = calc(pre[r], val[l + lb(f[l | 31] >> ( l & 31 ))]);
		if ( ( l = ( l >> 5 ) + 1 ) == ( r >>= 5 ) ) return z;
		int t = hb(r - l); return calc(z, calc(st[t][l], st[t][r - ( 1 << t )]));
	}
}

// build: RMQ::build(n, a), a is an array (not a vector!)
// query: RMQ::qry(l, r)
