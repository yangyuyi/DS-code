#include <iostream>
#include <string>
#include <stack>

#define LEFT 1
#define RIGHT 0

using namespace std;

template<class T>
class TreeNode {
public:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;

    TreeNode();

    explicit TreeNode(T data, TreeNode<T> *left = NULL, TreeNode<T> *right = NULL);
};

template<class T>
TreeNode<T>::TreeNode(T data, TreeNode<T> *left, TreeNode<T> *right) {
    this->data = data;
    this->left = left;
    this->right = right;
}

template<class T>
TreeNode<T>::TreeNode() {
    this->left = NULL;
    this->right = NULL;
}

template<class T>
class ExpBTR {
private:
    TreeNode<T> *root;

    bool PrintBracket(TreeNode<T> *node, int LeftOrRight);

public:
    ExpBTR();

    ~ExpBTR();

    TreeNode<T> *getRoot();

    void Display(TreeNode<T> *parent, TreeNode<T> *r, string prefix);

    void InCreate(string InExp);

    void PreCreate(string PreExp);

    void PostCreate(string PostExp);

    void PreOrder(TreeNode<T> *r);

    void InOrder(TreeNode<T> *r);

    void PostOrder(TreeNode<T> *r);

    void Delete(TreeNode<T> *r);
};

template<class T>
ExpBTR<T>::ExpBTR() {
    root = NULL;
}

template<class T>
ExpBTR<T>::~ExpBTR() {
    Delete(root);
}

template<class T>
void ExpBTR<T>::Delete(TreeNode<T> *r) {
    if (r) {
        Delete(r->left);
        Delete(r->right);
        delete r;
    }
}

template<class T>
void ExpBTR<T>::PreOrder(TreeNode<T> *r) {
    if (r) {
        cout << r->data << ' ';
        PreOrder(r->left);
        PreOrder(r->right);
    }
}

template<class T>
void ExpBTR<T>::InOrder(TreeNode<T> *r) {
    if (r) {
        if (PrintBracket(r, LEFT)) {
            cout << '(' << ' ';
            InOrder(r->left);
            cout << ')' << ' ';
        } else InOrder(r->left);
        cout << r->data << ' ';
        if (PrintBracket(r, RIGHT)) {
            cout << '(' << ' ';
            InOrder(r->right);
            cout << ')' << ' ';
        } else InOrder(r->right);
    }
}

template<class T>
void ExpBTR<T>::PostOrder(TreeNode<T> *r) {
    if (r) {
        PostOrder(r->left);
        PostOrder(r->right);
        cout << r->data << ' ';
    }
}

template<class T>
void ExpBTR<T>::InCreate(string InExp) {
    string exp;
    stack<double> operands;
    stack<char> operators;
    int i = 0;
    while (i < InExp.length()) {
        char ch = InExp[i++];
        if (ch == '+' || ch == '-') {
            while (!operators.empty() && (operators.top() != '(')) {
                exp += operators.top();
                exp += ' ';
                operators.pop();
            }
            operators.push(ch);
        } else if (ch == '*' || ch == '/') {
            while (!operators.empty() && (operators.top() != '(') && (operators.top() != '+') &&
                   (operators.top() != '-')) {
                exp += operators.top();
                exp += ' ';
                operators.pop();
            }
            operators.push(ch);
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            bool err = true;
            while (!operators.empty()) {
                char op = operators.top();
                operators.pop();
                if (op == '(') {
                    err = false;
                    break;
                }
                exp += op;
                exp += ' ';
            }
            if (err) {
                cout << "Error:missing '('!" << endl;
                return;
            }
        } else if (ch >= '0' && ch <= '9') {
            int new_opd = ch - '0';
            while (InExp.length() > i && (InExp[i] >= '0' && InExp[i] <= '9')) {
                new_opd *= 10;
                new_opd += InExp[i++] - '0';
            }
            exp += to_string(new_opd);
            exp += ' ';
        } else if (ch == ' ') {
            i++;
        } else {
            cout << "Error:illegal input!" << endl;
            return;
        }
    }

    while (!operators.empty()) {
        if (operators.top() == '(') {
            cout << "Error:missing ')'!" << endl;
            return;
        }
        exp += operators.top();
        exp += ' ';
        operators.pop();
    }
    PostCreate(exp);
}

template<class T>
void ExpBTR<T>::PreCreate(string PreExp) {
    root = new TreeNode<T>();
    stack<TreeNode<T> *> ops;
    TreeNode<T> *ptr = root;
    int i = 0;
    while (PreExp.length() > i) {
        char ch = PreExp[i++];
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            ptr->data = string(1, ch);
            ptr->left = new TreeNode<T>();
            ops.push(ptr);
            ptr = ptr->left;
        } else if (isdigit(ch)) {
            int new_opd = ch - '0';
            while (PreExp.length() > i && isdigit(PreExp[i])) {
                new_opd *= 10;
                new_opd += PreExp[i++] - '0';
            }
            ptr->data = to_string(new_opd);
            while (!ops.empty() && ops.top()->right != NULL) ops.pop();
            if (!ops.empty()) ptr = ops.top();
            else break;
            ptr->right = new TreeNode<T>();
            ptr = ptr->right;
        } else if (ch == ' ') continue;
        else {
            cout << "Illegal Input!" << endl;
            Delete(root);
            root = NULL;
            return;
        }
    }
    while (!ops.empty() && ops.top()->right != NULL) ops.pop();
    if (!ops.empty()) {
        cout << "Missing Operand!" << endl;
        Delete(root);
        root = NULL;
        return;
    }

    if (i < PreExp.length()) {
        cout << "Missing Operator!" << endl;
        Delete(root);
        root = NULL;
        return;
    }
}

template<class T>
void ExpBTR<T>::PostCreate(string PostExp) {
    stack<TreeNode<T> *> opds;
    int i = 0;
    while (PostExp.length() > i) {
        char ch = PostExp[i++];
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (opds.size() < 2) {
                cout << "Missing Operand!" << endl;
                Delete(root);
                root = NULL;
                return;
            }
            TreeNode<T> *opd2 = opds.top();
            opds.pop();
            TreeNode<T> *opd1 = opds.top();
            opds.pop();
            opds.push(new TreeNode<T>(string(1, ch), opd1, opd2));
        } else if (isdigit(ch)) {
            int new_opd = ch - '0';
            while (PostExp.length() > i && isdigit(PostExp[i])) {
                new_opd *= 10;
                new_opd += PostExp[i++] - '0';
            }
            opds.push(new TreeNode<T>(to_string(new_opd)));
        } else if (ch == ' ') continue;
        else {
            cout << "Illegal Input!" << endl;
            Delete(root);
            root = NULL;
            return;
        }
    }
    if (opds.size() > 1) {
        cout << "Missing Operator!" << endl;
        Delete(root);
        root = NULL;
        return;
    } else root = opds.top();
}

template<class T>
TreeNode<T> *ExpBTR<T>::getRoot() {
    return root;
}

template<class T>
bool ExpBTR<T>::PrintBracket(TreeNode<T> *node, int LeftOrRight) {
    if (node == NULL) return false;
    TreeNode<T> *left = node->left;
    TreeNode<T> *right = node->right;
    if (left == NULL || right == NULL) return false;
    string val_node = node->data;
    string val_left = left->data;
    string val_rignt = right->data;
    if (LeftOrRight == LEFT) {
        if ((val_node[0] == '*' || val_node[0] == '/') && (val_left[0] == '+' || val_left[0] == '-'))
            return true;
    } else if (LeftOrRight == RIGHT) {
        switch (val_node[0]) {
            case '-':
            case '*':
                if (val_rignt[0] == '+' || val_rignt[0] == '-') return true;
                break;
            case '/':
                if (val_rignt[0] == '+' || val_rignt[0] == '-' || val_rignt[0] == '*' || val_rignt[0] == '/')
                    return true;
                break;
        }
    }
    return false;
}

template<class T>
void ExpBTR<T>::Display(TreeNode<T> *parent, TreeNode<T> *r, string pref) {
    string prefix = pref + '|';
    if (r != NULL) {
        cout << prefix << '~' << r->data << endl;
        if (r == parent || r == parent->right) {
            prefix.pop_back();
            prefix += ' ';
        }
        prefix += ' ';
        Display(r, r->left, prefix);
        Display(r, r->right, prefix);
    } else {
        prefix.pop_back();
        prefix.pop_back();
    }
}

int main() {
    cout << "三 18072021[42] 杨雨怡 上机题3" << endl;
    string exp;
    int option=0;
    cout << "请选择输入表达式种类(0-中缀表达式 1-前缀表达式 2-后缀表达式):";
    cin >> option;
    if (option == 0) {
        cout << "请输入中缀表达式:";
        getchar();
        getline(cin, exp);
        ExpBTR<string> *exp_tr;
        exp_tr = new ExpBTR<string>();
        exp_tr->InCreate(exp);
        cout << "中缀表达式:";
        exp_tr->InOrder(exp_tr->getRoot());
        cout << endl;

        cout << "前缀表达式:";
        exp_tr->PreOrder(exp_tr->getRoot());
        cout << endl;

        cout << "后缀表达式:";
        exp_tr->PostOrder(exp_tr->getRoot());
        cout << endl;

        cout << "凹入法输出表达式二叉树图形:" << endl;
        string pref;
        exp_tr->Display(exp_tr->getRoot(), exp_tr->getRoot(), pref);
    }

    if (option == 1) {
        cout << "请输入前缀表达式:";
        getchar();
        getline(cin, exp);
        ExpBTR<string> *exp_tr;
        exp_tr = new ExpBTR<string>();
        exp_tr->PreCreate(exp);
        cout << "中缀表达式:";
        exp_tr->InOrder(exp_tr->getRoot());
        cout << endl;

        cout << "前缀表达式:";
        exp_tr->PreOrder(exp_tr->getRoot());
        cout << endl;

        cout << "后缀表达式:";
        exp_tr->PostOrder(exp_tr->getRoot());
        cout << endl;

        cout << "凹入法输出表达式二叉树图形:" << endl;
        string pref;
        exp_tr->Display(exp_tr->getRoot(), exp_tr->getRoot(), pref);
    }

    if (option == 2) {
        cout << "请输入后缀表达式:";
        getchar();
        getline(cin, exp);
        ExpBTR<string> *exp_tr;
        exp_tr = new ExpBTR<string>();
        exp_tr->PostCreate(exp);
        cout << "中缀表达式:";
        exp_tr->InOrder(exp_tr->getRoot());
        cout << endl;

        cout << "前缀表达式:";
        exp_tr->PreOrder(exp_tr->getRoot());
        cout << endl;

        cout << "后缀表达式:";
        exp_tr->PostOrder(exp_tr->getRoot());
        cout << endl;

        cout << "凹入法输出表达式二叉树图形:" << endl;
        string pref;
        exp_tr->Display(exp_tr->getRoot(), exp_tr->getRoot(), pref);
    }
    return 0;
}
