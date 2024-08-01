#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
{
	this->gridSizeF = 50.f;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = 100;
	this->maxSize.y = 100;
	this->layers = 1;
	this->maps.resize(this->maxSize.x);
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		
		this->maps.push_back(std::vector<std::vector<Tile>>());
		
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->maps[x].resize(this->maxSize.y);
			this->maps[x].push_back(std::vector<Tile>());
			
			for (size_t z = 0; z < this->layers; z++)
			{
				this->maps[x][y].resize(this->layers);
				this->maps[x][y].push_back(Tile(x * this->gridSizeF, y * this->gridSizeF,this->gridSizeF));
			}
		}
	}
}

//Functions

TileMap::~TileMap()
{
}
void TileMap::update()
{
}
void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->maps)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				z.render(target);
			}
		}
	}
}
