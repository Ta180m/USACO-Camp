#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

int a[303];
vector<int> G[303];

void dfs(int u, int p) {
	for (auto& v : G[u]) {
		dfs(v, u);
		
	}


}

int main() {
	int N;
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> a[i];
	for (int i = 1; i < N; ++i) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v), G[v].push_back(u);
	}

	dfs(1, 0);

}