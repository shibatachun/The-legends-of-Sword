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
		this->shape.getPosition().y +(this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height

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
void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}
//Functions
void gui::Button::update(const sf::Vector2f& mousePos)
{
	 /* Update the booleans for hover and pressed*/

	this->buttonState = BTN_IDLE;
	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
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

//Drop down List =============================================
gui::DropDownList::DropDownList(float x, float y, float width, float height,
	sf::Font& font, std::string list[], unsigned numOfElements, unsigned default_index)
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
				i)
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

void gui::DropDownList::update(const sf::Vector2f& mousePos,const float& dt)
{
	this->updateKeytime(dt);

	this->activeElement->update(mousePos);
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
			i->update(mousePos);
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
