#include <iostream>
#include <vector>
#include <string>

using namespace std;

// This class represents a single hotel room.
class Room {
public:
    int roomNumber;
    bool isBooked;

    Room(int num) : roomNumber(num), isBooked(false) {}

    void displayStatus() {
        cout << "Room " << roomNumber << ": " << (isBooked ? "Occupied" : "Available") << endl;
    }
};

// This class represents the hotel itself, containing a collection of rooms.
class Hotel {
private:
    vector<Room> rooms;

public:
    Hotel(int numRooms) {
        for (int i = 1; i <= numRooms; ++i) {
            rooms.push_back(Room(i));
        }
    }

    void displayAllRooms() {
        cout << "--- Room Status ---" << endl;
        for (Room& room : rooms) {
            room.displayStatus();
        }
        cout << "-------------------" << endl;
    }

    void bookRoom(int roomNum) {
        if (roomNum >= 1 && roomNum <= rooms.size()) {
            if (!rooms[roomNum - 1].isBooked) {
                rooms[roomNum - 1].isBooked = true;
                cout << "Room " << roomNum << " has been booked successfully." << endl;
            } else {
                cout << "Room " << roomNum << " is already occupied." << endl;
            }
        } else {
            cout << "Invalid room number." << endl;
        }
    }

    void checkoutRoom(int roomNum) {
        if (roomNum >= 1 && roomNum <= rooms.size()) {
            if (rooms[roomNum - 1].isBooked) {
                rooms[roomNum - 1].isBooked = false;
                cout << "Checkout for Room " << roomNum << " successful." << endl;
            } else {
                cout << "Room " << roomNum << " is not occupied." << endl;
            }
        } else {
            cout << "Invalid room number." << endl;
        }
    }
};

int main() {
    // Create a hotel with 10 rooms.
    Hotel myHotel(10);
    int choice, roomNumber;

    while (true) {
        cout << "\n--- Hotel Management System ---" << endl;
        cout << "1. Display all rooms" << endl;
        cout << "2. Book a room" << endl;
        cout << "3. Checkout a room" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                myHotel.displayAllRooms();
                break;
            case 2:
                cout << "Enter room number to book: ";
                cin >> roomNumber;
                myHotel.bookRoom(roomNumber);
                break;
            case 3:
                cout << "Enter room number to checkout: ";
                cin >> roomNumber;
                myHotel.checkoutRoom(roomNumber);
                break;
            case 4:
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}