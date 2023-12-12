#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main() {
    int secretNumber = rand() % 100 + 1;
    int guess;
    int attempts = 0;

    cout << setw(80) << "Welcome to the Number Guessing Game!" << endl << endl;
    cout << setw(82) << "Try to guess the number between 1 and 100." << endl;

    do {
        cout << "Enter your guess: ";
        cin >> guess;
        attempts++;

        if (guess > secretNumber) {
            cout << "Too high! Try again." << endl << endl;
        } else if (guess < secretNumber) {
            cout << "Too low! Try again." << endl << endl;
        } else {
            cout << "Congratulations! You guessed the number in " << attempts << " attempts." << endl;
        }
    } while (guess != secretNumber);

    return 0;
}

