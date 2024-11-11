#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <cctype>
#include <cmath> // For operations like sin, cos, etc.

using namespace std;

// Define the exceptions
class InvalidExpressionException : public runtime_error {
public:
    InvalidExpressionException(const string& msg) : runtime_error(msg) {}
};

// Helper function to perform basic arithmetic operations
float applyOperation(float a, float b, const string& op) {
    if (op == "+") return a + b;
    else if (op == "-") return a - b;
    else if (op == "*") return a * b;
    else if (op == "/") {
        if (b == 0) {
            throw InvalidExpressionException("Division by zero");
        }
        return a / b;
    } else {
        throw InvalidExpressionException("Invalid operator: " + op);
    }
}

// The evaluate function to process the fully parenthesized expression
float evaluate(const string& expression) {
    stack<float> operands;  // Stack for operands (numbers)
    stack<string> operators; // Stack for operators (+, -, *, /)

    stringstream ss(expression);
    string token;

    while (getline(ss, token, ' ')) {
        // Ignore whitespace or empty tokens
        if (token.empty()) continue;

        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && isdigit(token[1]))) {
            // Operand: push to operands stack
            operands.push(stof(token));
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            // Operator: push to operators stack
            operators.push(token);
        }
        else if (token == "(") {
            // Left parenthesis: do nothing (ignore)
            continue;
        }
        else if (token == ")") {
            // Right parenthesis: perform the operation
            if (operators.empty() || operands.size() < 2) {
                throw InvalidExpressionException("Invalid expression: missing operands or operator");
            }

            // Pop operands and operator
            float b = operands.top(); operands.pop();
            float a = operands.top(); operands.pop();
            string op = operators.top(); operators.pop();

            // Perform the operation and push the result back to the operands stack
            float result = applyOperation(a, b, op);
            operands.push(result);
        }
        else {
            // Invalid token
            throw InvalidExpressionException("Invalid token: " + token);
        }
    }

    if (operands.size() != 1) {
        throw InvalidExpressionException("Invalid expression: mismatched operands and operators");
    }

    // The final result should be the only element in the operands stack
    return operands.top();
}

// Test function to validate the evaluate function
void testEvaluate() {
    struct TestCase {
        string expression;
        float expectedResult;
    };

    // List of test cases with expressions and their expected results
    TestCase testCases[] = {
        {"( 1 + ( 2 + 3 ) )", 6},
        {"( ( 1 + 2 ) * ( 3 + 4 ) )", 21},
        {"( ( 10 + 5 ) / 3 )", 5},
        {"( ( 4 * ( 5 + 6 ) ) - 2 )", 42},
        {"( ( 6 / 2 ) * ( 3 + 4 ) )", 21}
    };

    for (const auto& testCase : testCases) {
        try {
            float result = evaluate(testCase.expression);
            cout << "Expression: " << testCase.expression << endl;
            cout << "Expected: " << testCase.expectedResult << ", Computed: " << result << endl;

            // Check if the computed result is close to the expected result (for floating point precision)
            if (abs(result - testCase.expectedResult) < 1e-6) {
                cout << "Test passed!" << endl;
            } else {
                cout << "Test failed!" << endl;
            }
            cout << endl;
        } catch (const InvalidExpressionException& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}

// Main function to run the test
int main() {
    testEvaluate();
    return 0;
}
