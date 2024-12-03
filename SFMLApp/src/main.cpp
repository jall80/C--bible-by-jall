#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <array>
//#include <memory> // EVALUATE USING THIS LIBRARY IN ORDER TO IMPROVE MEMORY HANDLING
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
std::vector<std::vector<Block>> createGrid(int width, int height, int blockSize) {
    // Calculate the number of columns and rows
    int cols = width / blockSize;
    int rows = height / blockSize;

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
    uint16_t width;
    uint16_t height;
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

uint16_t FourblocksSize = (generalScreen.width - (generalScreen.leftMargin + generalScreen.rightMargin))/4;

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

std::vector<LineTextParams> introductionTopics = {
    {"MenuIntroduction", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "1. INTRODUCTION TO C++ PROGRAMMING", RETRO_FONTH_PATH, 40, true},
    {"Topic1-1", 0, 0, CRTGreen, "1. History and Overview of C++", RETRO_FONTH_PATH, 30, false},
    {"Topic1-2", 0, 0, CRTGreen, "2. Setting Up the Development Environment", RETRO_FONTH_PATH, 30, false},
    {"Topic1-3", 0, 0, CRTGreen, "3. Basic Syntax and Structure", RETRO_FONTH_PATH, 30, false},
};


std::vector<LineTextParams> dataTypesTopics = {
    {"MenuDataTypes", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "2. Data Types in C++", RETRO_FONTH_PATH, 40, true},
    {"Topic2-1", 0, 0, CRTGreen, "1. Integral Types", RETRO_FONTH_PATH, 30, false},
    {"Topic2-2", 0, 0, CRTGreen, "2. Floating-point Types", RETRO_FONTH_PATH, 30, false},
    {"Topic2-3", 0, 0, CRTGreen, "3. Character Types", RETRO_FONTH_PATH, 30, false},
    {"Topic2-4", 0, 0, CRTGreen, "4. Boolean Type", RETRO_FONTH_PATH, 30, false},
    {"Topic2-5", 0, 0, CRTGreen, "5. Void Type", RETRO_FONTH_PATH, 30, false},
};


std::vector<LineTextParams> TopicIntegralTypes = {
    {"IntegralTypes", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "1. Integral Types", RETRO_FONTH_PATH, 40, true},
    {"Description", 0, 0, CRTGreen, "1. Description", RETRO_FONTH_PATH, 30, false},
    {"Example", 0, 0, CRTGreen, "2. Example", RETRO_FONTH_PATH, 30, false},
    {"Practice", 0, 0, CRTGreen, "3. Practice", RETRO_FONTH_PATH, 30, false},
};

std::vector<LineTextParams> TopicFloatingpointTypes = {
    {"Floating-pointTypes", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "2. Floating-point Types", RETRO_FONTH_PATH, 40, true},
    {"Description", 0, 0, CRTGreen, "1. Description", RETRO_FONTH_PATH, 30, false},
    {"Example", 0, 0, CRTGreen, "2. Example", RETRO_FONTH_PATH, 30, false},
    {"Practice", 0, 0, CRTGreen, "3. Practice", RETRO_FONTH_PATH, 30, false},
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
    std::array<uint16_t, 3> color;   // RGB color
    sf::Font font;                  // Font for the text
    sf::Text textObj;               // SFML Text object
    bool centerText;                // Flag to indicate if the text is center-aligned
    std::string fontPath;           // Path to the font file
    std::vector<std::shared_ptr<TextObject>> children; // Child nodes

public:
    // Constructor
    TextObject(const std::string& _name, uint16_t _x_position, uint16_t _y_position, 
               std::array<uint16_t, 3> _color, const std::string& _text, const std::string& _fontPath, 
               uint16_t _text_size, bool _centerText)
        : BaseObject(_name, 0, 0, _x_position, _y_position), color(_color), fontPath(_fontPath), centerText(_centerText) {

        if (!font.loadFromFile(fontPath)) {
            throw std::runtime_error("Failed to load font: " + fontPath);
        }

        textObj.setFont(font);
        textObj.setString(_text);
        textObj.setCharacterSize(_text_size);
        textObj.setFillColor(sf::Color(color[0], color[1], color[2]));

        sf::FloatRect textBounds = textObj.getLocalBounds();
        if (centerText) {
            textObj.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
        } else {
            textObj.setOrigin(0, textBounds.top + textBounds.height / 2);
        }

        textObj.setPosition(static_cast<float>(_x_position), static_cast<float>(_y_position));
    }


    // Destructor
    virtual ~TextObject() {
        std::cout << "Destroying TextObject: " << name << std::endl;
    }

    // Add a child node
    void addChild(std::shared_ptr<TextObject> child) {
        children.push_back(child);
    }

    // Get children
    const std::vector<std::shared_ptr<TextObject>>& getChildren() const {
        return children;
    }

    // Draw the text object and its children recursively
    void draw(sf::RenderWindow& window) {
        window.draw(textObj);
        for (const auto& child : children) {
            child->draw(window);
        }
    }

    // Print hierarchy for debugging
    void printHierarchy(int level = 0) const {
        std::string indentation(level * 2, ' ');
        std::cout << indentation << "- " << name << std::endl;
        for (const auto& child : children) {
            child->printHierarchy(level + 1);
        }
    }

    // Sincroniza las coordenadas con el objeto SFML
    void updateTextPosition() {
        textObj.setPosition(static_cast<float>(x_position), static_cast<float>(y_position));
    }

    // Set font size for the text object and optionally its children
    void setFontSize(uint16_t newFontSize, bool applyToChildren = false) {
        textObj.setCharacterSize(newFontSize);
        if (applyToChildren) {
            for (auto& child : children) {
                child->setFontSize(newFontSize, applyToChildren);
            }
        }
    }

    // Getters for required attributes
    std::array<uint16_t, 3> getColor() const {
        return color;
    }

    std::string getText() const {
        return textObj.getString();
    }

    std::string getFontPath() const {
        return fontPath;
    }

    uint16_t getTextSize() const {
        return textObj.getCharacterSize();
    }

    bool isCentered() const {
        return centerText;
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
    if (!music->openFromFile(AUDIOS_PATH + "MASTER_BOOT_RECORD_INTERRUPT_REQUEST.mp3")) {
        std::cerr << "Error loading music.\n";
        return nullptr; // Return nullptr to indicate failure
    }
    music->play();
    music->setLoop(true);
    return music;
}


// Función para dibujar los nodos existentes, comenzando desde un nodo raíz
void drawSheetFromRoot(
    const std::shared_ptr<TextObject>& rootNode,
    const ScreenParams& screen,
    sf::RenderWindow& window,
    uint16_t step_size
) {
    if (!rootNode) {
        std::cerr << "Error: Root node is null." << std::endl;
        return;
    }

    uint16_t next_line = step_size * 2; // Comenzar desde una posición vertical más centrada

    // Dibujar el nodo raíz centrado
    uint16_t root_x_position = general4BlocksX.blockX2; // Ajustar para centrar en la pantalla
    rootNode->setXPosition(root_x_position);  // Ajustar posición en X
    rootNode->setYPosition(next_line);       // Ajustar posición en Y
    rootNode->updateTextPosition();
    rootNode->draw(window); // Dibujar el nodo raíz

    next_line += step_size * 2; // Espacio adicional debajo del nodo raíz

    // Dibujar los hijos del nodo raíz
    const auto& children = rootNode->getChildren();
    for (const auto& child : children) {
        // Calcular la posición centrada para cada hijo
        uint16_t child_x_position = general4BlocksX.blockX2;
        child->setXPosition(child_x_position); // Actualizar posición X del hijo
        child->setYPosition(next_line);        // Actualizar posición Y del hijo
        child->updateTextPosition();
        child->draw(window); // Dibujar el hijo
        
        next_line += step_size; // Avanzar a la siguiente línea
    }
}


void populateRootWithSubtopics(
    const std::shared_ptr<TextObject>& root,
    std::vector<std::shared_ptr<TextObject>> subTopics)
{
    for (const auto& child : subTopics) {
        root->addChild(child);
    }
}

std::vector<std::shared_ptr<TextObject>> createTextObjects(const std::vector<LineTextParams>& params) {
    std::vector<std::shared_ptr<TextObject>> textObjects;

    for (const auto& param : params) {
        auto textObject = std::make_shared<TextObject>(
            param.name, 
            param.x_position, 
            param.y_position, 
            param.color, 
            param.text, 
            param.fontPath, 
            param.textSize, 
            param.centered
        );

        textObjects.push_back(textObject);
    }

    return textObjects;
}


uint16_t initAndStartMainWindowLoop(){

    // Create the grid using the function
    auto grid = createGrid(SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE);

    // Create a window
    sf::RenderWindow window(sf::VideoMode(generalScreen.width, generalScreen.height), WINDOW_TITLE);


    // Create PrintObject objects
    TextureObject* background = new TextureObject(BACKGROUND_IMAGE_OBJ, generalScreen.width, generalScreen.height, 0, 0);
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

     // Create the root object
        auto mainMenu = std::make_shared<TextObject>(
        mainMenuParams.name,
        mainMenuParams.x_position,
        mainMenuParams.y_position,
        mainMenuParams.color,
        mainMenuParams.text,
        mainMenuParams.fontPath,
        mainMenuParams.textSize,
        mainMenuParams.centered
    );

    // Create TextObjects from generalTopics struct
    auto subTopics = createTextObjects(generalTopics);

    //Assing subTopics as children nodes to mainMenu root node
    populateRootWithSubtopics(mainMenu, subTopics);

    // Get children from root node
    const auto& mainMenuSubs = mainMenu->getChildren();

    // Create music pointer
    std::shared_ptr<sf::Music> music = loadAndPlayMusic();
    bool isMusicPlaying = true; // Initial sound state

    // Main window loop
    int8_t types = 0;
    int8_t context = 0;
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
                        mainMenuSubs[types]->setFontSize(30);  // Reset previous font size to 30
                        types--;  // Decrease index
                        
                        if (types < 0) {  // If index is out of bounds, wrap around to the last element
                            types = mainMenuSubs.size() - 1;
                        }
                        
                        mainMenuSubs[types]->setFontSize(38);  // Update new font size to 38
                        break;
                    case sf::Keyboard::Down:
                        mainMenuSubs[types]->setFontSize(30);  // Reset previous font size to 30
                        types++;  // Increase index
                        
                        if (types >= mainMenuSubs.size()) {  // If index exceeds size, reset to 0
                            types = 0;
                        }
                        
                        mainMenuSubs[types]->setFontSize(38);  // Update new font size to 38
                        break;
                    // I MUST FINISH THIS PART :)
                    case sf::Keyboard::Enter:

                        if(types != 0){

                            context = 1;
                        }
                        break;
                    case sf::Keyboard::Left:
                        if (context == 1){
   
                            context = 0;
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
        drawSheetFromRoot(mainMenu, generalScreen, window, 50);

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