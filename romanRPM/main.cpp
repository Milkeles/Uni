#include <iostream>
#include <string>
using namespace std;

// Stack implementation
template <class T>
struct node {
    T data;
    node<T>* link;
};

template <class T>
class stack {
private:
    node<T>* top;
public:
    stack() { top = nullptr; }
    ~stack();
    void push(T const&);
    T pop();
    T peek();
    bool isEmpty() { return top == nullptr; }
};

template <class T>
stack<T>::~stack() {
    while (top) {
        node<T>* temp = top;
        top = top->link;
        delete temp;
    }
}

template <class T>
void stack<T>::push(T const& data) {
    node<T>* newNode = new node<T>();
    newNode->data = data;
    newNode->link = top;
    top = newNode;
}

template <class T>
T stack<T>::pop() {
    if (top) {
        node<T>* temp = top;
        T data = top->data;
        top = top->link;
        delete temp;
        return data;
    }
    else {
        throw runtime_error("Stack underflow");
    }
}

template <class T>
T stack<T>::peek() {
    if (top) {
        return top->data;
    }
    else {
        throw runtime_error("Stack is empty");
    }
}

// Helper functions
bool isOperator(char const& c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int priority(char const& c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '(') return 0;
    return -1;
}

float calculate(char const& op, float a, float b) {
    float res;
    switch (op) {
    case '+':
        res = a + b;
        break;
    case '-':
        res = a - b;
        break;
    case '*':
        res = a * b;
        break;
    case '/':
        res = a / b;
        break;
    default:
        throw runtime_error("Unknown operator");
    }
    return res;
}

int getValue(const char& c) {
    switch (c) {
    case 'I':
        return 1;
    case 'V':
        return 5;
    case 'X':
        return 10;
    case 'L':
        return 50;
    case 'C':
        return 100;
    case 'D':
        return 500;
    case 'M':
        return 1000;
    default:
        return 0; // Return 0 for unrecognized characters
    }
}

string toRPM(string& expr) {
    string result = "";
    stack<char>* operations = new stack<char>();
    char prevChar = '\0';

    size_t i = 0;
    while (i < expr.length()) {
        char c = expr[i];
        if (isalpha(c)) {
            // Start of a Roman numeral
            string romanNumeral = "";
            while (i < expr.length() && isalpha(expr[i])) {
                romanNumeral += expr[i];
                i++;
            }
            // Add the Roman numeral to result (with a space)
            result += romanNumeral + ' ';
            prevChar = 'a'; // Set prevChar to indicate we just had a numeral
            continue; // Skip the rest of the loop, as we've already advanced i
        }
        else if (c == '(') {
            operations->push(c);
        }
        else if (c == ')') {
            while (!operations->isEmpty() && operations->peek() != '(') {
                result += operations->pop();
                result += ' ';
            }
            operations->pop(); // Remove '('
        }
        else if (isOperator(c)) {
            if ((prevChar == '(' || isOperator(prevChar) || prevChar == '\0')) {
                if (c == '-') {
                    result += "0 ";
                    operations->push(c);
                }
            } else {
                while (!operations->isEmpty() && priority(operations->peek()) >= priority(c)) {
                    result += operations->pop();
                    result += ' ';
                }
                operations->push(c);
                result += ' ';
            }
        }
        prevChar = c;
        i++;
    }

    while (!operations->isEmpty()) {
        result += operations->pop();
        result += ' ';
    }

    delete operations;
    return result;
}

float evaluate(string& expr) {
    stack<float>* nums = new stack<float>();
    string currentToken = "";
    size_t i = 0;

    // Inline function to parse Roman numerals
    auto parseRomanNumeral = [](const string& s) -> int {
        int total = 0;
        int prev = 0;
        for (auto it = s.rbegin(); it != s.rend(); ++it) {
            int val = getValue(*it);
            if (val < prev)
                total -= val;
            else
                total += val;
            prev = val;
        }
        return total;
    };

    while (i <= expr.length()) {
        char c = (i < expr.length()) ? expr[i] : '\0';
        if (isalpha(c) || isdigit(c)) {
            // Build Roman numeral or number token
            currentToken += c;
            i++;
        }
        else if (c == ' ' || c == '\0') {
            if (!currentToken.empty()) {
                // Process the token
                if (currentToken.length() == 1 && isOperator(currentToken[0])) {
                    // Operator
                    float num2 = nums->pop();
                    float num1 = nums->pop();
                    float res = calculate(currentToken[0], num1, num2);
                    nums->push(res);
                } else {
                    // Token is a Roman numeral or number
                    float num;
                    if (isdigit(currentToken[0])) {
                        num = stof(currentToken);
                    } else {
                        num = parseRomanNumeral(currentToken);
                    }
                    nums->push(num);
                }
                currentToken = "";
            }
            i++;
        }
        else if (isOperator(c)) {
            if (!currentToken.empty()) {
                // Process the current token before the operator
                float num;
                if (isdigit(currentToken[0])) {
                    num = stof(currentToken);
                } else {
                    num = parseRomanNumeral(currentToken);
                }
                nums->push(num);
                currentToken = "";
            }
            // Process operator
            string op(1, c);
            currentToken = op;
            // Process the operator immediately since operators are single characters
            float num2 = nums->pop();
            float num1 = nums->pop();
            float res = calculate(c, num1, num2);
            nums->push(res);
            currentToken = "";
            i++;
        }
        else {
            // Skip any other characters (shouldn't happen)
            i++;
        }
    }
    float finalResult = nums->pop();
    delete nums;
    return finalResult;
}

int main() {
    string expression;
    getline(cin, expression);
    string rpmExpression = toRPM(expression);
    float result = evaluate(rpmExpression);
    cout << result << endl;
    return 0;
}
