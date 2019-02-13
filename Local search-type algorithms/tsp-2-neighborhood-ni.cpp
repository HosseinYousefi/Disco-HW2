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

const ld EPS = 1e-15;

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

bool onSegment(const Point& p, const Point& q, const Point& r)  {
    return      q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) 
            &&  q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
} 

int orientation(const Point& p, const Point& q, const Point& r) {
    ld val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
    if (abs(val) <= EPS) // colinear 
        return 0;
    return val > 0 ? 1 : 2; // clock or counterclock wise 
}

bool doIntersect(const Point& p1, const Point& q1, const Point& p2, const Point& q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) 
        return true;
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 

    return false;
} 

map<int, int> id;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand((unsigned)time(0));
    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x >> points[i];
        id[i] = x;
    }
    int times = 20;
    vector<int> bestNext;
    ld bestCost = INFINITY;
    int firstOne, bestOne = 1e9 + 9;
    while (times--) { // trying 20 random starting cities
        vector<bool> mark(n);
        int current = firstOne = rand() % n;
        ld totalCost = 0;
        vector<int> nxt(n, -1); // storing the tour in some sort of circular linked list for easier insertion
        nxt[current] = current;
        for (int cnt = 0; cnt < n - 1; ++cnt) {
            mark[current] = true;
            ld best = INFINITY;
            int neighbor = -1, insertAfter = -1;
            for (int i = 0; i < n; ++i) {
                if (!mark[i]) {
                    int cur = firstOne;
                    for (int j = 0; j <= cnt; ++j) {
                        if (
                                dist(points[i], points[cur]) 
                            +   dist(points[i], points[nxt[cur]])
                            -   dist(points[cur], points[nxt[cur]])
                            <   best
                        ) {
                            best =      
                                dist(points[i], points[cur]) 
                            +   dist(points[i], points[nxt[cur]])
                            -   dist(points[cur], points[nxt[cur]]);
                            neighbor = i;
                            insertAfter = cur;
                        }
                        cur = nxt[cur];
                    }
                }
            }
            current = neighbor;
            totalCost += best;
            nxt[current] = nxt[insertAfter];
            nxt[insertAfter] = current;
        }
        if (bestCost > totalCost) { // keeping the best one
            bestCost = totalCost;
            bestNext = nxt;
            bestOne = firstOne;
        }
    }
    int current;
    current = bestOne;
    vector<pair<int, int>> circuit;
    while (bestNext[current] != bestOne) {
        circuit.emplace_back(current, bestNext[current]);
        current = bestNext[current];
    }
    circuit.emplace_back(current, bestNext[current]);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (doIntersect(
                points[circuit[i].first],
                points[circuit[i].second],
                points[circuit[j].first],
                points[circuit[j].second])
            ) {
                
            }
        }
    }
}
