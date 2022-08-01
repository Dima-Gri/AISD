#include <iostream>
#include <vector>

// сумма и прибавление на отрезке
long long N, Q;

struct Node {
    long long sum, add = 0;
};

class SegmentTree {
public:
    std::vector<Node> tree;

    long long left_child(long long v) {
        return 2 * v;
    }

    long long right_child(long long v) {
        return 2 * v + 1;
    }

    void build(const std::vector<long long> &vec, long long v, long long tl, long long tr) {
        if (tl == tr) {
            tree[v].sum = vec[tl];
        } else {
            long long m = (tl + tr) / 2;
            build(vec, left_child(v), tl, m);
            build(vec, right_child(v), m + 1, tr);
            tree[v].sum = tree[left_child(v)].sum + tree[right_child(v)].sum;
        }
    }

    void push(long long v, long long tl, long long tr) {
        if (tree[v].add) {
            tree[v].sum += tree[v].add * (tr - tl + 1);
            tree[left_child(v)].add += tree[v].add;
            tree[right_child(v)].add += tree[v].add;
            tree[v].add = 0;
        }
    }


    long long sum(long long v, long long tl, long long tr, long long ql, long long qr) {
        if (tl > qr || tr < ql)
            return 0;
        push(v, tl, tr);
        if (ql == tl && qr == tr)
            return tree[v].sum;
        long long m = (tl + tr) / 2;
        return sum(left_child(v), tl, m, ql, std::min(qr, m)) + sum(right_child(v), m + 1, tr, std::max(ql, m + 1), qr);
    }


    void update(long long v, long long tl, long long tr, long long ql, long long qr, long long x) {
        if (tl > qr || tr < ql)
            return;
        if (ql == tl && tr == qr){
            tree[v].add += x;
        }else {
            long long size = std::min(tr, qr) - std::max(tl, ql) + 1;
            tree[v].sum += size * x;
            long long m = (tl + tr) / 2;
            update(left_child(v), tl, m, ql, std::min(qr, m), x);
            update(right_child(v), m + 1, tr, std::max(ql, m + 1), qr, x);
        }
    }
};


int main() {
    std::cin >> N;
    std::vector<long long> vec;

    SegmentTree tree;
    tree.tree.resize(8 * N);

    for (long long i = 0; i < N; i++) {
        long long a;
        std::cin >> a;
        vec.push_back(a);
    }

    tree.build(vec, 1ll, 0, N - 1);

    std::cin >> Q;
    for (long long i = 0; i < Q; i++) {
        long long id, L, R, x;
        std::cin >> id;
        if (id == 1) {
            std::cin >> L >> R;
            std::cout << tree.sum(1, 0, N - 1, L, R) << std::endl;
        } else {
            std::cin >> L >> R >> x;
            tree.update(1, 0, N - 1, L, R, x);
        }
    }
    return 0;
}
