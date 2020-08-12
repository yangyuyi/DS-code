#include <iostream>
#include <stack>
#include <cmath>
#include <string>

using namespace std;

class Calculator {
private:
    string exp;
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
    cout << "Please input the expression end by '=':" << endl;
    while (cin >> ch, ch != '=') {
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
            cin.putback(ch);
            int new_opd;
            cin >> new_opd;
            exp += to_string(new_opd);
            exp += ' ';
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

    int i = 0;
    while (exp.length() > i) {
        char c = exp[i++];
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (!compute(c)) return;
        }
        if (c >= '0' && c <= '9') {
            double opd = c - '0';
            while (exp.length() > i && (exp[i] >= '0' && exp[i] <= '9')) {
                opd *= 10;
                opd += exp[i++] - '0';
            }
            operands.push(opd);
        }
    }

    if (operands.size() != 1) {
        cout << "Error!" << endl;
        return;
    }
    cout << "ans=" << operands.top() << endl;
    clear();
}

void Calculator::clear() {
    while (!operands.empty()) operands.pop();
    while (!operators.empty()) operators.pop();
}

int main() {
    Calculator *cal;
    cal = new Calculator();
    cal->run();
    return 0;
}
