#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H
#include "State.h"


#include "Button.h"
class SettingsState :
    public State
{
private:
    //Variables
    sf::Texture background_texture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, Button*> buttons;
    std::map<std::string, sf::Music> bgm;

    //Functions

    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

    
public:
    SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
 
    virtual ~SettingsState();

    //Accessors
    
    


    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    //Render
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

#endif