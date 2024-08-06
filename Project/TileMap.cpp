#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->maps[x][y][z];
				this->maps[x][y][z] = NULL;
			}
			this->maps[x][y].clear();
		}
		this->maps[x].clear();
	}
	this->maps.clear();
	//std::cout << this->maps.size() << "\n";
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height,std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->maxMapSize.x = gridSize * width;
	this->maxMapSize.y = gridSize * height;
	this->layers = 1;
	this->textureFile = texture_file;
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

	if (!this->tileSheet.loadFromFile(texture_file))
	{
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET." << "\n";
	}
}



TileMap::~TileMap()
{
	this->clear();
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

void TileMap::addtile(const unsigned x, const unsigned y, const unsigned z,const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	//Take two indicies from the mouse position in the grid and add a tile to that position if the internal tilemap array allows it.
	if(	x < this->maxSize.x && x>=0 && 
		y < this->maxSize.y && y>=0 &&
		z < this->layers && z>=0)
	{
		if (this->maps[x][y][z] == NULL) 
		{
			/*Ok to add tile*/
			this->maps[x][y][z] = new Tile(x , y , this->gridSizeF,this->tileSheet, texture_rect,collision,type);
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
void TileMap::saveToFile(const std::string file_name)
{
	/*Saves the entire tilemap to a text-
	Format: 
	Basic:
	Size x y
	gridSize
	layers
	texture file
	All Tiles:
	gridPos x y ,layer, Texture rect x y, collision, type
	*/

	std::ofstream out_file;
	out_file.open(file_name);
	if (out_file.is_open())
	{
		out_file << this->maxSize.x << " " << this -> maxSize.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";
		
		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					if(this->maps[x][y][z])
						out_file <<x << " " <<y<<" "<<z<<" "<< this->maps[x][y][z]->getAsString() << " "; //Make Sure this last space is not save!!
				}
			}
		}

	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << "\n";
	}
	out_file.close();

	
}
void TileMap::loadFromFile(const std::string file_name)
{

	std::ifstream in_file;
	in_file.open(file_name);
	if (in_file.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string texture_file = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;

		unsigned trX = 0;
		unsigned trY = 0;
		bool collision = false;
		short type = 0;

		//Basic
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;
		
		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		//this->maxMapSize.x = gridSize * width;
		//this->maxMapSize.y = gridSize * height;
		this->layers = 1;
		this->textureFile = texture_file;
		this->clear();
		this->maps.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
		
		for (size_t x = 0; x < this->maxSize.x; x++)
		{

			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				this->maps[x].resize(this->maxSize.y, std::vector<Tile*>());


				for (size_t z = 0; z < this->layers; z++)
				{

					this->maps[x][y].resize(this->layers, NULL);

				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))
		{
			std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET." << "\n";
		}
		//load all tiles
		while (in_file >> x>>y>>z>>trX>>trY>>collision>>type)
		{
			this->maps[x][y][z] = new Tile(
				x, y,
				this->gridSizeF, 
				this->tileSheet, 
				sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU),
				collision,
				type);
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
	}
	in_file.close();


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
			for (auto* z : y)
			{
				if (z != NULL)
					z->render(target);
			}
		}
	}
}