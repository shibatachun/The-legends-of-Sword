#include "GameState.h"

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

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

void GameState::initTextures()
{
	
	if (!this->textures["PLAYER"].loadFromFile("Resources/images/Sprites/Player/soldier_all_sheet.png"))
	{
		throw "ERROR::GAME_STATE::FAILD_TO_LOAD_PLAYER_TEXTURE";
	}
	
	
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window,this->font);
	this->pmenu->addButton("QUIT", 200.f, "Quit");
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER"]);

}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts\\ThaleahFat.ttf"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
	}
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window,supportedKeys,states)
{
	this->initKeybinds();
	this->initFonts();

	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
		{
			this->pauseState();

		}
		else
		{
			this->unpauseState();

		}
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f,dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f,dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);
	
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused)
	{
		this->updatePlayerInput(dt);
		this->player->update(dt);

		
	}
	else //Pause update
	{

		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
	
}

void GameState::render(sf::RenderTarget* target )
{
	if (!target)
	{
		target = this->window;
		
	}
	this->player->render(*target);
	if (this->paused)//Pause 
	{
		this->pmenu->render(*target);
	}
	
}
