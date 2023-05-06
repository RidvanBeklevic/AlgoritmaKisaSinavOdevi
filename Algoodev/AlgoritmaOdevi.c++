#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <functional>

using namespace std;

void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
int kadanesAlgorithm(int arr[], int n);
vector<vector<int>> dijkstraAlgorithm(const vector<vector<int>> &graph, int n);

int main() {
    int arr[] = {10, 80, 30, 90, 40, 50, 70};
    int n = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, 0, n - 1);

    cout << "Siralanmis Dizi: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int arr2[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    int max_sum = kadanesAlgorithm(arr2, n2);
    cout << "Maximum ardisik toplam: " << max_sum << endl;

    vector<vector<int>> graph = {
        {0, 10, 0, 0, 0, 0},
        {10, 0, 5, 0, 0, 0},
        {0, 5, 0, 20, 1, 0},
        {0, 0, 20, 0, 2, 0},
        {0, 0, 1, 2, 0, 0},
        {0, 0, 0, 0, 0, 0}
    };
    int n3 = graph.size();

    vector<vector<int>> shortest_distances = dijkstraAlgorithm(graph, n3);

    cout << "En kisa mesafeler:" << endl;

    for (int i = 0; i < n3; i++) {
        for (int j = 0; j < n3; j++) {
            if (shortest_distances[i][j] == INT_MAX) {
                cout << "INF ";
            } else {
                cout << shortest_distances[i][j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

int kadanesAlgorithm(int arr[], int n) {
    int max_so_far = 0, max_ending_here = 0;
    for (int i = 0; i < n; i++) {
        max_ending_here = max_ending_here + arr[i];
        if (max_ending_here < 0) {
            max_ending_here = 0;
        }
       
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
        }
    }
    return max_so_far;
}

vector<vector<int>> dijkstraAlgorithm(const vector<vector<int>> &graph, int n) {
    vector<vector<int>> shortest_distances(n, vector<int>(n, INT_MAX));
    for (int source = 0; source < n; ++source) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, source});
        while (!pq.empty()) {
            int u = pq.top().second;
            int dist_u = pq.top().first;
            pq.pop();
            if (shortest_distances[source][u] != INT_MAX)
                continue;

            shortest_distances[source][u] = dist_u;

            for (int v = 0; v < n; ++v) {
                if (graph[u][v] != 0) {
                    int alt_distance = dist_u + graph[u][v];
                    if (shortest_distances[source][v] > alt_distance) {
                        pq.push({alt_distance, v});
                    }
                }
            }
        }
    }
    return shortest_distances;
}