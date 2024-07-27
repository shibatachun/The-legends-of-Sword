#include "MainMenuState.h"



MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys,states)
{
	this->initVariables();
	this->initBackground();

	this->initFonts();
	this->initKeybinds();
	this->initButtons();


	 
	

}


MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Initializer functions
void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
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

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts\\ThaleahFat.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
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
void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button((this->window->getSize().x/2.f)-75, 300, 150, 50,
		&this->font, "New Game",50,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["SETTINGS"] = new Button((this->window->getSize().x / 2.f) - 75, 450, 150, 50,
		&this->font, "Settings",50,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE"] = new Button((this->window->getSize().x / 2.f) - 75, 600, 150, 50, 
		&this->font, "Editor",50,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new Button((this->window->getSize().x / 2.f) - 75, 800, 150, 50,
		&this->font, "Quit",50,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	
}



void MainMenuState::updateInput(const float& dt)
{
	
	//if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))


}

void MainMenuState::updateButtons()
{
	/*Update all the buttons in the state and handles their functionality */
	for (auto &it:  this->buttons)
	{
		it.second->update(this->mousePosView);

	}
	//New Game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportKeys,this->states));
	}
	//Settings
	
	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->window, this->supportKeys, this->states));
	}
	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}



}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	
	this->updateButtons();

	
	
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;

	}

	target->draw(this->background);
	
	this->renderButtons(*target);

	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x,this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/

	
}