const long long INF = 1e18;
struct dinic {
	const static bool SCALING = false; // scaling = EV log(max C) with larger constant
	long long lim = 1;

	struct edge {
		int u, v;
		long long cap, flow;
	};

	int n, s, t;
	vector<int> level, ptr;
	vector<edge> e;
	vector<vector<int>> g;

	dinic(int _n) : n(_n), level(_n), ptr(_n), g(_n) {
		e.clear();
		for(int i = 0; i < n; ++i) {
			ptr[i] = 0;
			g[i].clear();
		}
	}

	void add_edge(int u, int v, long long c) {
		g[u].push_back((int)e.size());
		e.push_back({u, v, c, 0});
		g[v].push_back((int)e.size());
		e.push_back({v, u, 0, 0});
	}

	long long get_max_flow(int _s, int _t) {
		s = _s, t = _t;
		long long flow = 0;
		for(lim = SCALING ? (1ll << 59) : 1; lim > 0; lim >>= 1) {
			while(1) {
				if(!bfs()) break;
				fill(ptr.begin(), ptr.end(), 0);
				while(long long pushed = dfs(s, INF))
					flow += pushed;
			}
		}
		return flow;
	}

	private:
	bool bfs() {
		queue<int> q;
		q.push(s);
		fill(level.begin(), level.end(), -1);
		level[s] = 0;
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int id : g[u]) {
				if(e[id].cap - e[id].flow < lim)
					continue;
				if(level[e[id].v] != -1)
					continue;
				level[e[id].v] = level[u] + 1;
				q.push(e[id].v);
			}
		}
		return level[t] != -1;
	}

	long long dfs(int u, long long flow) {
		if(!flow)
			return 0;
		if(u == t)
			return flow;
		for(; ptr[u] < (int)g[u].size(); ++ptr[u]) {
			int id = g[u][ptr[u]], to = e[id].v;
			if(level[to] != level[u] + 1)
				continue;
			long long pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
			if(pushed) {
				e[id].flow += pushed;
				e[id ^ 1].flow -= pushed;
				return pushed;
			}
		}
		return 0;
	}
};
