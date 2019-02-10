#define _USE_MATH_DEFINES

#ifdef LOCAL
#include "prettyprint.hpp"
#endif

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

template <typename... Ts>
void eprint(Ts&&... ts) {
#ifdef LOCAL
    ((cerr << ts << " "), ...) << endl;
#endif
}

#define DEBUG(x...) eprint("[" #x "]:", x)

struct Point {
    ld x, y;
};

istream& operator>>(istream& in, Point& p) {
    return in >> p.x >> p.y;
}

ostream& operator<<(ostream& out, const Point& p) {
    return out << "(" << p.x << ", " << p.y << ")";
}

ld square(ld x) {
    return x * x;
}

ld dist(const Point& a, const Point& b) {
    return sqrt(square(a.x - b.x) + square(a.y - b.y));
}

map<int, int> id;
vector<bool> mark;
vector<Point> points;
vector<multiset<int>> adj;
ld cost = 0;
int lastOne, n;

void dfs(int v) {
    if (!mark[v]) {
        mark[v] = true;
        cout << id[v] << ' ';
    }
    while (adj[v].size()) {
        int u = *adj[v].begin();
        adj[v].erase(adj[v].begin());
        adj[u].erase(adj[u].find(v));
        dfs(u);
    }
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    points.resize(n);
    mark.resize(n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x >> points[i];
        id[i] = x;
    }
    vector<ld> d(n, INFINITY);
    vector<int> parent(n);
    d[0] = 0;
    for (int i = 0; i < n - 1; ++i) {
        pair<ld, int> bestPoint{INFINITY, 0};
        for (int j = 0; j < n; ++j)
            if (!mark[j])
                bestPoint = min(bestPoint, make_pair(d[j], j));
        int u = bestPoint.second;
        mark[u] = true;
        for (int j = 0; j < n; ++j) {
            if (!mark[j] && dist(points[u], points[j]) < d[j]) {
                d[j] = dist(points[u], points[j]);
                parent[j] = u;
            }
        }
    }
    adj.resize(n);
    for (int i = 0; i < n; ++i) {
        adj[parent[i]].insert(i); 
        adj[i].insert(parent[i]);
    }
    set<int> odd;
    for (int i = 0; i < n; ++i) {
        if (adj[i].size() & 1) { // finding a MWPM between odd vertices
            odd.insert(i);
        }
    }
    while (odd.size()) { // greedy heuristic to find a MWPM, always get the two with the lowest distance!
        tuple<ld, int, int> mn{INFINITY, -1, -1};
        for (int i : odd) {
            for (int j : odd) {
                if (i != j) {
                    mn = min(mn, make_tuple(dist(points[i], points[j]), i, j));
                }
            }
        }
        ld d;
        int u, v;
        tie(d, u, v) = mn;
        adj[u].insert(v);
        adj[v].insert(u);
        odd.erase(u);
        odd.erase(v);
    }
    // finding the eulerian circuit
    mark.assign(n, false);
    dfs(0);
    cout << id[0] << '\n';
}
