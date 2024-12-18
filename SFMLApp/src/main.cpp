#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <array>
#include <memory> // EVALUATE USING THIS LIBRARY IN ORDER TO IMPROVE MEMORY HANDLING
#include <filesystem> // For filesystem operations
#include <cstdint>
#include <optional>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <cmath>
#include <stdexcept> // For std::runtime_error
#include <condition_variable>
#include <functional> // Necesario


const std::string AUDIOS_PATH = "audios/";
const std::string IMAGES_PATH = "images/";
const std::string FONTS_PATH = "fonts/";
const std::string ICONS_PATH = "images/icons/";
const std::string RETRO_FONTH_PATH = FONTS_PATH + "retro_computer.ttf";
const std::string MUSIC_FILE = "MASTER_BOOT_RECORD_INTERRUPT_REQUEST.mp3";

const std::string WINDOW_TITLE = "C++ Bible by JALL";
const std::string BACKGROUND_IMAGE_OBJ = "BackgroundImage";
const std::string BACKGROUND_IMAGE_FILE = "realCRT.jpeg";
const std::string SOUND_ON_OBJ = "soundON";
const std::string SOUND_ON_FILE = "soundON.png";
const std::string SOUND_OFF_OBJ = "soundOFF";
const std::string SOUND_OFF_FILE = "soundOFF.png";
const std::string CPP150_IMAGE_OBJ = "cpp150";
const std::string CPP150_IMAGE_FILE = "cpp150.png";


const std::string CPP100FILL_IMAGE_OBJ = "cpp100filled";
const std::string CPP100FILL_IMAGE_FILE = "cpp100filled.png";

const std::string X100_IMAGE_OBJ = "Xicon100";
const std::string X100_IMAGE_FILE = "Xicon100.png";

constexpr std::array<uint16_t, 3> CRTGreen{0, 255, 128};

// For moving object

const int EXTRA_MARGING = 5;
const int MAX_VELOCITY = EXTRA_MARGING - 1;  //This in order to avoid a segmentation fault, when the object meets the margin
const float OVERLAP_PERCENTAGE = 0.8; // 0.5 - 1  1 -> no overlap
const int MIN_SIZE = 50;

//For matrix

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int BLOCK_SIZE = 15;

//Font sizes

const int NORMAL_FONT = 30;
const float FONT_RESIZE = 1.27;
const int BIG_FONT = int(NORMAL_FONT * FONT_RESIZE);
const int MENU_FONT_SIZE = 40;
const int LINE_SPACING = 40;

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


struct StructTextureObject {
    std::string name;
    std::string path;
    uint16_t width;
    uint16_t height;
    uint16_t x_position;
    uint16_t y_position;
    float velocity_x;
    float velocity_y;
};

StructTextureObject iconCpp150 = {"iconCpp150", ICONS_PATH + CPP150_IMAGE_FILE, 150, 150, 0, 0, -1.0f, -2.0f} ;

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
    uint16_t fontSize;
    bool centered;
    std::optional<std::vector<LineTextParams>> subtopics;
    int depth;
};

//{"Floating-pointTypes", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "2. Floating-point Types", RETRO_FONTH_PATH, 40, true},

std::vector<LineTextParams> TopicFloatingpointTypes = {
    {"Description", 0, 0, CRTGreen, "Description", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"Example", 0, 0, CRTGreen, "Example", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"Practice", 0, 0, CRTGreen, "Practice", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
};

//   {"IntegralTypes", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "1. Integral Types", RETRO_FONTH_PATH, 40, true},
std::vector<LineTextParams> TopicIntegralTypes = {
    {"1.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"2.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"3.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},

    {"4.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"5.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"6.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},

    {"7.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"8.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"9.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},

    {"10.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"11.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"12.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},

    {"13.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"14.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"15.Practice", 0, 0, CRTGreen, "GGPractice gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},

    {"16.Description", 0, 0, CRTGreen, "GGDescription gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"17.Example", 0, 0, CRTGreen, "GGExample gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"18.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},

    {"19.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"20.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"21.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 3},
    
};

//{"MenuIntroduction", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "1. INTRODUCTION TO C++ PROGRAMMING", RETRO_FONTH_PATH, 40, true},

std::vector<LineTextParams> introductionTopics = {
    {"Topic1-1", 0, 0, CRTGreen, "History and Overview of C++", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 2},
    {"Topic1-2", 0, 0, CRTGreen, "Setting Up the Development Environment", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 2},
    {"Topic1-3", 0, 0, CRTGreen, "Basic Syntax and Structure", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 2},
};

//{"MenuDataTypes", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "2. Data Types in C++", RETRO_FONTH_PATH, 40, true},
std::vector<LineTextParams> dataTypesTopics = {
    {"Topic2-1", 0, 0, CRTGreen, "Integral Types", RETRO_FONTH_PATH, NORMAL_FONT, false, TopicIntegralTypes, 2},
    {"Topic2-2", 0, 0, CRTGreen, "Floating-point Types", RETRO_FONTH_PATH, NORMAL_FONT, false, TopicFloatingpointTypes, 2},
    {"Topic2-3", 0, 0, CRTGreen, "Character Types", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 2},
    {"Topic2-4", 0, 0, CRTGreen, "Boolean Type", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 2},
    {"Topic2-5", 0, 0, CRTGreen, "Void Type", RETRO_FONTH_PATH, NORMAL_FONT, false, std::nullopt, 2},
};

LineTextParams mainMenuParams = {"mainMenu", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "MAIN MENU", RETRO_FONTH_PATH, MENU_FONT_SIZE, true};

std::vector<LineTextParams> generalTopics = {
    {"Topic1", 0, 0, CRTGreen, "Introduction to C++ Programming", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic2", 0, 0, CRTGreen, "Data Types in C++", RETRO_FONTH_PATH, NORMAL_FONT, false, dataTypesTopics, 1},
    {"Topic3", 0, 0, CRTGreen, "Control Structures in C++", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic4", 0, 0, CRTGreen, "Functions and Parameters in C++", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic5", 0, 0, CRTGreen, "Object-Oriented Programming Concepts", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic6", 0, 0, CRTGreen, "Memory Management", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic7", 0, 0, CRTGreen, "Standard Template Library (STL)", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic8", 0, 0, CRTGreen, "File Handling in C++", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic9", 0, 0, CRTGreen, "Error Handling and Debugging", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic10", 0, 0, CRTGreen, "Advanced Topics in C++", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},

    {"Topic11", 0, 0, CRTGreen, "GGG Introduction to C++ Programming", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic12", 0, 0, CRTGreen, "GGG Data Types in C++", RETRO_FONTH_PATH, NORMAL_FONT, false, dataTypesTopics, 1},
    {"Topic13", 0, 0, CRTGreen, "GGG Control Structures in C++", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic14", 0, 0, CRTGreen, "GGG Functions and Parameters in C++", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic15", 0, 0, CRTGreen, "GGGG Object-Oriented Programming Concepts", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic16", 0, 0, CRTGreen, "GGG Memory Management", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic17", 0, 0, CRTGreen, "GGG Standard Template Library (STL)", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic18", 0, 0, CRTGreen, "GGG File Handling in C++", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic19", 0, 0, CRTGreen, "GGG Error Handling and Debugging", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic20", 0, 0, CRTGreen, "GGG Advanced Topics in C++", RETRO_FONTH_PATH, NORMAL_FONT, false, dataTypesTopics, 1},


    {"Topic11", 0, 0, CRTGreen, "GGG Introduction to C++ Programming", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic12", 0, 0, CRTGreen, "GGG Data Types in C++", RETRO_FONTH_PATH, NORMAL_FONT, false, dataTypesTopics, 1},
    {"Topic13", 0, 0, CRTGreen, "GGG Control Structures in C++", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic14", 0, 0, CRTGreen, "GGG Functions and Parameters in C++", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic15", 0, 0, CRTGreen, "GGGG Object-Oriented Programming Concepts", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic16", 0, 0, CRTGreen, "GGG Memory Management", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic17", 0, 0, CRTGreen, "GGG Standard Template Library (STL)", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic18", 0, 0, CRTGreen, "GGG File Handling in C++", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic19", 0, 0, CRTGreen, "GGG Error Handling and Debugging", RETRO_FONTH_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic20", 0, 0, CRTGreen, "GGG Advanced Topics in C++", RETRO_FONTH_PATH, NORMAL_FONT, false, dataTypesTopics, 1}
};


void enumerateTopics(std::vector<LineTextParams>& topics, int depth = 0) {
    for (size_t i = 0; i < topics.size(); ++i) {
        std::ostringstream numberedText;
        numberedText << std::string(depth * 2, ' ') << (i + 1) << ". " << topics[i].text;
        topics[i].text = numberedText.str();

        // Si hay subtemas, enumerarlos recursivamente
        if (topics[i].subtopics) {
            enumerateTopics(*topics[i].subtopics, depth + 1);
        }
    }
}


// Función para eliminar temas que excedan el tamaño máximo permitido
void filterTopicsBySize(std::vector<LineTextParams>& topics, const ScreenParams& screenParams) {
    const uint16_t maxWidth = screenParams.width - general4BlocksX.blockX2 - screenParams.leftMargin;

    auto fitsWithinScreen = [&](const LineTextParams& topic) {
        // Calcular el ancho estimado del texto en píxeles
        uint16_t estimatedWidth = topic.text.size() * (topic.fontSize * 0.9) * FONT_RESIZE;
        return estimatedWidth <= maxWidth;
    };

    topics.erase(std::remove_if(topics.begin(), topics.end(), [&](LineTextParams& topic) {
        // Filtrar subtemas recursivamente
        if (topic.subtopics) {
            filterTopicsBySize(*topic.subtopics, screenParams);
        }

        // Si el tema no cabe en la pantalla, lanzar un error
        if (!fitsWithinScreen(topic)) {
            throw std::runtime_error("Topic '" + topic.name + "' exceeds the maximum width of " + std::to_string(maxWidth) + " pixels.");
        }

        return false; // No se eliminan temas aquí, solo se valida su tamaño
    }), topics.end());
}

//////////////////////////////////////

//////////////////////////////////

class ThreadController {
public:
    ThreadController() : stopFlag(false), pauseFlag(false) {}

    // Iniciar el hilo con la función proporcionada
    void start(std::function<void()> func) {
        stopFlag = false;
        pauseFlag = false;
        controlledThread = std::thread([this, func]() {
            while (!stopFlag) {
                // Manejo de pausa: se espera si está en pausa
                {
                    std::unique_lock<std::mutex> lock(controlMutex);
                    pauseCondition.wait(lock, [this]() { return !pauseFlag || stopFlag; });
                }

                // Revisar si se solicitó detener el hilo
                if (stopFlag) break;

                // Ejecutar la función proporcionada
                func();
            }
        });
    }

    // Pausar el hilo
    void pause() {
        {
            std::lock_guard<std::mutex> lock(controlMutex);
            pauseFlag = true;  // Poner el hilo en pausa
        }
        pauseCondition.notify_all();  // Notificar al hilo
    }

    // Reanudar el hilo
    void resume() {
        {
            std::lock_guard<std::mutex> lock(controlMutex);
            pauseFlag = false;  // Reanudar el hilo
        }
        pauseCondition.notify_all();  // Notificar al hilo que se reanude
    }

    // Detener el hilo
    void stop() {
        {
            std::lock_guard<std::mutex> lock(controlMutex);
            stopFlag = true;  // Detener el hilo
            pauseFlag = false;  // Asegurar que no esté en pausa
        }
        pauseCondition.notify_all();  // Desbloquear el hilo si estaba esperando
        if (controlledThread.joinable()) {
            controlledThread.join();  // Esperar a que el hilo termine
        }
    }

    // Verificar si el hilo está pausado
    bool isPaused() const {
        return pauseFlag.load();
    }

    std::atomic<bool>& getPauseFlag() {
    return pauseFlag;
    }

    ~ThreadController() {
        stop();
    }

private:
    std::thread controlledThread;
    std::mutex controlMutex;
    std::condition_variable pauseCondition;
    std::atomic<bool> stopFlag;  // Cambiado a atomic para evitar problemas de sincronización
    std::atomic<bool> pauseFlag;  // Cambiado a atomic
};

class BaseObject {
protected:
    uint16_t height;
    uint16_t width;
    uint16_t x_position;
    uint16_t y_position;
    std::string name;
    float velocity_x; // Nueva variable miembro para la velocidad en X
    float velocity_y; // Nueva variable miembro para la velocidad en Y

public:
    // Constructor sin velocidad
    BaseObject(const std::string& _name, uint16_t _width, uint16_t _height, uint16_t _x_position, uint16_t _y_position)
        : name(_name), width(_width), height(_height), x_position(_x_position), y_position(_y_position), velocity_x(0.0f), velocity_y(0.0f) {}

    // Constructor con velocidad
    BaseObject(const std::string& _name, uint16_t _width, uint16_t _height, uint16_t _x_position, uint16_t _y_position, float _velocity_x, float _velocity_y)
        : name(_name), width(_width), height(_height), x_position(_x_position), y_position(_y_position), velocity_x(_velocity_x), velocity_y(_velocity_y) {}

    // Destructor
    virtual ~BaseObject() = default;

    // Getters
    std::string getName() const { return name; }
    uint16_t getHeight() const { return height; }
    uint16_t getWidth() const { return width; }
    uint16_t getXPosition() const { return x_position; }
    uint16_t getYPosition() const { return y_position; }
    float getVelocityX() const { return velocity_x; }
    float getVelocityY() const { return velocity_y; }

    // Setters
    void setName(const std::string& _name) { name = _name; }
    void setHeight(uint16_t _height) { height = _height; }
    void setWidth(uint16_t _width) { width = _width; }
    void setXPosition(uint16_t _x_position) { x_position = _x_position; }
    void setYPosition(uint16_t _y_position) { y_position = _y_position; }
    void setVelocityX(float _velocity_x) { velocity_x = _velocity_x; }
    void setVelocityY(float _velocity_y) { velocity_y = _velocity_y; }
};

// Clase derivada TextureObject
class TextureObject : public BaseObject {
private:
    sf::Texture texture;         // Textura para el objeto
    sf::Sprite textureSprite;    // Sprite para dibujar el objeto

public:
    // Constructor sin velocidad
    TextureObject(const std::string& _name, uint16_t _width, uint16_t _height, uint16_t _x_position, uint16_t _y_position)
        : BaseObject(_name, _width, _height, _x_position, _y_position) {}

    // Constructor con velocidad
    TextureObject(const std::string& _name, uint16_t _width, uint16_t _height, uint16_t _x_position, uint16_t _y_position, float _velocity_x, float _velocity_y)
        : BaseObject(_name, _width, _height, _x_position, _y_position, _velocity_x, _velocity_y) {}

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

    // Función para actualizar la posición del objeto
    void updatePosition() {
        textureSprite.setPosition(static_cast<float>(x_position), static_cast<float>(y_position));
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

    // Get the width of the text
    float getTextWidth() const {
        return textObj.getLocalBounds().width;
    }

    // Get the width of the text
    float getTextHeight() const {
        return textObj.getLocalBounds().height;
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


bool isFarEnough(const std::vector<TextureObject*>& objects, float x, float y, float minDistance) {
    for (const auto& obj : objects) {
        float dx = obj->getXPosition() - x;
        float dy = obj->getYPosition() - y;
        if (std::sqrt(dx * dx + dy * dy) < minDistance) {
            return false;
        }
    }
    return true;
}

std::vector<TextureObject*> createMovingObjects(int n, std::vector<std::vector<Block>> grid, StructTextureObject object) {
    if (n <= 0) return {};

    if (n > 10) {
        throw std::runtime_error("Max num of moving objects is 10. Got: " + std::to_string(n));
    }

    if (MIN_SIZE * 2 > object.width) {
        throw std::runtime_error(
        "The size of the square object must be at least double the minimum size. "
        "Got: " + std::to_string(object.width) + ", required: " + std::to_string(MIN_SIZE * 2));
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::vector<TextureObject*> movingObjectPointer;
    const float minDistance = object.width;

    for (int i = 0; i < n; ++i) {
        int size = MIN_SIZE + (std::rand() % (object.width - (MIN_SIZE - 1))); // Tamaño entre MIN_SIZE y object.width
        float posX, posY;
        bool validPosition = false;

        while (!validPosition) {
            posX = grid[8][16].x + (std::rand() % (grid[100][60].x - grid[8][16].x + 1));
            posY = grid[8][16].y + (std::rand() % (grid[100][60].y - grid[8][16].y + 1));

            if (isFarEnough(movingObjectPointer, posX, posY, minDistance)) {
                validPosition = true;
            }
        }

        std::unique_ptr<TextureObject> texture = std::make_unique<TextureObject>(
            object.name, size, size, posX, posY, object.velocity_x, object.velocity_y);

        if (!texture->loadTexture(object.path)) {
            for (auto obj : movingObjectPointer) {
                delete obj;
            }
            return {}; // Limpia y retorna vacío si falla
        }

        movingObjectPointer.push_back(texture.release());
    }
    return movingObjectPointer;
}

void drawObjects(const std::vector<TextureObject*>& objects, sf::RenderWindow& window) {
    for (auto* obj : objects) {
        if (obj) {
            obj->draw(window);
        }
    }
}

// Function to handle the button
void handleSoundButton(sf::Sprite& soundButton, 
                       sf::Texture& soundOnTexture, 
                       sf::Texture& soundOffTexture, 
                       sf::Music& music, 
                       std::atomic<bool>& isMusicPlaying, 
                       const sf::RenderWindow& window) 
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (soundButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        if (isMusicPlaying.load()) {
            music.pause();
            soundButton.setTexture(soundOffTexture); // Switch to sound-off icon
            isMusicPlaying.store(false);
        } else {
            music.play();
            soundButton.setTexture(soundOnTexture); // Switch to sound-on icon
            isMusicPlaying.store(true);
        }
    }
}

void handleMovingButton(sf::Sprite& movingButton,
                        sf::Texture& movingONTexture,  
                        sf::Texture& movingOffTexture, 
                        const sf::RenderWindow& window,
                        ThreadController& threadController,
                        std::vector<TextureObject*>& movingObjectPointer,
                        std::vector<std::vector<Block>>& grid,           
                        StructTextureObject& object)                  
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (movingButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        if (threadController.isPaused()) {
            // Limpia el vector antes de asignar nuevos objetos
            for (auto* obj : movingObjectPointer) {
                delete obj; // Libera la memoria de cada puntero
            }
            movingObjectPointer.clear();

            // Crea nuevos objetos y actualiza el vector
            movingObjectPointer = createMovingObjects(8, grid, object);
            movingButton.setTexture(movingONTexture); 
            threadController.resume(); // Reanudar el hilo si está pausado
        } else {
            // Limpia el vector para destruir los objetos actuales
            for (auto* obj : movingObjectPointer) {
                delete obj; // Libera la memoria de cada puntero
            }
            movingObjectPointer.clear();

            movingButton.setTexture(movingOffTexture); 
            threadController.pause(); // Pausar el hilo si está corriendo
        }
    }
}


// Load music
std::shared_ptr<sf::Music> loadAndPlayMusic() {
    auto music = std::make_shared<sf::Music>();
    if (!music->openFromFile(AUDIOS_PATH + MUSIC_FILE)) {
        std::cerr << "Error loading music.\n";
        return nullptr; // Return nullptr to indicate failure
    }
    music->play();
    music->setLoop(true);
    return music;
}


int findNumberInArrays(const std::vector<int*>& vec, int number) {
    for (size_t i = 0; i < vec.size(); i++) {
        int* array = vec[i];  // Obtener el arreglo

        // Buscar el número en el arreglo hasta encontrar el final (-1)
        for (size_t j = 0; array[j] != -1; j++) {
            if (array[j] == number) {
                return array[0];  // Retornar el primer elemento del arreglo donde se encuentra el número
            }
        }
    }
    return -1;  // Retornar -1 si no se encuentra el número
}



int* createIndexArray(const std::vector<int>& indices) {
    int* indexArray = new int[indices.size()];  // Crear un arreglo dinámico
    std::copy(indices.begin(), indices.end(), indexArray);  // Copiar los índices en el arreglo
    return indexArray;
}

std::vector<int*> predictOverflow(
    const std::shared_ptr<TextObject>& rootNode,
    const ScreenParams& screen,
    sf::RenderWindow& window
) {
    const auto& children = rootNode->getChildren();
    std::vector<int*> vec;  // Vector para almacenar los arreglos de índices
    std::vector<int> currentIndices;  // Lista temporal de índices antes del desbordamiento
    int next_line = LINE_SPACING * 2 + screen.topMargin + 50;  // Inicializar posición de la siguiente línea

    for (size_t i = 0; i < children.size(); i++) {
        // Verificar si la posición del próximo nodo excede el margen inferior
        if (next_line > screen.height - screen.bottomMargin) {
            currentIndices.push_back(-1);  // sentinel
            // Guardar el arreglo de índices hasta donde ocurrió el primer desbordamiento
            int* indexArray = createIndexArray(currentIndices);
            vec.push_back(indexArray);

            // Reiniciar la lista de índices y la posición de la siguiente línea
            currentIndices.clear();
            next_line = LINE_SPACING * 2 + screen.topMargin + 50;  // Reiniciar posición de la siguiente línea
        }

        // Agregar el índice del nodo actual
        currentIndices.push_back(i);

        // Actualizar la posición de la siguiente línea en función de la altura del texto
        next_line += children[i]->getTextHeight() + LINE_SPACING;
    }

    // Verificar si hay elementos no procesados (última sección sin desbordamiento)
    if (!currentIndices.empty()) {
        int* indexArray = createIndexArray(currentIndices);
        vec.push_back(indexArray);
    }

    return vec;  // Retornar el vector de arreglos de índices
}


//drawMenuFromRoot
// Función para dibujar los nodos existentes, comenzando desde un nodo raíz
void drawMenuFromRoot(
    const std::shared_ptr<TextObject>& rootNode,
    const ScreenParams& screen,
    sf::RenderWindow& window,
    int overflow
) {
    if (!rootNode) {
        std::cerr << "Error: Root node is null." << std::endl;
        return;
    }

    uint16_t next_line = screen.topMargin + 50; // Comenzar desde el margen superior

    // Dibujar el nodo raíz centrado
    uint16_t root_x_position = general4BlocksX.blockX2; // Ajustar para centrar en la pantalla
    rootNode->setXPosition(root_x_position);  // Ajustar posición en X
    rootNode->setYPosition(next_line);       // Ajustar posición en Y
    rootNode->updateTextPosition();
    rootNode->draw(window); // Dibujar el nodo raíz

    next_line += LINE_SPACING * 2; // Espacio adicional debajo del nodo raíz

    uint16_t child_x_position = general4BlocksX.blockX2;
    const auto& children = rootNode->getChildren();

    for (size_t i = overflow; i < children.size(); ++i) {

        if (next_line > screen.height - screen.bottomMargin) {
            break; 
        }

        // Dibujar el hijo en la nueva posición
        children[i]->setYPosition(next_line);
        children[i]->setXPosition(child_x_position);
        children[i]->updateTextPosition();
        children[i]->draw(window);

        next_line += children[i]->getTextHeight() + LINE_SPACING; // Avanzar a la siguiente línea


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
            param.fontSize, 
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

// Función para detectar si dos objetos están colisionando
bool isColliding(const TextureObject& obj1, const TextureObject& obj2) {
    // Comprobar si las cajas de los objetos se solapan
    return !(obj1.getXPosition() + obj1.getWidth()*OVERLAP_PERCENTAGE < obj2.getXPosition() || 
             obj1.getXPosition() > obj2.getXPosition() + obj2.getWidth()*OVERLAP_PERCENTAGE || 
             obj1.getYPosition() + obj1.getHeight()*OVERLAP_PERCENTAGE < obj2.getYPosition() || 
             obj1.getYPosition() > obj2.getYPosition() + obj2.getHeight()*OVERLAP_PERCENTAGE);
}


void moveObjects(std::vector<TextureObject*>& objects, 
                 const sf::RenderWindow& window, 
                 std::atomic<bool>& needsRedraw, 
                 std::atomic<bool>& isPaused) {  // Flag de pausa
    try {
        while (!isPaused.load() && window.isOpen()) {
            if (isPaused.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Espera mientras esté pausado
                continue; // Salta al siguiente ciclo si está pausado
            }

            // Realizar el movimiento de los objetos sin tocar la ventana
            for (size_t i = 0; i < objects.size(); ++i) {
                auto* obj = objects[i];

                // Obtener las velocidades en X e Y directamente del objeto
                float velocity_x = obj->getVelocityX();
                float velocity_y = obj->getVelocityY();

                // Obtener la posición actual del objeto
                float posX = obj->getXPosition();
                float posY = obj->getYPosition();

                // Aplicar las velocidades para mover el objeto
                posX += velocity_x;  // Movimiento en X
                posY += velocity_y;  // Movimiento en Y

                // Verificar colisiones con los límites de la ventana
                if (posX <= EXTRA_MARGING || posX + obj->getWidth() >= window.getSize().x - EXTRA_MARGING) {
                    obj->setVelocityX(-velocity_x); // Invertir velocidad en X
                }
                if (posY <= EXTRA_MARGING || posY + obj->getHeight() >= window.getSize().y - EXTRA_MARGING) {
                    obj->setVelocityY(-velocity_y); // Invertir velocidad en Y
                }

                // Actualizar la posición del objeto
                obj->setXPosition(posX);
                obj->setYPosition(posY);
                obj->updatePosition(); // Actualiza la posición en el sprite

                // Verificar colisiones con otros objetos
                for (size_t j = i + 1; j < objects.size(); ++j) {
                    auto* otherObj = objects[j];

                    // Comprobar si hay colisión entre obj y otherObj
                    if (isColliding(*obj, *otherObj)) {
                        // Invertir las velocidades en X y Y de ambos objetos en caso de colisión
                        obj->setVelocityX(-velocity_x);
                        obj->setVelocityY(-velocity_y);
                        otherObj->setVelocityX(-otherObj->getVelocityX());
                        otherObj->setVelocityY(-otherObj->getVelocityY());
                    }
                }
            }

            // Indicar que se necesita redibujar la ventana
            needsRedraw.store(true);
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Pausa controlada para evitar bloqueo
        }
    } catch (const std::exception& e) {
        std::cerr << "Error en el hilo de movimiento: " << e.what() << std::endl;
    }
}


uint16_t initAndStartMainWindowLoop() {
    // Initialize the grid once
    auto grid = createGrid(SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE);

    filterTopicsBySize(generalTopics, generalScreen);
    enumerateTopics(generalTopics);

    // Create the main application window
    sf::RenderWindow window(sf::VideoMode(generalScreen.width, generalScreen.height), WINDOW_TITLE);

    // Load and validate textures
    std::unique_ptr<TextureObject> background = std::make_unique<TextureObject>(BACKGROUND_IMAGE_OBJ, generalScreen.width, generalScreen.height, 0, 0);
    if (!background->loadTexture(IMAGES_PATH + BACKGROUND_IMAGE_FILE)) return -1;

    std::unique_ptr<TextureObject> soundON = std::make_unique<TextureObject>(SOUND_ON_OBJ, 50, 50, grid[122][1].x, grid[122][1].y);
    if (!soundON->loadTexture(ICONS_PATH + SOUND_ON_FILE)) return -1;

    std::unique_ptr<TextureObject> soundOFF = std::make_unique<TextureObject>(SOUND_OFF_OBJ, 50, 50, grid[122][1].x, grid[122][1].y);
    if (!soundOFF->loadTexture(ICONS_PATH + SOUND_OFF_FILE)) return -1;


    std::unique_ptr<TextureObject> movingON = std::make_unique<TextureObject>(CPP100FILL_IMAGE_OBJ, 50, 50, grid[122][8].x, grid[122][8].y);
    if (!movingON->loadTexture(ICONS_PATH + CPP100FILL_IMAGE_FILE)) return -1;

    std::unique_ptr<TextureObject> movingOFF = std::make_unique<TextureObject>(X100_IMAGE_OBJ, 50, 50, grid[122][8].x, grid[122][8].y);
    if (!movingOFF->loadTexture(ICONS_PATH + X100_IMAGE_FILE)) return -1;

    // Initialize menu and hierarchical tree
    auto mainMenu = std::make_shared<TextObject>(
        mainMenuParams.name, mainMenuParams.x_position, mainMenuParams.y_position, mainMenuParams.color,
        mainMenuParams.text, mainMenuParams.fontPath, mainMenuParams.fontSize, mainMenuParams.centered
    );
    createTree(mainMenu, generalTopics, 1);

    std::vector<int> indices;
    std::shared_ptr<sf::Music> music = loadAndPlayMusic();
    std::atomic<bool> isMusicPlaying = true;

    auto selectedMenu = mainMenu;
    auto selectedMenuChildren = selectedMenu->getChildren();
    int8_t types = 0;


    std::vector<int*> overflow_list = predictOverflow(selectedMenu, generalScreen, window);

    std::atomic<bool> needsRedraw(true);

    // puedo destruirlos y volverlos a contruir
    std::vector<TextureObject*> movingObjectPointer = createMovingObjects(8, grid, iconCpp150);


    ThreadController movementThread;
    
    movementThread.start([&]() {
    moveObjects(std::ref(movingObjectPointer), std::cref(window), std::ref(needsRedraw), std::ref(movementThread.getPauseFlag()));
    });



    // Main event loop
    while (window.isOpen()) {
        sf::Event event;
        selectedMenuChildren[types]->setFontSize(BIG_FONT);
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    needsRedraw = true;
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    } else if (event.key.code == sf::Keyboard::Up) {
                        selectedMenuChildren[types]->setFontSize(NORMAL_FONT);
                        types = (types - 1 + selectedMenuChildren.size()) % selectedMenuChildren.size();
                        selectedMenuChildren[types]->setFontSize(BIG_FONT);
                    } else if (event.key.code == sf::Keyboard::Down) {
                        selectedMenuChildren[types]->setFontSize(NORMAL_FONT);
                        types = (types + 1) % selectedMenuChildren.size();
                        selectedMenuChildren[types]->setFontSize(BIG_FONT);
                    } else if (event.key.code == sf::Keyboard::Enter && !selectedMenu->isLeaf()) {
                        selectedMenuChildren[types]->setFontSize(NORMAL_FONT);
                        indices.push_back(types);
                        auto subtopics = findNestedSubtopics(generalTopics, indices);
                        if (!subtopics.empty()) {
                            createTree(selectedMenu->getChildren()[types], subtopics, 1);
                            selectedMenu = selectedMenu->getChildren()[types];
                            selectedMenuChildren = selectedMenu->getChildren();
                            types = 0; // Bringing back user to first element of the new deployed list
                            selectedMenuChildren[types]->setFontSize(BIG_FONT);
                            overflow_list = predictOverflow(selectedMenu, generalScreen, window);
                        } else {
                            indices.pop_back();
                        }
                    } else if (event.key.code == sf::Keyboard::Left && selectedMenu != mainMenu) {
                        selectedMenu->removeAllChildren();
                        selectedMenu = selectedMenu->getParent();
                        selectedMenuChildren = selectedMenu->getChildren();
                        indices.pop_back();
                        types = 0; // Bringing back user to first element of the new deployed list
                        selectedMenuChildren[types]->setFontSize(BIG_FONT);
                        overflow_list = predictOverflow(selectedMenu, generalScreen, window);
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        handleSoundButton(soundON->getTextureSprite(), soundON->getTexture(), soundOFF->getTexture(), *music, isMusicPlaying, window);
                        handleMovingButton(movingON->getTextureSprite(), movingON->getTexture(), movingOFF->getTexture(), window, movementThread, movingObjectPointer, grid, iconCpp150);
                        needsRedraw = true;
                    }
                    break;

                default:
                    break;
            }
        }

        // Redraw only if necessary
        if (needsRedraw) {
            window.clear();
            background->draw(window);
            if (!movementThread.isPaused()){
                drawObjects(movingObjectPointer, window);
            }
            soundON->draw(window);
            movingON->draw(window);
            drawMenuFromRoot(selectedMenu, generalScreen, window, findNumberInArrays(overflow_list, types));
            window.display();
            needsRedraw = false;
        } else {
            // Reduce CPU usage when idle
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    movementThread.stop();

    return 0;
}


int main() {

    return initAndStartMainWindowLoop();

    //return 0;
}