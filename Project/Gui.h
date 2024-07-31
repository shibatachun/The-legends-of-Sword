#ifndef GUI_H
#define GUI_H

#include<vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#include <iostream>
#include <fstream>
#include <sstream>

#include <ctime>
#include <cstdlib>

#include <vector>

enum buuton_states{BTN_IDLE = 0,BTN_HOVER, BTN_ACTIVE };
namespace gui{
	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;
		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;
		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineidleColor;
		sf::Color outlinehoverColor;
		sf::Color outlineactiveColor;


	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent,
			sf::Color outline_hover_color = sf:: Color::Transparent, 
			sf::Color outline_active_color = sf:: Color::Transparent,
			short unsigned id = 0);
		~Button();
		//Accessors
		const bool isPressed() const;
		const std::string getText() const;
		const sf::Vector2f getTextPosition() const;
		const short unsigned& getId() const;
		//Modifiers
		void setText(const std::string text);
		void setTextPosition(const float x, const float y);

		void setId(const short unsigned id);
		//Functions
			void update(const sf::Vector2f& mousePos);
			void render(sf::RenderTarget& target);

	};

	class DropDownList
	{
	private:
		float keytime;
		float keytimeMax;
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;
		

	public:
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[],  unsigned numOfElements, unsigned defalut_index = 0);
		~DropDownList();
		//Functions
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2f& mousePos,const float& dt);
		void render(sf::RenderTarget& target);
	};
}



#endif
