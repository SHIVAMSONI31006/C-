#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>

// --- Data Structures ---
// A struct to represent a student with their ID, name, and a list of grades.
struct Student {
    std::string id;
    std::string name;
    std::vector<double> grades;
};

// --- Function Prototypes ---
// Function to display the main menu to the user.
void displayMenu();

// Functions for managing student data.
void addStudent(std::vector<Student>& students);
void addGrade(std::vector<Student>& students);
void displayGrades(const std::vector<Student>& students);
void calculateAverage(const std::vector<Student>& students);

// Functions for file I/O to save and load data.
void saveData(const std::vector<Student>& students, const std::string& filename);
void loadData(std::vector<Student>& students, const std::string& filename);

// Helper function to find a student by their ID.
int findStudentById(const std::vector<Student>& students, const std::string& id);

// --- Main Program ---
int main() {
    // A vector to hold all student objects.
    std::vector<Student> students;
    const std::string filename = "grades.txt";
    int choice;

    // Load data from file at program start.
    loadData(students, filename);

    // Main program loop with a menu.
    while (true) {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Input validation to handle non-integer input.
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                addGrade(students);
                break;
            case 3:
                displayGrades(students);
                break;
            case 4:
                calculateAverage(students);
                break;
            case 5:
                saveData(students, filename);
                std::cout << "Student data saved successfully.\n";
                break;
            case 6:
                std::cout << "Exiting program. Goodbye!\n";
                // Save data on exit for a clean termination.
                saveData(students, filename);
                return 0; // Exit the program.
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

// --- Function Implementations ---

/**
 * @brief Displays the main menu options to the user.
 */
void displayMenu() {
    std::cout << "\n--- Student Grade Management System ---\n";
    std::cout << "1. Add a new student\n";
    std::cout << "2. Add a grade for a student\n";
    std::cout << "3. Display all student grades\n";
    std::cout << "4. Calculate a student's average grade\n";
    std::cout << "5. Save data\n";
    std::cout << "6. Exit\n";
}

/**
 * @brief Adds a new student to the system.
 * @param students A reference to the vector of Student objects.
 */
void addStudent(std::vector<Student>& students) {
    std::string id, name;
    std::cout << "Enter student ID: ";
    std::cin >> id;

    // Check if a student with the same ID already exists.
    if (findStudentById(students, id) != -1) {
        std::cout << "Error: A student with this ID already exists.\n";
        return;
    }

    std::cout << "Enter student name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer.
    std::getline(std::cin, name);

    students.push_back({id, name, {}});
    std::cout << "Student added successfully!\n";
}

/**
 * @brief Adds a new grade for an existing student.
 * @param students A reference to the vector of Student objects.
 */
void addGrade(std::vector<Student>& students) {
    std::string id;
    double grade;
    std::cout << "Enter student ID to add a grade: ";
    std::cin >> id;

    int index = findStudentById(students, id);
    if (index == -1) {
        std::cout << "Error: Student not found.\n";
        return;
    }

    std::cout << "Enter the grade (0-100): ";
    std::cin >> grade;

    // Input validation for the grade value.
    if (std::cin.fail() || grade < 0 || grade > 100) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid grade. Please enter a value between 0 and 100.\n";
        return;
    }

    students[index].grades.push_back(grade);
    std::cout << "Grade added successfully!\n";
}

/**
 * @brief Displays the grades for all students.
 * @param students A constant reference to the vector of Student objects.
 */
void displayGrades(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No students found.\n";
        return;
    }

    std::cout << "\n--- Student Grades ---\n";
    for (const auto& student : students) {
        std::cout << "ID: " << student.id << ", Name: " << student.name << "\n";
        std::cout << "Grades: ";
        if (student.grades.empty()) {
            std::cout << "No grades recorded.\n";
        } else {
            for (double grade : student.grades) {
                std::cout << grade << " ";
            }
            std::cout << "\n";
        }
    }
}

/**
 * @brief Calculates and displays the average grade for a specific student.
 * @param students A constant reference to the vector of Student objects.
 */
void calculateAverage(const std::vector<Student>& students) {
    std::string id;
    std::cout << "Enter student ID to calculate average: ";
    std::cin >> id;

    int index = findStudentById(students, id);
    if (index == -1) {
        std::cout << "Error: Student not found.\n";
        return;
    }

    const auto& student = students[index];
    if (student.grades.empty()) {
        std::cout << "No grades recorded for this student.\n";
        return;
    }

    double sum = 0.0;
    for (double grade : student.grades) {
        sum += grade;
    }
    double average = sum / student.grades.size();

    // Set precision for the average grade output.
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average grade for " << student.name << " (ID: " << student.id << "): " << average << "\n";
}

/**
 * @brief Saves the student data to a file in a simple, comma-separated format.
 * @param students A constant reference to the vector of Student objects.
 * @param filename The name of the file to save to.
 */
void saveData(const std::vector<Student>& students, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for saving.\n";
        return;
    }

    for (const auto& student : students) {
        file << student.id << "," << student.name;
        for (double grade : student.grades) {
            file << "," << grade;
        }
        file << "\n";
    }
    file.close();
}

/**
 * @brief Loads student data from a file and populates the vector.
 * @param students A reference to the vector of Student objects.
 * @param filename The name of the file to load from.
 */
void loadData(std::vector<Student>& students, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "No saved data found. Starting with an empty system.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        Student student;
        std::string part;
        size_t pos = 0;
        int part_count = 0;

        while ((pos = line.find(',')) != std::string::npos) {
            part = line.substr(0, pos);
            if (part_count == 0) {
                student.id = part;
            } else if (part_count == 1) {
                student.name = part;
            } else {
                student.grades.push_back(std::stod(part));
            }
            line.erase(0, pos + 1);
            part_count++;
        }
        // Handle the last part (the last grade or just the name/id).
        if (!line.empty()) {
            if (part_count == 0) { // Only ID
                student.id = line;
            } else if (part_count == 1) { // ID and Name
                student.name = line;
            } else { // At least one grade
                student.grades.push_back(std::stod(line));
            }
        }
        students.push_back(student);
    }
    file.close();
    std::cout << "Student data loaded successfully.\n";
}

/**
 * @brief Helper function to find a student by their ID.
 * @param students A constant reference to the vector of Student objects.
 * @param id The ID to search for.
 * @return The index of the student in the vector, or -1 if not found.
 */
int findStudentById(const std::vector<Student>& students, const std::string& id) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}
