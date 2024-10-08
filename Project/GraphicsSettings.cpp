#include "stdafx.h"
#include "GraphicsSettings.h"
GraphicsSettings::GraphicsSettings()
{
	this->title = "DEFAULT";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->verticalSync = false;
	this->frameRareLimit = 120;
	this->contextSettings.antialiasingLevel = 0;
	this->videoModes = sf::VideoMode::getFullscreenModes();


}

//Functions
void  GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream ofs(path);


	if (ofs.is_open()) {
		ofs << this->title;
		ofs << this->resolution.width << " " << this->resolution.height;
		ofs << this->fullscreen;
		ofs << this->frameRareLimit;
		ofs << this->verticalSync;
		ofs << this->contextSettings.antialiasingLevel;

	}
	else
	{
		std::cerr << "can't open file" << "/n";
	}
	ofs.close();
}
void GraphicsSettings::loadFromFile(const std::string path)
{
	std::ifstream ifs(path);


	if (ifs.is_open()) {
		std::getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->fullscreen;
		ifs >> this->frameRareLimit;
		ifs >> this->verticalSync;
		ifs >> this->contextSettings.antialiasingLevel;

	}
	else
	{
		std::cerr << "can't open file" << "/n";
	}
	ifs.close();
}