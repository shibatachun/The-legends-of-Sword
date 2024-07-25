#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H
#include <iostream>
#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class AnimationComponent
{
private:
	class Animation
	{
	public:

		//Vairables

		sf::Texture& textureSheet;
		float speed;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect endRect;


		Animation(sf::Texture& textureSheet,int start_x,int start_y,int end_x,int end_y, int width, int height)
			: textureSheet(textureSheet), speed(speed), width(width), height(height)
		{
		
			this->startRect = sf::IntRect(start_x, start_y, width, height);
			this->endRect = sf::IntRect(end_x, end_y, width, height);
		}

		//Functions
		void update(const float& dt)
		{

		}
		void play();
		void pause();
		void reset();


	private:

	};

	std::map<std::string, Animation> animations;

public:
	AnimationComponent();
	virtual ~AnimationComponent();
};

#endif

