#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <filesystem> // For filesystem operations

const std::string AUDIOS_PATH = "audios/";
const std::string IMAGES_PATH = "images/";
const std::string FONTS_PATH = "fonts/";
const std::string ICONS_PATH = "images/icons/";

const std::string WINDOW_TITLE = "C++ Bible by JALL";
const std::string BACKGROUND_IMAGE_OBJ = "BackgroundImage";
const std::string BACKGROUND_IMAGE_FILE = "realCRT.jpeg";
const std::string SOUND_ON_OBJ = "soundON";
const std::string SOUND_ON_FILE = "soundON.png";
const std::string SOUND_OFF_OBJ = "soundOFF";
const std::string SOUND_OFF_FILE = "soundOFF.png";
const std::string CPP150_IMAGE_OBJ = "cpp150";
const std::string CPP150_IMAGE_FILE = "cpp150.png";
constexpr std::array<int, 3> CRTGreen{0, 255, 128};


struct LineTextParams {
    std::string name;
    int x_position;
    int y_position;
    std::array<int, 3> color;
    std::string text;
    std::string fontPath;
    int textSize;
    bool centered;
};

LineTextParams mainMenuParams = {"mainMenu", 1920 / 2, 50, CRTGreen, "MAIN MENU", FONTS_PATH + "retro_computer.ttf", 40, true};


std::vector<LineTextParams> topics = {
    {"Topic1", 0, 0, CRTGreen, "1. Introduction to C++ Programming", FONTS_PATH + "retro_computer.ttf", 30, false},
    {"Topic2", 0, 0, CRTGreen, "2. Data Types in C++", FONTS_PATH + "retro_computer.ttf", 30, false},
    {"Topic3", 0, 0, CRTGreen, "3. Control Structures in C++", FONTS_PATH + "retro_computer.ttf", 30, false},
    {"Topic4", 0, 0, CRTGreen, "4. Functions and Parameters in C++", FONTS_PATH + "retro_computer.ttf", 30, false},
    {"Topic5", 0, 0, CRTGreen, "5. Object-Oriented Programming Concepts", FONTS_PATH + "retro_computer.ttf", 30, false},
    {"Topic6", 0, 0, CRTGreen, "6. Memory Management", FONTS_PATH + "retro_computer.ttf", 30, false},
    {"Topic7", 0, 0, CRTGreen, "7. Standard Template Library (STL)", FONTS_PATH + "retro_computer.ttf", 30, false},
    {"Topic8", 0, 0, CRTGreen, "8. File Handling in C++", FONTS_PATH + "retro_computer.ttf", 30, false},
    {"Topic9", 0, 0, CRTGreen, "9. Error Handling and Debugging", FONTS_PATH + "retro_computer.ttf", 30, false},
    {"Topic10", 0, 0, CRTGreen, "10. Advanced Topics in C++", FONTS_PATH + "retro_computer.ttf", 30, false}
};


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
    bool centerText;

public:
    // Constructor for figures
    PrintObject(const std::string& _name, int _width, int _height, int _x_position, int _y_position, std::array<int, 3> _color)
        : name(_name), width(_width), height(_height), x_position(_x_position), y_position(_y_position), color(_color), isText(false), centerText(false) {}

    // Constructor for images (sets default values)
    explicit PrintObject(const std::string& _name, int _width, int _height, int _x_position, int _y_position)
        : name(_name), width(_width), height(_height), x_position(_x_position), y_position(_y_position), color{255, 255, 255}, isText(false), centerText(false) {}

    // Constructor for text
    PrintObject(const std::string& _name, int _x_position, int _y_position, std::array<int, 3> _color, 
                const std::string& _text, const std::string& fontPath, int _text_size, bool centerText)
        : name(_name), width(0), height(0), x_position(_x_position), y_position(_y_position), color(_color), isText(true) {
        if (!font.loadFromFile(fontPath)) {
            throw std::runtime_error("Failed to load font: " + fontPath);
        }
        textObj.setFont(font);
        textObj.setString(_text);
        textObj.setCharacterSize(_text_size);
        textObj.setFillColor(sf::Color(color[0], color[1], color[2]));

        sf::FloatRect textBounds = textObj.getLocalBounds();

        if (centerText) {
            // Center-align the text
            textObj.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
        } else {
            // Left-align the text
            textObj.setOrigin(0, textBounds.top + textBounds.height / 2); // Only vertically centered
        }

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


    sf::Texture& getTexture() {
    return texture;
    }

    const sf::Texture& getTexture() const {
        return texture;
    }

    sf::Sprite& getTextureSprite() {
        return textureSprite;
    }

    const sf::Sprite& getTextureSprite() const {
        return textureSprite;
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

// Load music
std::shared_ptr<sf::Music> loadAndPlayMusic() {
    auto music = std::make_shared<sf::Music>();
    if (!music->openFromFile(AUDIOS_PATH + "MIX_MASTER_BOOT_RECORD_INTERRUPT_REQUEST_INTERNET_PROTOCOL.mp3")) {
        std::cerr << "Error loading music.\n";
        return nullptr; // Return nullptr to indicate failure
    }
    music->play();
    music->setLoop(true);
    return music;
}

std::vector<std::shared_ptr<PrintObject>> createPrintObjects(const std::string& fontsPath) {
    // Crear el vector de PrintObjects como shared_ptr
    std::vector<std::shared_ptr<PrintObject>> printObjects;
    int page_beggining_h = 50;
    int page_beggining_v = 1920 / 2 - 1920 / 4;
    int step_size = 50;
    int next_line = 0;

    // Añadir objetos al vector usando std::make_shared
    printObjects.push_back(
        std::make_shared<PrintObject>(
            mainMenuParams.name, 
            mainMenuParams.x_position, 
            mainMenuParams.y_position, 
            mainMenuParams.color, 
            mainMenuParams.text, 
            mainMenuParams.fontPath, 
            mainMenuParams.textSize, 
            mainMenuParams.centered
        )
    );
    next_line = mainMenuParams.y_position + 100;

    for (const auto& topic : topics) {
        printObjects.push_back(std::make_shared<PrintObject>(
            topic.name, page_beggining_v, next_line, topic.color,
            topic.text, topic.fontPath, topic.textSize, topic.centered
        ));
        next_line = next_line + step_size;
    }

    return printObjects;
}



void drawPrintObjects(sf::RenderWindow& window, const std::vector<std::shared_ptr<PrintObject>>& printObjects) {
    for (const auto& obj : printObjects) {
        obj->draw(window); // Llamar al método draw usando el puntero
    }
}

int initAndStartMainWindowLoop(){

    // Create a window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), WINDOW_TITLE);


    // Create PrintObject objects
    PrintObject* background = new PrintObject(BACKGROUND_IMAGE_OBJ, 1920, 1080, 0, 0);
    if (!background->loadTexture(IMAGES_PATH + BACKGROUND_IMAGE_FILE)) {
        return -1; // Exit if texture loading fails
    }

    // Create PrintObject objects
    PrintObject* cpp150 = new PrintObject(CPP150_IMAGE_OBJ, 100, 100, 200, 800);
    if (!cpp150->loadTexture(ICONS_PATH + CPP150_IMAGE_FILE)) {
        return -1; // Exit if texture loading fails
    }


    // Create PrintObject objects
    PrintObject* soundON = new PrintObject(SOUND_ON_OBJ, 50, 50, 1920 - 100, 30);
    if (!soundON->loadTexture(ICONS_PATH + SOUND_ON_FILE)) {
        return -1; // Exit if texture loading fails
    }

    // Create PrintObject objects
    PrintObject* soundOFF = new PrintObject(SOUND_OFF_OBJ, 50, 50, 1920 - 100, 30);
    if (!soundOFF->loadTexture(ICONS_PATH + SOUND_OFF_FILE)) {
        return -1; // Exit if texture loading fails
    }

    // Create vector with text objects
    std::vector<std::shared_ptr<PrintObject>> textObjects = createPrintObjects(FONTS_PATH);

    std::shared_ptr<sf::Music> music = loadAndPlayMusic();
    bool isMusicPlaying = true; // Initial sound state

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
                handleSoundButton(soundON->getTextureSprite(), soundON->getTexture(), soundOFF->getTexture(), *music, isMusicPlaying, window);
            }
        }

        // Draw elements
        window.clear();
        background->draw(window);
        cpp150->draw(window);
        soundON->draw(window);
        drawPrintObjects(window, textObjects);
        window.display();
    }

    // Delete objects
    delete background;
    delete cpp150;
    delete soundON;
    delete soundOFF;
    return 0;
}


int main() {

    return initAndStartMainWindowLoop();

    //return 0;
}
