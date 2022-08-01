#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<std::pair<int, int>>> graph(n + 1);
    std::vector<std::vector<int>> dist(n + 1, std::vector<int>(n + 1, 1e9));

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            int a;
            std::cin >> a;
            if (i != j) {
                graph[i].push_back({j, a});
            }
            dist[i][j] = a;
        }
    }

    for (size_t k = 1; k <= n; ++k) {
        for (size_t from = 1; from <= n; ++from) {
            for (size_t to = 1; to <= n; ++to) {
                dist[from][to] = std::min(dist[from][to], dist[from][k] + dist[k][to]);
            }
        }
    }
    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            std::cout << dist[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
