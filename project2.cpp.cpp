#include <iostream>
#include <fstream>
#include <string>

// Function to encrypt a file using a Caesar cipher
void encryptFile(const std::string& inputFile, const std::string& outputFile, int key) {
    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return;
    }

    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Error: Could not create output file." << std::endl;
        return;
    }

    char ch;
    while (inFile.get(ch)) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            ch = static_cast<char>((ch - base + key) % 26 + base);
        }
        outFile.put(ch);
    }

    std::cout << "File encrypted successfully. Encrypted text saved to " << outputFile << std::endl;

    inFile.close();
    outFile.close();
}

// Function to decrypt a file using a Caesar cipher
void decryptFile(const std::string& inputFile, const std::string& outputFile, int key) {
    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return;
    }

    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Error: Could not create output file." << std::endl;
        return;
    }

    char ch;
    while (inFile.get(ch)) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            ch = static_cast<char>((ch - base - key + 26) % 26 + base);
        }
        outFile.put(ch);
    }

    std::cout << "File decrypted successfully. Decrypted text saved to " << outputFile << std::endl;

    inFile.close();
    outFile.close();
}

int main() {
    int choice, key;
    std::string inputFile, outputFile;

    std::cout << "Caesar Cipher File Encryptor/Decryptor" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "1. Encrypt a file" << std::endl;
    std::cout << "2. Decrypt a file" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    std::cout << "Enter the input filename: ";
    std::cin >> inputFile;
    std::cout << "Enter the output filename: ";
    std::cin >> outputFile;
    std::cout << "Enter the key (an integer): ";
    std::cin >> key;

    // Normalize the key to be within 0-25
    key = (key % 26 + 26) % 26;

    if (choice == 1) {
        encryptFile(inputFile, outputFile, key);
    } else if (choice == 2) {
        decryptFile(inputFile, outputFile, key);
    } else {
        std::cout << "Invalid choice." << std::endl;
    }

    return 0;
}