#include <iostream>
#include "Airport.h" // Include your Airport header file here

int displayMenu(); // Function declaration
bool promptToContinue(); // Function declaration

int main() {
    std::cout << "Welcome to Airport simulator" << std::endl;
    int choice;

    while (true) {
        choice = displayMenu(); // Capture user's choice
        if (choice == 0) {
            break; // Exit the loop if the user chooses to exit
        }

        Airport airport;
        switch (choice) {
        case 1:
            airport.airport_small();
            break;
        case 2:
            airport.airport_medium_fixed();
            break;
        case 3:
            // Call the function for P3 version of the airport simulator
                break;
        case 4:
            // Call the function for P4 version of the airport simulator
                break;
        case 5:
            // Call the function for P5 version of the airport simulator
                break;
        }
        // Display the menu again
        std::cout << std::endl; // Add a newline for clarity
    }

    std::cout << "Thank you for using the airport simulator" << std::endl;

    return 0;
}

// Function definition to display menu and return user's choice
int displayMenu() {
    int choice;
    std::cout << "Please select the version of the airport simulator you would like to run" << std::endl;
    std::cout << "1. Run P1 version of Airport simulator" << std::endl
              << "2. Run P2 version of Airport simulator" << std::endl
              << "3. Run P3 version of Airport simulator" << std::endl
              << "4. Run P4 version of Airport simulator" << std::endl
              << "5. Run P5 version of Airport simulator" << std::endl
              << "0. Exit" << std::endl
              << "Enter your choice: ";

    while (!(std::cin >> choice) || (choice < 0 || choice > 5)) {
        std::cout << "Invalid choice. Please enter a number between 0 and 5: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return choice; // Return user's choice
}

// Function to prompt the user to continue or exit
bool promptToContinue() {
    char choice;
    std::cout << "Enter 'E' to exit, or any other key to continue: ";
    std::cin >> choice;
    if (choice == 'E' || choice == 'e') {
        std::cout << "Exiting..." << std::endl;
        return false; // Return false to indicate exiting
    } else {
        return true; // Return true to indicate continuing
    }
}