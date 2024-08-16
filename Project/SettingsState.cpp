#include "stdafx.h"
#include "SettingsState.h"

SettingsState::SettingsState(StateData *state_data)
	:State(state_data)
{
	
	this->initVariables();
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
	this->dropDownListWidth = (this->window->getSize().x) / 8.f;
	
	this->dropDownListHeight = (this->window->getSize().y) / 18.f;
	this->dropDownListPosition.x = (this->window->getSize().x / 2.f) - (dropDownListWidth / 2.f);
	this->dropDownListPosition.y = (this->window->getSize().y / 2.f) - (dropDownListHeight / 2.f);
	
	std::cout <<"DropDownList Width: " << this->dropDownListWidth << '\n';
		std::cout<<"DropDownList Height" << this->dropDownListHeight << '\n';
		std::cout <<"DropDownList Position x" << this->dropDownListPosition.x << '\n';
		std::cout <<"DropDownList Position y" << this->dropDownListPosition.y << '\n';
	this->modes = sf::VideoMode::getFullscreenModes();
	

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
	float width = gui::p2pX(8.24f,vm);
	float height = gui::p2pY(4.62f,vm);


	//Buttons
	this->buttons["SAVE_STATE"] = new gui::Button(
		gui::p2pX(34.3f, vm),gui::p2pY(74.1f, vm),
		width, height,
		&this->font, "SAVE", gui::calCCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["BACK_STATE"] = new gui::Button(
		gui::p2pX(61.7f, vm), gui::p2pY(74.1f, vm),
		width, height,
		&this->font, "BACK", gui::calCCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	//Modes
	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	//DropDownList
	this->dropDownList["RESOLUTION"] = new gui::DropDownList(gui::p2pX(43.8f, vm), gui::p2pY(47.2f, vm),
		gui::p2pX(12.5f, vm), gui::p2pY(5.6f, vm), font, modes_str.data(), modes_str.size());

	//std::cout << this->dropDownListWidth << " " << this->dropDownListHeight << " " << this->dropDownListPosition.x << " " << this->dropDownListPosition.y << std::endl;
	
	//Text
	this->optionsText.setFont(this->font);
	//this->optionsText.setPosition(this->dropDownList["RESOLUTION"].get);
	this->optionsText.setPosition(sf::Vector2f(gui::p2pX(5.2f,vm),gui::p2pY(41.7f,vm)));
	this->optionsText.setCharacterSize(gui::calCCharSize(vm,70));
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));
	this->optionsText.setString(
		"Resolution \n\nFullscreen\n\nVsync \n\nAntialiasing \n"
	);

}

void SettingsState::resetGui()
{
	/*
	 * Clears the GUI elements and re-initialises the GUI/
	 * 
	 * @return void
	 */
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();
	auto it2 = this->dropDownList.begin();
	for (it2 = this->dropDownList.begin(); it2 != this->dropDownList.end(); ++it2)
	{
		delete it2->second;
	}
	this->dropDownList.clear();


	this->initGui();
}

void SettingsState::RePosition()
{
	for (auto& i : this->dropDownList)
	{
		i.second->reRender(this->dropDownListPosition.x, this->dropDownListPosition.y, this->dropDownListWidth, this->dropDownListHeight);
	}
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
		it.second->update(this->mousePosWindow);

	}
	//Button functionality
	//Quit the game
	if (this->buttons["BACK_STATE"]->isPressed())
	{
		this->endState();
	}

	if (this->buttons["SAVE_STATE"]->isPressed())
	{
		//Remove later
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownList["RESOLUTION"]->getActiveElementId()];
		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
		//this->initVariables();
		//this->RePosition();

		this->resetGui();

		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
	//Dropdown lists
	for (auto& it : this->dropDownList)
	{
		it.second->update(this->mousePosWindow,dt);
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
	
	target->draw(this->optionsText);
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x,this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/


}

