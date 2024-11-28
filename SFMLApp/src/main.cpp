#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <array>

const std::string AUDIOS_PATH = "audios/";
const std::string IMAGES_PATH = "images/";
const std::string FONTS_PATH = "fonts/";
const std::string ICONS_PATH = "images/icons/";

class PrintObject {
private:
    int height, width, x_position, y_position;
    std::string name; // Object name
    std::array<int, 3> color; // RGB color
    sf::Texture texture; // Texture for the object
    sf::Sprite textureSprite; // Sprite to draw the object
    sf::Font font; // Font for the text
    sf::Text textObj; // SFML Text object
    bool isText; // Flag to indicate if this is a text object

public:
    // Constructor for figures
    PrintObject(const std::string& _name, int _width, int _height, int _x_position, int _y_position, std::array<int, 3> _color)
        : name(_name), width(_width), height(_height), x_position(_x_position), y_position(_y_position), color(_color), isText(false) {}

    // Constructor for images (sets default values)
    explicit PrintObject(const std::string& _name, int _width, int _height, int _x_position, int _y_position)
        : name(_name), width(_width), height(_height), x_position(_x_position), y_position(_y_position), color{255, 255, 255}, isText(false) {}

    // Constructor for text
    PrintObject(const std::string& _name, int _x_position, int _y_position, std::array<int, 3> _color, const std::string& _text, const std::string& fontPath, int _text_size)
        : name(_name), width(0), height(0), x_position(_x_position), y_position(_y_position), color(_color), isText(true) {
        if (!font.loadFromFile(fontPath)) {
            throw std::runtime_error("Failed to load font: " + fontPath);
        }
        textObj.setFont(font);
        textObj.setString(_text);
        textObj.setCharacterSize(_text_size);
        textObj.setFillColor(sf::Color(color[0], color[1], color[2]));
        sf::FloatRect textBounds = textObj.getLocalBounds();
        textObj.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2); // Center the text
        textObj.setPosition(static_cast<float>(_x_position), static_cast<float>(_y_position));
    }

    // Destructor
    ~PrintObject() {
        std::cout << "Destroying PrintObject: " << name << std::endl;
    }

    // Getters and setters
    std::string getName() const { return name; }
    void setName(const std::string& _name) { name = _name; }

    int getHeight() const { return height; }
    void setHeight(int _height) {
        if (_height >= 0) {
            height = _height;
        } else {
            std::cerr << "Height cannot be negative." << std::endl;
        }
    }

    int getWidth() const { return width; }
    void setWidth(int _width) {
        if (_width >= 0) {
            width = _width;
        } else {
            std::cerr << "Width cannot be negative." << std::endl;
        }
    }

    int getX_position() const { return x_position; }
    void setX_position(int _x_position) { x_position = _x_position; }

    int getY_position() const { return y_position; }
    void setY_position(int _y_position) { y_position = _y_position; }

    void getColor(int& r, int& g, int& b) const {
        r = color[0];
        g = color[1];
        b = color[2];
    }

    void setColor(int r, int g, int b) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }

    // Load texture for image objects
    bool loadTexture(const std::string& path) {
        if (!texture.loadFromFile(path)) {
            std::cerr << "Error loading texture from file: " << path << std::endl;
            return false;
        }
        textureSprite.setTexture(texture);
        textureSprite.setPosition(static_cast<float>(x_position), static_cast<float>(y_position));
        textureSprite.setScale(
            static_cast<float>(width) / texture.getSize().x,
            static_cast<float>(height) / texture.getSize().y
        );
        return true;
    }

    // Draw the object (image or text) on the screen
    void draw(sf::RenderWindow& window) {
        if (isText) {
            window.draw(textObj);
        } else {
            window.draw(textureSprite);
        }
    }
};

// Function to handle the button
void handleSoundButton(sf::Sprite& soundButton, 
                       sf::Texture& soundOnTexture, 
                       sf::Texture& soundOffTexture, 
                       sf::Music& music, 
                       bool& isMusicPlaying, 
                       const sf::RenderWindow& window) 
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (soundButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        if (isMusicPlaying) {
            music.pause();
            soundButton.setTexture(soundOffTexture); // Switch to sound-off icon
            isMusicPlaying = false;
        } else {
            music.play();
            soundButton.setTexture(soundOnTexture); // Switch to sound-on icon
            isMusicPlaying = true;
        }
    }
}

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML GUI + Audio");

    // Load button textures
    sf::Texture soundOnTexture, soundOffTexture;
    if (!soundOnTexture.loadFromFile(ICONS_PATH + "soundON.png") || !soundOffTexture.loadFromFile(ICONS_PATH + "soundOFF.png")) {
        std::cerr << "Error loading button images.\n";
        return -1;
    }

    // Create sprite for button
    sf::Sprite soundButton;
    soundButton.setTexture(soundOnTexture);
    soundButton.setPosition(1920 - soundOnTexture.getSize().x - 10, 10); // Margin from top-right corner

    // Load music
    sf::Music music;
    if (!music.openFromFile(AUDIOS_PATH + "CONFIG.mp3")) {
        std::cerr << "Error loading music.\n";
        return -1;
    }
    music.play();
    music.setLoop(true);

    bool isMusicPlaying = true; // Initial sound state

    // Create PrintObject objects
    PrintObject* background = new PrintObject("Background Image", 1920, 1080, 0, 0);
    if (!background->loadTexture(IMAGES_PATH + "greenCircuit.png")) {
        return -1; // Exit if texture loading fails
    }
    PrintObject* textObj = new PrintObject("WelcomeText", 1920 / 2, 1080 / 2, {51, 204, 51}, "OLA K HACE?", FONTS_PATH + "ARIAL.ttf", 30);
    PrintObject* textObj2 = new PrintObject("ResponseText", 1920 / 2 + 200, 1080 / 2 + 200, {51, 204, 51}, "NADA Y UD?", FONTS_PATH + "ARIAL.ttf", 30);

    // Main window loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            // Handle mouse clicks
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                handleSoundButton(soundButton, soundOnTexture, soundOffTexture, music, isMusicPlaying, window);
            }
        }

        // Draw elements
        window.clear();
        background->draw(window);
        textObj->draw(window);
        textObj2->draw(window);
        window.draw(soundButton); // Draw button
        window.display();
    }

    delete background;
    delete textObj;
    delete textObj2;

    return 0;
}
