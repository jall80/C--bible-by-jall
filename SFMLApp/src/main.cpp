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
const std::string RETRO_FONTH_PATH = FONTS_PATH + "retro_computer.ttf";

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

LineTextParams mainMenuParams = {"mainMenu", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "MAIN MENU", RETRO_FONTH_PATH, 40, true};

std::vector<LineTextParams> generalTopics = {
    {"Topic1", 0, 0, CRTGreen, "1. Introduction to C++ Programming", RETRO_FONTH_PATH, 30, false},
    {"Topic2", 0, 0, CRTGreen, "2. Data Types in C++", RETRO_FONTH_PATH, 30, false},
    {"Topic3", 0, 0, CRTGreen, "3. Control Structures in C++", RETRO_FONTH_PATH, 30, false},
    {"Topic4", 0, 0, CRTGreen, "4. Functions and Parameters in C++", RETRO_FONTH_PATH, 30, false},
    {"Topic5", 0, 0, CRTGreen, "5. Object-Oriented Programming Concepts", RETRO_FONTH_PATH, 30, false},
    {"Topic6", 0, 0, CRTGreen, "6. Memory Management", RETRO_FONTH_PATH, 30, false},
    {"Topic7", 0, 0, CRTGreen, "7. Standard Template Library (STL)", RETRO_FONTH_PATH, 30, false},
    {"Topic8", 0, 0, CRTGreen, "8. File Handling in C++", RETRO_FONTH_PATH, 30, false},
    {"Topic9", 0, 0, CRTGreen, "9. Error Handling and Debugging", RETRO_FONTH_PATH, 30, false},
    {"Topic10", 0, 0, CRTGreen, "10. Advanced Topics in C++", RETRO_FONTH_PATH, 30, false}
};

LineTextParams introMenuParams = {"MenuIntroduction", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "1. INTRODUCTION TO C++ PROGRAMMING", RETRO_FONTH_PATH, 40, true};

std::vector<LineTextParams> introductionTopics = {
    {"Topic1-1", 0, 0, CRTGreen, "1. History and Overview of C++", RETRO_FONTH_PATH, 30, false},
    {"Topic1-2", 0, 0, CRTGreen, "2. Setting Up the Development Environment", RETRO_FONTH_PATH, 30, false},
    {"Topic1-3", 0, 0, CRTGreen, "3. Basic Syntax and Structure", RETRO_FONTH_PATH, 30, false},
};


//////////////////////////////////////

//////////////////////////////////

class BaseObject {
protected:
    uint16_t height;
    uint16_t width;
    uint16_t x_position;
    uint16_t y_position;
    std::string name;

public:
    // Constructor
    BaseObject(const std::string& _name, uint16_t _width, uint16_t _height, uint16_t _x_position, uint16_t _y_position)
        : name(_name), width(_width), height(_height), x_position(_x_position), y_position(_y_position) {}

    // Destructor
    virtual ~BaseObject() = default;

    // Getters
    std::string getName() const { return name; }
    uint16_t getHeight() const { return height; }
    uint16_t getWidth() const { return width; }
    uint16_t getXPosition() const { return x_position; }
    uint16_t getYPosition() const { return y_position; }

    // Setters
    void setName(const std::string& _name) { name = _name; }
    void setHeight(uint16_t _height) { height = _height; }
    void setWidth(uint16_t _width) { width = _width; }
    void setXPosition(uint16_t _x_position) { x_position = _x_position; }
    void setYPosition(uint16_t _y_position) { y_position = _y_position; }
};

// Clase derivada TextureObject
class TextureObject : public BaseObject {
private:
    sf::Texture texture;         // Textura para el objeto
    sf::Sprite textureSprite;    // Sprite para dibujar el objeto

public:
    // Constructor
    TextureObject(const std::string& _name, uint16_t _width, uint16_t _height, uint16_t _x_position, uint16_t _y_position)
        : BaseObject(_name, _width, _height, _x_position, _y_position) {}

    // Destructor
    virtual ~TextureObject() {
        std::cout << "Destroying TextureObject: " << name << std::endl;
    }

    // Función para cargar la textura
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

    // Función para dibujar el objeto en la pantalla
    void draw(sf::RenderWindow& window) {
        window.draw(textureSprite);
    }
};


class TextObject : public BaseObject {
private:
    std::array<uint16_t, 3> color;  // RGB color
    sf::Font font;                  // Font for the text
    sf::Text textObj;               // SFML Text object
    bool centerText;                // Flag to indicate if the text is center-aligned

public:
    // Constructor for text objects
    TextObject(const std::string& _name, uint16_t _x_position, uint16_t _y_position, std::array<uint16_t, 3> _color,
               const std::string& _text, const std::string& fontPath, uint16_t _text_size, bool _centerText)
        : BaseObject(_name, 0, 0, _x_position, _y_position), color(_color), centerText(_centerText) {

        // Load the font
        if (!font.loadFromFile(fontPath)) {
            throw std::runtime_error("Failed to load font: " + fontPath);
        }

        textObj.setFont(font);
        textObj.setString(_text);
        textObj.setCharacterSize(_text_size);
        textObj.setFillColor(sf::Color(color[0], color[1], color[2]));

        // Center or left align the text
        sf::FloatRect textBounds = textObj.getLocalBounds();

        if (centerText) {
            // Center-align the text
            textObj.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
        } else {
            // Left-align the text
            textObj.setOrigin(0, textBounds.top + textBounds.height / 2); // Only vertically centered
        }

        // Set the position of the text object
        textObj.setPosition(static_cast<float>(_x_position), static_cast<float>(_y_position));
    }

    // Destructor
    virtual ~TextObject() {
        std::cout << "Destroying TextObject: " << name << std::endl;
    }

    // Getters for color
    void getColor(uint16_t& r, uint16_t& g, uint16_t& b) const {
        r = color[0];
        g = color[1];
        b = color[2];
    }

    // Setters for color
    void setColor(uint16_t r, uint16_t g, uint16_t b) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
        textObj.setFillColor(sf::Color(color[0], color[1], color[2]));
    }

    // Setter for font size
    void setFontSize(uint16_t newFontSize) {
        if (newFontSize > 0) { // Ensure font size is valid
            textObj.setCharacterSize(newFontSize);
        } else {
            std::cerr << "Error: Font size must be greater than 0." << std::endl;
        }
    }

    // Draw the text object on the window
    void draw(sf::RenderWindow& window) {
        window.draw(textObj);
    }
};

class MenuObject : public TextObject {
private:
    std::vector<LineTextParams> lineTextParams; // Vector de estructuras LineTextParams
    std::vector<MenuObject> childMenus;        // Vector de objetos MenuObject (solo para mainMenu)

public:
    // Constructor para mainMenu
    MenuObject(const std::string& _name, uint16_t _x_position, uint16_t _y_position, 
               std::array<uint16_t, 3> _color, const std::string& _text, 
               const std::string& fontPath, uint16_t _text_size, bool _centerText, 
               const std::vector<LineTextParams>& _lineTextParams, 
               const std::vector<MenuObject>& _childMenus)
        : TextObject(_name, _x_position, _y_position, _color, _text, fontPath, _text_size, _centerText),
          lineTextParams(_lineTextParams), childMenus(_childMenus) {}

    // Constructor para subMenu
    MenuObject(const std::string& _name, uint16_t _x_position, uint16_t _y_position, 
               std::array<uint16_t, 3> _color, const std::string& _text, 
               const std::string& fontPath, uint16_t _text_size, bool _centerText, 
               const std::vector<LineTextParams>& _lineTextParams)
        : TextObject(_name, _x_position, _y_position, _color, _text, fontPath, _text_size, _centerText),
          lineTextParams(_lineTextParams), childMenus({}) {}

    // Destructor
    ~MenuObject() {
        std::cout << "Destroying MenuObject: " << getName() << std::endl;
    }

    // Add a new line to the vector
    void addLine(const LineTextParams& line) {
        lineTextParams.push_back(line);
    }

    // Remove a line from the vector (by index)
    void removeLine(size_t index) {
        if (index < lineTextParams.size()) {
            lineTextParams.erase(lineTextParams.begin() + index);
        } else {
            std::cerr << "Error: Invalid index for removeLine." << std::endl;
        }
    }

    // Add a child menu (only for mainMenu)
    void addChildMenu(const MenuObject& childMenu) {
        childMenus.push_back(childMenu);
    }

    // Getters
    const std::vector<LineTextParams>& getLineTextParams() const {
        return lineTextParams;
    }

    const std::vector<MenuObject>& getChildMenus() const {
        return childMenus;
    }

    // Draw the menu object and all its lines
    void draw(sf::RenderWindow& window) {
        // Draw the main text object
        TextObject::draw(window);

        // Draw additional lines
        for (const auto& line : lineTextParams) {
            sf::Text tempText;
            sf::Font tempFont;
            if (!tempFont.loadFromFile(line.fontPath)) {
                std::cerr << "Error: Could not load font from path: " << line.fontPath << std::endl;
                continue;
            }

            tempText.setFont(tempFont);
            tempText.setString(line.text);
            tempText.setCharacterSize(line.textSize);
            tempText.setFillColor(sf::Color(line.color[0], line.color[1], line.color[2]));

            // Center text if required
            if (line.centered) {
                sf::FloatRect textBounds = tempText.getLocalBounds();
                tempText.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
            } else {
                tempText.setOrigin(0, 0); // No centering
            }

            tempText.setPosition(static_cast<float>(line.x_position), static_cast<float>(line.y_position));
            window.draw(tempText);
        }

        // Si childMenus contiene objetos no constantes
        for (auto& childMenu : childMenus) {  // Usa auto& en lugar de const auto&
            childMenu.draw(window);
        }
    }
};

//////////////////////////////////////////

void updateFontSize(std::vector<std::shared_ptr<TextObject>>& textObject, size_t index, int newFontSize) {
    if (index >= textObject.size()) {
        std::cerr << "Error: Index out of range." << std::endl;
        return;
    }

    // Update the font size of the TextObject at the given index
    textObject[index]->setFontSize(newFontSize);
}

// Search in vector of objects
const BaseObject& getTopicByIndex(const std::vector<BaseObject>& topics, size_t index) {
    if (index >= topics.size()) {
        throw std::out_of_range("Index out of range");
    }
    return topics[index];
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


std::vector<std::shared_ptr<TextObject>> createSheet(
    bool hasTitle,
    uint16_t page_beggining_h,
    uint16_t page_beggining_v,
    uint16_t step_size, 
    const ScreenParams& screen,
    const std::vector<LineTextParams>& topics,
    const LineTextParams& title
) {
    // Crear el vector de TextObjects como shared_ptr
    std::vector<std::shared_ptr<TextObject>> TextObjects;
    uint16_t next_line = 0;

    if (hasTitle){
        // Añadir objetos al vector usando std::make_shared
        TextObjects.push_back(
            std::make_shared<TextObject>(
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
        TextObjects.push_back(std::make_shared<TextObject>(
            topic.name, screen.leftMargin + page_beggining_v, next_line, topic.color,
            topic.text, topic.fontPath, topic.textSize, topic.centered
        ));
        next_line = next_line + step_size;
    }

    return TextObjects;
}



void drawTextObjects(sf::RenderWindow& window, const std::vector<std::shared_ptr<TextObject>>& TextObjects) {
    for (const auto& obj : TextObjects) {
        obj->draw(window);
    }
}


uint16_t initAndStartMainWindowLoop(){

    // Create the grid using the function
    auto grid = createGrid(SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE);

    // Create a window
    sf::RenderWindow window(sf::VideoMode(generalScreen.screenWidth, generalScreen.screenHeight), WINDOW_TITLE);


    // Create PrintObject objects
    TextureObject* background = new TextureObject(BACKGROUND_IMAGE_OBJ, generalScreen.screenWidth, generalScreen.screenHeight, 0, 0);
    if (!background->loadTexture(IMAGES_PATH + BACKGROUND_IMAGE_FILE)) {
        return -1; // Exit if texture loading fails
    }

    // Create PrintObject objects
    TextureObject* cpp150 = new TextureObject(CPP150_IMAGE_OBJ, 100, 100, grid[8][56].x , grid[4][56].y);
    if (!cpp150->loadTexture(ICONS_PATH + CPP150_IMAGE_FILE)) {
        return -1; // Exit if texture loading fails
    }

    // Create PrintObject objects
    TextureObject* soundON = new TextureObject(SOUND_ON_OBJ, 50, 50, grid[122][1].x, grid[122][1].y);
    if (!soundON->loadTexture(ICONS_PATH + SOUND_ON_FILE)) {
        return -1; // Exit if texture loading fails
    }

    // Create PrintObject objects
    TextureObject* soundOFF = new TextureObject(SOUND_OFF_OBJ, 50, 50, grid[122][1].x, grid[122][1].y);
    if (!soundOFF->loadTexture(ICONS_PATH + SOUND_OFF_FILE)) {
        return -1; // Exit if texture loading fails
    }

    //std::vector<std::shared_ptr<TextObject>> IntroductionMenuObjects = createSheet(true, 0, general4BlocksX.blockX2, 80, generalScreen , introductionTopics, introMenuParams);
    // Create vector with text objects
    std::vector<std::shared_ptr<TextObject>> MenuObjects = createSheet(true, 0, general4BlocksX.blockX2, 50, generalScreen , generalTopics, mainMenuParams);


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
                        updateFontSize(MenuObjects, types, 30);  // Reset previous font size to 30
                        types--;  // Decrease index
                        if (types < 0) {  // If index is out of bounds, wrap around to the last element
                            types = MenuObjects.size() - 1;
                        }
                        updateFontSize(MenuObjects, types, 38);  // Update new font size to 38
                        break;
                    case sf::Keyboard::Down:
                        updateFontSize(MenuObjects, types, 30);  // Reset previous font size to 30
                        types++;  // Increase index
                        if (types >= MenuObjects.size()) {  // If index exceeds size, reset to 0
                            types = 0;
                        }
                        updateFontSize(MenuObjects, types, 38);  // Update new font size to 38
                        break;
                    case sf::Keyboard::Enter:
                        //updateFontSize(MenuObjects, types, 20);  // Update new font size to 38
                        //const PrintObject& selectedTopic = getTopicByIndex(MenuObjects, type);
                        if(types == 1){
                            MenuObjects = createSheet(true, 0, general4BlocksX.blockX2, 80, generalScreen , introductionTopics, introMenuParams);
                        }
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
        soundON->draw(window);
        drawTextObjects(window, MenuObjects);
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
