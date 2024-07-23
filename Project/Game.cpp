#include "Game.h"


//Constructor

Game::Game()
{
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

//Initializer functions
void Game::initWindow()
{	
	std::ifstream ifs("Config/window.ini");
	std::string title = "None";
	sf::VideoMode window_bounds(800,600);
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;

	}
	else
	{
		std::cerr << "can't open file" << "/n";
	}
	ifs.close();

	this->mWindow = new sf::RenderWindow(window_bounds, title);
	this->mWindow->setFramerateLimit(framerate_limit);
	this->mWindow->setVerticalSyncEnabled(vertical_sync_enabled);

}

void Game::initKeys()
{
	this->supportedKeys.emplace("Escape", sf::Keyboard::Key::Escape);
	this->supportedKeys.emplace("A", sf::Keyboard::Key::A);
	this->supportedKeys.emplace("D", sf::Keyboard::Key::D);
	this->supportedKeys.emplace("W", sf::Keyboard::Key::W);
	this->supportedKeys.emplace("S", sf::Keyboard::Key::S);

	std::cout << this->supportedKeys.at("A") << "\n";
}
//Functions
void Game::initStates()
{
	this->states.push(new GameState(this->mWindow,&this->supportedKeys));
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


