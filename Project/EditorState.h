#ifndef EDITORSTATE_H
#define EDITORSTATE_H
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState :
    public State
{
private:
    //Variables
    
    sf::View view;
    sf::Font  font;
    sf::Text cursorText;
    sf::Vector2f mousePositionOffset;
    PauseMenu* pmenu;
    std::map<std::string, gui::Button*> buttons;

    TileMap* tileMap;
    sf::RectangleShape sidebar;
    sf::IntRect textureRect;
    sf::RectangleShape selectorRect;
    std::map<int, std::string> textureFileSet;
    gui::TextureSelector* textureSelector;

    sf::RectangleShape collisionBox;

    float cameraSpeed;
    bool collision;
    short type; 
    int layer;
    bool tileAddLock;
    //Functions
    void initVariables();
    void initView();
    void initBackground();
    void initFonts();
    void initText();
    void initKeybinds();
    void initButtons();
    void initPauseMenu();
    void initGui();
    void initTileMap();
    void initTextureFileSets();

public:
    EditorState(StateData *state_data);
    virtual ~EditorState();

    //Functions

    void updateInput(const float& dt);
    void updateEditorInput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    //Render
    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

#endif
