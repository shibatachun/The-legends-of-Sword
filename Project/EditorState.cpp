#include "stdafx.h"
#include "EditorState.h"

EditorState::EditorState(StateData *state_data)
	:State(state_data)
{
	this->initVariables();
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
	this->buttons["SELECTOR"] =  new gui::Button(((this->stateData->window->getSize().x)*0.8), ((this->stateData->window->getSize().y) * 0.9), 50.f, 50.f,
		&font, "SELECTOR", 30,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));;


}

void EditorState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
	this->pmenu->addButton("QUIT", 500.f, "Quit");
}

void EditorState::initGui()
{
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
	this->tileMap = new TileMap(this->stateData->gridSize, 20, 20);
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
	//Add a tile to the tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&& this->getKeytime())
	{
		if (!this->textureSelector->getActive())
		{
			this->tileMap->addtile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
		}
		else {
			this->textureRect = this->textureSelector->getTextureRect();
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
	{
		if (!this->textureSelector->getActive())
		{
			this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
		}
	} 

	//change texture

}

void EditorState::updateButtons()
{
	/*Update all the buttons in the state and handles their functionality */
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);

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

void EditorState::updateGui()
{
	this->textureSelector->update(this->mousePosWindow);

	if (!this->textureSelector->getActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize,this->mousePosGrid.y * this->stateData->gridSize);
	}
	this->cursorText.setPosition(this->mousePosView.x+100.f, this->mousePosView.y - 50.f);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y <<
		"\n" << this->mousePosGrid.x << " " << this->mousePosGrid.y <<
		"\n" << this->textureRect.left << " " << this->textureRect.top;
	this->cursorText.setString(ss.str());

}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused)
	{
		this->updateButtons();
		this->updateGui();
		this->updateEditorInput(dt);
	}
	else
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
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
	if (!this->textureSelector->getActive())
	{
		if (this->mousePosView.x < this->tileMap->getMaxMapSize().x && this->mousePosView.y < this->tileMap->getMaxMapSize().y)
		{

		target.draw(this->selectorRect);
		}
		
	}

	this->textureSelector->render(target);
	target.draw(this->cursorText);
	
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;

	}
	this->tileMap->render(*target);
	this->renderButtons(*target);
	this->renderGui(*target);
	
	if (this->paused)
	{
		this->pmenu->render(*target);
	}

}