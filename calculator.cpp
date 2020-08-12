#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;

class Calculator {
private:
    vector<string> vec;
    string tmp_str;
    stack<double> operands;
    stack<char> operators;

    bool get_two_operands(double &opd1, double &opd2);

    bool compute(char op);

public:
    Calculator();

    void run();

    void clear();
};

Calculator::Calculator() {
    clear();
}

bool Calculator::get_two_operands(double &opd1, double &opd2) {
    if (operands.empty()) {
        cout << "Error:missing operand" << endl;
        return false;
    }
    opd1 = operands.top();
    operands.pop();
    if (operands.empty()) {
        cout << "Error:missing operand" << endl;
        return false;
    }
    opd2 = operands.top();
    operands.pop();
    return true;
}

bool Calculator::compute(char op) {
    bool res;
    double opd1, opd2;
    res = get_two_operands(opd1, opd2);
    if (!res) {
        clear();
        return false;
    }

    switch (op) {
        case '+':
            operands.push(opd2 + opd1);
            break;
        case '-':
            operands.push(opd2 - opd1);
            break;
        case '*':
            operands.push(opd2 * opd1);
            break;
        case '/':
            if (abs(opd1) < 1E-7) {
                cout << "Error:divided by 0" << endl;
                return false;
            } else operands.push(opd2 / opd1);
            break;
        default:
            break;
    }
    return true;

}

void Calculator::run() {
    char ch;
    cout << "1) Infix Expression -> Postfix Expression" << endl;
    cout << "Please input an expression ended by '=':" << endl;
    while (cin >> ch, ch != '=') {
        if (ch == '+' || ch == '-') {
            while (!operators.empty() && (operators.top() != '(')) {
                tmp_str = "";
                tmp_str += operators.top();
                vec.push_back(tmp_str);
                operators.pop();
            }
            operators.push(ch);
        } else if (ch == '*' || ch == '/') {
            while (!operators.empty() && (operators.top() != '(') && (operators.top() != '+') &&
                   (operators.top() != '-')) {
                tmp_str = "";
                tmp_str += operators.top();
                vec.push_back(tmp_str);
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
                tmp_str = op;
                vec.push_back(tmp_str);
            }
            if (err) {
                cout << "Error:missing '('!" << endl;
                return;
            }
        } else if (ch >= '0' && ch <= '9') {
            cin.putback(ch);
            double new_opd;
            cin >> new_opd;
            tmp_str = "";
            tmp_str += to_string(new_opd);
            vec.push_back(tmp_str);
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
        tmp_str = "";
        tmp_str += operators.top();
        vec.push_back(tmp_str);
        operators.pop();
    }

    cout << "Postfix Expression:";
    for (auto &i: vec) {
        char c = i[0];
        if (c == '+' || c == '-' || c == '*' || c == '/') cout << i << ' ';
        if (c >= '0' && c <= '9') cout << atof(i.c_str()) << ' ';
    }
    cout << endl;

    cout << "2) Postfix Expression -> Answer" << endl;

    for (auto &i : vec) {
        char c = i[0];
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (!compute(c)) return;
        }
        if (c >= '0' && c <= '9') {
            double opd;
            opd = atof(i.c_str());
            operands.push(opd);
        }
    }

    if (operands.size() != 1) {
        cout << "Error!" << endl;
        return;
    }

    cout << "ans = " << operands.top() << endl;
    clear();
}

void Calculator::clear() {
    while (!operands.empty()) operands.pop();
    while (!operators.empty()) operators.pop();
}

int main() {
    cout << "二 18072021[42] 杨雨怡 上机题2" << endl;
    Calculator *cal;
    cal = new Calculator();
    cal->run();
    return 0;
}
