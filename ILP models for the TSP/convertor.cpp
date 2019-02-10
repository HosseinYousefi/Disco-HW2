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
int main(int argc, char* argv[]) {
    assert(argc >= 3); // an input & output path
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    int n;
    fin >> n;
    fout << "n = " << n << ";\n";
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        fin >> points[i];
    }
    fout << "c = [|\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fout << dist(points[i], points[j]);
            fout << (j == n - 1 ? "|\n": ", ");
        }
    }
    fout << "|];\n";
}
