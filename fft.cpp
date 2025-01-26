using cd = complex<long double>;

void fft(vector<cd> &a, bool invert) {
  int n = a.size(), L = __builtin_ctz(n);
  vector<int> rev(n);
  for(int i = 0; i < n; i++) {
    rev[i] = (rev[i >> 1] | (i & 1) << L) >> 1;
    if(i < rev[i]) swap(a[i], a[rev[i]]);
  }
  for(int len = 2; len <= n; len <<= 1) {
    cd wlen = polar(1.0L, acos(-1.0L) / len * (invert ? -2 : 2));
    for(int i = 0; i < n; i += len) {
      cd w = 1;
      for(int j = 0; j < len / 2; j++) {
        cd u = a[i + j];
        cd v = a[i + j + len / 2] * w;
        a[i + j] = u + v;
        a[i + j + len / 2] = u - v;
        w *= wlen;
      }
    }
  }
  if(invert) {
    for(auto &x : a) x /= n;
  }
}

vector<long long> conv(const vector<long long> &a, const vector<long long> &b) {
  if(a.empty() || b.empty()) return {};
  int n = 1;
  while(n < int(a.size() + b.size()) - 1) n <<= 1;
  vector<cd> in(n), out(n);
  for(int i = 0; i < int(a.size()); i++) {
    in[i].real(a[i]);
  }
  for(int i = 0; i < int(b.size()); i++) {
    in[i].imag(b[i]);
  }
  fft(in, false);
  for(int i = 0; i < n; i++) {
    in[i] *= in[i];
  }
  for(int i = 0; i < n; i++) {
    int j = -i & (n - 1);
    out[i] = in[i] - conj(in[j]);
  }
  fft(out, true);
  vector<long long> res(n);
  for(int i = 0; i < n; i++) {
    res[i] = (long long)(imag(out[i]) / 4 + 0.5);
  }
//  while(!res.empty() and res.back() == 0) {
//    res.pop_back();
//  }
  return res;
}
