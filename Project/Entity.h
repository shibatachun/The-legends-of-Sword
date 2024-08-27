#ifndef ENTITY_H
#define ENTITY_H

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"

class HitboxComponent;
class MovementComponent;
class AnimationComponent;
class AttributeComponent; 
class SkillComponent;

class Entity
{
private:
	void initVariables();

	//Can directly access by child classes
protected:
	
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;
	AttributeComponent* attributeComponent;
	SkillComponent* skillComponent;
	

public:
	Entity();
	virtual ~Entity();
	//Component functions
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(
		float offset_x, float offset_y,
		float width, float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent( sf::Texture& texture_sheet);
	void createAttributeComponent(const int level);
	void createSkillComponent();

	//Acceesors
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2f getCenter() const;
	virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const ;
	virtual const sf::Vector2f& getVelocity() const;
	//Modifiers
	virtual void setPosition(const float x, const float y);
	
	//Functions
	virtual const float getDistance(const Entity& entity) const;
	virtual void move( const float x, const float y,const float dt );
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();
	virtual void update(const float& dt, sf::Vector2f& mouse_Pos_View) = 0 ;
	virtual void render(sf::RenderTarget& target,sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox) = 0;


};
#endif // 



