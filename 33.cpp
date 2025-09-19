#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Generate a random number between 1 and 100
    int secretNumber = rand() % 100 + 1;
    int guess = 0;
    int tries = 0;

    std::cout << "Welcome to the Number Guessing Game!" << std::endl;
    std::cout << "I have a number in mind between 1 and 100." << std::endl;

    // Loop until the player guesses the correct number
    do {
        std::cout << "Enter your guess: ";
        std::cin >> guess;
        tries++;

        if (guess > secretNumber) {
            std::cout << "Too high! Try again." << std::endl;
        } else if (guess < secretNumber) {
            std::cout << "Too low! Try again." << std::endl;
        } else {
            std::cout << "Congratulations! You guessed the correct number." << std::endl;
            std::cout << "It took you " << tries << " tries to guess the number." << std::endl;
        }
    } while (guess != secretNumber);

    return 0;
}