#include "stdafx.h"
#include "EditorState.h"

EditorState::EditorState(StateData *state_data)
	:State(state_data)
{
	this->initVariables();
	this->initView();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();

}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	delete this->pmenu;
	delete this->tileMap;
	delete this->textureSelector;
}

//Initializer functions
void EditorState::initVariables()
{
	this->textureRect= sf::IntRect(0,0,static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TileTypes::DEFAULT;
	this->cameraSpeed = 100.f;

}

void EditorState::initView()
{
	this->view.setSize(sf::Vector2f(
		this->stateData->gfxSettings->resolution.width, 
		this->stateData->gfxSettings->resolution.height));
	this->view.setCenter(
		this->stateData->gfxSettings->resolution.width / 2.f, 
		this->stateData->gfxSettings->resolution.height / 2.f);


	
}

void EditorState::initBackground()
{
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts\\ThaleahFat.ttf"))
	{
		throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT");
	}
}

void EditorState::initText()
{
	
	
	this->cursorText.setFont(this->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(20);
	this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y);

}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");

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

void EditorState::initButtons()
{
	this->buttons["SELECTOR"] =  new gui::Button(((this->stateData->window->getSize().x)*0.8), ((this->stateData->window->getSize().y) * 0.9),120.f, 100.f,
		&font, "SELECTOR", 30,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50));;


}

void EditorState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
	this->pmenu->addButton("QUIT", 700.f, "Quit");
	this->pmenu->addButton("SAVE", 400.f, "Save");
	this->pmenu->addButton("LOAD", 300.f, "LOAD");
}

void EditorState::initGui()
{
	this->sidebar.setPosition(sf::Vector2f(0, static_cast<float>(this->stateData->gfxSettings->resolution.height * 0.9)));
	this->sidebar.setSize(sf::Vector2f(static_cast<float>(this->stateData->gfxSettings->resolution.width), static_cast<float>(this->stateData->gfxSettings->resolution.height*0.1)));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize,this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color(255,255,255,150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector((this->stateData->window->getSize().x)*0.5, (this->stateData->window->getSize().y) * 0.2
		, 500.f, 500.f, this->stateData->gridSize, this->tileMap->getTileSheet(), this->font);

}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "Resources/images/Tiles/TX_Tileset_Grass.png");
}


//Functions
void EditorState::updateInput(const float& dt)
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

void EditorState::updateEditorInput(const float& dt)
{

	//Move view
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		this->view.move(-std::floor((this->mousePosView.x - this->
			mousePositionOffset.x)),-std::floor((this->mousePosView.y-this->mousePositionOffset.y)));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
	{
		this->view.move(0.f, -this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->view.move(0.f, this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->view.move(-this->cameraSpeed * dt,0.f );
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->view.move(this->cameraSpeed * dt,0.f );
	}
	//Add a tile to the tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&& this->getKeytime() && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		if (!this->textureSelector->getActive()&& !this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			this->tileMap->addtile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect,this->collision,this->type);
		}
		else {
			this->textureRect = this->textureSelector->getTextureRect();
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime() && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		if (!this->textureSelector->getActive() && !this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
		}
	} 

	//toggle collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION"))) && this->getKeytime())
	{
		if (this->collision)
			this->collision = false;
		else
			this->collision = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INCREASE_TYPE"))) && this->getKeytime())
	{
		++this->type;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DECREASE_TYPE"))) && this->getKeytime())
	{
		if(this->type>0)
			--this->type;
	}
}

void EditorState::updateButtons()
{
	/*Update all the buttons in the state and handles their functionality */
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);

	}
	if (this->buttons["SELECTOR"]->isPressed() && this->getKeytime())
	{
		if (this->textureSelector->getHidden())
		{
			this->textureSelector->setHidden(false);
			this->textureSelector->setActice(true);
		}
		else
		{
			this->textureSelector->setHidden(true);
			this->textureSelector->setActice(false);
		}
		
	}
}

void EditorState::updateGui(const float& dt)
{
	this->textureSelector->update(this->mousePosWindow, dt);

	if (!this->textureSelector->getActive() && !this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize,this->mousePosGrid.y * this->stateData->gridSize);
	}
	this->cursorText.setPosition(this->mousePosView.x+100.f, this->mousePosView.y - 50.f);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y <<
		"\n" << this->mousePosGrid.x << " " << this->mousePosGrid.y <<
		"\n" << this->textureRect.left << " " << this->textureRect.top <<
		"\n" << "Collision: " << this->collision <<
		"\n" <<"Type: "<< this->type;
	this->cursorText.setString(ss.str());

}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}
	if (this->pmenu->isButtonPressed("SAVE"))
	{
		this->tileMap->saveToFile("text.slmp");
	}
	if (this->pmenu->isButtonPressed("LOAD"))
	{
		this->tileMap->loadFromFile("text.slmp");
	}
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions(&this->view );
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused)
	{
		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorInput(dt);
	}
	else
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
	this->mousePositionOffset = this->mousePosView;
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	if (!this->textureSelector->getActive() && !this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
	{
		if (this->mousePosView.x < this->tileMap->getMaxMapSize().x && this->mousePosView.y < this->tileMap->getMaxMapSize().y)
		{
			target.setView(this->view);
			target.draw(this->selectorRect);
		}
		
	}
	target.setView(this->window->getDefaultView());

	this->textureSelector->render(target);
	target.draw(this->sidebar);

	target.setView(this->view);
	target.draw(this->cursorText);



	
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;

	}
	target->setView(this->view);
	this->tileMap->render(*target);

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target);

	this->renderGui(*target);
	
	if (this->paused)
	{
		target->setView(this->window->getDefaultView());
		this->pmenu->render(*target);
	}

}