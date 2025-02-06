int lower_bound(long long v) {
  long long sum = 0;
  int pos = 0;
  for (int i = LG; i >= 0; i--) {
    if (pos + (1 << i) <= n and sum + bit[pos + (1 << i)] < v) {
      sum += bit[pos + (1 << i)];
      pos += (1 << i);
    }
  }
  return pos + 1;
}