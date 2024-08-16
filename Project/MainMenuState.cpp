#include "stdafx.h"
#include "MainMenuState.h"

MainMenuState::MainMenuState(StateData* state_data)
	:State(state_data)
{
	
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGUI();
	 
	

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

void MainMenuState::initGUI()
{

	sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	//Background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	if (!this->background_texture.loadFromFile("Resources/images/Backgrounds/bg1.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGOUND_TEXTURE";

	}
	this->background.setTexture(&this->background_texture);
	 
	float width = gui::p2pX(8.24f, vm);
	float height = gui::p2pY(4.62f,vm);

	//Buttons
	this->buttons["GAME_STATE"] = new gui::Button((gui::p2pX(50.f, vm)-(width/2.f)), gui::p2pY(27.8f, vm), width, height,
		&this->font, "New Game", gui::calCCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["SETTINGS_STATE"] = new gui::Button((gui::p2pX(50.f, vm) - (width / 2.f)), gui::p2pY(41.7f, vm), width, height,
		&this->font, "Settings", gui::calCCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE"] = new gui::Button((gui::p2pX(50.f, vm) - (width / 2.f)), gui::p2pY(55.6f, vm), width, height,
		&this->font, "Editor", gui::calCCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new gui::Button((gui::p2pX(50.f, vm) - (width / 2.f)), gui::p2pY(74.1f, vm), width, height,
		&this->font, "Quit", gui::calCCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	
}

void MainMenuState::resetGUI()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();
	this->initGUI();
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
		it.second->update(this->mousePosWindow);

	}

	//New Game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}
	//Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}
	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
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