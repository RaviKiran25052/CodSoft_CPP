#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int operation;
    bool exit = false;

    cout << std::setw(70) << "Simple Calculator\n" << endl;
    while (!exit) {
        cout << "-----------------------------" << endl;
        cout << " Choose operation:\n";
        cout << "   1. Addition (+)\n";
        cout << "   2. Subtraction (-)\n";
        cout << "   3. Multiplication (*)\n";
        cout << "   4. Division (/)\n";
        cout << "   0. Quit\n";
        cout << "Enter operation number: ";
        cin >> operation;
        cout << endl;
        if (operation == 0) {
            exit = true;
            cout << "Exiting calculator. Goodbye!" << endl;
            continue;
        } else if (operation < 1 || operation > 4) {
            cout << "Invalid operation! Please choose a valid number from the menu." << endl;
            continue;
        }

        double num1, num2, result;

        cout << "Enter first number: ";
        cin >> num1;
        cout << "Enter second number: ";
        cin >> num2;        
        cout << endl;
        
        switch (operation) {
            case 1:
                result = num1 + num2;
                cout << "Result: " << result << endl;
                break;
            case 2:
                result = num1 - num2;
                cout << "Result: " << result << endl;
                break;
            case 3:
                result = num1 * num2;
                cout << "Result: " << result << endl;
                break;
            case 4:
                if (num2 != 0) {
                    result = num1 / num2;
                    cout << "Result: " << result << endl;
                } else {
                    cout << "Error! Division by zero is not allowed." << endl;
                }
                break;
        }
    }

    return 0;
}

