#include "stdafx.h"
#include "PlayerGUI.h"

//Initializer
void PlayerGUI::initFont()
{
	this->font.loadFromFile("Fonts/ThaleahFat.ttf");
}

void PlayerGUI::initHPBar()
{
	
	
	this->hpBar = new gui::ProgressBar(
		1.f, 8.3f, 10.4f, 2.8f, 
		this->player->getAttributeComponent()->hpMax,
		sf::Color::Red, 180,
		this->vm, &this->font);
	
}

void PlayerGUI::initEXPBar()
{

	this->expBar = new gui::ProgressBar(
		1.f, 5.6f, 10.4f, 1.9f,
		this->player->getAttributeComponent()->expNext,
		sf::Color::Blue, 220,
		this->vm, &this->font);
	
}

void PlayerGUI::initLevelBar()
{
	float width = gui::p2pX(1.6f, this->vm);
	float height = gui::p2pY(2.8f,this->vm);
	float x = gui::p2pX(1.f,this->vm);
	float y = gui::p2pY(1.9f,this->vm);


	this->levelBarBack.setSize(sf::Vector2f(width, height));
	this->levelBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->levelBarBack.setPosition(x, y);



	this->levelBarText.setFont(this->font);
	this->levelBarText.setCharacterSize(gui::calCCharSize(this->vm, 120));
	this->levelBarText.setPosition(
		this->levelBarBack.getPosition().x + gui::p2pX(0.53f,this->vm),
		this->levelBarBack.getPosition().y + gui::p2pY(0.5f,this->vm)
	);
}


PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm)
	:vm(vm)
{
	this->player = player;
	this->initFont();
	this->initEXPBar();
	this->initHPBar();
	this->initLevelBar();
}

PlayerGUI::~PlayerGUI()
{
	delete this->hpBar;
}

//Functions
void PlayerGUI::updateHPBar()
{
	this->hpBar->update(this->player->getAttributeComponent()->hp);
}

void PlayerGUI::updateEXPBar()
{
	this->expBar->update(this->player->getAttributeComponent()->exp);
}

void PlayerGUI::updateLevelBar()
{
	this->levelBarString = std::to_string(this->player->getAttributeComponent()->level);
	this->levelBarText.setString(this->levelBarString);
}

void PlayerGUI::update(const float& dt)
{
	this->updateLevelBar();
	this->updateEXPBar();
	this->updateHPBar();
}

void PlayerGUI::renderHPBar(sf::RenderTarget& target)
{
	this->hpBar->render(target);
}

void PlayerGUI::renderEXPBar(sf::RenderTarget& target)
{
	this->expBar->render(target);
}

void PlayerGUI::renderLevelBar(sf::RenderTarget& target)
{
	target.draw(this->levelBarBack);

	target.draw(this->levelBarText);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->renderLevelBar(target);
	this->renderHPBar(target);
	this->renderEXPBar(target);
}
