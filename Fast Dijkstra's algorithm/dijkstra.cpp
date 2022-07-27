#include <iostream>
#include <vector>
#include <climits>
#include <set>

int main() {
    long long n, m, start, finish;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<long long, long long>>> graph(n + 1);
    std::vector<long long> parents(n + 1);
    std::vector<bool> ind(n + 1);
    std::vector<long long> path;

    for (long long i = 1; i <= m; ++i) {
        long long a, b, w;
        std::cin >> a >> b >> w;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
    }
    std::cin >> start >> finish;
    std::vector<size_t> dist(n + 1, LLONG_MAX);

    std::set<std::pair<long long, long long>> current_vert;
    dist[start] = 0;
    current_vert.insert({dist[start], start});
    while (!current_vert.empty()) {
        long long v = current_vert.begin()->second;
        current_vert.erase(current_vert.begin());
        for (auto&[u, w]: graph[v]) {
            if (dist[u] > dist[v] + w) {
                current_vert.erase({dist[u], u});
                dist[u] = dist[v] + w;
                current_vert.insert({dist[u], u});
                parents[u] = v;
            }
        }
    }
    if (dist[finish] == LLONG_MAX) {
        std::cout << -1;
        return 0;
    }
    std::cout << dist[finish];
    return 0;
}
