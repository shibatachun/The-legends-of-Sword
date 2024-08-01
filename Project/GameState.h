#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"

#include "PauseMenu.h"
#include "TileMap.h"
class GameState :
    public State
{
private:
    PauseMenu* pmenu;
    Player* player;
    sf::Font font;
    //Resources
    std::map<std::string, sf::Texture> textures;
    TileMap map;
    //Functions
    void initKeybinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initPlayers();

public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    //Functions
    void updateInput(const float& dt);
    
    void updatePlayerInput(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};
#endif
