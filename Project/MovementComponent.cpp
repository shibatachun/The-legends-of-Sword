#include "stdafx.h"
#include "MovementComponent.h"


MovementComponent::MovementComponent(sf::Sprite& sprite,
	float maxVelocity,float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}
MovementComponent::~MovementComponent()
{
}

const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;
		break;
	case MOVING:
		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;
		break;
	case MOVEING_LEFT:
		if (this->velocity.x < 0.f)
			return true;
		break;
	case MOVING_RIGHT:
		if (this->velocity.x > 0.f)
			return true;
		break;
	case MOVING_UP:
		if (this->velocity.y < 0.f)
			return true;
		break;
	case MOVING_DOWN:
		if (this->velocity.y > 0.f)
			return true;
	default:
		break;
	}
	return false;
}

void MovementComponent::stopVelocity()
{
	/* Resets the velocity to 0.*/
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
	/*Reset velocity at y axis*/
	this->velocity.y = 0.f;
}


//Functions
void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	/*Aceelerating a sprite unitl it reaches the max velocity*/
	//Acceleration
	this->velocity.x += this->acceleration * dir_x;

	
	this->velocity.y += this->acceleration * dir_y;
	
}


void MovementComponent::update(const float& dt)
{
	
	/*
	Decelerations the sprite and controls the maximum velocity
	Moves the sprites.
	*/
	if (this->velocity.x > 0.f)

	{	//Max velocity check for right
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;
		
		//Deceleration x positive
		this->velocity.x  -= deceleration;
		if (this->velocity.x < 0.f)
		{
			this->velocity.x = 0.f;
		}
	}
	else if (this->velocity.x < 0.f)
	{
		//Max velocity check x for left
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;

	}
	


	if (this->velocity.y > 0.f) //check for right
	{

		//Max velocity check for right
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		//Deceleration y positive
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f)//check for left
	{
		//Max velocity check x for left
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;
		//Deceleration y negatgive
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;

	}
	//Final move
	this->sprite.move(this->velocity * dt); //Uses velocity

}
