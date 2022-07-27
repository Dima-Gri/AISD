#include <iostream>
#include <vector>

bool change = true;

void bellman_ford(int start, int n, int inf) {
    std::vector<int> dist(n + 1, inf);
    std::vector<int> prev(n + 1, 0);
    dist[start] = 0;
    for (int k = 1; (k < n) && change; ++k) {
        change = false;
        for (int i = 1; i < n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (dist[i] != inf) {
                    if (dist[j] > dist[i] + (179 * i + 719 * j) % 1000 - 500) {
                        dist[j] = dist[i] + (179 * i + 719 * j) % 1000 - 500;
                        prev[j] = i;
                        change = true;
                    }
                }
            }
        }
        if (!change) {
            break;
        }
    }
    std::cout << dist[n];
}

int main() {
    int n;
    std::cin >> n;
    bellman_ford(1, n, 1e9);
    return 0;
}
