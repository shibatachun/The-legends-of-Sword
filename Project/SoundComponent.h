#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H




class SoundComponent
{
private:
	


public:
	SoundComponent(float dt,sf::Music);
	virtual ~SoundComponent();

	//Function
	void update();
	void play();
	void pause();

	
};

#endif

