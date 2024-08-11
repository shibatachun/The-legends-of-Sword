#include "stdafx.h"
#include "Game.h"

//Constructor
Game::Game()
{
	
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initTextureResource();
	this->initStateData();
	this->initStates();
	
}

Game::~Game() {
	delete this->mWindow;
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();

	}
}

void Game::initVariables()
{
	this->mWindow = NULL;

	this->dt = 0.f;
	this->gridSize = 128.f;
}

//Initializer functions
void Game::initWindow()
{	
	

	if (this->gfxSettings.fullscreen)
	{
		this->mWindow = new sf::RenderWindow(
			this->gfxSettings.resolution, this->gfxSettings.title,
			this->gfxSettings.fullscreen, this->gfxSettings.contextSettings);
	}
	else
	{

		this->mWindow = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);
	}

	this->mWindow->setFramerateLimit(this->gfxSettings.frameRareLimit);
	this->mWindow->setVerticalSyncEnabled(this->gfxSettings.verticalSync);

}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] =key_value;
		}
	}
	ifs.close();
	
//DEBUG REMOVE later
	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n";
	}
}

void Game::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("Config/graphics.ini");


}

void Game::initStateData()
{
	
	this->stateData.window = this->mWindow;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
	this->stateData.textureResourcePath = &this->textureResource;
}

void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
	
}

void Game::initTextureResource()
{
	int index = 0;
	std::string directoryPath = "Resources/images/Tiles";
	for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".png") {
		
			textureResource[index] = entry.path().string();
			index++;
		}
	}
	//this->textureResource[0] = "Resources/images/Tiles/TX_Tileset_Grass_1.png";
	//this->textureResource[1] = "Resources/images/Tiles/Dungeon_Tileset_1.png";
	//this->textureResource[2] = "Resources/images/Tiles/TX_Tileset_Stone_Ground.png";

	for (const auto& [key, value] : textureResource) {
		std::cout << "Index: " << key << " | Path: " << value << std::endl;
	}
}

//Functions
void Game::endApplication()
{
	std::cout << "Ending Application" << "\n";
}

void Game::processEvents() {
	
	while (this->mWindow->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->mWindow->close();
		}
	}

}

void Game::update()
{
	this->processEvents();
	if (!this->states.empty())
	{
		if (this->mWindow->hasFocus()) {
			this->states.top()->update(this->dt);
			if (this->states.top()->getQuit())
			{
				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	//Application end
	else
	{
		this->endApplication();
		this->mWindow->close();
	}
	
	

}

void Game::run() {
	while (this->mWindow->isOpen()) {

		this->updateDt();
		this->update();
		this->render();

	}
}

void Game::render() {
	this->mWindow->clear();
	if (!this->states.empty())
	{
		this->states.top()->render();
	}
	this->mWindow->display();

}

void Game::updateDt()
{	
	/*Updates the dt variable with the time it takes to update and render one frame*/
	this->dt = this->dtClock.restart().asSeconds();



} 


