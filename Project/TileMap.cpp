 #include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	for (int x = 0; x < this->maxSize.x; x++)
	{
		for (int y = 0; y < this->maxSize.y; y++)
		{
			for (int z = 0; z < this->layers; z++)
			{
				for (size_t k = 0; k < this->maps[x][y][z].size(); k++)
				{
					delete this->maps[x][y][z][k];
					this->maps[x][y][z][k] = NULL;
				}
				
				this->maps[x][y][z].clear();
			}
			this->maps[x][y].clear();
		}
		this->maps[x].clear();
	}
	this->maps.clear();

	this->quadtree->clear();
	//std::cout << this->maps.size() << "\n";
}

TileMap::TileMap(float gridSize, int width, int height, std::map<int, std::string>& textureFileSet)
{
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<int>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->maxSizeWorldF.x = gridSize * static_cast<float>(width);
	this->maxSizeWorldF.y = gridSize * static_cast<float>(height);
	this->layers = 1;
	this->textureFileSet = textureFileSet;
	this->quadtree = new QuadTree(sf::FloatRect(0, 0, this->maxSizeWorldF.x, this->maxSizeWorldF.y));

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0; 
	this->layer = 0;


	this->maps.resize(this->maxSize.x, std::vector<std::vector<std::vector<Tile*>>>());
	for (int x = 0; x < this->maxSize.x; x++)
	{
		
		for (int y = 0; y < this->maxSize.y; y++)
		{
			this->maps[x].resize(this->maxSize.y, std::vector<std::vector<Tile*>>());
			
			
			for (int z = 0; z < this->layers; z++)
			{

				this->maps[x][y].resize(this->layers,std::vector<Tile*>());
				
			}
		}
	}

	/*if (!this->tileSheet.loadFromFile(this->textureFile))
	{
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET." << "\n";
	}*/
	initTextureSet();

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);

}



TileMap::~TileMap()
{
	this->clear();
	delete this->quadtree;
}

//initializer

void TileMap::initTextureSet()
{
	for (auto& i : this->textureFileSet)
	{

		if (this->tileSheetSet[this->tileSheetCount].loadFromFile(i.second))
			tileSheetCount++;
		else
			std::cout << "ERROR::CAN NOT LOAD FROM TEXTURE FILE";
	}
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

const int TileMap::getLayerSize(const int x, const int y, const int z) const
{
	if (x >= 0 && x < this->maps.size())
	{
		if (y >= 0 && y < this->maps[x].size())
		{
			if (layer >= 0 && layer < this->maps[x][y].size())
			{
				return this->maps[x][y][layer].size();
			}
		}
	}
	return -1;
}
//Functions

void TileMap::addtile(const int x, const int y, const int z, int tileIndex ,const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	//Take two indicies from the mouse position in the grid and add a tile to that position if the internal tilemap array allows it.
	if(	x < this->maxSize.x && x>=0 && 
		y < this->maxSize.y && y>=0 &&
		z < this->layers && z>=0)
	{
		/*Ok to add tile*/
		Tile* tile = new Tile(x, y, this->gridSizeF, tileIndex, this->tileSheetSet[tileIndex], texture_rect, collision, type);
		this->maps[x][y][z].push_back(tile);
		if (collision)
		{
			this->quadtree->insert(tile);
			this->quadtree->printAllTiles();
		}
	
	}
}

void TileMap::removeTile(const int x, const int y, const int z)
{
	//Take two indicies from the mouse position in the grid and remove a tile at that position if the internal tilemap array allows it.
	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (!this->maps[x][y][z].empty())
		{
			/*Ok to remove tile*/
			delete this->maps[x][y][z][this->maps[x][y][z].size()-1];
			this->maps[x][y][z].pop_back();

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
			<< this->gridSizeI << "\n"
			<< this->layers << "\n";
		
		for (int x = 0; x < this->maxSize.x; x++)
		{
			for (int y = 0; y < this->maxSize.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if (!this->maps[x][y][z].empty())
					{
						for (int k = 0; k < this->maps[x][y][z].size(); k++)
						{

						out_file << x << " " << y << " " << z << " " << this->maps[x][y][z][k]->getAsString() << " "; //Make Sure this last space is not save!!
						}
					}
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
		sf::Vector2i size;
		int gridSize = 0;
		int layers = 0;
		std::string texture_file = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int index = 0;
		int trX = 0;
		int trY = 0;
		
		bool collision = false;
		short type = 0;

		//Basic
		in_file >> size.x >> size.y >> gridSize >> layers;
		
		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = static_cast<unsigned>(this->gridSizeF);
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		//this->maxMapSize.x = gridSize * width;
		//this->maxMapSize.y = gridSize * height;
		this->clear();
		this->quadtree = new QuadTree(sf::FloatRect(0, 0, this->gridSizeF * this->maxSize.x, this->gridSizeF * this->maxSize.y));
		this->layers = layers;
		//this->textureFile = texture_file;
		
	
		this->maps.resize(this->maxSize.x, std::vector<std::vector<std::vector<Tile*>>>());
		for (int x = 0; x < this->maxSize.x; x++)
		{

			for (int y = 0; y < this->maxSize.y; y++)
			{
				this->maps[x].resize(this->maxSize.y, std::vector< std::vector<Tile*>>());


				for (int z = 0; z < this->layers; z++)
				{

					this->maps[x][y].resize(this->layers, std::vector<Tile*>());

				}
			}
		}

		/*if (!this->tileSheet.loadFromFile(texture_file))
		{
			std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET." << "\n";
		}*/
		//load all tiles
		while (in_file >> x>>y>>z >> index>> trX >> trY>>collision>>type)
		{
			Tile* tile = new Tile(
				x, y,
				this->gridSizeF,
				index,
				this->tileSheetSet[index],
				sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
				collision,
				type);
			this->maps[x][y][z].push_back (tile);
			if (collision)
			{
				std::cout << "dui" << "\n";
				this->quadtree->insert(tile);
				this->quadtree->printAllTiles();
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
	}
	in_file.close();


}

//void TileMap::updateCollision(Entity* entity, const float& dt)
//{
//	//World Bounds
//	if (entity->getPosition().x < 0.f)
//	{
//		entity->setPosition(0.f, entity->getPosition().y);
//		entity->stopVelocityX();
//
//	}
//	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x) {
//
//		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
//		entity->stopVelocityX();
//	}
//
//	if (entity->getPosition().y < 0.f)
//	{
//		entity->setPosition(entity->getPosition().x, 0.f);
//		entity->stopVelocityY();
//
//	}
//	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y) {
//
//		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
//		entity->stopVelocityY();
//	}
//
//	//Tiles
//	this->fromX = entity->getGridPosition(this->gridSizeI).x - 10;
//	if (this->fromX < 0)
//	{
//		this->fromX = 0;
//	}
//	else if (this->fromX > this->maxSize.x)
//	{
//		this->fromX = this->maxSize.x;
//	}
//
//	this->toX = entity->getGridPosition(this->gridSizeI).x + 10;
//	if (this->toX < 0)
//	{
//		this->toX = 0;
//	}
//	else if (this->toX > this->maxSize.x)
//	{
//		this->toX = this->maxSize.x;
//	}
//
//	this->fromY = entity->getGridPosition(this->gridSizeI).y - 10;
//	if (this->fromY < 0)
//	{
//		this->fromY = 0;
//	}
//	else if (this->fromY > this->maxSize.y)
//	{
//		this->fromY = this->maxSize.y;
//	}
//
//
//	this->toY = entity->getGridPosition(this->gridSizeI).y + 10;
//
//	if (this->toY < 0)
//	{
//		this->toY = 0;
//	}
//	else if (this->toY > this->maxSize.y)
//	{
//		this->toY = this->maxSize.y;
//	}
//
//
//
//	for (int x = fromX; x < this->toX; x++)
//	{
//
//		for (int y = this->fromY; y < this->toY; y++)
//		{
//			for (int k = 0; k < this->maps[x][y][this->layer].size(); k++)
//			{
//
//
//				if (this->maps[x][y][this->layer][k] != NULL) {
//					sf::FloatRect playerBounds = entity->getGlobalBounds();
//					sf::FloatRect wallBounds = this->maps[x][y][this->layer][k]->getGlobalBounds();
//					sf::FloatRect nextPositionBound = entity->getNextPositionBounds(dt);
//
					//if (this->maps[x][y][this->layer][k]->getCollision() &&
					//	this->maps[x][y][this->layer][k]->intersects(nextPositionBound))
//					{
//
						//Bottom collision
						//if (playerBounds.top < wallBounds.top &&
						//	playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height &&
						//	playerBounds.left < wallBounds.left + wallBounds.width &&
						//	playerBounds.left + playerBounds.width > wallBounds.left)
						//{
						//	entity->stopVelocityY();

						//	entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
						//}
						//Top collision
						//else if (playerBounds.top > wallBounds.top &&
						//	playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height &&
						//	playerBounds.left < wallBounds.left + wallBounds.width &&
						//	playerBounds.left + playerBounds.width > wallBounds.left)
						//{
						//	entity->stopVelocityY();

						//	entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
						//}
						//Right Collision
						//if (playerBounds.left < wallBounds.left &&
						//	playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width &&
						//	playerBounds.top < wallBounds.top + wallBounds.height &&
						//	playerBounds.top + playerBounds.height > wallBounds.top)
						//{
						//	entity->stopVelocityX();

						//	entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
						//}
						//Left Collision
						//else if (playerBounds.left > wallBounds.left &&
						//	playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width &&
						//	playerBounds.top < wallBounds.top + wallBounds.height &&
						//	playerBounds.top + playerBounds.height > wallBounds.top)
						//{
						//	entity->stopVelocityX();

						//	entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
						//}
//					}
//				}
//			}
//
//
//
//		}
//
//	}
//
//}

void TileMap::updateCollision(Entity* entity, const float& dt)
{
	//World Bounds
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();

	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x) {

		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}

	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();

	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y) {

		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}

	int range = 1;
	sf::Vector2i entityGridPos = entity->getGridPosition(this->gridSizeI);
	sf::FloatRect entityBounds((entityGridPos.x - range) * this->gridSizeI,
		(entityGridPos.y - range) * this->gridSizeI,
		(2 * range + 1) * this->gridSizeI,
		(2 * range + 1) * this->gridSizeI);
	//std::cout << "entity bounds" << entityBounds.getPosition().x << " " << entityBounds.getPosition().y << std::endl;
	std::vector<Tile*> potentialColliders;
	this->quadtree->query(entityBounds, potentialColliders); 
	//for (auto& i : potentialColliders)
	//{
	//	sf::Vector2f pos = i->getPosition();
	//	std::cout << "Potential Colliders Tiles at position: (" << pos.x << ", " << pos.y << ")" << std::endl;
	//}

	for (Tile* tile : potentialColliders) {
		if (tile != NULL) {
			sf::FloatRect playerBounds = entity->getGlobalBounds();
			sf::FloatRect wallBounds = tile->getGlobalBounds();
			sf::FloatRect nextPositionBound = entity->getNextPositionBounds(dt);
			if (tile->getCollision() &&
				tile->intersects(nextPositionBound))
			{
				//Bottom collision
				if (playerBounds.top < wallBounds.top &&
					playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height &&
					playerBounds.left < wallBounds.left + wallBounds.width &&
					playerBounds.left + playerBounds.width > wallBounds.left)
				{
					entity->stopVelocityY();

					entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
				}
				//Top collision
				else if (playerBounds.top > wallBounds.top &&
					playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height &&
					playerBounds.left < wallBounds.left + wallBounds.width &&
					playerBounds.left + playerBounds.width > wallBounds.left)
				{
					entity->stopVelocityY();

					entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
				}
				//Right Collision
				if (playerBounds.left < wallBounds.left &&
					playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width &&
					playerBounds.top < wallBounds.top + wallBounds.height &&
					playerBounds.top + playerBounds.height > wallBounds.top)
				{
					entity->stopVelocityX();

					entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
				}
				//Left Collision
				else if (playerBounds.left > wallBounds.left &&
					playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width &&
					playerBounds.top < wallBounds.top + wallBounds.height &&
					playerBounds.top + playerBounds.height > wallBounds.top)
				{
					entity->stopVelocityX();

					entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
				}
			}
			
		}




	}
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target, const sf::Vector2i& gridPosition)
{
	
	this->layer = 0;
	this->fromX = gridPosition.x - 10;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxSize.x)
	{
		this->fromX = this->maxSize.x;
	}

	this->toX = gridPosition.x + 10;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxSize.x)
	{
		this->toX = this->maxSize.x;
	}

	this->fromY = gridPosition.y - 10;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->maxSize.y)
	{
		this->fromY = this->maxSize.y;
	}


	this->toY = gridPosition.y + 10;

	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toY > this->maxSize.y)
	{
		this->toY = this->maxSize.y;
	}

	for (int x = fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
				for (size_t k = 0; k < this->maps[x][y][this->layer].size(); k++)
				{
					if (this->maps[x][y][this->layer][k]->getType() == TileTypes::DOODAD)
					{
						this->deferredRenderStack.push(this->maps[x][y][this->layer][k]);
					}
					else
					{
						this->maps[x][y][this->layer][k]->render(target);
					}

					if (this->maps[x][y][this->layer][k]->getCollision())
					{
						this->collisionBox.setPosition(this->maps[x][y][this->layer][k]->getPosition());
						target.draw(this->collisionBox);

					}
				
				}	
		}

	}
	
	/*else {
		for (auto& x : this->maps)
		{
			for (auto& y : x)
			{
				for (auto &z : y)
				{
					for (auto* k : z)
					{
						k->render(target);
						if (k->getCollision())
						{
							this->collisionBox.setPosition(k->getPosition());
							target.draw(this->collisionBox);
						}
					}
					
				}
			}
		}
	}*/

}

void TileMap::renderDeferred(sf::RenderTarget& target)
{
	while (!this->deferredRenderStack.empty())
	{
		deferredRenderStack.top()->render(target);
		deferredRenderStack.pop();
	}
}
