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
	this->maxSizeWorldF.x = gridSize * static_cast<float>( width);
	this->maxSizeWorldF.y = gridSize * static_cast<float>(height);
	this->layers = 1;
	this->textureFile = texture_file;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0; 
	this->layer = 0;

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

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);

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
const sf::Vector2f TileMap::getMaxMapSize()
{	
	return this->maxSizeWorldF;
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


void TileMap::updateCollision(Entity* entity)
{
	//World Bounds
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosstion(0.f, entity->getPosition().y);
		entity->stopVelocityX();

	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width >this->maxSizeWorldF.x) {

		entity->setPosstion(this->maxSizeWorldF.x - entity->getGlobalBounds().width,entity->getPosition().y);
		entity->stopVelocityX();
	}
	
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosstion( entity->getPosition().x, 0.f);
		entity->stopVelocityY();

	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height> this->maxSizeWorldF.y) {

		entity->setPosstion(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}

	//Tiles
	this->fromX = entity->getGridPosition(this->gridSizeU).x -1;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxSize.x)
	{
		this->fromX = this->maxSize.x ;
	}

	this->toX = entity->getGridPosition(this->gridSizeU).x + 3;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxSize.x)
	{
		this->toX = this->maxSize.x ;
	}

	this->fromY = entity->getGridPosition(this->gridSizeU).y - 1;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->maxSize.y)
	{
		this->fromY = this->maxSize.y ;
	}


	this->toY = entity->getGridPosition(this->gridSizeU).y + 3;

	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toY > this->maxSize.y)
	{
		this->toY = this->maxSize.y ;
	}
	
	
	
	for (size_t x = fromX; x < this->toX; x++)
	{

		for (size_t y = this->fromY; y < this->toY; y++)
		{
			sf::FloatRect playerBounds = entity->getGlobalBounds();
			sf::FloatRect wallBounds = this->maps[x][y][this->layer]->getGlobalBounds();
			sf::FloatRect nextPositionBound = entity->getNextPositionBounds();

			if (this->maps[x][y][this->layer]->getCollision() &&
				this->maps[x][y][this->layer]->intersects(nextPositionBound))
			{
				//Bottom collision
				if (playerBounds.top < wallBounds.top &&
					playerBounds.top+playerBounds.height < wallBounds.top + wallBounds.height&&
					playerBounds.left < wallBounds.left + wallBounds.width &&
					playerBounds.left+playerBounds.width > wallBounds.left)
				{
					entity->stopVelocityY();
					entity->setPosstion(playerBounds.left, wallBounds.top - playerBounds.height);
				}
				//Top collision
				else if (playerBounds.top > wallBounds.top  &&
					playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height &&
					playerBounds.left < wallBounds.left + wallBounds.width &&
					playerBounds.left + playerBounds.width > wallBounds.left)
				{
					entity->stopVelocityY();
					entity->setPosstion(playerBounds.left, wallBounds.top - playerBounds.height);
				}
			}
				
				
			
		}
	
	}
	
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target, Entity* entity)
{
	if (entity) {
		this->layer = 0;
		this->fromX = entity->getGridPosition(this->gridSizeU).x - 5;
		if (this->fromX < 0)
		{
			this->fromX = 0;
		}
		else if (this->fromX > this->maxSize.x)
		{
			this->fromX = this->maxSize.x;
		}

		this->toX = entity->getGridPosition(this->gridSizeU).x + 8;
		if (this->toX < 0)
		{
			this->toX = 0;
		}
		else if (this->toX > this->maxSize.x)
		{
			this->toX = this->maxSize.x;
		}

		this->fromY = entity->getGridPosition(this->gridSizeU).y - 5;
		if (this->fromY < 0)
		{
			this->fromY = 0;
		}
		else if (this->fromY > this->maxSize.y)
		{
			this->fromY = this->maxSize.y;
		}


		this->toY = entity->getGridPosition(this->gridSizeU).y + 8;

		if (this->toY < 0)
		{
			this->toY = 0;
		}
		else if (this->toY > this->maxSize.y)
		{
			this->toY = this->maxSize.y;
		}

		for (size_t x = fromX; x < this->toX; x++)
		{
			for (size_t y = this->fromY; y < this->toY; y++)
			{

				this->maps[x][y][this->layer]->render(target);
				if (this->maps[x][y][this->layer]->getCollision())
				{
					this->collisionBox.setPosition(this->maps[x][y][this->layer]->getPosition());
					target.draw(this->collisionBox);

				}


			}

		}
	}
	else {
		for (auto& x : this->maps)
		{
			for (auto& y : x)
			{
				for (auto* z : y)
				{
					if (z != NULL)
					{
						z->render(target);
						if (z->getCollision())
						{
							this->collisionBox.setPosition(z->getPosition());
							target.draw(this->collisionBox);

						}
					}
				}
			}
		}
	}

}