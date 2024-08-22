#include "stdafx.h"
#include "GameState.h"

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height);
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0, 0,
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height));
}

void GameState::initView()
{
	this->view.setSize(sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width), 
		static_cast<float>(this->stateData->gfxSettings->resolution.height)
	));

	this->view.setSize(sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width) /2.f,
		static_cast<float>(this->stateData->gfxSettings->resolution.height) /2.f
	));
}

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
	
	if (!this->textures["PLAYER"].loadFromFile("Resources/images/Sprites/Player/Sheet.png"))
	{
		throw "ERROR::GAME_STATE::FAILD_TO_LOAD_PLAYER_TEXTURE";
	}
	
	
}

void GameState::initPauseMenu()
{
	sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution,this->font);
	this->pmenu->addButton("QUIT", gui::p2pY(18.5f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calCCharSize(vm), "Quit");
}

void GameState::initShaders()
{
	if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER." << std::endl;
	}
	
}

void GameState::initPlayers()
{
	this->player = new Player(200.f, 200.f, this->textures["PLAYER"]);

}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player,this->stateData->gfxSettings->resolution);
}

void GameState::initTileMap()
{
	//this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, *this->stateData->textureResourcePath);
	this->tileMap = new TileMap("text.slmp",*this->stateData->textureResourcePath);
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts\\ThaleahFat.ttf"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
	}
}

GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initShaders();
	this->initPlayers();
	this->initPlayerGUI();
	this->initTileMap();

	
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->playerGUI;
	delete this->tileMap;
	
}

void GameState::updateView(const float& dt)
{
	//Mouse view

	this->view.setCenter(
		std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x)
			- static_cast<float>(this->stateData->gfxSettings->resolution.width/2)) / 10.f)
		,std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) 
			- static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 10.f)
	);
	if (this->view.getSize().x <= this->tileMap->getMaxSizeF().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);

		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x)
		{
			this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getCenter().x / 2.f, this->view.getCenter().y);

		}
	}
	if (this->view.getSize().y <= this->tileMap->getMaxSizeF().y) {
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);

		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeF().y)
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
		}
	}
		this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
		this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
	
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
	{
		this->player->move(0.f, -1.f,dt);
		if (this->getKeytime())
			this->player->gainEXP(10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->move(0.f, 1.f, dt);
		if (this->getKeytime())
			this->player->loseEXP(1);

	}
	
}

void GameState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->update(dt);
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}
}

void GameState::updateTileMap(const float& dt)
{

	this->tileMap->update(this->player,dt);
	
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused)
	{
		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->updateTileMap(dt);

		this->player->update(dt,this->mousePosView);
		this->playerGUI->update(dt);

	

		
		
	}
	else //Pause update
	{

		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
	
}

void GameState::render(sf::RenderTarget* target )
{
	if (!target)
	{
		target = this->window;
		
	}

	this->renderTexture.clear();
	this->renderTexture.setView(this->view);
	this->tileMap->render(this->renderTexture,15,9,
		this->viewGridPosition,
		&this->core_shader,
		this->player->getCenter(), false);
	/*this->tileMap->render(this->renderTexture, 30, 30,
		this->player->getGridPosition(static_cast<int>(this->stateData->gridSize)),
		NULL,
		sf::Vector2f(), false);*/
	this->player->render(this->renderTexture,&this->core_shader,this->player->getCenter(), false);
	//this->tileMap->renderDeferred(this->renderTexture,NULL,sf::Vector2f());
	
	this->tileMap->renderDeferred(this->renderTexture,&this->core_shader,this->player->getCenter());

	//Render GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);
	if (this->paused)//Pause 
	{
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	//Final Render
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
