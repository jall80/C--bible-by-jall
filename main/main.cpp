#include <iostream>
#include <vector>
#include <string>
#include <limits> // For std::numeric_limits
#include "../constants/topics.h" // Relative path to topics.h

/**
 * @brief Prints the list of topics with their corresponding indices.
 * 
 * @param topics A vector containing the list of topics to display.
 */
void topics_printer(const std::vector<std::string>& topics) {
    // Iterate through the topics and print each with its index
    for (size_t i = 0; i < topics.size(); ++i) {
        std::cout << i + 1 << ". " << topics[i] << std::endl;
    }
}

/**
 * @brief Displays a menu to the user, allowing them to select a topic.
 * 
 * @param topics A vector containing the list of topics.
 */
void main_menu(const std::vector<std::string>& topics) {
    int topic_number = 0; // Variable to store the user's choice

    // Print the list of topics
    topics_printer(topics);

    while (true){
        // Prompt the user for input
        std::cout << "Please enter a number: " << std::flush;

        // Check if the input is valid (integer expected)
        if (!(std::cin >> topic_number)) {
            std::cin.clear(); // Clear error flags if input is invalid
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input! Please enter a valid number." << std::endl;
        }
        // Check if the number is within the valid range of topics
        else if (topic_number >= 1 && topic_number <= topics.size()) {
            // Display the selected topic
            std::cout << topic_number << ". " << topics[topic_number - 1] << std::endl;
            break;
        } 
        else {
            // Inform the user if their choice is out of range
            std::cout << "Invalid choice! Please select a number between 1 and " << topics.size() << "." << std::endl;
        }
    }
}

/**
 * @brief The main entry point of the program.
 * 
 * Initializes the list of topics and calls the main menu.
 * 
 * @return int Returns 0 upon successful execution.
 */
int main() {

    // Call the main menu with the list of topics
    main_menu(topics);

    return 0; // Indicate successful program termination
}
