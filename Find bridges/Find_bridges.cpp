#include <iostream>
#include "vector"
#include "algorithm"


int current_time = 0;
std::vector<int> bridges;

enum class Flag {
    Unused,
    Process,
    Used
};

void dfs(int v, int in_edge, std::vector<std::vector<std::pair<int, int>>> &graph, std::vector<Flag> &ind,
         std::vector<int> &in_time, std::vector<int> &ret) {
    ind[v] = Flag::Process;
    in_time[v] = ret[v] = ++current_time;
    for (const auto&[u, edge_id]: graph[v]) {
        if (u == v) continue;
        if (ind[u] == Flag::Process && edge_id != in_edge) {
            ret[v] = std::min(ret[v], in_time[u]);
        } else if (ind[u] == Flag::Unused) {
            dfs(u, edge_id, graph, ind, in_time, ret);
            ret[v] = std::min(ret[v], ret[u]);
        }
        if (ret[u] > in_time[v]) {
            bridges.push_back(edge_id);
        }
    }
    ind[v] = Flag::Used;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> graph(n + 1);
    std::vector<int> in_time(n + 1);
    std::vector<int> ret(n + 1);
    std::vector<Flag> ind(n + 1, Flag::Unused);

    for (int i = 1; i <= m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back({b, i});
        graph[b].push_back({a, i});
    }
    for (int i = 1; i <= n; ++i) {
        if (ind[i] == Flag::Unused) {
            dfs(i, 0, graph, ind, in_time, ret);
        }
    }

    std::cout << bridges.size() << std::endl;
    std::sort(bridges.begin(), bridges.end());
    for (const auto &it: bridges) {
        std::cout << it << " ";
    }

    return 0;
}
