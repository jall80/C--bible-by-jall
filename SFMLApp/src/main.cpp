#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML GUI + Audio");

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

    sf::Text text("Press ESC to exit :P", font, 30);
    text.setFillColor(sf::Color::White);

    // Adjust the text position to the center of the window
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2); // Center the text
    text.setPosition(1280 / 2, 720 / 2); // Center of the window

    // Create a white border with a thickness of 50 pixels
    float outlineThickness = 50.f;
    sf::RectangleShape border(sf::Vector2f(
        1280 - 2 * outlineThickness, // Width reduced by the thickness
        720 - 2 * outlineThickness  // Height reduced by the thickness
    ));
    border.setFillColor(sf::Color::Transparent);       // No fill
    border.setOutlineThickness(outlineThickness);      // Border thickness
    border.setOutlineColor(sf::Color::White);          // Border color
    border.setPosition(outlineThickness, outlineThickness); // Center the border inside the window

    // Main window loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        // Draw elements
        window.clear();
        window.draw(border); // Draw the white border
        window.draw(text);   // Draw the centered text
        window.display();
    }

    return 0;
}
