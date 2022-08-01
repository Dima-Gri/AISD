#include "iostream"
#include <ctime>
#include <random>

struct Node {
    int y, x, size = 1;
    long long sum;
    Node *right = nullptr, *left = nullptr;

    Node(int x) : y(rand()), x(x), sum(x) {};
};

class Treap {

public:
    Node *root = nullptr;

    static int get_size(Node *A) {
        return (A) ? A->size : 0;
    }

    static long long get_sum(Node *t) {
        return t ? t->sum : 0;
    }

    static void update_size(Node *A) {
        if (A) {
            A->size = get_size(A->right) + get_size(A->left) + 1;
        }
    }

    static void update_sum(Node *A) {
        if (A) {
            A->sum = get_sum(A->left) + get_sum(A->right) + A->x;
        }
    }

    static Node *merge(Node *A, Node *B) {
        if (!A) return B;
        if (!B) return A;
        if (A->y >= B->y) {
            A->right = merge(A->right, B);
            update_size(A);
            update_sum(A);
            return A;
        } else {
            B->left = merge(A, B->left);
            update_size(B);
            update_sum(B);
            return B;
        }
    }

    static void split(Node *A, int k, Node *&left, Node *&right) {
        if (!A) {
            left = nullptr;
            right = nullptr;
            return;
        }
        if (get_size(A->left) < k) {
            split(A->right, k - get_size(A->left) - 1, A->right, right);
            left = A;
        } else {
            split(A->left, k, left, A->left);
            right = A;
        }
        update_size(left);
        update_size(right);
        update_sum(left);
        update_sum(right);
    }

    void pushBack(int value) {
        root = merge(root, new Node(value));
    }

    static void Swap(Treap *T1, Treap *T2, int left, int right) {
        int left1 = (left + 1) / 2, right1 = right / 2;
        int left2 = left / 2, right2 = (right + 1) / 2 - 1;
        Node *A1, *B1, *C1, *A2, *B2, *C2;

        Treap::split(T1->root, left1, A1, B1);
        Treap::split(B1, right1 - left1 + 1, B1, C1); // T1 = (A1, B1, C1)

        Treap::split(T2->root, left2, A2, B2);
        Treap::split(B2, right2 - left2 + 1, B2, C2); // T2 = (A2, B2, C2)

        T1->root = Treap::merge(Treap::merge(A1, B2), C1);
        Treap::update_sum(T1->root);
        T2->root = Treap::merge(Treap::merge(A2, B1), C2);
        Treap::update_sum(T2->root);

    }

    static long long Sum(Treap *T1, Treap *T2, int left, int right) {
        if (left > right) return 0;
        int left1 = (left + 1) / 2, right1 = right / 2;

        int left2 = left / 2, right2 = (right + 1) / 2 - 1;
        Node *A1, *B1, *C1, *A2, *B2, *C2;
        Treap::split(T1->root, left1, A1, B1);
        Treap::split(B1, right1 - left1 + 1, B1, C1); // T1 = (A1, B1, C1)
        Treap::split(T2->root, left2, A2, B2);
        Treap::split(B2, right2 - left2 + 1, B2, C2); // T2 = (A2, B2, C2)
        long long res = Treap::get_sum(B1) + Treap::get_sum(B2);
        T1->root = Treap::merge(Treap::merge(A1, B1), C1);
        T2->root = Treap::merge(Treap::merge(A2, B2), C2);

        return res;
    }

};


int main() {
    srand(time(NULL));
    int n, m, index = 1;
    while (true) {
        std::cin >> n >> m;
        if (n == 0 && m == 0) {
            return 0;
        }
        Treap T1, T2;
        std::cout << "Swapper " << index << ":" << std::endl;
        for (int i = 1; i <= n; i++) {
            int val;
            std::cin >> val;
            if (i % 2 == 1) {
                T1.pushBack(val);
            } else {
                T2.pushBack(val);
            }
        }

        for (int i = 0; i < m; i++) {
            int a, b, type;
            std::cin >> type >> a >> b;
            if (type == 1) {
                Treap::Swap(&T1, &T2, a - 1, b - 1);

            } else {
                std::cout << Treap::Sum(&T1, &T2, a - 1, b - 1) << std::endl;
            }
        }
        ++index;
        std::cout << std::endl;
    }
    return 0;
}
