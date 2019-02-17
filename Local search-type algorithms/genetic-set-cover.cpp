#include <bits/stdc++.h>

using namespace std;

int seed;
mt19937 rng;

int nElements, nSets;
vector<int> weight;
vector<set<int>> sets;

struct Member {
    vector<bool> chosen;
    int weightOfChosen;
    set<int> covers;

    Member() : chosen(nSets), weightOfChosen(0) {}

    pair<int, int> fitness() const {
        return {nElements - int(covers.size()),  weightOfChosen};
    }

    bool operator<(const Member& m) {
        return fitness() < m.fitness();
    }

    void addSet(int i) {
        chosen[i] = true;
        weightOfChosen += weight[i];
        for (int element : sets[i])
            covers.insert(element);
    }
};

const int POPULATION = 10000;
array<Member, POPULATION> population;

Member crossover(const Member& a, const Member& b) {
    Member c;
    for (int i = 0; i < nSets; ++i) {
        int rnd = rng() % 100;
        if (rnd < 6) { // 6% mutation;
            c.chosen[i] = rng() & 1;
        } else if (rnd < 53) { // a
            c.chosen[i] = a.chosen[i];
        } else { // b
            c.chosen[i] = b.chosen[i];
        }
        if (c.chosen[i]) {
            c.addSet(i);
        }
    }
    return c;
}

Member randomMember() {
    Member c;
    for (int i = 0; i < nSets; ++i) {
        if (rng() & 1) {
            c.addSet(i);
        }
    }
    return c;
}

void populate() {
    for (auto& member : population) {
        member = randomMember();
    }
}

void output() {
    for (int i = 0; i < nSets; ++i) {
        if (population.front().chosen[i])
            cout << i + 1 << ' ';
    }
    cout << endl;
}

void runGenetic() {
    populate();
    // running for 9 secs accounting for input/output
    time_t start = time(nullptr);
    int numOfGen = 0;
    while (difftime(time(nullptr), start) < 9.0) {
        sort(population.begin(), population.end());
        
        array<Member, POPULATION> newGeneration;

        // keeping top 10% of population
        for (int i = 0; i < POPULATION / 10; ++i)
            newGeneration[i] = population[i];
        
        // from top 50% of population we'll produce offspring
        for (int i = POPULATION / 10; i < POPULATION; ++i) {
            int mom = rng() % (POPULATION / 2);
            int dad = rng() % (POPULATION / 2);
            newGeneration[i] = crossover(population[mom], population[dad]);
        }

        population = newGeneration;
        ++numOfGen;

        // cerr << numOfGen << endl;
        // output();
    }
}

void input() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> nElements >> nSets;
    weight.resize(nSets);
    sets.resize(nSets);
    for (int i = 0; i < nSets; ++i) {
        cin >> weight[i];
        string line;
        getline(cin, line);
        stringstream ss(line);
        int element;
        while (ss >> element) {
            sets[i].insert(element);
        }
    }
}

int main() {
    seed = int(chrono::system_clock::now().time_since_epoch().count());
    rng.seed(seed);

    input();
    runGenetic();
    output();
}
