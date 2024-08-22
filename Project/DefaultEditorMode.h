#ifndef DEFAULTEDITORMODE_H 
#define DEFAULTEDITORMODE_H 
#include "EditorMode.h"
class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;
class DefaultEditorMode :
    public EditorMode
{
private:
    sf::Text cursorText;
    sf::RectangleShape sidebar;
    sf::IntRect textureRect;
    sf::RectangleShape selectorRect;
    std::map<int, std::string> textureFileSet;
    gui::TextureSelector* textureSelector;
    sf::RectangleShape collisionBox;
    std::map<std::string, gui::Button*> buttons;
    bool collision;
    short type;
    int layer;
    bool tileAddLock;
    int binalinag;
    void initVariables();
    void initGui();
    
public:
    DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual~DefaultEditorMode();

    void updateInput(const float& dt) ;

    void updateGui(const float& dt);
    void updateButtons();
    void update(const float& dt);

    //Render

    void renderGui(sf::RenderTarget& target);

    void render(sf::RenderTarget* target = NULL);
};

#endif

