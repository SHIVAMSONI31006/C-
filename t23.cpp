#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cctype>

void display_game_status(const std::string& secret_word, const std::string& guessed_letters) {
    std::cout << "\nWord to guess: ";
    for (char letter : secret_word) {
        if (guessed_letters.find(letter) != std::string::npos) {
            std::cout << letter << " ";
        } else {
            std::cout << "_ ";
        }
    }
    std::cout << "\nGuessed letters: " << guessed_letters << std::endl;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(0)));

    std::vector<std::string> words = {"programming", "computer", "keyboard", "algorithm", "developer", "challenge", "internet"};
    std::string secret_word = words[std::rand() % words.size()];
    std::string guessed_letters = "";
    int max_guesses = 7;
    int guesses_left = max_guesses;

    std::cout << "Welcome to the Word Guessing Game!" << std::endl;
    std::cout << "You have " << max_guesses << " guesses to find the secret word." << std::endl;

    while (guesses_left > 0) {
        display_game_status(secret_word, guessed_letters);
        std::cout << "You have " << guesses_left << " guesses left." << std::endl;

        char guess;
        std::cout << "Enter a letter guess: ";
        std::cin >> guess;
        guess = std::tolower(guess);

        if (std::isalpha(guess)) {
            if (guessed_letters.find(guess) != std::string::npos) {
                std::cout << "You've already guessed that letter. Try another one!" << std::endl;
                continue;
            }

            guessed_letters += guess;

            if (secret_word.find(guess) != std::string::npos) {
                std::cout << "Correct guess!" << std::endl;
                bool all_found = true;
                for (char letter : secret_word) {
                    if (guessed_letters.find(letter) == std::string::npos) {
                        all_found = false;
                        break;
                    }
                }
                if (all_found) {
                    std::cout << "\nCongratulations! You've guessed the word: " << secret_word << std::endl;
                    break;
                }
            } else {
                std::cout << "Incorrect guess." << std::endl;
                guesses_left--;
            }
        } else {
            std::cout << "Invalid input. Please enter a letter." << std::endl;
        }

        if (guesses_left == 0) {
            std::cout << "\nGame over! The word was: " << secret_word << std::endl;
        }
    }

    return 0;
}