#include <iostream>
#include <vector>

// Дерево отрезков на обновление и сумму на отрезке

class SegmentTree {
public:
    std::vector<long long> tree;

    long long left_child(long long v) {
        return 2 * v;
    }

    long long right_child(long long v) {
        return 2 * v + 1;
    }

    void build(const std::vector<long long> &vec, long long v, long long tl, long long tr) {
        if (tl == tr) {
            tree[v] = vec[tl];
        } else {
            long long m = (tl + tr) / 2;
            build(vec, left_child(v), tl, m);
            build(vec, right_child(v), m + 1, tr);
            tree[v] = tree[left_child(v)] + tree[right_child(v)];
        }
    }

    long long sum(long long v, long long tl, long long tr, long long ql, long long qr) {
        if (tl > qr || tr < ql)
            return 0;
        if (ql == tl && qr == tr)
            return tree[v];
        long long m = (tl + tr) / 2;
        return sum(left_child(v), tl, m, ql, std::min(qr, m)) + sum(right_child(v), m + 1, tr, std::max(ql, m + 1), qr);
    }

    void upd(long long v, long long tl, long long tr, long long pos, long long n_v) {
        if (tl == tr)
            tree[v] = n_v;
        else {
            long long m = (tl + tr) / 2;
            if (pos <= m) {
                upd(left_child(v), tl, m, pos, n_v);
            } else {
                upd(right_child(v), m + 1, tr, pos, n_v);
            }
            tree[v] = tree[left_child(v)] + tree[right_child(v)];
        }
    }
};


int main() {
    long long N, Q;
    std::cin >> N;
    std::vector<long long> vec;

    SegmentTree tree;
    tree.tree.resize(4 * N);

    for (long long i = 0; i < N; i++) {
        long long a;
        std::cin >> a;
        vec.push_back(a);
    }

    tree.build(vec, 1ll, 0, N - 1);

    std::cin >> Q;
    for (long long i = 0; i < Q; i++) {
        long long id, L, R;
        std::cin >> id >> L >> R;
        if (id == 1) {
            std::cout << tree.sum(1, 0, N - 1, L, R) << std::endl;
        } else {
            tree.upd(1, 0, N - 1, L, R);
        }
    }
    return 0;
}
