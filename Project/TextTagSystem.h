#pragma once
class TextTagSystem
{
private:
	class TextTag
	{
	private:
		sf::Text text;
		float dirY;
		float dirX;
		float lifetime;
		float speed;


	public:
		TextTag(sf::Font& font, std::string text,
			float pos_x, float pox_y,
			float dir_x, float dir_y,
			sf::Color color,
			unsigned char_size,
			float lifetime, float speed)
		{
			this->text.setFont(font);
			this->text.setPosition(pos_x, pox_y);
			this->text.setFillColor(color);
			this->text.setCharacterSize(char_size);
			this->dirX = dir_x;
			this->dirY = dir_y;
			this->lifetime = lifetime;
			this->speed = speed;
		}
		~TextTag() {

		}
		//Accessor
		inline const bool canBeRemoved() const { return this->lifetime <= 0.f; }
		
		//Function
		void update(const float& dt)
		{

			if (this->lifetime > 0.f)
			{
				this->lifetime -= 100.f * dt;

			}


		}
		void render(sf::RenderTarget* target)
		{
			target->draw(this->text);
		}
	};

	sf::Font font;
	std::vector<TextTag*> tags;

public:
	TextTagSystem();
	virtual ~TextTagSystem();

	//Functions
	void addTextTag(TextTag* text_tag);

	void removeTextTag();

	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

