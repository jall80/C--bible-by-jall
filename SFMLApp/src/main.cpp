#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <array>
#include <memory> // EVALUATE USING THIS LIBRARY IN ORDER TO IMPROVE MEMORY HANDLING
#include <filesystem> // For filesystem operations
#include <cstdint>
#include <optional>

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
    std::optional<std::vector<LineTextParams>> subtopics;
    int depth;
};

//{"Floating-pointTypes", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "2. Floating-point Types", RETRO_FONTH_PATH, 40, true},

std::vector<LineTextParams> TopicFloatingpointTypes = {
    {"Description", 0, 0, CRTGreen, "1. Description", RETRO_FONTH_PATH, 30, false, std::nullopt, 3},
    {"Example", 0, 0, CRTGreen, "2. Example", RETRO_FONTH_PATH, 30, false, std::nullopt, 3},
    {"Practice", 0, 0, CRTGreen, "3. Practice", RETRO_FONTH_PATH, 30, false, std::nullopt, 3},
};

//   {"IntegralTypes", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "1. Integral Types", RETRO_FONTH_PATH, 40, true},
std::vector<LineTextParams> TopicIntegralTypes = {
    {"Description", 0, 0, CRTGreen, "1. Description gg", RETRO_FONTH_PATH, 30, false, std::nullopt, 3},
    {"Example", 0, 0, CRTGreen, "2. Example gg", RETRO_FONTH_PATH, 30, false, std::nullopt, 3},
    {"Practice", 0, 0, CRTGreen, "3. Practice gg", RETRO_FONTH_PATH, 30, false, std::nullopt, 3},
};


//{"MenuIntroduction", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "1. INTRODUCTION TO C++ PROGRAMMING", RETRO_FONTH_PATH, 40, true},

std::vector<LineTextParams> introductionTopics = {
    {"Topic1-1", 0, 0, CRTGreen, "1. History and Overview of C++", RETRO_FONTH_PATH, 30, false, std::nullopt, 2},
    {"Topic1-2", 0, 0, CRTGreen, "2. Setting Up the Development Environment", RETRO_FONTH_PATH, 30, false, std::nullopt, 2},
    {"Topic1-3", 0, 0, CRTGreen, "3. Basic Syntax and Structure", RETRO_FONTH_PATH, 30, false, std::nullopt, 2},
};

//{"MenuDataTypes", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "2. Data Types in C++", RETRO_FONTH_PATH, 40, true},
std::vector<LineTextParams> dataTypesTopics = {
    {"Topic2-1", 0, 0, CRTGreen, "1. Integral Types", RETRO_FONTH_PATH, 30, false, TopicIntegralTypes, 2},
    {"Topic2-2", 0, 0, CRTGreen, "2. Floating-point Types", RETRO_FONTH_PATH, 30, false, TopicFloatingpointTypes, 2},
    {"Topic2-3", 0, 0, CRTGreen, "3. Character Types", RETRO_FONTH_PATH, 30, false, std::nullopt, 2},
    {"Topic2-4", 0, 0, CRTGreen, "4. Boolean Type", RETRO_FONTH_PATH, 30, false, std::nullopt, 2},
    {"Topic2-5", 0, 0, CRTGreen, "5. Void Type", RETRO_FONTH_PATH, 30, false, std::nullopt, 2},
};

LineTextParams mainMenuParams = {"mainMenu", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "MAIN MENU", RETRO_FONTH_PATH, 40, true};

std::vector<LineTextParams> generalTopics = {
    {"Topic1", 0, 0, CRTGreen, "1. Introduction to C++ Programming", RETRO_FONTH_PATH, 30, false, introductionTopics, 1},
    {"Topic2", 0, 0, CRTGreen, "2. Data Types in C++", RETRO_FONTH_PATH, 30, false, dataTypesTopics, 1},
    {"Topic3", 0, 0, CRTGreen, "3. Control Structures in C++", RETRO_FONTH_PATH, 30, false, introductionTopics, 1},
    {"Topic4", 0, 0, CRTGreen, "4. Functions and Parameters in C++", RETRO_FONTH_PATH, 30, false, introductionTopics, 1},
    {"Topic5", 0, 0, CRTGreen, "5. Object-Oriented Programming Concepts", RETRO_FONTH_PATH, 30, false, introductionTopics, 1},
    {"Topic6", 0, 0, CRTGreen, "6. Memory Management", RETRO_FONTH_PATH, 30, false, introductionTopics, 1},
    {"Topic7", 0, 0, CRTGreen, "7. Standard Template Library (STL)", RETRO_FONTH_PATH, 30, false, introductionTopics, 1},
    {"Topic8", 0, 0, CRTGreen, "8. File Handling in C++", RETRO_FONTH_PATH, 30, false, introductionTopics, 1},
    {"Topic9", 0, 0, CRTGreen, "9. Error Handling and Debugging", RETRO_FONTH_PATH, 30, false, introductionTopics, 1},
    {"Topic10", 0, 0, CRTGreen, "10. Advanced Topics in C++", RETRO_FONTH_PATH, 30, false, introductionTopics, 1}
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
    std::weak_ptr<TextObject> parent;

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

    // Método para establecer el padre
    void setParent(const std::shared_ptr<TextObject>& _parent) {
        parent = _parent;
    }

    // Método para obtener el padre
    std::shared_ptr<TextObject> getParent() const {
        return parent.lock(); // Convierte el weak_ptr en shared_ptr si es válido
    }


    // Add a child node
    void addChild(std::shared_ptr<TextObject> child) {
        children.push_back(child);
    }

    // Get children
    const std::vector<std::shared_ptr<TextObject>>& getChildren() const {
        return children;
    }


    // Draw the text object and its children recursively (ELIMINATE recursively OR ADD IT IN ANOTHER FUNCTION )
    void draw(sf::RenderWindow& window) {
        window.draw(textObj);
        /*
        for (const auto& child : children) {
            child->draw(window);
        }
        */
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

    bool isLeaf() const {
    return children.empty();
    }

    // Método para eliminar todos los hijos
    void removeAllChildren() {
        for (auto& child : children) {
            // Romper la relación del hijo con este nodo como su padre
            if (auto sharedChild = child->getParent()) {
                if (sharedChild.get() == this) {
                    child->setParent(nullptr);
                }
            }
        }
        children.clear(); // Vaciar el vector de hijos
    }

};


// Función recursiva para calcular la profundidad máxima del árbol
int getMaxDepth(const std::shared_ptr<TextObject>& node) {
    if (!node) {
        return 0; // Árbol vacío
    }

    int maxDepth = 0;
    for (const auto& child : node->getChildren()) {
        maxDepth = std::max(maxDepth, getMaxDepth(child));
    }

    return maxDepth + 1; // 0 has not children (leaf node)/ 1 has at least one child
}

std::vector<LineTextParams> findNestedSubtopics(
    const std::vector<LineTextParams>& generalTopics,
    const std::vector<int>& indices
) {
    const std::vector<LineTextParams>* currentLevel = &generalTopics;

    for (int index : indices) {
        if (index < 0 || index >= currentLevel->size()) {
            throw std::out_of_range("Índice fuera de rango en generalTopics o subtopics.");
        }

        const LineTextParams& selectedTopic = (*currentLevel)[index];
        if (!selectedTopic.subtopics.has_value()) {
            // Si no hay subtopics, retornamos un vector vacío
            std::cerr << "Leaf node found. No more submenus.\n";
            return {};
        }

        // Moverse al siguiente nivel
        currentLevel = &selectedTopic.subtopics.value();
    }

    // Retornar el último nivel de subtopics como vector
    return *currentLevel;
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
        child->setParent(root);
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


void createTree(const std::shared_ptr<TextObject>& root, 
                const std::vector<LineTextParams>& nodes, 
                int maxDepth, 
                int currentDepth = 1) {
    if (!root || currentDepth > maxDepth) {
        return; // Base case: If root is null or max depth is reached, do nothing.
    }

    // Step 1: Create child nodes from the current level of LineTextParams.
    auto subTopics = createTextObjects(nodes);
    
    // Step 2: Populate the root node with these children.
    populateRootWithSubtopics(root, subTopics);

    // Step 3: Recursively process each node's subtopics, if present and within depth.
    for (size_t i = 0; i < nodes.size(); ++i) {
        const auto& node = nodes[i];
        if (node.subtopics.has_value()) {
            // If the node has subtopics, recursively create a tree for them.
            createTree(subTopics[i], node.subtopics.value(), maxDepth, currentDepth + 1);
        }
    }
}


uint16_t initAndStartMainWindowLoop() {
    // Initialize the grid based on screen dimensions and block size
    auto grid = createGrid(SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE);

    // Create the main application window
    sf::RenderWindow window(sf::VideoMode(generalScreen.width, generalScreen.height), WINDOW_TITLE);

    // Create the background texture object and load its texture
    TextureObject* background = new TextureObject(BACKGROUND_IMAGE_OBJ, generalScreen.width, generalScreen.height, 0, 0);
    if (!background->loadTexture(IMAGES_PATH + BACKGROUND_IMAGE_FILE)) {
        return -1; // Exit if the background texture fails to load
    }

    // Create the cpp150 icon texture object and load its texture
    TextureObject* cpp150 = new TextureObject(CPP150_IMAGE_OBJ, 100, 100, grid[8][56].x , grid[4][56].y);
    if (!cpp150->loadTexture(ICONS_PATH + CPP150_IMAGE_FILE)) {
        return -1; // Exit if the icon texture fails to load
    }

    // Create the "Sound ON" icon texture object and load its texture
    TextureObject* soundON = new TextureObject(SOUND_ON_OBJ, 50, 50, grid[122][1].x, grid[122][1].y);
    if (!soundON->loadTexture(ICONS_PATH + SOUND_ON_FILE)) {
        return -1; // Exit if the texture fails to load
    }

    // Create the "Sound OFF" icon texture object and load its texture
    TextureObject* soundOFF = new TextureObject(SOUND_OFF_OBJ, 50, 50, grid[122][1].x, grid[122][1].y);
    if (!soundOFF->loadTexture(ICONS_PATH + SOUND_OFF_FILE)) {
        return -1; // Exit if the texture fails to load
    }

    // Initialize the main menu as the root object for the tree structure
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

    // Build the hierarchical tree structure starting from the root menu
    createTree(mainMenu, generalTopics, 1);

    // A vector to store the navigation path through the menu hierarchy
    std::vector<int> indices = {};

    // Load and start playing background music
    std::shared_ptr<sf::Music> music = loadAndPlayMusic();
    bool isMusicPlaying = true; // Tracks the current music state (ON/OFF)

    bool change = true; // Tracks if the screen needs to be redrawn
    auto selectedMenu = mainMenu; // Points to the currently selected menu
    std::vector<std::shared_ptr<TextObject>> selectedMenuChildren = mainMenu->getChildren(); // Get children of the current menu
    int8_t types = 0;   // Tracks the currently selected child index
    int8_t context = 0; // Context variable (usage undefined in this scope)

    // Main event-processing and rendering loop
    while (window.isOpen()) {
        sf::Event event;

        // Process all events in the event queue
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                // Close the window when the user presses Escape or closes the window
                window.close();
            }

            // Handle mouse clicks for toggling sound
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                handleSoundButton(soundON->getTextureSprite(), soundON->getTexture(), soundOFF->getTexture(), *music, isMusicPlaying, window);
                change = true; // Mark the screen as needing an update
            }

            // Handle keyboard input for navigation and interaction
            if (event.type == sf::Event::KeyPressed) {
                change = true; // Screen will need an update
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        // Navigate to the previous menu item (wrapping around if necessary)
                        selectedMenuChildren[types]->setFontSize(30);  // Reset font size of the current item
                        types = (types - 1 + selectedMenuChildren.size()) % selectedMenuChildren.size(); // Wrap index
                        selectedMenuChildren[types]->setFontSize(38);  // Highlight new item
                        break;
                    case sf::Keyboard::Down:
                        // Navigate to the next menu item (wrapping around if necessary)
                        selectedMenuChildren[types]->setFontSize(30);  // Reset font size of the current item
                        types = (types + 1) % selectedMenuChildren.size(); // Wrap index
                        selectedMenuChildren[types]->setFontSize(38);  // Highlight new item
                        break;
                    case sf::Keyboard::Enter:
                        // Enter the selected submenu if it's not a leaf node
                        if (!selectedMenu->isLeaf()) {
                            selectedMenuChildren[types]->setFontSize(30); // Reset font size
                            indices.push_back(types); // Add current selection to path
                            auto subtopics = findNestedSubtopics(generalTopics, indices);
                            if (!subtopics.empty()) {
                                createTree(selectedMenu->getChildren()[types], subtopics, 1); // Build submenu
                                selectedMenu = selectedMenu->getChildren()[types]; // Navigate to submenu
                                selectedMenuChildren = selectedMenu->getChildren(); // Update children
                            } else {
                                std::cerr << "No subtopics found." << std::endl;
                                indices.pop_back(); // Remove invalid path step
                            }
                        }
                        break;
                    case sf::Keyboard::Left:
                        // Go back to the parent menu if not at the root
                        if (selectedMenu != mainMenu) {
                            selectedMenu->removeAllChildren(); // Clear current submenu
                            selectedMenu = selectedMenu->getParent(); // Navigate to parent
                            selectedMenuChildren = selectedMenu->getChildren(); // Update children
                            indices.pop_back(); // Remove last path step
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        // Redraw the screen if necessary
        if (change) {
            window.clear();
            background->draw(window); // Draw background
            cpp150->draw(window);     // Draw icon
            soundON->draw(window);    // Draw sound ON icon
            drawSheetFromRoot(selectedMenu, generalScreen, window, 50); // Draw menu
            window.display(); // Display the rendered frame
            change = false;   // Reset update flag
        }
    }

    // Clean up dynamically allocated objects
    delete background;
    delete cpp150;
    delete soundON;
    delete soundOFF;

    return 0; // Indicate successful execution
}


int main() {

    return initAndStartMainWindowLoop();

    //return 0;
}