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
    StateData* stateData;
    sf::Font  font;
    PauseMenu* pmenu;
    std::map<std::string, gui::Button*> buttons;

    TileMap map;
    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
    void initPauseMenu();
 

public:
    EditorState(StateData *state_data);
    virtual ~EditorState();

    //Functions

    void updateInput(const float& dt);
    void updateButtons();
    void updatePauseMenuButtons();
    void update(const float& dt);
    //Render
    void renderButtons(sf::RenderTarget&);
    void render(sf::RenderTarget* target = NULL);
};

#endif
