#include "stdafx.h"
#include "Gui.h"


gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color,
	sf::Color outline_hover_color,
	sf::Color outline_active_color,
	short unsigned id)
{

	this->buttonState = BTN_IDLE;
	this->id = id;
	this->shape.setPosition(sf::Vector2f(x,y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idleColor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x+(this->shape.getGlobalBounds().width / 2.f )- this->text.getGlobalBounds().width/2.f,
		this->shape.getPosition().y 
	);
	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineidleColor = idle_color;
	this->outlinehoverColor = hover_color;
	this->outlineactiveColor = active_color;

	this->pressedTimesCount = 0;


}

gui::Button::~Button()
{

}

const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
	{
		return true;
	}
	return false;
}

//Accessors
const std::string gui::Button::getText()   const
{
	return this->text.getString();
}

const sf::Vector2f gui::Button::getTextPosition() const
{
	return this->text.getPosition();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}
//Modifiers
void gui::Button::setTextPosition(const float x, const float y)
{
	this->text.setPosition(x,y);
}

void gui::Button::setButtonPosition(const float x, const float y)
{
	this->shape.setPosition(x, y);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}
bool gui::Button::PressedCorrector()
{
	int i = 0;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		i++;
	}
	return false;
}
//Functions
void gui::Button::update(const sf::Vector2i& mousePosWindow)
{
	 /* Update the booleans for hover and pressed*/
	
	this->buttonState = BTN_IDLE;
	//Hover
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{

		this->buttonState = BTN_HOVER;
	
		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			
			this->buttonState = BTN_ACTIVE;
		}
	}
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->shape.setOutlineColor(this->outlineidleColor);
		this->text.setFillColor(this->textIdleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->shape.setOutlineColor(this->outlinehoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->shape.setOutlineColor(this->outlineactiveColor);
		this->text.setFillColor(this->textActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->text.setOutlineColor(sf::Color::Green);
		break;
	}


}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

//Drop down List =============================================================================================
gui::DropDownList::DropDownList(float x, float y, float width, float height,
	sf::Font& font, std::string list[], size_t numOfElements, int default_index)
	:font(font), showList(false),keytimeMax(1.f),keytime(0.f)
{
	//unsigned nrOfElements = sizeof(list) / sizeof(std::string);

	this->activeElement = new gui::Button(
		x, y, width, height,
		&this->font,list[default_index], 30,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50));

	for (size_t i = 0; i < numOfElements; i++)
	{
		this->list.push_back(
			new gui::Button(
				x, y + (height * (i + 1)), width, height,
				&this->font, list[i], 30,
				sf::Color(255, 255, 255, 155), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
				sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
				static_cast<unsigned short>(i))
		);
	}
	
	
}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this ->list[i];
	}
}

const unsigned short& gui::DropDownList::getActiveElementId() const
{
	return this->activeElement->getId();
}

//Accessors
const bool gui::DropDownList::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

void gui::DropDownList::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
	{
		this->keytime += 10.f * dt;
	}

}

void gui::DropDownList::update(const sf::Vector2i& mousePosWindow,const float& dt)
{
	this->updateKeytime(dt);

	this->activeElement->update(mousePosWindow);
	//Show and hide the list
	if (this->activeElement->isPressed() && getKeytime())
	{
		if (this->showList)
			this->showList = false;
		else
			this ->showList = true;
	}
	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->update(mousePosWindow);
			if (i->isPressed()&&this->getKeytime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setTextPosition(i->getTextPosition().x,this->activeElement->getTextPosition().y);
				this->activeElement->setId(i->getId());
			}
		}

	}

}

void gui::DropDownList::reRender(float x, float y, float width, float height)
{
	for (auto& i : this->list)
	{
		i->setButtonPosition(x, y);
	}
	
}

void gui::DropDownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);
	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}

	}

}
//Texture Selector =============================================================================================

gui::TextureSelector::TextureSelector(float x, float y, float width, 
	float height,float gridSize,
	const sf::Texture* texture_sheet, const sf::Font& font)
	: keytimeMax(1.f), keytime(0.f)
{
	this->gridSize = gridSize;
	this->active = false;
	this->hidden = false;
	this->positionX = x;
	this->positionY = y;
	float offset = 100.f;


	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x + offset, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x + offset, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));
		
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->sheet.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));
	}

	this->seletor.setPosition(x + offset, y);
	this->seletor.setSize(sf::Vector2f(gridSize,gridSize));
	this->seletor.setFillColor(sf::Color::Transparent);
	this->seletor.setOutlineThickness(1.f);
	this->seletor.setOutlineColor(sf::Color::Red);
	
	this->textureRect.width = static_cast<int>(gridSize);
	this->textureRect.height = static_cast<int>(gridSize);
}

gui::TextureSelector::~TextureSelector()
{
	
}
//Accessors
const bool& gui::TextureSelector::getActive() const
{
	return this->active;
}

const bool& gui::TextureSelector::getHidden() const
{
	return this->hidden;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

void gui::TextureSelector::setHidden(const bool& hidden)
{
	this->hidden = hidden;
}

void gui::TextureSelector::setActice(const bool& active)
{
	this->active = active;
}

void gui::TextureSelector::setPosition(const float x, const float y)
{

}

//Functions
void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	if (!this->hidden)
	{
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			this->active = true;
		}
		else {

			this->active = false;
		}
		if (this->active)
		{
			this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
			this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);

			this->seletor.setPosition(
				this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize);

			//update texture rectangle
			this->textureRect.left = static_cast<int>(this->seletor.getPosition().x - this->bounds.getPosition().x);
			this->textureRect.top = static_cast<int>(this->seletor.getPosition().y - this->bounds.getPosition().y);
		}
	}
}

const bool gui::TextureSelector::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

void gui::TextureSelector::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
	{
		this->keytime += 10.f * dt;
	}

}

void gui::TextureSelector::render(sf::RenderTarget& target)
{
	
	if (!this->hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);
		if (this->active)
			target.draw(this->seletor);
	}

}
