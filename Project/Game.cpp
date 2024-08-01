#include "stdafx.h"
#include "Game.h"



//Constructor

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initKeys();
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
	this->fullscreen = false;
	this->dt = 0.f;
}

//Initializer functions
void Game::initWindow()
{	
	std::ifstream ifs("Config/window.ini");
	this->videomodes = sf::VideoMode::getFullscreenModes();
	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	
	bool fullscreen = false;

	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> antialiasing_level;

	}
	else
	{
		std::cerr << "can't open file" << "/n";
	}
	ifs.close();
	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;
	if (this->fullscreen)
	{
		this->mWindow = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, this->windowSettings);
	}
	else
	{

		this->mWindow = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);
	}

	this->mWindow->setFramerateLimit(framerate_limit);
	this->mWindow->setVerticalSyncEnabled(vertical_sync_enabled);

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
//Functions
void Game::initStates()
{
	this->states.push(new MainMenuState(this->mWindow, &this->supportedKeys,&this->states));
	
}

void Game::endApplication()
{
	std::cout << "Ending Application" << "\n";
}

//Function
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
		
		this->states.top()->update(this->dt);
		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
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


