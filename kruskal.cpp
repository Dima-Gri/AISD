#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

const int N = 1e6;
std::vector<int> parent(N, -1);

void make_set(int x) {
    parent[x] = x;
}

int find_set(int x) {
    if (x == parent[x]) {
        return x;
    } else {
        return parent[x] = find_set(parent[x]);
    }
}

int union_sets(int x, int y) {
    int x_root = find_set(x);
    int y_root = find_set(y);
    if (rand() % 2 == 0) {
        std::swap(x_root, y_root);
    }
    parent[y_root] = x_root;
    return x_root;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::tuple<int, int, int>> edges;
    std::vector<std::vector<int>> weight(n + 1, std::vector<int>(n + 1));
    for (; m > 0; --m) {
        int a, b, w;
        std::cin >> a >> b >> w;
        edges.push_back({w, a, b});
        weight[a][b] = w;
    }
    std::sort(edges.begin(), edges.end());

    for (int i = 1; i <= n; ++i) {
        make_set(i);
    }
    int count = 0;
    std::vector<std::pair<int, int>> result;
    for (auto[w, a, b]: edges) {
        if (find_set(a) != find_set(b)) {
            count += weight[a][b];
            union_sets(a, b);
        }
    }
    std::cout << count;
    return 0;
}

