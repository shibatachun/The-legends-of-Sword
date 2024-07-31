#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window,supportedKeys,states)
{

	this->initVariables();
	this->initBackground();

	this->initFonts();
	this->initKeybinds();
	this->initGui();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownList.begin();
	for (it2 = this->dropDownList.begin(); it2 != this->dropDownList.end(); ++it2)
	{
		delete it2->second;
	}

	
}
//Initializer functions
void SettingsState::initVariables()
{
}

void SettingsState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);
	if (!this->background_texture.loadFromFile("Resources/images/Backgrounds/bg1.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGOUND_TEXTURE";

	}
	this->background.setTexture(&this->background_texture);
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts\\ThaleahFat.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportKeys->at(key2);
		}
	}
	ifs.close();


}

void SettingsState::initGui()
{

	this->buttons["SAVE_STATE"] = new gui::Button((this->window->getSize().x / 2.f) - 300.f, 800.f, 150.f, 50.f,
		&this->font, "SAVE", 50,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["BACK_STATE"] = new gui::Button((this->window->getSize().x / 2.f) + 225.f,  800.f, 150.f, 50.f,
		&this->font, "BACK", 50,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::string li[] = { "1920x1080","800x600","640x480" };
	this->dropDownList["RESOLUTION"] = new gui::DropDownList((this->window->getSize().x / 2.f)-100.f, 450.f, 200.f, 50.f, font, li, 3);


}
//Accessors

//Functions

void SettingsState::updateInput(const float& dt)
{

	//if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))


}

void SettingsState::updateGui(const float& dt)
{
	/*Update all the gui elements in the state and handles their functionality */
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);

	}
	//Button functionality
	//Quit the game
	if (this->buttons["BACK_STATE"]->isPressed())
	{
		this->endState();
	}

	if (this->buttons["SAVE_STATE"]->isPressed())
	{
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
	//Dropdown lists
	for (auto& it : this->dropDownList)
	{
		it.second->update(this->mousePosView,dt);
	}
	//Dropdown lists functionality
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();

	this->updateInput(dt);

	this->updateGui(dt);




}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropDownList)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;

	}

	target->draw(this->background);

	this->renderGui(*target);
	
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x,this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/


}
