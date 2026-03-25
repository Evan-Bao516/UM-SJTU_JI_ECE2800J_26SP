#ifndef P2_H
#define P2_H

// Part 1: Linked Lists
struct ListNode {
    int val = 0;
    ListNode *next = nullptr;
};

ListNode *list_construct(const int *arr, int n);
// Requires: arr points to an array of at least n integers. n >= 0.
/* Effects: Allocates and returns a new linked list containing arr[0], arr[1], ..., arr[n-1] in that
order. Returns nullptr if n == 0. */

void list_destroy(ListNode *list);
// Effects: Recursively deallocates every node reachable from list. Does nothing if list is nullptr.

void list_print(const ListNode *list);
/* Effects: Prints list to cout as ( v1 v2 ... vn ) followed by a newline. Prints ( ) followed by a
newline if list is nullptr. */
// Example: A list ( 1 2 3 ) produces the output: 1 | ( 1 2 3 )

int size(const ListNode *list);
// Effects: Returns the number of elements in list. Returns 0 if list is nullptr.

int sum(const ListNode *list);
// Effects: Returns the sum of all elements in list. Returns 0 if list is nullptr.

int product(const ListNode *list);
// Effects: Returns the product of all elements in list. Returns 1 if list is nullptr.

ListNode *reverse(const ListNode *list);
// Effects: Allocates and returns a new list that is the reverse of list. The original list is not modified.

ListNode *append(const ListNode *first, const ListNode *second);
/* Effects: Allocates and returns a new list consisting of all elements of first followed by all elements
of second. Neither first nor second is modified. */
// Example: append(( 2 4 6 ), ( 1 3 )) returns a new list ( 2 4 6 1 3 ).

ListNode *filter_odd(const ListNode *list);
/* Effects: Allocates and returns a new list containing only the elements of list that are odd, in their
original order. The original list is not modified. */
// Example: filter_odd(( 3 4 1 5 6 )) returns a new list ( 3 1 5 ).

ListNode *filter_even(const ListNode *list);
/* Effects: Allocates and returns a new list containing only the elements of list that are even, in their
original order. The original list is not modified. */

ListNode *filter(const ListNode *list, bool (*fn)(int));
/* Effects: Allocates and returns a new list containing precisely the elements of list for which
fn(element) returns true , in their original order. The original list is not modified. */
// Example: If fn returns true for odd integers, filter(list, fn) produces the same result as filter_odd(list).

ListNode *insert_list(const ListNode *list1, const ListNode *list2, unsigned int n);
// Requires: n <= size(first).
/* Effects: Allocates and returns a new list consisting of:
1. The first n elements of first,
2. followed by all elements of second,
3. followed by the elements of first starting at position n (0-indexed).
Neither first nor second is modified. */
// Example: insert_list(( 1 2 3 ), ( 4 5 6 ), 2) returns ( 1 2 4 5 6 3 ).

ListNode *chop(const ListNode *list, unsigned int n);
// Requires: size(list) >= n.
/* Effects: Allocates and returns a new list equal to list with its last n elements removed. The original
list is not modified. */
// Example: chop(( 1 2 3 4 5 ), 2) returns ( 1 2 3 ).

// Part 2: Binary Trees
struct TreeNode {
    int val = 0;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
};

TreeNode *tree_construct(const int *preorder, const int *inorder, int n);
/* Requires:
1. preorder and inorder are arrays of length n containing the same n distinct integers.
2. preorder gives the preorder traversal (root, left subtree, right subtree) of a binary tree.
3. inorder gives the inorder traversal (left subtree, root, right subtree) of the same tree.
4. n >= 0. */
/* Effects: Allocates and returns the unique binary tree whose preorder and inorder traversals match
the given arrays. Returns nullptr if n == 0. */
/* Example: Given preorder = [4, 2, 3, 5] and inorder = [2, 3, 4, 5], tree_construct builds:
1 |  4
2 | / \
3 | 2 5
4 | \
5 |  3
*/

void tree_destroy(TreeNode *tree);
// Effects: Recursively deallocates every node reachable from tree . Does nothing if tree is nullptr.

void tree_print(const TreeNode *tree);
/* Effects: Prints the tree to cout in a rotated in-order layout:
1. Traverse in the order: right subtree, root, left subtree.
2. Each node is printed on its own line, indented by 4 * depth spaces (the root is at depth 0, its
children at depth 1, and so on).
3. Each line contains only the spaces and the integer value, followed by a newline.
4. Prints nothing if tree is nullptr. */
/* Example: For the tree:
1 |  4
2 | / \
3 | 2 5
4 | \
5 |  3
tree_print produces:
1 |    5
2 |4
3 |        3
4 |    2
Explanation: 5 is at depth 1 (4 spaces), 4 is at depth 0 (0 spaces), 3 is at depth 2 (8 spaces), 2 is at
depth 1 (4 spaces). Reading top-to-bottom gives the reverse in-order sequence 5 4 3 2. */

int tree_sum(const TreeNode *tree);
// Effects: Returns the sum of all node values in tree . Returns 0 if tree is nullptr.

bool tree_search(const TreeNode *tree, int key);
/* Effects: Returns true if any node in tree holds value key ; returns false otherwise. Returns
false if tree is nullptr. */

int depth(const TreeNode *tree);
/* Effects: Returns the number of nodes on the longest path from the root to any leaf. Returns 0 if
tree is nullptr. A single-node tree has depth 1. */
/* Example:
1 |  4
2 | / \
3 | 2 5
4 | \
5 |  3
6 |  /
7 | 6
This tree has depth 4. */

int tree_min(const TreeNode *tree);
// Requires: tree != nullptr.
// Effects: Returns the minimum value among all nodes in tree.

ListNode *traversal(const TreeNode *tree);
/* Effects: Allocates and returns a new list containing the node values of tree in inorder (left subtree
-> root -> right subtree). Returns nullptr if tree is nullptr. */
/* Example: For the tree:
1 |  4
2 | / \
3 | 2 5
4 | \
5 |  3
traversal returns ( 2 3 4 5 ). */

bool tree_hasPathSum(const TreeNode *tree, int target);
/* Effects: Returns true if and only if tree contains at least one root-to-leaf path whose node values
sum to target . Returns false if tree is nullptr. */
/* Definition: A root-to-leaf path is a sequence of nodes beginning at the root and ending at a leaf (a
node whose both children are nullptr). */
/* Example:
1 |   4
2 |  / \
3 |  1 5
4 | / \
5 | 3 6
The three root-to-leaf paths and their sums are: 4->1->3 = 8, 4->1->6 = 11, 4->5 = 9.
tree_hasPathSum(tree, 9) returns true ; tree_hasPathSum(tree, 10) returns false. */

bool covered_by(const TreeNode *tree_A, const TreeNode *tree_B);
// Effects: Returns true if tree A is covered by tree B according to the definition above; false otherwise.

bool contained_by(const TreeNode *tree_A, const TreeNode *tree_B);
// Effects: Returns true if tree A is covered by tree B or by any subtree of B; false otherwise.

TreeNode *insert_tree(int elt, const TreeNode *tree);
// Requires: tree is a valid sorted binary tree.
/* Effects: Allocates and returns a new sorted binary tree identical to tree with elt inserted at the
unique leaf position that maintains the sorted property. The original tree is not modified. */
/* Example: Inserting 1 into:
1 |  4
2 | / \
3 | 2 5
4 | \
5 |  3
yields:
1 |   4
2 |  / \
3 |  2 5
4 | / \
5 | 1 3
*/

#endif  // P2_H
