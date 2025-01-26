bool vis[maxn * 2];
int mx[maxn * 2], my[maxn * 2];
bool dfs(int u) {
	int i, to;
	if(u == 0) return 1;
	if(vis[u]) return 0;
	vis[u] = true;
	to = g[u].size();
	for(i = 0; i < to; i++) {
		if(dfs(my[g[u][i]])) {
			mx[u] = g[u][i];
			my[g[u][i]] = u;
			return 1;
		}
	}
	return 0;
}  
int max_matching() {
  int match = 0;
  memset(mx, 0, sizeof(mx));
  memset(my, 0, sizeof(my));
  while(true) {
		int inc = 0;
		memset(vis, 0, sizeof(vis));
		for(int i = 1; i <= n; i++) {
			if(!mx[i] and dfs(i)) {
				inc++;
			}
		}
    if(inc > 0) match += inc;
	  else break;
  }
  return match;
}
