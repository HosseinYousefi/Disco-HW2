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

ld square(ld x) {
    return x * x;
}

ld dist(const Point& a, const Point& b) {
    return sqrt(square(a.x - b.x) + square(a.y - b.y));
}

vector<vector<int>> adj;
vector<bool> mark;
vector<int> deg;

void dfs(int v) {
    cout << v + 1 << ", ";
    mark[v] = true;
    for (int u : adj[v]) {
        ++deg[u];
        if (!mark[u])
            dfs(u);
    }
}

int main(int argc, char* argv[]) {
    // gets answer of minizinc and output different components
    assert(argc >= 2); // an input
    ifstream fin(argv[1]);
    int n;
    fin >> n;
    adj.resize(n);
    mark.resize(n);
    deg.resize(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x;
            fin >> x;
            if (x) {
                adj[i].push_back(j);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!mark[i]) {
            cout << "{";
            dfs(i);
            cout << "\b\b}\n";
        }
    }
}
