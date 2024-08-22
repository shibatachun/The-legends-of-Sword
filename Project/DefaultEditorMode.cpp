#include "stdafx.h"
#include "DefaultEditorMode.h"


void DefaultEditorMode::initVariables()
{
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TileTypes::DEFAULT;
	
	this->layer = 0;
	this->tileAddLock = false;
}

void DefaultEditorMode::initGui()
{
	//Text
	this->cursorText.setFont(*this->editorStateData->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(20);
	this->cursorText.setPosition(this->editorStateData->mousePosView->x, this->editorStateData->mousePosView->y);


	//General Gui
	this->sidebar.setPosition(sf::Vector2f(0, static_cast<float>(this->stateData->gfxSettings->resolution.height * 0.9)));
	this->sidebar.setSize(sf::Vector2f(static_cast<float>(this->stateData->gfxSettings->resolution.width), static_cast<float>(this->stateData->gfxSettings->resolution.height * 0.1)));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	//this->textureSelector = new gui::TextureSelector(static_cast<float> ((this->stateData->window->getSize().x) * 0.5), static_cast<float>((this->stateData->window->getSize().y) * 0.2)
	//	, 500.f, 500.f, this->stateData->gridSize, this->tileMap->getTileSheet(), this->font);
	this->textureSelector = new gui::TextureSelector(static_cast<float> ((this->stateData->window->getSize().x) * 0.5), static_cast<float>((this->stateData->window->getSize().y) * 0.2)
		, 500.f, 500.f, this->stateData->gridSize, *this->stateData->textureResourcePath, *this->editorStateData->font);

	//Buttons
	this->buttons["SELECTOR"] = new gui::Button(
		(static_cast<float>((this->stateData->window->getSize().x) * 0.8)),
		(static_cast<float>((this->stateData->window->getSize().y) * 0.9)), 120.f, 100.f,
		this->editorStateData->font, "SELECTOR", 30,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50));;
}

DefaultEditorMode::DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
	:EditorMode(state_data,tile_map,editor_state_data)
{
	this->initVariables();
	this->initGui();
}

DefaultEditorMode::~DefaultEditorMode()
{
	delete this->textureSelector;
}
//Functions
void DefaultEditorMode::updateInput(const float& dt)
{
	//Add a tile to the tilemap
	//std::cout << this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)) << std::endl;
	//std::cout << this->editorStateData->mousePosWindow->x <<" y: "<<this->editorStateData->mousePosWindow->y << std::endl;
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime() && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		if (!this->textureSelector->getActive() && !this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
		{
			if (this->tileAddLock)
			{
				if (this->tileMap->tileEmpty(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0))
				{
					this->tileMap->addtile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureSelector->getTileIndex(), this->textureRect, this->collision, this->type);
				}
			}
			else
			{
				this->tileMap->addtile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureSelector->getTileIndex(), this->textureRect, this->collision, this->type);

			}
		}
		else {
			this->selectorRect.setTexture(this->textureSelector->getTexture());
			this->textureRect = this->textureSelector->getTextureRect();
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime() && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		if (!this->textureSelector->getActive() && !this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
		{
			this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0);
		}
	}

	//toggle collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TOGGLE_COLLISION"))) && this->getKeytime())
	{
		if (this->collision)
			this->collision = false;
		else
			this->collision = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("INCREASE_TYPE"))) && this->getKeytime())
	{
		++this->type;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("DECREASE_TYPE"))) && this->getKeytime())
	{
		if (this->type > 0)
			--this->type;
	}
	//Set lock on / off
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TOGGLE_TILE_LOCK"))) && this->getKeytime())
	{
		if (this->tileAddLock)
		{
			this->tileAddLock = false;

		}
		else
			this->tileAddLock = true;

	}
}

void DefaultEditorMode::updateButtons()
{
	/*Update all the buttons in the state and handles their functionality */
	for (auto& it : this->buttons)
	{

		it.second->update(*this->editorStateData->mousePosWindow);

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

void DefaultEditorMode::updateGui(const float& dt)
{	/*Update all the buttons in the state and handles their functionality */
	
	this->textureSelector->update( *this->editorStateData->mousePosWindow, dt);

	if (!this->textureSelector->getActive() && !this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
	{
		this->selectorRect.setTextureRect(this->textureRect);
	
		this->selectorRect.setPosition(this->editorStateData->mousePosGrid->x * this->stateData->gridSize, this->editorStateData->mousePosGrid->y * this->stateData->gridSize);
	}
	this->cursorText.setPosition(this->editorStateData->mousePosView->x + 100.f, this->editorStateData->mousePosView ->y - 50.f);

	std::stringstream ss;
	ss << this->editorStateData->mousePosView->x << " " << this->editorStateData->mousePosView->y <<
		"\n" << this->editorStateData->mousePosGrid->x << " " << this->editorStateData->mousePosGrid->y <<
		"\n" << this->textureRect.left << " " << this->textureRect.top <<
		"\n" << "Collision: " << this->collision <<
		"\n" << "Type: " << this->type <<
		"\n" << "Tiles: " << this->tileMap->getLayerSize(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, this->layer) <<
		"\n" << "Tile locl: " << this->tileAddLock;
	this->cursorText.setString(ss.str());
}

void DefaultEditorMode::update(const float& dt)
{

	this->updateButtons();
	this->updateGui(dt);
	this->updateInput(dt);

}

void DefaultEditorMode::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	if (!this->textureSelector->getActive() && !this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosView)))
	{
		//std::cout << "jinlaile" << std::endl;
		if (this->editorStateData->mousePosView->x < this->tileMap->getMaxMapSize().x && this->editorStateData->mousePosView->y < this->tileMap->getMaxMapSize().y)
		{
			
			target.setView(*this->editorStateData->view);
			target.draw(this->selectorRect);
		}

	}
	target.setView(this->stateData->window->getDefaultView());

	this->textureSelector->render(target);

	target.draw(this->sidebar);

	target.setView(*this->editorStateData->view);

	target.draw(this->cursorText);
}

void DefaultEditorMode::render(sf::RenderTarget* target)
{

	this->renderGui(*target);
}
