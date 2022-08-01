#include <iostream>
#include <vector>
#include <set>
#include "cmath"
#include "algorithm"

struct node {
    int value, height, frequency;
    node *left, *right, *parent;

    node(int v) {
        value = v;
        left = nullptr;
        right = nullptr;
        height = 1;
        frequency = 1;
    }
};

struct tree {
    node *root = nullptr;
    int height = 1;
    std::set<int> lists;
    std::set<int> forks;
    std::set<int> branches;
    bool AVL = true;

    void insert(node *n, int v) {
        if (n->value < v) {
            if (n->right != nullptr) {
                insert(n->right, v);
            } else {
                node *n_new = new node(v);
                n->right = n_new;
                n->right->height = n->height + 1;
                height = std::max(height, n->right->height);
                n_new->parent = n;
            }
        } else if (n->value > v) {
            if (n->left != nullptr) {
                insert(n->left, v);
            } else {
                node *n_new = new node(v);
                n->left = n_new;
                n->left->height = n->height + 1;
                height = std::max(height, n->left->height);
                n_new->parent = n;
            }
        } else {
            ++n->frequency;
        }
    }

    int find_second_max() {
        node cur = *root;
        while (cur.right != nullptr) {
            cur = *cur.right;
        }
        if (cur.left != nullptr) {
            cur = *cur.left;
            while (cur.right != nullptr) {
                cur = *cur.right;
            }
        } else {
            cur = *cur.parent;
        }
        return cur.value;
    }

    void print_tree(node *n = nullptr) {
        if (n == nullptr) {
            n = root;
        }
        bool flag = false;
        if (n->left == nullptr) {
            std::cout << n->value << " " << n->frequency << std::endl;
            flag = true;
        } else {
            print_tree(n->left);
        }
        if (!flag) {
            std::cout << n->value << " " << n->frequency << std::endl;
        }
        if (n->right == nullptr) {
        } else {
            print_tree(n->right);
        }
    }

    void get_list(node *n = nullptr) {
        if (n == nullptr) {
            n = root;
        }
        if (n->right == nullptr && n->left == nullptr) {
            lists.insert(n->value);
            return;
        }
        if (n->left) {
            get_list(n->left);
        }
        if (n->right) {
            get_list(n->right);
        }
    }

    void get_fork(node *n = nullptr) {
        if (n == nullptr) {
            n = root;
        }
        if (n->right != nullptr && n->left != nullptr) {
            forks.insert(n->value);
        }
        if (n->left) {
            get_fork(n->left);
        }
        if (n->right) {
            get_fork(n->right);
        }
    }

    void get_branch(node *n = nullptr) {
        if (n == nullptr) {
            n = root;
        }
        if (n->right != nullptr && n->left == nullptr || n->right == nullptr && n->left != nullptr) {
            branches.insert(n->value);
        }
        if (n->left) {
            get_branch(n->left);
        }
        if (n->right) {
            get_branch(n->right);
        }
    }

    void set_height(node *n = nullptr) {
        if (n == nullptr) {
            n = root;
        }
        if (n->left == nullptr && n->right == nullptr) {
            n->height = 1;
        } else if (n->right != nullptr && n->left == nullptr || n->right == nullptr && n->left != nullptr) {
            if (n->right != nullptr && n->left == nullptr) {
                set_height(n->right);
                n->height = n->right->height + 1;
            } else {
                set_height(n->left);
                n->height = n->left->height + 1;
            }
        } else {
            set_height(n->left);
            set_height(n->right);
            n->height = std::max(n->left->height + 1, n->right->height + 1);
        }
    }

    void AVL_check(node *n = nullptr) {
        if (n == nullptr) {
            n = root;
        }
        if (n->left == nullptr && n->right == nullptr) {
            return;
        } else if (n->right != nullptr && n->left == nullptr || n->right == nullptr && n->left != nullptr) {
            if (n->right != nullptr && n->left == nullptr) {
                if (n->right->height > 1) {
                    AVL = false;
                    return;
                }
                AVL_check(n->right);

            } else {
                if (n->left->height > 1) {
                    AVL = false;
                    return;
                }
                AVL_check(n->left);

            }
        } else {
            if (std::max(n->left->height, n->right->height) - std::min(n->left->height, n->right->height) > 1) {
                AVL = false;
                return;
            }
            AVL_check(n->left);
            AVL_check(n->right);
        }

    }
};

int main() {
    tree new_tree;
    int a;
    std::cin >> a;
    node on = node(a);
    new_tree.root = &on;
    while (a != 0) {
        std::cin >> a;
        if (a != 0) {
            new_tree.insert(new_tree.root, a);
        }

    }
    new_tree.print_tree();

    return 0;
}

