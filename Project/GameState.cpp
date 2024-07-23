#include "GameState.h"

void GameState::initKeybinds()
{
	this->keybinds.emplace("MOVE_LEFT",this->supportKeys->at("A"));
	this->keybinds.emplace("MOVE_RIGHT", this->supportKeys->at("D"));
	this->keybinds.emplace("MOVE_UP", this->supportKeys->at("W"));
	this->keybinds.emplace("MOVE_DOWN", this->supportKeys->at("S"));

}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	:State(window,supportedKeys)
{
	this->initKeybinds();
}

GameState::~GameState()
{
}

void GameState::endState()
{
	std::cout << "Ending gameState" << "\n";

}

void GameState::updateInput(const float& dt)
{
	this->checkForQuit();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player.move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player.move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player.move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player.move(dt, 0.f, 1.f);
}

void GameState::update(const float& dt)
{
	this->updateInput(dt);
	this->player.update(dt);
}

void GameState::render(sf::RenderTarget* target )
{
	if (!target)
	{
		target = this->window;
		
	}
	this->player.render(this->window);
	
}
