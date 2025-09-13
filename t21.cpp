//=============================================================================
//
// Simple Console Drawing Program
//
// This program demonstrates a basic drawing system in a console environment
// using C++. The drawing canvas is a 2D grid represented by a vector of
// strings. The program includes functions to draw a single point, a line,
// and a rectangle by modifying the characters in the canvas.
//
// The drawing operations are "hardcoded" within the main function, as
// requested, to showcase the logic and function calls. For a real-world
// application, these would typically be driven by user input.
//
// To compile and run this program, you can use a C++ compiler like g++.
// Example: g++ drawing_program.cpp -o drawing_program && ./drawing_program
//
//=============================================================================

#include <iostream>
#include <vector>
#include <string>

// Define the dimensions of our drawing canvas.
const int CANVAS_WIDTH = 50;
const int CANVAS_HEIGHT = 20;
const char BACKGROUND_CHAR = ' ';

// A 2D canvas represented as a vector of strings.
using Canvas = std::vector<std::string>;

/**
 * @brief Prints the current state of the canvas to the console.
 * @param canvas The canvas to be printed.
 */
void print_canvas(const Canvas& canvas) {
    // Top border
    std::cout << "+" << std::string(CANVAS_WIDTH, '-') << "+" << std::endl;

    // Print each row of the canvas.
    for (const auto& row : canvas) {
        std::cout << "|" << row << "|" << std::endl;
    }

    // Bottom border
    std::cout << "+" << std::string(CANVAS_WIDTH, '-') << "+" << std::endl;
}

/**
 * @brief Initializes a canvas with a blank background.
 * @return An empty canvas.
 */
Canvas create_blank_canvas() {
    return Canvas(CANVAS_HEIGHT, std::string(CANVAS_WIDTH, BACKGROUND_CHAR));
}

/**
 * @brief Draws a single character at a specified coordinate.
 * @param canvas The canvas to draw on.
 * @param x The x-coordinate (column).
 * @param y The y-coordinate (row).
 * @param character The character to draw.
 */
void draw_point(Canvas& canvas, int x, int y, char character) {
    // Check if the coordinates are within the canvas boundaries.
    if (x >= 0 && x < CANVAS_WIDTH && y >= 0 && y < CANVAS_HEIGHT) {
        canvas[y][x] = character;
    }
}

/**
 * @brief Draws a line between two points using a simple algorithm.
 * @param canvas The canvas to draw on.
 * @param x1 The starting x-coordinate.
 * @param y1 The starting y-coordinate.
 * @param x2 The ending x-coordinate.
 * @param y2 The ending y-coordinate.
 * @param character The character to use for the line.
 */
void draw_line(Canvas& canvas, int x1, int y1, int x2, int y2, char character) {
    // Simple line drawing algorithm (DDA or similar).
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = std::max(std::abs(dx), std::abs(dy));
    float x_increment = static_cast<float>(dx) / steps;
    float y_increment = static_cast<float>(dy) / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; ++i) {
        draw_point(canvas, static_cast<int>(x + 0.5), static_cast<int>(y + 0.5), character);
        x += x_increment;
        y += y_increment;
    }
}

/**
 * @brief Draws a rectangle outline.
 * @param canvas The canvas to draw on.
 * @param x The top-left x-coordinate.
 * @param y The top-left y-coordinate.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param character The character to use for the rectangle.
 */
void draw_rectangle(Canvas& canvas, int x, int y, int width, int height, char character) {
    // Draw the top and bottom lines of the rectangle.
    draw_line(canvas, x, y, x + width, y, character);
    draw_line(canvas, x, y + height, x + width, y + height, character);

    // Draw the left and right lines.
    draw_line(canvas, x, y, x, y + height, character);
    draw_line(canvas, x + width, y, x + width, y + height, character);
}

int main() {
    // Create an empty canvas.
    Canvas canvas = create_blank_canvas();

    std::cout << "Initial blank canvas:" << std::endl;
    print_canvas(canvas);

    std::cout << "\nDrawing a single point at (10, 5) with character 'O'." << std::endl;
    draw_point(canvas, 10, 5, 'O');
    print_canvas(canvas);

    std::cout << "\nDrawing a line from (5, 15) to (40, 5) with character '#'." << std::endl;
    draw_line(canvas, 5, 15, 40, 5, '#');
    print_canvas(canvas);

    std::cout << "\nDrawing a rectangle at (25, 10) with width 20 and height 8 with character '*'." << std::endl;
    draw_rectangle(canvas, 25, 10, 20, 8, '*');
    print_canvas(canvas);

    std::cout << "\nDone drawing. Final canvas state shown above." << std::endl;

    return 0;
}
