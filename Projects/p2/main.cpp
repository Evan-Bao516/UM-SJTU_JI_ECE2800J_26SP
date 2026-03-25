#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "p2.h"

namespace {
bool is_odd(int num) {
    return num % 2 != 0;
}

bool is_even(int num) {
    return num % 2 == 0;
}

void set_list(std::map<std::string, ListNode*>& lists,
              const std::string& name, ListNode* newList) {
    if (lists.count(name) != 0) {
        list_destroy(lists[name]);
    }
    lists[name] = newList;
}

void set_tree(std::map<std::string, TreeNode*>& trees,
              const std::string& name, TreeNode* newTree) {
    if (trees.count(name) != 0) {
        tree_destroy(trees[name]);
    }
    trees[name] = newTree;
}

void handle_list_command(const std::string& cmd,
                         std::map<std::string, ListNode*>& lists) {
    if (cmd == "LIST_NEW") {
        std::string name;
        int nnn = 0;
        std::cin >> name >> nnn;
        nnn = std::max(nnn, 0);
        std::vector<int> arr(static_cast<size_t>(nnn));
        for (size_t i = 0; i < static_cast<size_t>(nnn); ++i) {
            std::cin >> arr.at(i);
        }
        set_list(lists, name, list_construct(arr.data(), nnn));
    } else if (cmd == "LIST_DEL") {
        std::string name;
        std::cin >> name;
        if (lists.count(name) != 0) {
            list_destroy(lists[name]);
            lists.erase(name);
        }
    } else if (cmd == "LIST_PRINT") {
        std::string name;
        std::cin >> name;
        list_print(lists[name]);
    } else if (cmd == "LIST_SIZE") {
        std::string name;
        std::cin >> name;
        std::cout << size(lists[name]) << "\n";
    } else if (cmd == "LIST_SUM") {
        std::string name;
        std::cin >> name;
        std::cout << sum(lists[name]) << "\n";
    } else if (cmd == "LIST_PRODUCT") {
        std::string name;
        std::cin >> name;
        std::cout << product(lists[name]) << "\n";
    } else if (cmd == "LIST_REVERSE") {
        std::string dst;
        std::string src;
        std::cin >> dst >> src;
        set_list(lists, dst, reverse(lists[src]));
    } else if (cmd == "LIST_APPEND") {
        std::string dst;
        std::string src1;
        std::string src2;
        std::cin >> dst >> src1 >> src2;
        set_list(lists, dst, append(lists[src1], lists[src2]));
    } else if (cmd == "LIST_FILTER_ODD") {
        std::string dst;
        std::string src;
        std::cin >> dst >> src;
        set_list(lists, dst, filter_odd(lists[src]));
    } else if (cmd == "LIST_FILTER_EVEN") {
        std::string dst;
        std::string src;
        std::cin >> dst >> src;
        set_list(lists, dst, filter_even(lists[src]));
    } else if (cmd == "LIST_FILTER") {
        std::string dst;
        std::string src;
        std::string pred;
        std::cin >> dst >> src >> pred;
        if (pred == "ODD") {
            set_list(lists, dst, filter(lists[src], is_odd));
        } else {
            set_list(lists, dst, filter(lists[src], is_even));
        }
    } else if (cmd == "LIST_INSERT") {
        std::string dst;
        std::string src1;
        std::string src2;
        unsigned int nnn = 0;
        std::cin >> dst >> src1 >> src2 >> nnn;
        set_list(lists, dst, insert_list(lists[src1], lists[src2], nnn));
    } else if (cmd == "LIST_CHOP") {
        std::string dst;
        std::string src;
        unsigned int nnn = 0;
        std::cin >> dst >> src >> nnn;
        set_list(lists, dst, chop(lists[src], nnn));
    }
}

bool handle_tree_modify(const std::string& cmd, std::map<std::string, TreeNode*>& trees) {
    if (cmd == "TREE_NEW") {
        std::string name;
        int nnn = 0;
        std::cin >> name >> nnn;
        nnn = std::max(nnn, 0);
        std::vector<int> input_pre(static_cast<size_t>(nnn));
        std::vector<int> input_in(static_cast<size_t>(nnn));
        for (size_t i = 0; i < static_cast<size_t>(nnn); ++i) {
            std::cin >> input_pre.at(i);
        }
        for (size_t i = 0; i < static_cast<size_t>(nnn); ++i) {
            std::cin >> input_in.at(i);
        }
        set_tree(trees, name, tree_construct(input_pre.data(), input_in.data(), nnn));
        return true;
    }
    if (cmd == "TREE_DEL") {
        std::string name;
        std::cin >> name;
        if (trees.count(name) != 0) {
            tree_destroy(trees[name]);
            trees.erase(name);
        }
        return true;
    }
    if (cmd == "TREE_INSERT") {
        std::string dst;
        std::string src;
        int elt = 0;
        std::cin >> dst >> src >> elt;
        set_tree(trees, dst, insert_tree(elt, trees[src]));
        return true;
    }
    return false;
}

void handle_tree_command(const std::string& cmd, std::map<std::string,
                         TreeNode*>& trees, std::map<std::string, ListNode*>& lists) {
    if (handle_tree_modify(cmd, trees)) {
        return;
    }
    if (cmd == "TREE_PRINT") {
        std::string name;
        std::cin >> name;
        tree_print(trees[name]);
    } else if (cmd == "TREE_SUM") {
        std::string name;
        std::cin >> name;
        std::cout << tree_sum(trees[name]) << "\n";
    } else if (cmd == "TREE_SEARCH") {
        std::string name;
        int key = 0;
        std::cin >> name >> key;
        std::cout << (tree_search(trees[name], key) ? "true" : "false") << "\n";
    } else if (cmd == "TREE_DEPTH") {
        std::string name;
        std::cin >> name;
        std::cout << depth(trees[name]) << "\n";
    } else if (cmd == "TREE_MIN") {
        std::string name;
        std::cin >> name;
        std::cout << tree_min(trees[name]) << "\n";
    } else if (cmd == "TREE_TRAVERSAL") {
        std::string dst;
        std::string src;
        std::cin >> dst >> src;
        set_list(lists, dst, traversal(trees[src]));
    } else if (cmd == "TREE_PATHSUM") {
        std::string name;
        int target = 0;
        std::cin >> name >> target;
        std::cout << (tree_hasPathSum(trees[name], target) ? "true" : "false") << "\n";
    } else if (cmd == "TREE_COVERED") {
        std::string nameA;
        std::string nameB;
        std::cin >> nameA >> nameB;
        std::cout << (covered_by(trees[nameA], trees[nameB]) ? "true" : "false") << "\n";
    } else if (cmd == "TREE_CONTAINED") {
        std::string nameA;
        std::string nameB;
        std::cin >> nameA >> nameB;
        std::cout << (contained_by(trees[nameA], trees[nameB]) ? "true" : "false") << "\n";
    }
}
}  // namespace

int main() {
    try {
        std::map<std::string, ListNode*> lists;
        std::map<std::string, TreeNode*> trees;
        std::string cmd;
        while (std::cin >> cmd) {
            if (cmd.find("LIST") == 0) {
                handle_list_command(cmd, lists);
            } else if (cmd.find("TREE") == 0) {
                handle_tree_command(cmd, trees, lists);
            }
        }
        for (const auto& pair : lists) {
            list_destroy(pair.second);
        }
        for (const auto& pair : trees) {
            tree_destroy(pair.second);
        }
    }
    catch(...) {
        return 1;
    }

    return 0;
}
