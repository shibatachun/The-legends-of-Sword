#ifndef ENEMYEDITORMODE_H
#define ENEMYEDITORMODE_H
#include "EditorMode.h"
#include "EnemySpawner.h"

class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;
class EnemySpawner;
class EnemyEditorMode :
    public EditorMode
{
private:
    sf::Text cursorText;
    sf::RectangleShape sidebar;
    sf::IntRect textureRect;
    sf::RectangleShape selectorRect;

    int type;
    int amount;
    int timeToSpawn;
    float MaxDistance;

    void initVariables();
    void initGui();
public:
    EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~EnemyEditorMode();

    //Functions
    void updateInput(const float& dt);

    void updateGui(const float& dt);
    void updateButtons();
    void update(const float& dt);

    //Render

    void renderGui(sf::RenderTarget& target);

    void render(sf::RenderTarget& target);
};
#endif

