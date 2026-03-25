#include <iostream>
#include <cstdlib>
#include "p2.h"

namespace {
void list_print_helper(const ListNode *list) {
    if (list == nullptr) {
        return;
    }
    std::cout << list->val << " ";
    list_print_helper(list->next);
}

ListNode *reverse_helper(const ListNode *list, ListNode *new_head) {
    if (list == nullptr) {
        return new_head;
    }
    return reverse_helper(list->next, new ListNode{list->val, new_head});
}

ListNode *copy_list(const ListNode *list) {
    if (list == nullptr) {
        return nullptr;
    }
    return new ListNode{list->val, copy_list(list->next)};
}

bool is_odd(int num) {
    return num % 2 != 0;
}

bool is_even(int num) {
    return num % 2 == 0;
}

ListNode *chop_helper(const ListNode *list, unsigned int keep) {
    if (keep == 0) {
        return nullptr;
    }
    return new ListNode{list->val, chop_helper(list->next, keep - 1)};
}

int find_idx(const int *arr, int val, int curr, int arrlen) {
    if (curr >= arrlen) {
        return -1;
    }
    if (arr[curr] == val) {
        return curr;
    }
    return find_idx(arr, val, curr + 1, arrlen);
}

void tree_print_spaces(int iii) {
    if (iii == 0) {
        return;
    }
    std::cout << " ";
    tree_print_spaces(iii - 1);
}

void tree_print_helper(const TreeNode *tree, int depth) {
    if (tree == nullptr) {
        return;
    }
    tree_print_helper(tree->right, depth + 1);
    tree_print_spaces(depth * 4);
    std::cout << tree->val << "\n";
    tree_print_helper(tree->left, depth + 1);
}

int max_val(int iii, int jjj) {
    return iii > jjj ? iii : jjj;
}

int min_val(int iii, int jjj) {
    return iii < jjj ? iii : jjj;
}

ListNode *traverse_helper(const TreeNode *node, ListNode *acc) {
    if (node == nullptr) {
        return acc;
    }
    acc = traverse_helper(node->right, acc);
    acc = new ListNode{node->val, acc};
    acc = traverse_helper(node->left, acc);
    return acc;
}

TreeNode *copy_tree(const TreeNode *tree) {
    if (tree == nullptr) {
        return nullptr;
    }
    return new TreeNode{tree->val, copy_tree(tree->left), copy_tree(tree->right)};
}
}  // namespace

ListNode *list_construct(const int *arr, int n) {
    if (n == 0) {
        return nullptr;
    }
    return new ListNode{arr[0], list_construct(arr + 1, n - 1)};
}

void list_destroy(ListNode *list) {
    if (list == nullptr) {
        return;
    }
    list_destroy(list->next);
    delete list;
}

void list_print(const ListNode *list) {
    if (list == nullptr) {
        std::cout << "( )\n";
    } else {
        std::cout << "( ";
        list_print_helper(list);
        std::cout << ")\n";
    }
}

int size(const ListNode *list) {
    if (list == nullptr) {
        return 0;
    }
    return 1 + size(list->next);
}

int sum(const ListNode *list) {
    if (list == nullptr) {
        return 0;
    }
    return list->val + sum(list->next);
}

int product(const ListNode *list) {
    if (list == nullptr) {
        return 1;
    }
    return list->val * product(list->next);
}

ListNode *reverse(const ListNode *list) {
    return reverse_helper(list, nullptr);
}

ListNode *append(const ListNode *first, const ListNode *second) {
    if (first == nullptr) {
        return copy_list(second);
    }
    return new ListNode{first->val, append(first->next, second)};
}

ListNode *filter(const ListNode *list, bool (*fn)(int)) {
    if (list == nullptr) {
        return nullptr;
    }
    if (fn(list->val)) {
        return new ListNode{list->val, filter(list->next, fn)};
    }
    return filter(list->next, fn);
}

ListNode *filter_odd(const ListNode *list) {
    return filter(list, is_odd);
}

ListNode *filter_even(const ListNode *list) {
    return filter(list, is_even);
}

ListNode *insert_list(const ListNode *list1, const ListNode *list2, unsigned int n) {
    if (n == 0) {
        return append(list2, list1);
    }
    if (list1 == nullptr) {
        return nullptr;
    }
    return new ListNode{list1->val, insert_list(list1->next, list2, n - 1)};
}

ListNode *chop(const ListNode *list, unsigned int n) {
    const int list_size = size(list);
    if (list_size <= 0 || (unsigned int)list_size <= n) {
        return nullptr;
    }
    return chop_helper(list, (unsigned int)list_size - n);
}

TreeNode *tree_construct(const int *preorder, const int *inorder, int n) {
    if (n == 0) {
        return nullptr;
    }
    const int root_val = preorder[0];
    const int iii = find_idx(inorder, root_val, 0, n);
    const int left_size = iii;
    const int right_size = n - iii - 1;
    TreeNode* left_tree = tree_construct(preorder + 1, inorder, left_size);
    TreeNode* right_tree = tree_construct(preorder + 1 + left_size, inorder + iii + 1, right_size);
    return new TreeNode{root_val, left_tree, right_tree};
}

void tree_destroy(TreeNode *tree) {
    if (tree == nullptr) {
        return;
    }
    tree_destroy(tree->left);
    tree_destroy(tree->right);
    delete tree;
}

void tree_print(const TreeNode *tree) {
    tree_print_helper(tree, 0);
}

int tree_sum(const TreeNode *tree) {
    if (tree == nullptr) {
        return 0;
    }
    return tree->val + tree_sum(tree->left) + tree_sum(tree->right);
}

bool tree_search(const TreeNode *tree, int key) {
    if (tree == nullptr) {
        return false;
    }
    if (tree->val == key) {
        return true;
    }
    return tree_search(tree->left, key) || tree_search(tree->right, key);
}

int depth(const TreeNode *tree) {
    if (tree == nullptr) {
        return 0;
    }
    return 1 + max_val(depth(tree->left), depth(tree->right));
}

int tree_min(const TreeNode *tree) {
    int min_num = tree->val;
    if (tree->left != nullptr) {
        min_num = min_val(min_num, tree_min(tree->left));
    }
    if (tree->right != nullptr) {
        min_num = min_val(min_num, tree_min(tree->right));
    }
    return min_num;
}

ListNode *traversal(const TreeNode *tree) {
    return traverse_helper(tree, nullptr);
}

bool tree_hasPathSum(const TreeNode *tree, int target) {
    if (tree == nullptr) {
        return false;
    }
    if (tree->left == nullptr && tree->right == nullptr) {
        return target == tree->val;
    }
    return tree_hasPathSum(tree->left, target - tree->val) ||
    tree_hasPathSum(tree->right, target - tree->val);
}

bool covered_by(const TreeNode *tree_A, const TreeNode *tree_B) {
    if (tree_A == nullptr) {
        return true;
    }
    if (tree_B == nullptr) {
        return false;
    }
    if (tree_A->val != tree_B->val) {
        return false;
    }
    return covered_by(tree_A->left, tree_B->left) && covered_by(tree_A->right, tree_B->right);
}

bool contained_by(const TreeNode *tree_A, const TreeNode *tree_B) {
    if (covered_by(tree_A, tree_B)) {
        return true;
    }
    if (tree_B == nullptr) {
        return false;
    }
    return contained_by(tree_A, tree_B->left) || contained_by(tree_A, tree_B->right);
}

TreeNode *insert_tree(int elt, const TreeNode *tree) {
    if (tree == nullptr) {
        return new TreeNode{elt, nullptr, nullptr};
    }
    if (elt < tree->val) {
        return new TreeNode{tree->val, insert_tree(elt, tree->left), copy_tree(tree->right)};
    }
    return new TreeNode{tree->val, copy_tree(tree->left), insert_tree(elt, tree->right)};
}
