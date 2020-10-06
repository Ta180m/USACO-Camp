#include "grader.h"
#include <bits/stdc++.h>
#define par first
#define sz second
using namespace std;
using ii = pair<int, int>;
constexpr int INF = 2e9;
 
int cnt;
unordered_map<string, int> s;
vector<pair<int, ii>> m[200002];

inline void alloc(string cow) { if (s.find(cow) == end(s)) s[cow] = ++cnt, m[cnt].emplace_back(0, ii(cnt, 1)); }

inline ii & get(int i, int timestamp) {	return prev(upper_bound(begin(m[i]), end(m[i]), make_pair(timestamp, ii(INF, 0))))->second; }

int find_set(int i, int timestamp) {
	int & p = get(i, timestamp).par;
	return (p == i) ? i : (p = find_set(p, timestamp));
}
 
void add_friend(string cow1, string cow2, int timestamp) {
	alloc(cow1), alloc(cow2);
	int i = find_set(s[cow1], timestamp), j = find_set(s[cow2], timestamp);
	if (i == j) return;
	ii x = get(i, timestamp), y = get(j, timestamp);
	if (x.sz < y.sz) swap(i, j);
	m[i].emplace_back(timestamp, ii(i, x.sz + y.sz)), m[j].emplace_back(timestamp, ii(i, 0));
}
 
bool check_friend(string cow1, string cow2, int timestamp) {
	alloc(cow1), alloc(cow2);
	return find_set(s[cow1], timestamp) == find_set(s[cow2], timestamp);
}
 
int get_number_of_friends(string cow, int timestamp) {
	alloc(cow);
	return get(find_set(s[cow], timestamp), timestamp).sz;
}