#include <iostream>
#include <vector>
#include <string>
#include <limits> // For std::numeric_limits
#include "../constants/topics.h" // Relative path to topics.h
#include "../topics_objects/topics_objects.h" // Relative path to topics_objects.h

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
            // Create topic object
            Topic* topic_selected = new Topic(topics[topic_number - 1], topic_number, "DEFAULT, TO DO");
            // Display the topic details
            std::cout << "Topic ID: " << topic_selected->getId() << std::endl;
            std::cout << "Name: " << topic_selected->getName() << std::endl;
            //Delete object after usage
            delete topic_selected; // Automatically calls the destructor

            // Create sub_topic object
            SubTopic* sub_topic_selected = new SubTopic(topics[topic_number - 1], topic_number, "DEFAULT, TO DO", "Example subtopic name", "Example subtopic description", topic_number + 10);
            // Display the topic details
            std::cout << "SubTopic ID: " << sub_topic_selected->getSubId() << std::endl;
            std::cout << "Name: " << sub_topic_selected->getSubName() << std::endl;
            std::cout << "Description: " << sub_topic_selected->getSubDescription() << std::endl;
            //Delete object after usage
            delete sub_topic_selected; // Automatically calls the destructor

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
