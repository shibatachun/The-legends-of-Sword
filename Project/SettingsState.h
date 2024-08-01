#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H
#include "State.h"




class SettingsState :
    public State
{
private:
    //Variables

    GraphicsSettings& gfxSettings;
    sf::Texture background_texture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownList;
    std::map<std::string, sf::Music> bgm;

    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;


    float dropDownListWidth;
    float dropDownListHeight;
    float buttonWidth;
    float buttonHeight;

    sf::Vector2f dropDownListPosition;
    

    
    //Functions

    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGui();
    void initText();

    void RePosition();
    
public:
    SettingsState(sf::RenderWindow* window,GraphicsSettings& gfxSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
 
    virtual ~SettingsState();

    //Accessors
    
    


    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);
    
    //Render
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
    void reRender(sf::RenderTarget& target);
};

#endif