#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite), textureSheet(texture_sheet), lastAnimation(NULL), priorityAnimation(NULL)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

 bool& AnimationComponent::isDone(const std::string key) 
{
	 return this->animations[key]->isDone();
}




void AnimationComponent::addAnimation(const std::string key
	, float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height,  float offset_x,  float offset_y)
{	
	
	this->animations[key] = new Animation(this->sprite, this->textureSheet
		, animation_timer, start_frame_x, start_frame_y, frames_x, frames_y, width, height,offset_x,offset_y);
}

bool AnimationComponent::play(const std::string key, const float& dt, const bool priority )
{
	
	
	if (this->priorityAnimation)
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}

			}
			//if the priority animation is done, remove it.
			if(this->animations[key]->play(dt))
			{
			
				this->priorityAnimation = NULL;
			}

		}
	}
	else
	{
		if (priority)
		{
			this->priorityAnimation = animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}

		}
		if (this->animations[key]->play(dt))
		{
			this->priorityAnimation = NULL;
		}
	}
	return this->isDone(key);

}

void AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{
	if (this->priorityAnimation)
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}

			}
			if (this->animations[key]->play(dt, abs(modifier / modifier_max)))
			{
				
				this->priorityAnimation = NULL;
			}

		}
	}
	else
	{
		if (priority)
		{
			this->priorityAnimation = animations[key];
		}
		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}

		}
		if (this->animations[key]->play(dt, abs(modifier / modifier_max)))
		{
			this->priorityAnimation = NULL;
		}
	}
}
 