#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->maxMapSize.x = gridSize * width;
	this->maxMapSize.y = gridSize * height;
	this->layers = 1;

	this->maps.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->maps[x].resize(this->maxSize.y, std::vector<Tile*>());
			
			
			for (size_t z = 0; z < this->layers; z++)
			{
				this->maps[x][y].resize(this->layers,NULL);
				
			}
		}
	}

	if (!this->tileSheet.loadFromFile("Resources/images/Tiles/TX_Tileset Grass.png"))
	{
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET." << "\n";
	}
}



TileMap::~TileMap()
{
	for (size_t x = 0; x < this->maxSize.x; x ++ )
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->maps[x][y][z];
			}
		}
	}
	
}
//Accessors

const sf::Texture* TileMap::getTileSheet()
{
	return &this->tileSheet;
}
const sf::Vector2i TileMap::getMaxMapSize()
{	
	return this->maxMapSize;
}
//Functions
void TileMap::update()
{
}


void TileMap::addtile(const unsigned x, const unsigned y, const unsigned z,const sf::IntRect& texture_rect)
{
	//Take two indicies from the mouse position in the grid and add a tile to that position if the internal tilemap array allows it.
	if(	x < this->maxSize.x && x>=0 && 
		y < this->maxSize.y && y>=0 &&
		z < this->layers && z>=0)
	{
		if (this->maps[x][y][z] == NULL) 
		{
			/*Ok to add tile*/
			this->maps[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF,this->tileSheet, texture_rect);
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	//Take two indicies from the mouse position in the grid and remove a tile at that position if the internal tilemap array allows it.
	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->maps[x][y][z] != NULL)
		{
			/*Ok to remove tile*/
			delete this->maps[x][y][z];
			this->maps[x][y][z] = NULL;

		}
	}
}
void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->maps)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if (z != NULL)
					z->render(target);
			}
		}
	}
}