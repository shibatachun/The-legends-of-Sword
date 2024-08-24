#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"

#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "Sword.h"
#include "Bow.h"





class GameState :
    public State
{
private:

    sf::View view;
    sf::Vector2i viewGridPosition;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    PauseMenu* pmenu;

    sf::Shader core_shader;

    Player* player;
    std::vector<Enemy*> activeEnemies;
    PlayerGUI* playerGUI;
    sf::Font font;
    //Resources
    std::map<std::string, sf::Texture> textures;
    EnemySystem* enemySystem;
    TileMap* tileMap;
    //Functions
    void initDeferredRender();
    void initView();
    void initKeybinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initShaders();
    void initEnemySytem();
    void initPlayers();
    void initPlayerGUI();
    void initTileMap();
   

public:
    GameState(StateData *state_data);
    virtual ~GameState();

    //Functions
    void updateView(const float& dt);
    void updateInput(const float& dt);
    
    void updatePlayerInput(const float& dt);
    void updatePlayerGUI(const float& dt);
    void updatePauseMenuButtons();
    void updateTileMap(const float& dt);
    void updatePlayer(const float& dt);
    void updateEnemies(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};
#endif
