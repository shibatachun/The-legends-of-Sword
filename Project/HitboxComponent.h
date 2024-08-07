#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H




class HitboxComponent
{

private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;
public:
	HitboxComponent(sf::Sprite& sprite, 
		float offset_x, float offset_y,
		float width,float height);
	virtual ~HitboxComponent();

	//Accessors
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	// Modifers
	void setPosition(sf::Vector2f& position);
	void setPosition(const float x, const float y);
	//Function

	bool intersects(const sf::FloatRect& frect);
	void update();
	void render(sf::RenderTarget& target);



};


#endif

