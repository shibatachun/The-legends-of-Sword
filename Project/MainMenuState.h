#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H


#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "State.h"
class MainMenuState :
    public State
{
private:
    //Variables
    sf::Texture background_texture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, sf::Music> bgm;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~MainMenuState();

    //Functions
    
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    //Render
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

#endif // !MAINMENUSTATE_H


