#include <iostream>
#include <vector>

int main() {
    int n, start, finish;
    std::cin >> n >> start >> finish;
    std::vector<std::vector<std::pair<int, int>>> graph(n + 1);
    std::vector<int> parents(n + 1);
    std::vector<bool> ind(n + 1);
    std::vector<int> path;

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            int a;
            std::cin >> a;
            if (i != j && a != -1) {
                graph[i].push_back({j, a});
            }

        }
    }
    std::vector<int> dist(n + 1, 1e9);
    dist[start] = 0;
    for (int i = 1; i <= n; ++i) {
        int v = -1;
        for (int j = 1; j <= n; ++j)
            if (!ind[j]) {
                if (v == -1 || dist[j] < dist[v]) {
                    v = j;
                }
            }
        if (dist[v] == 1e9)
            break;
        ind[v] = true;
        for (size_t j = 0; j < graph[v].size(); ++j) {
            int old = dist[graph[v][j].first];
            dist[graph[v][j].first] = std::min(dist[v] + graph[v][j].second, dist[graph[v][j].first]);
            if (old != dist[graph[v][j].first]) {
                parents[graph[v][j].first] = v;
            }
        }
    }
    if (dist[finish] == 1e9) {
        std::cout << "Path not exists";
        return 0;
    }
    int now = finish;
    while (now != start) {
        path.push_back(now);
        now = parents[now];
    }
    path.push_back(start);

    reverse(path.begin(), path.end());
    for (auto it: path) {
        std::cout << it << " ";
    }
    return 0;
}
