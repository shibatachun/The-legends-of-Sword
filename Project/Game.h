#ifndef GAME_H
#define GAME_H


#include "MainMenuState.h"

class Game {
public:
	//Constructor/Destructors
	Game();
	virtual ~Game();
	//Functions

	//Regular
	void endApplication();
	
	//Update
	void processEvents();
	void update();

	void updateDt();
	//Render
	void render();
	//Core
	void run();

private:

	class GraphicsSettings
	{
	public:
		GraphicsSettings()
		{
			this->title = "DEFAULT";
			this->resolution = sf::VideoMode::getDesktopMode();
			this->fullscreen = false;
			this->verticalSync = false;
			this->frameRareLimit = 120;
			this->contextSettings.antialiasingLevel = 0;
			this->videoModes = sf::VideoMode::getFullscreenModes();


		}
		//Variables
		std::string title;
		sf::VideoMode resolution;
		bool fullscreen;
		bool verticalSync;
		unsigned frameRareLimit;

		sf::ContextSettings contextSettings;

		std::vector<sf::VideoMode> videoModes;

		//Functions
		void saveToFile(const std::string path)
		{
			std::ofstream ofs(path);


			if (ofs.is_open()) {
				ofs <<this->title;
				ofs << this->resolution.width <<" "<< this->resolution.height;
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
		void loadFromFile(const std::string path)
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

	};
	//Variables
	GraphicsSettings gfxSettings;
	sf::RenderWindow* mWindow;
	sf::Event sfEvent;

	
	sf::Clock dtClock;
	//Map mMap;
	//Character mPlayer;
	float dt;

	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	

	//Initialization
	void initVariables();
	void initWindow();
	void initKeys();
	void initGraphicsSettings();
	void initStates();

	

	

};
#endif
