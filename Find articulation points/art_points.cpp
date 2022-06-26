#include <iostream>
#include <vector>
#include <set>

int current_time = 0;
std::set<int> bridges;

enum class Flag {
    Unused,
    Process,
    Used
};


void dfs(int now, int parent, std::vector<std::vector<int>> &graph, std::vector<Flag> &ind,
         std::vector<int> &in_time, std::vector<int> &ret) {
    ind[now] = Flag::Process;
    in_time[now] = ret[now] = ++current_time;
    int count = 0;
    for (auto neigh: graph[now]) {
        if (neigh == parent) continue;
        if (ind[neigh] == Flag::Process) {
            ret[now] = std::min(ret[now], in_time[neigh]);
        } else {
            dfs(neigh, now, graph, ind, in_time, ret);
            ++count;
            ret[now] = std::min(ret[now], ret[neigh]);
            if (parent != 0 && in_time[now] <= ret[neigh]) {
                bridges.insert(now);
            }
        }
        if (parent == 0 && count > 1) {
            bridges.insert(now);
        }
    }
    ind[now] = Flag::Used;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n + 1);
    std::vector<int> in_time(n + 1);
    std::vector<int> ret(n + 1);
    std::vector<Flag> ind(n + 1, Flag::Unused);

    for (size_t i = 1; i <= m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for (int i = 1; i <= n; ++i) {
        if (ind[i] == Flag::Unused) {
            dfs(i, 0, graph, ind, in_time, ret);
        }
    }

    std::cout << bridges.size() << std::endl;
    for (const auto &it: bridges) {
        std::cout << it << std::endl;
    }

    return 0;
}
