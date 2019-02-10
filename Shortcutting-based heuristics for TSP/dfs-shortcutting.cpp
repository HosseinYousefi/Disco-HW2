#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

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
vector<vector<int>> adj;
vector<bool> mark;
vector<Point> points;
ld cost = 0;
int lastOne;

void dfs(int v) {
    cout << id[v] << ' ';
    mark[v] = true;
    lastOne = v;
    for (int u : adj[v]) {
        if (!mark[u]) {
            cost += dist(points[u], points[v]);
            dfs(u);
        }
    }
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
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
        adj[parent[i]].push_back(i);
        adj[i].push_back(parent[i]);
    }
    mark.assign(n, false);
    dfs(0);
    cout << id[0] << '\n';
    cost += dist(points[lastOne], points[0]);
}
