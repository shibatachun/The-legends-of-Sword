#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"


class Entity
{
private:
	void initVariables();

	//Can directly access by child classes
protected:
	
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	

public:
	Entity();
	virtual ~Entity();
	//Component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	//Functions
	virtual void setPosstion(const float x, const float y);
	virtual void move( const float x, const float y,const float dt );
	virtual void update(const float& dt) ;
	virtual void render(sf::RenderTarget* target);


};
#endif // 



