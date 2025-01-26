using type = int;
struct matrix {
  vector <vector <type> > data;

  int row() const { return data.size(); } 

  int col() const { return data[0].size(); }

  auto & operator [] (int i) { return data[i]; }
  
  const auto & operator[] (int i) const { return data[i]; }

  matrix() = default;
  
  matrix(int r, int c): data(r, vector <type> (c)) { }

  matrix(const vector <vector <type> > &d): data(d) { }

  friend ostream & operator << (ostream &out, const matrix &d) {
    for (auto x : d.data) {
      for (auto y : x) out << y << ' ';
      out << '\n';
    }
    return out;
  }

  static matrix identity(long long n) {
    matrix a = matrix(n, n);
    while (n--) a[n][n] = 1;
    return a;
  }

  matrix operator * (const matrix &b) {
    matrix a = *this;
    assert(a.col() == b.row()); 
    matrix c(a.row(), b.col());
    for (int i = 0; i < a.row(); ++i)
      for (int j = 0; j < b.col(); ++j)
        for (int k = 0; k < a.col(); ++k){
          c[i][j] += 1ll * a[i][k] % mod * (b[k][j] % mod) % mod;
          c[i][j] %= mod;
        }
    return c;
  }

  matrix power(long long exp) {
    assert(row() == col());  
    matrix base = *this, ans = identity(row());
    for (; exp > 0; exp >>= 1, base = base * base)
        if (exp & 1) ans = ans * base;
    return ans;
  }
};
