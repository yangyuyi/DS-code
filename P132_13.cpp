#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<class T>
class TreeNode {
private:
    T value;
    TreeNode<T> *left_child;
    TreeNode<T> *right_child;
public:
    TreeNode();

    explicit TreeNode(T val);

    T val();

    TreeNode<T> *left();

    TreeNode<T> *right();

    void setLeft(TreeNode<T> *left);

    void setRight(TreeNode<T> *right);
};

template<class T>
TreeNode<T>::TreeNode() {
    left_child = NULL;
    right_child = NULL;
}

template<class T>
TreeNode<T>::TreeNode(T val) {
    value = val;
    left_child = NULL;
    right_child = NULL;
}

template<class T>
T TreeNode<T>::val() {
    return value;
}

template<class T>
TreeNode<T> *TreeNode<T>::left() {
    return left_child;
}

template<class T>
TreeNode<T> *TreeNode<T>::right() {
    return right_child;
}

template<class T>
void TreeNode<T>::setLeft(TreeNode<T> *left) {
    left_child = left;
}

template<class T>
void TreeNode<T>::setRight(TreeNode<T> *right) {
    right_child = right;
}

template<class T>
class BinarySearchTree {
private:
    TreeNode<T> *root;
public:
    BinarySearchTree();

    explicit BinarySearchTree(vector<T> src);

    ~BinarySearchTree();

    TreeNode<T> *getRoot();

    TreeNode<T> *CreateTree(vector<T> src);

    void DeleteTree(TreeNode<T> *r);

    void insert(TreeNode<T> *&r, T val);

    void PreOrder(TreeNode<T> *r);

    void InOrder(TreeNode<T> *r);

    void PostOrder(TreeNode<T> *r);
};

template<class T>
BinarySearchTree<T>::BinarySearchTree() {
    root = NULL;
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(vector<T> src) {
    root = NULL;
    root = CreateTree(src);
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
    DeleteTree(root);
}

template<class T>
TreeNode<T> *BinarySearchTree<T>::getRoot() {
    return root;
}

template<class T>
TreeNode<T> *BinarySearchTree<T>::CreateTree(vector<T> src) {
    for (int i = 0; i < src.size(); i++) insert(root, src[i]);
    return root;
}

template<class T>
void BinarySearchTree<T>::DeleteTree(TreeNode<T> *r) {
    if (r != NULL) {
        DeleteTree(r->left());
        DeleteTree(r->right());
        delete r;
    }
}

template<class T>
void BinarySearchTree<T>::insert(TreeNode<T> *&r, T val) {
    TreeNode<T> *p;
    TreeNode<T> *node;
    node = new TreeNode<T>(val);
    if (r == NULL) {
        r = node;
        return;
    } else p = r;
    while (p != NULL) {
        if (p->val() == val) return;
        if (p->val() > val) {
            if (p->left() == NULL) {
                p->setLeft(node);
                return;
            } else p = p->left();
        } else {
            if (p->right() == NULL) {
                p->setRight(node);
                return;
            } else p = p->right();
        }
    }
}

template<class T>
void BinarySearchTree<T>::PreOrder(TreeNode<T> *r) {
    if (r == NULL) return;
    cout << r->val() << ' ';
    PreOrder(r->left());
    PreOrder(r->right());
}

template<class T>
void BinarySearchTree<T>::InOrder(TreeNode<T> *r) {
    if (r == NULL) return;
    InOrder(r->left());
    cout << r->val() << ' ';
    InOrder(r->right());
}

template<class T>
void BinarySearchTree<T>::PostOrder(TreeNode<T> *r) {
    if (r == NULL) return;
    PostOrder(r->left());
    PostOrder(r->right());
    cout << r->val() << ' ';
}

int main() {
    vector<string> data = {"wxw", "wxz", "wzw", "wzy", "wzz", "yyw", "yyx", "zww", "zwx", "zwy", "zyw", "zyx", "zyy",
                           "zyz"};
    BinarySearchTree<string> *BST;
    BST = new BinarySearchTree<string>(data);
    cout << "PreOrder:";
    BST->PreOrder(BST->getRoot());
    cout << endl;
    cout << "InOrder:";
    BST->InOrder(BST->getRoot());
    cout << endl;
    cout << "PostOrder:";
    BST->PostOrder(BST->getRoot());
    cout << endl;
    return 0;
}
