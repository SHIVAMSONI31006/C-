#include <iostream>
#include <vector>
#include <string>

// A structure to represent a single to-do task.
// It contains a description and a boolean to track its completion status.
struct Task {
    std::string description;
    bool completed = false;
};

// Function to display the main menu to the user.
void showMenu() {
    std::cout << "\n--- To-Do List Application ---" << std::endl;
    std::cout << "1. View tasks" << std::endl;
    std::cout << "2. Add a new task" << std::endl;
    std::cout << "3. Mark a task as completed" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << "Enter your choice: ";
}

// Function to view all tasks in the list.
// It iterates through the vector and prints each task's status and description.
void viewTasks(const std::vector<Task>& tasks) {
    std::cout << "\n--- Your Tasks ---" << std::endl;
    if (tasks.empty()) {
        std::cout << "No tasks in the list." << std::endl;
    } else {
        // Loop through each task and display its index, status, and description.
        for (size_t i = 0; i < tasks.size(); ++i) {
            // Use a checkmark for completed tasks and a space for incomplete ones.
            char status = tasks[i].completed ? 'X' : ' ';
            std::cout << i + 1 << ". [" << status << "] " << tasks[i].description << std::endl;
        }
    }
    std::cout << "--------------------" << std::endl;
}

// Function to add a new task to the list.
// It prompts the user for a task description and adds it to the vector.
void addTask(std::vector<Task>& tasks) {
    std::string description;
    std::cout << "Enter the new task description: ";
    // Use std::ws to discard any leading whitespace characters (like the newline from previous input).
    std::getline(std::cin >> std::ws, description);
    
    tasks.push_back({description}); // Add the new task to the vector.
    std::cout << "Task added successfully!" << std::endl;
}

// Function to mark a task as completed.
// It prompts the user for a task number and updates its status if the input is valid.
void markTaskAsCompleted(std::vector<Task>& tasks) {
    viewTasks(tasks); // Show the tasks first so the user can choose which to complete.
    if (tasks.empty()) {
        return; // Exit if there are no tasks to mark.
    }

    int taskNumber;
    std::cout << "Enter the number of the task to mark as completed: ";
    std::cin >> taskNumber;

    // Validate the user's input to ensure it's a valid task number.
    if (taskNumber > 0 && taskNumber <= tasks.size()) {
        tasks[taskNumber - 1].completed = true;
        std::cout << "Task " << taskNumber << " marked as completed!" << std::endl;
    } else {
        std::cout << "Invalid task number. Please try again." << std::endl;
    }
}

// The main function where the program execution begins.
int main() {
    std::vector<Task> tasks; // The vector to store all the tasks.
    int choice;

    do {
        showMenu(); // Display the menu.
        std::cin >> choice;

        // A switch statement to handle the user's choice.
        switch (choice) {
            case 1:
                viewTasks(tasks);
                break;
            case 2:
                addTask(tasks);
                break;
            case 3:
                markTaskAsCompleted(tasks);
                break;
            case 4:
                std::cout << "Exiting application. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 4." << std::endl;
                // Clear the error flags on cin and discard invalid input.
                std::cin.clear();
                std::cin.ignore(256, '\n');
                break;
        }
    } while (choice != 4);

    return 0;
}
