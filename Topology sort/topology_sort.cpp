#include <iostream>
#include "vector"

std::vector<size_t> topology;
bool not_exist = false;

enum class Flag {
    Unused,
    Process,
    Used
};

void dfs(size_t now, size_t parent, std::vector<std::vector<int>> &graph, std::vector<Flag> &used) {
    used[now] = Flag::Process;
    for (const auto &neigh: graph[now]) {
        if (used[neigh] == Flag::Process && neigh != parent) {
            not_exist = true;
        } else if (used[neigh] == Flag::Unused) {
            dfs(neigh, now, graph, used);
        }
    }
    used[now] = Flag::Used;
    topology.push_back(now);
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph(n + 1);
    std::vector<Flag> used(n + 1, Flag::Unused);

    for (size_t i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
    }

    for (size_t i = 1; i <= n; ++i) {
        if (used[i] == Flag::Unused) {
            dfs(i, 0, graph, used);
        }
    }

    std::reverse(topology.begin(), topology.end());

    if (!not_exist) {
        for (const auto &it: topology) {
            std::cout << it << " ";
        }
        return 0;
    }
    std::cout << "Topology sort can not be build";

    return 0;
}
