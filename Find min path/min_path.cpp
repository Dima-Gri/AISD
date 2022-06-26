#include <iostream>
#include <vector>
#include <queue>

int start, finish;
std::vector<int> d;
std::vector<int> parent;

void bfs(const std::vector<std::vector<int>> &graph, std::vector<bool> &used) {
    std::queue<int> q;
    q.push(start);
    used[start] = true;
    parent[start] = -1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto it: graph[v]) {
            if (!used[it]) {
                used[it] = true;
                q.push(it);
                d[it] = d[v] + 1;
                parent[it] = v;
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n + 1);
    std::vector<bool> used(n + 1);
    d.assign(n + 1, 0);
    parent.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int a;
            std::cin >> a;
            if (a) {
                graph[i].push_back(j);
            }
        }
    }

    std::cin >> start >> finish;
    bfs(graph, used);
    if (!used[finish]) {
        std::cout << "Path not exists";
        return 0;
    }
    std::cout << d[finish] << std::endl;

    if (d[finish]) {
        std::vector<int> path;
        int now = finish;
        while (now != -1) {
            path.push_back(now);
            now = parent[now];
        }

        std::reverse(path.begin(), path.end());
        for (const auto it: path)
            std::cout << it << " ";
    }


    return 0;
}
