#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <filesystem> // For filesystem operations
#include <cstdint>

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
constexpr std::array<uint16_t, 3> CRTGreen{0, 255, 128};

//For matrix

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int BLOCK_SIZE = 15;

// Calculate the number of rows and columns
const int rows = SCREEN_HEIGHT / BLOCK_SIZE;
const int cols = SCREEN_WIDTH / BLOCK_SIZE;

// Structure to represent a block of 30x30 pixels
struct Block {
    int x, y; // Coordinates of the block
    int width = BLOCK_SIZE; // Width of the block
    int height = BLOCK_SIZE; // Height of the block

    Block(int _x, int _y) : x(_x), y(_y) {}
};

// Function to create and initialize the 2D matrix with (columns, rows) order
std::vector<std::vector<Block>> createGrid(int screenWidth, int screenHeight, int blockSize) {
    // Calculate the number of columns and rows
    int cols = screenWidth / blockSize;
    int rows = screenHeight / blockSize;

    // Create the 2D matrix
    std::vector<std::vector<Block>> grid(cols, std::vector<Block>());

    // Initialize the matrix with blocks
    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            grid[j].emplace_back(j * blockSize, i * blockSize);
        }
    }

    return grid; // Return the initialized matrix
}



struct ScreenParams {
    uint16_t screenWidth;
    uint16_t screenHeight;
    uint16_t leftMargin;
    uint16_t rightMargin;
    uint16_t topMargin;
    uint16_t bottomMargin;
};

ScreenParams generalScreen = {SCREEN_WIDTH, SCREEN_HEIGHT, 50, 50, 50, 50};

struct ScreenBlocks_X{
    uint16_t blockX1;
    uint16_t blockX2;
    uint16_t blockX3;
    uint16_t blockX4;
};

uint16_t FourblocksSize = (generalScreen.screenWidth - (generalScreen.leftMargin + generalScreen.rightMargin))/4;

ScreenBlocks_X general4BlocksX = {
    static_cast<uint16_t>(0), 
    static_cast<uint16_t>(FourblocksSize),
    static_cast<uint16_t>(FourblocksSize * 2),
    static_cast<uint16_t>(FourblocksSize * 3),
};


struct LineTextParams {
    std::string name;
    uint16_t x_position;
    uint16_t y_position;
    std::array<uint16_t, 3> color;
    std::string text;
    std::string fontPath;
    uint16_t textSize;
    bool centered;
};

LineTextParams mainMenuParams = {"mainMenu", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "MAIN MENU", FONTS_PATH + "retro_computer.ttf", 40, true};

std::vector<LineTextParams> generalTopics = {
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

//////////////////////////////////////



class PrintObject {
private:
    uint16_t height, width, x_position, y_position;
    std::string name; // Object name
    std::array<uint16_t, 3> color; // RGB color
    sf::Texture texture; // Texture for the object
    sf::Sprite textureSprite; // Sprite to draw the object
    sf::Font font; // Font for the text
    sf::Text textObj; // SFML Text object
    bool isText; // Flag to indicate if this is a text object
    bool centerText;

public:
    // Constructor for figures
    PrintObject(const std::string& _name, uint16_t _width, uint16_t _height, uint16_t _x_position, uint16_t _y_position, std::array<uint16_t, 3> _color)
        : name(_name), width(_width), height(_height), x_position(_x_position), y_position(_y_position), color(_color), isText(false), centerText(false) {}

    // Constructor for images (sets default values)
    explicit PrintObject(const std::string& _name, uint16_t _width, uint16_t _height, uint16_t _x_position, uint16_t _y_position)
        : name(_name), width(_width), height(_height), x_position(_x_position), y_position(_y_position), color{255, 255, 255}, isText(false), centerText(false) {}

    // Constructor for text
    PrintObject(const std::string& _name, uint16_t _x_position, uint16_t _y_position, std::array<uint16_t, 3> _color, 
                const std::string& _text, const std::string& fontPath, uint16_t _text_size, bool centerText)
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

    uint16_t getHeight() const { return height; }
    void setHeight(uint16_t _height) {
        if (_height >= 0) {
            height = _height;
        } else {
            std::cerr << "Height cannot be negative." << std::endl;
        }
    }

    uint16_t getWidth() const { return width; }
    void setWidth(uint16_t _width) {
        if (_width >= 0) {
            width = _width;
        } else {
            std::cerr << "Width cannot be negative." << std::endl;
        }
    }

    uint16_t getX_position() const { return x_position; }
    void setX_position(uint16_t _x_position) { x_position = _x_position; }

    uint16_t getY_position() const { return y_position; }
    void setY_position(uint16_t _y_position) { y_position = _y_position; }

    void getColor(uint16_t& r, uint16_t& g, uint16_t& b) const {
        r = color[0];
        g = color[1];
        b = color[2];
    }

    void setColor(uint16_t r, uint16_t g, uint16_t b) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }

    sf::Font& getFontSise() {
        return font;
    }

    // Setter for font size
    void setFontSize(uint16_t newFontSize) {
        if (newFontSize > 0) { // Ensure font size is valid
            textObj.setCharacterSize(newFontSize);
        } else {
            std::cerr << "Error: Font size must be greater than 0." << std::endl;
        }
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


void updateFontSize(std::vector<std::shared_ptr<PrintObject>>& textObject, size_t index, int newFontSize) {
    if (index >= textObject.size()) {
        std::cerr << "Error: Index out of range." << std::endl;
        return;
    }

    // Update the font size of the PrintObject at the given index
    textObject[index]->setFontSize(newFontSize);
}


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


std::vector<std::shared_ptr<PrintObject>> createSheet(
    bool hasTitle,
    uint16_t page_beggining_h,
    uint16_t page_beggining_v,
    uint16_t step_size, 
    const ScreenParams& screen,
    const std::vector<LineTextParams>& topics,
    const LineTextParams& title
) {
    // Crear el vector de PrintObjects como shared_ptr
    std::vector<std::shared_ptr<PrintObject>> PrintObjects;
    uint16_t next_line = 0;

    if (hasTitle){
        // Añadir objetos al vector usando std::make_shared
        PrintObjects.push_back(
            std::make_shared<PrintObject>(
                title.name, 
                title.x_position, 
                title.y_position, 
                title.color, 
                title.text, 
                title.fontPath, 
                title.textSize, 
                title.centered
            )
        );
        next_line = title.y_position + step_size * 2;
    } else {next_line = screen.topMargin + page_beggining_h;}

    for (const auto& topic : topics) {
        PrintObjects.push_back(std::make_shared<PrintObject>(
            topic.name, screen.leftMargin + page_beggining_v, next_line, topic.color,
            topic.text, topic.fontPath, topic.textSize, topic.centered
        ));
        next_line = next_line + step_size;
    }

    return PrintObjects;
}



void drawPrintObjects(sf::RenderWindow& window, const std::vector<std::shared_ptr<PrintObject>>& PrintObjects) {
    for (const auto& obj : PrintObjects) {
        obj->draw(window);
    }
}

uint16_t initAndStartMainWindowLoop(){

    // Create the grid using the function
    auto grid = createGrid(SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE);

    // Create a window
    sf::RenderWindow window(sf::VideoMode(generalScreen.screenWidth, generalScreen.screenHeight), WINDOW_TITLE);


    // Create PrintObject objects
    PrintObject* background = new PrintObject(BACKGROUND_IMAGE_OBJ, generalScreen.screenWidth, generalScreen.screenHeight, 0, 0);
    if (!background->loadTexture(IMAGES_PATH + BACKGROUND_IMAGE_FILE)) {
        return -1; // Exit if texture loading fails
    }

    // Create PrintObject objects
    PrintObject* cpp150 = new PrintObject(CPP150_IMAGE_OBJ, 100, 100, grid[8][56].x , grid[4][56].y);
    if (!cpp150->loadTexture(ICONS_PATH + CPP150_IMAGE_FILE)) {
        return -1; // Exit if texture loading fails
    }

    // Create PrintObject objects
    PrintObject* soundON = new PrintObject(SOUND_ON_OBJ, 50, 50, grid[122][1].x, grid[122][1].y);
    if (!soundON->loadTexture(ICONS_PATH + SOUND_ON_FILE)) {
        return -1; // Exit if texture loading fails
    }

    // Create PrintObject objects
    PrintObject* soundOFF = new PrintObject(SOUND_OFF_OBJ, 50, 50, grid[122][1].x, grid[122][1].y);
    if (!soundOFF->loadTexture(ICONS_PATH + SOUND_OFF_FILE)) {
        return -1; // Exit if texture loading fails
    }

    std::shared_ptr<PrintObject> UP_button;
    // Create vector with text objects
    std::vector<std::shared_ptr<PrintObject>> textObjects = createSheet(true, 0, general4BlocksX.blockX2, 50, generalScreen , generalTopics, mainMenuParams);

    std::shared_ptr<sf::Music> music = loadAndPlayMusic();
    bool isMusicPlaying = true; // Initial sound state

    // Main window loop
    int8_t types = 0;
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

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        updateFontSize(textObjects, types, 30);  // Reset previous font size to 30
                        types--;  // Decrease index
                        if (types < 0) {  // If index is out of bounds, wrap around to the last element
                            types = textObjects.size() - 1;
                        }
                        updateFontSize(textObjects, types, 38);  // Update new font size to 38
                        break;
                    case sf::Keyboard::Down:
                        updateFontSize(textObjects, types, 30);  // Reset previous font size to 30
                        types++;  // Increase index
                        if (types >= textObjects.size()) {  // If index exceeds size, reset to 0
                            types = 0;
                        }
                        updateFontSize(textObjects, types, 38);  // Update new font size to 38
                        break;
                    default:
                        break;
                }
            }
        }

        // Draw Blocks
        window.clear();
        background->draw(window);
        cpp150->draw(window);
        if (UP_button) {
            UP_button->draw(window);
        }
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
