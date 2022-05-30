#include <iostream>
#include <vector>

bool flag = false;
int start, end;

void
dfs(int now, int parent, std::vector<std::vector<int>> &graph, std::vector<int> &ind, std::vector<int> &road) {
    ind[now] = 1;
    for (const auto &neigh: graph[now]) {
        if (ind[neigh] == 1 && neigh != parent) {
            start = neigh;
            end = now;
            flag = true;
        } else if (ind[neigh] == 0) {
            road[neigh] = now;
            dfs(neigh, now, graph, ind, road);
        }
    }
    ind[now] = 2;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n + 1);
    std::vector<int> ind(n + 1);
    std::vector<int> road(n + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int a;
            std::cin >> a;
            if (a == 1) {
                graph[i + 1].push_back(j + 1);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (!ind[i]) {
            dfs(i, 0, graph, ind, road);
        }
    }
    
    if (flag) {
        std::cout << "YES" << std::endl;

        std::vector<int> cycle;
        cycle.push_back(start);

        int v = end;
        while (v != start) {
            cycle.push_back(v);
            v = road[v];
        }

        std::reverse(cycle.begin(), cycle.end());
        std::cout << cycle.size() << std::endl;

        for (auto it : cycle) {
            std::cout << it << " ";
        }
    } else {
        std::cout << "NO";
    }
    return 0;
}
