#ifndef EDITORSTATE_H
#define EDITORSTATE_H
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "DefaultEditorMode.h"

class State;
class StateData;
class Gui;
class PauseMenu;
class TileMap;
class Tile;
class EditorMode;
class DefaultEditorMode;
class EditorStateData;


enum EditorModes {DEFAULT_MODE = 0, ENMEY};



class EditorState :
    public State
{
private:
    //Variables
    EditorStateData editorStateData;

    sf::View view;
    float cameraSpeed;
    sf::Font  font;
    PauseMenu* pmenu;
 
    sf::Vector2f mousePositionOffset;
   
    std::map<std::string, gui::Button*> buttons;

    TileMap* tileMap;



    std::vector<EditorMode*> modes;

    //Functions
    void initVariables();
    void initEditorStateData();
    void initView();
    void initFonts();
  
    void initKeybinds();
    void initButtons();
    void initPauseMenu();
    void initGui();
    void initTileMap();
    void initModes();

public:
    EditorState(StateData *state_data);
    virtual ~EditorState();

    //Functions

    void updateInput(const float& dt);
    void updateEditorInput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);
    void updateMode(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    //Render
    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void renderModes(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

#endif
