/*  Initially, we sort the intervals [si,fi] based on their start si.
    Then, we will describe the binary search to solve the problem.
    We want to maximize the minimum distance between stores. (That is, we want the stores to have the maximum possible distance).
    The maximum minimum distance (dmin) generally ranges between low=1 and high=max(fi)-min(si).
    We set dmin=mid=(low+high)/2 and check if the N stores can fit into our M intervals having at least this distance.
    Specifically, I place the 1st store in the 1st available position and the second store dmin positions later unless it's not possible, so it goes to the first available position>dmin.
    IF: the intervals run out before I place all N stores then distance not feasible and set high=mid-1 and repeat.
    IF: the N stores fit, check if I can go for a larger dmin hence low=mid+1 and repeat.
    TERMINATION: when low>high
*/

#include <iostream>
#include <algorithm>
using namespace std;

// Function to check if we can place the stores with a given distance
bool canPlaceStores(int N, int M, pair<int, int> spaces[], int dmin) {
    int placed_stores = 1;  // We start from 1 because the first store has already been placed in the first available position
    int last_position = spaces[0].first;  // Place the first store at the start of the first interval

    for (int i = 0; i < M; ++i) {
        int start = spaces[i].first;
        int end = spaces[i].second;
        // We start placing the store from the first position that is at least d_min away from the previous one
        int position = max(start, last_position + dmin);

        // We place stores in this area
        while (position <= end) {
            placed_stores++;
            last_position = position;
            if (placed_stores == N) {
                return true;  // All stores have been placed
            }
            position += dmin;  // Move to the next position with at least d_min distance
        }
    }

    return false;  // We failed to place all stores
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    pair<int, int> spaces[M];  // Array of intervals of type pair<int, int>

    // Read the intervals
    for (int i = 0; i < M; ++i) {
        scanf("%d %d",&spaces[i].first, &spaces[i].second);
    }

    // Sort the intervals in ascending order based on their start (si)
    sort(spaces, spaces + M);

    // Initialization for binary search
    int low = 1, high = spaces[M - 1].second - spaces[0].first;
    int dmin = 0;

    // Binary search
    while (low <= high) {
        int mid = (low + high) / 2;
        if (canPlaceStores(N, M, spaces, mid)) {
            dmin = mid; // We can place the stores with this distance dmin
            low = mid + 1;  // Try a larger distance
        } else {
            high = mid - 1;  // We cannot place the stores with this distance dmin and try a smaller distance
        }
    }

    // Print the maximum possible minimum distance
    printf("%d\n",dmin);

    return 0;
}
