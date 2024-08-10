#ifndef GUI_H
#define GUI_H



enum buuton_states{BTN_IDLE = 0,BTN_HOVER, BTN_ACTIVE };
namespace gui{
	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;
		int pressedTimesCount;
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
		void setButtonPosition(const float x, const float y);

		void setId(const short unsigned id);
		//Functions
		bool PressedCorrector();
		void update(const sf::Vector2i& mousePosWindow);
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
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], size_t numOfElements, int defalut_index = 0);
		~DropDownList();

		//Initializer
		
		//Accessors
		const unsigned short& getActiveElementId() const;
		//Modifiers
		
		//Functions
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow,const float& dt);
		void render(sf::RenderTarget& target);
		void reRender(float x, float y, float width, float height);
	};

	class TextureSelector
	{
	private:

		float gridSize;
		float positionX;
		float positionY;
		bool active;
		float keytime;
		float keytimeMax;
		int tileSheetCount;
		short tileIndex;
		bool hidden;
	
		sf::RectangleShape bounds;
		sf::RectangleShape buttonBar;
		sf::Sprite sheet;
		sf::RectangleShape seletor;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;
		sf::Font font;
		sf::Texture tileSheet;
		std::map<std::string, gui::Button*> buttons;
		std::map<int, std::string> textureTilePathSet;
		std::map<int, sf::Texture> tileSheetSet;

	

	public:
		TextureSelector(float x, float y,float width, float height, float gridSize,const std::map<int,std::string>& textureTileSet,const sf::Font& font);
		~TextureSelector();

		//Initializer
		void initButton();
		void initTileSheetSet();
		//Accessors
		const bool& getActive() const;
		const bool& getHidden() const;
 		const sf::IntRect& getTextureRect() const;
		const sf::Texture* getTexture() const;
		const int getTileIndex() const;
		//Modifiers
		void setHidden(const bool& hidden);
		void setActice(const bool& active);
		void setPosition(const float x, const float y);
		
		//Function

		void updateButtons(const sf::Vector2i& mousePosWindow);
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);

	};
}



#endif
