#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

void clearScreen();
double getNumber(const string& prompt);
char getOperation();
void calculateAndPrint(double num1, char operation, double num2);
bool isValidNumber(const string& input);

int main() {
    cout << fixed << setprecision(2);
    char continueChoice = 'y';

    while (continueChoice == 'y' || continueChoice == 'Y') {
        clearScreen();

        cout << "\t\tWelcome to the Professional Calculator!" << endl;
        cout << "\t*********************************************" << endl;

        double num1 = getNumber("Enter the first number: ");
        char operation = getOperation();
        double num2 = getNumber("Enter the second number: ");

        cout << endl;
        calculateAndPrint(num1, operation, num2);

        cout << "\nDo you want to perform another calculation? (y/n): ";
        cin >> continueChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    clearScreen();
    cout << "\nThank you for using the calculator. Goodbye!" << endl;
    return 0;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Check if string is a valid number (like 12, -5.3, 0.56)
bool isValidNumber(const string& input) {
    bool hasDecimal = false;
    int start = 0;

    if (input.empty()) return false;

    if (input[0] == '-' || input[0] == '+')
        start = 1;

    for (int i = start; i < (int)input.size(); ++i) {
        if (input[i] == '.') {
            if (hasDecimal) return false; // More than one decimal point
            hasDecimal = true;
        } else if (!isdigit(input[i])) {
            return false; // Not a digit
        }
    }
    return true;
}

double getNumber(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);

        if (isValidNumber(input)) {
            stringstream ss(input);
            double number;
            ss >> number;
            return number;
        } else {
            cout << "Invalid input. Please enter a valid numeric value (e.g., 12.5, -3)." << endl;
        }
    }
}

char getOperation() {
    string input;
    while (true) {
        cout << "Enter an operation (+, -, *, /): ";
        getline(cin, input);

        if (input.size() == 1 && (input[0] == '+' || input[0] == '-' || input[0] == '*' || input[0] == '/')) {
            return input[0];
        } else {
            cout << "Invalid operation. Please enter only one of (+, -, *, /)." << endl;
        }
    }
}

void calculateAndPrint(double num1, char operation, double num2) {
    double result;
    bool success = true;

    switch (operation) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                cerr << "Error: Division by zero is not allowed." << endl;
                success = false;
            } else {
                result = num1 / num2;
            }
            break;
        default:
            cerr << "Error: Unexpected invalid operation." << endl;
            success = false;
            break;
    }

    if (success) {
        cout << "Result: " << num1 << " " << operation << " " << num2 << " = " << result << endl;
    }
}
