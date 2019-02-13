#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> w;
vector<int> bins, bestAssignment, currentAssignment, partialSum;
int n, c, bestAnswer;

int findLowerBound(int index, int numOfBins) {
    // For finding the lower bound, we drop the constraint on the fact
    // that the object must be completely in one bin.
    //
    // So the minimum number of bins is ceil((w[index + 1] + ... w[n - 1] - capLeft) / c)
    // where capLeft is the total remaining capacity from the previous bins so
    // capLeft = c * numOfBins - (w[0] + ... w[index])
    int capLeft = c * numOfBins - partialSum[index];
    return (partialSum[n - 1] - partialSum[index] - capLeft + c - 1) / c;
}

void dfs(int index, int answer) {
    if (index == n - 1) { // We are done
        if (answer < bestAnswer) {
            bestAnswer = answer;
            copy(currentAssignment.begin(), currentAssignment.end(), bestAssignment.begin());
        }
        return;
    }

    for (int i = 0; i < answer; ++i) {
        if (bins[i] >= w[index + 1].first) { // if it fits in the i-th bin
            if (findLowerBound(index + 1, answer) + answer < bestAnswer) {
                // We can possibly get a better answer
                // so let's put index+1-th item to bin #i
                bins[i] -= w[index + 1].first;
                currentAssignment[w[index + 1].second] = i;
                dfs(index + 1, answer);

                // At the end, undoing: removing the item from the bin
                bins[i] += w[index + 1].first;
                currentAssignment[index + 1] = -1;
            }
        }
    }
    // Creating a new bin
    if (findLowerBound(index + 1, answer + 1) + answer + 1 < bestAnswer) {
        // So let's put index+1-th item to the last bin
        bins[answer] -= w[index + 1].first;
        currentAssignment[w[index + 1].second] = answer;

        dfs(index + 1, answer + 1);
    }
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> c;
    w.resize(n);
    // Maximum number of bins is n, initially they have capacity c.
    bins.resize(n, c);
    currentAssignment.resize(n, -1);

    // In the worst case all of items will go in different packs
    bestAssignment.resize(n);
    iota(bestAssignment.begin(), bestAssignment.end(), 0);
    bestAnswer = n;

    for (int i = 0; i < n; ++i) {
        cin >> w[i].first;
        // Keeping the original index
        w[i].second = i;
    }

    // Sorting the weights in non-increasing order
    sort(w.rbegin(), w.rend());

    // Keeping a partial sum of weights to calculate the lowerbound faster
    partialSum.resize(n);
    partialSum[0] = w[0].first;
    for (int i = 1; i < n; ++i)
        partialSum[i] = partialSum[i - 1] + w[i].first;
    
    // We always put the first one in the first bin
    currentAssignment[w[0].second] = 0;
    bins[0] -= w[0].first;
    dfs(0, 1);
    for (int i : bestAssignment)
        cout << i + 1 << ' ';
    cout << '\n';
}
