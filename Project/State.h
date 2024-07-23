#ifndef STATE_H
#define STATE_H

#include "Entity.h"


#include "Map.h"
#include "Character.h"
class State
{
private:

protected:
	sf::RenderWindow* window;
	std::map<std::string, int>* supportKeys;
	std::map<std::string, int> keybinds;

	//Resources
	std::vector<sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;

	bool quit;

public:
	State(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys);
	virtual ~State();

	const bool& getQuit() const;

	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt ) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
	virtual void checkForQuit();
	virtual void endState() = 0;


};

#endif


