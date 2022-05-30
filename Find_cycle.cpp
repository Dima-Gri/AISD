#include <iostream>
#include "vector"


int n, start, end;
bool flag = false;
std::vector<std::vector<int>> graph;
std::vector<int> ind, road, cycle;

void dfs(int now, int parent) {
    ind[now] = 1;
    for (const auto &neigh: graph[now]) {
        if (ind[neigh] == 1 && neigh != parent) {
            start = neigh;
            end = now;
            flag = true;
        } else if (ind[neigh] == 0) {
            road[neigh] = now;
            dfs(neigh, now);
        }
    }
    ind[now] = 2;
}

void resize() {
    graph.assign(n + 1, std::vector<int>());
    ind.assign(n + 1, 0);
    road.assign(n + 1, 0);
}

void init() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int a;
            std::cin >> a;
            if (a == 1) {
                graph[i + 1].push_back(j + 1);
            }
        }
    }
}

void recovery() {
    cycle.push_back(start);
    int v = end;
    while (v != start) {
        cycle.push_back(v);
        v = road[v];
    }
    std::reverse(cycle.begin(), cycle.end());
}

void print_cycle() {
    for (const auto& it: cycle) {
        std::cout << it << " ";
    }
}

int main() {
    std::cin >> n;

    resize();
    init();

    for (int i = 1; i <= n; ++i) {
        if (!ind[i]) {
            dfs(i, 0);
        }
    }

    if (flag) {
        std::cout << "Cycle exists" << std::endl;
        recovery();
        print_cycle();
        return 0;
    }
    std::cout << "Cycle not exists";

    return 0;
}
