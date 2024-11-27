#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML GUI + Audio");

    // Load a music file
    sf::Music music;
    if (!music.openFromFile("audios/CONFIG.mp3")) {
        std::cerr << "Error loading the audio file." << std::endl;
        return -1;
    }
    music.setLoop(true); // Set to loop
    music.play(); // Play the music

    // Create a text object
    sf::Font font;
    if (!font.loadFromFile("fonts/ARIAL.ttf")) { 
        std::cerr << "Error loading the font." << std::endl;
        return -1;
    }

    // Define the "computer green" color
    sf::Color computerGreen(51, 204, 51);

    // Create the text
    sf::Text text("Press ESC to exit :P", font, 30);
    text.setFillColor(computerGreen);

    // Adjust the text position to the center of the window
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2); // Center the text
    text.setPosition(1920 / 2, 1080 / 2); // Center of the window

    // Load the background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/retroScreen.png")) { // Ensure you use the correct path to your PNG
        std::cerr << "Error loading the background image." << std::endl;
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    // Create a button in the upper-right corner
    sf::RectangleShape button(sf::Vector2f(100, 25)); // Width: 100, Height: 50
    button.setFillColor(sf::Color(128, 128, 128)); // Gray button
    button.setPosition(1920 - 110, 10); // 10 pixels margin from the top-right corner

    // Create text for the button
    sf::Text buttonText("Music ON/OFF", font, 15);
    buttonText.setFillColor(sf::Color(0, 0, 0)); // Black text
    sf::FloatRect buttonTextBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(buttonTextBounds.left + buttonTextBounds.width / 2, buttonTextBounds.top + buttonTextBounds.height / 2);
    buttonText.setPosition(button.getPosition().x + button.getSize().x / 2, button.getPosition().y + button.getSize().y / 2);

    bool isMusicPlaying = true; // Track music state

    // Main window loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            // Handle mouse click on the button
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    if (isMusicPlaying) {
                        music.pause();
                        isMusicPlaying = false;
                    } else {
                        music.play();
                        isMusicPlaying = true;
                    }
                }
            }
        }

        // Change button color on hover
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            button.setFillColor(sf::Color(180, 180, 180)); // Lighter gray when hovered
        } else {
            button.setFillColor(sf::Color(128, 128, 128)); // Default gray button
        }

        // Draw elements
        window.clear();
        window.draw(backgroundSprite); // Draw the background image
        window.draw(text);
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }

    return 0;
}
