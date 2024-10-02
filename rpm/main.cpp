#include <iostream>
#include "stack.h"

using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int priority(char op) {
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    if(op == '(') return 0;
    return -1;
}

string toRPM(const string & expr) {
    string result = "";
    stack<char> * operations = new stack<char>;

    for(char c: expr) {
        if(isalpha(c) || isdigit(c)) {
            result.push_back(c);
        } else if(c == '(') {
            operations->push(c);
        } else if(c == ')') {

            if(operations->isEmpty()) {
                delete operations;
                return "Invalid Expression";
            }

            while(!operations->isEmpty() && operations->peek() != '(') {
                result.push_back(operations->pop());
            }

            if(operations->isEmpty()) {
                delete operations;
                return "Invalid Expression";
            }

            operations->pop();

        } else if(isOperator(c)) {
            while(!operations->isEmpty() && priority(operations->peek()) >= priority(c)) {
                result.push_back(operations->pop());
            }
            operations->push(c);
        } else {
            delete operations;
            return "Invalid Expression";
        }
    }

    while(!operations->isEmpty()) {
        if(operations->peek() == '(') {
            delete operations;
            return "Invalid Expression";
        }
        result.push_back(operations->pop());
    }

    delete operations;
    return result;
}

int main() {
    string line;
    getline(cin, line);
    cout << toRPM(line) << '\n';
    return 0;
}
