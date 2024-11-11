#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <cmath> // For operations like sin, cos, etc.

using namespace std;

// Define the exceptions
class InvalidExpressionException : public runtime_error {
public:
    InvalidExpressionException(const string& msg) : runtime_error(msg) {}
};

// Template to check if a type is numeric (integral or floating-point)
template <typename T>
struct is_numeric {
    static const bool value = std::is_integral<T>::value || std::is_floating_point<T>::value;
};

// Helper function to perform basic arithmetic operations
template <typename T>
T applyOperation(T a, T b, const string& op) {
    static_assert(is_numeric<T>::value, "T must be a numeric type");

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
template <typename T>
T evaluate(const string& expression) {
    stack<T> operands;  // Stack for operands (numbers)
    stack<string> operators; // Stack for operators (+, -, *, /)

    stringstream ss(expression);
    string token;

    while (getline(ss, token, ' ')) {
        // Ignore whitespace or empty tokens
        if (token.empty()) continue;

        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && isdigit(token[1]))) {
            // Operand: push to operands stack
            operands.push(static_cast<T>(stof(token)));  // Convert string to numeric type
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
            T b = operands.top(); operands.pop();
            T a = operands.top(); operands.pop();
            string op = operators.top(); operators.pop();

            // Perform the operation and push the result back to the operands stack
            T result = applyOperation(a, b, op);
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

// Test function to validate the evaluate function and compare results with expected values
template <typename T>
void testEvaluate() {
    struct TestCase {
        string expression;
        T expectedResult;
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
            T result = evaluate<T>(testCase.expression);
            cout << "Expression: " << testCase.expression << endl;
            cout << "Expected: " << testCase.expectedResult << ", Computed: " << result << endl;

            if (abs(result - testCase.expectedResult) < 1e-6) {
                cout << "Test passed!" << endl;
            } else {
                cout << "Test failed!" << endl;
            }
            cout << endl;
        }
        catch (const InvalidExpressionException& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}

// Main function to run the test for various types
int main() {
    cout << "Testing with float:" << endl;
    testEvaluate<float>();

    cout << "\nTesting with int:" << endl;
    testEvaluate<int>();

    return 0;
}
