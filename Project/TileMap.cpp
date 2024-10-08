 #include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{

	if (!this->maps.empty())
	{
		for (int x = 0; x < this->maps.size(); x++)
		{
			for (int y = 0; y < this->maps[x].size(); y++)
			{
				for (int z = 0; z < this->maps[x][y].size(); z++)
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
	}
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
	this->quadtree = new QuadTree<Tile>(sf::FloatRect(0, 0, this->maxSizeWorldF.x, this->maxSizeWorldF.y));
	this->box = new gui::ConfirmationBox("Are you sure to save the map? It will rewrite your previous map.", "Yes", "NO");
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

TileMap::TileMap(const std::string file_name, std::map<int, std::string>& textureFileSet)
{

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;
	this->textureFileSet = textureFileSet;
	this->initTextureSet();
	this->loadFromFile(file_name);
	this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
	
}

TileMap::~TileMap()
{
	this->clear();
	delete this->quadtree;
	delete this->box;
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

const bool TileMap::tileEmpty(const int x, const int y, const int z) const
{
	if (x >= 0 && x < this->maxSize.x &&
		y >= 0 && y < this->maxSize.y &&
		z >= 0 && z < this->layers)
	{
		return this->maps[x][y][z].empty();
	}
		
	//throw("ERROR::TILEMAP::TILEEMTPY::TRYING TO ACCESS OUT OF BOUNDS TILE");
	return false;
}

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
	if (x >= 0 && x < static_cast<int>(this->maps.size()))
	{
		if (y >= 0 && y < static_cast<int>(this->maps[x].size()))
		{
			if (layer >= 0 && layer < static_cast<int>(this->maps[x][y].size()))
			{
				return static_cast<int>(this->maps[x][y][layer].size());
			}
		}
	}
	return -1;
}

const sf::Vector2i& TileMap::getMaxSizeGrid() const
{
	return this->maxSize;
}

const sf::Vector2f& TileMap::getMaxSizeF() const
{
	return this->maxSizeWorldF;
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


		Tile* tile;
		
		//this->maps[x][y][z].push_back(new RegularTile(x, y, this->gridSizeF, tileIndex, this->tileSheetSet[tileIndex], texture_rect, collision, type));
		tile = new RegularTile(x, y, this->gridSizeF, tileIndex, this->tileSheetSet[tileIndex], texture_rect, collision, type);

		

		this->maps[x][y][z].push_back(tile);
		if (collision)
		{
			this->quadtree->insert(tile);
			//this->quadtree->printAllTiles();
		}
	
	}
}

void TileMap::addtile(const int x, const int y, const int z, int tileIndex, const sf::IntRect& texture_rect,
	const int enemy_type, const int enemy_amout, const int enemy_tts, const int enemy_md)
{
	//Take two indicies from the mouse position in the grid and add a tile to that position if the internal tilemap array allows it.
	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{

		//this->maps[x][y][z].push_back(new EnemySpawner(x, y, this->gridSizeF, tileIndex, this->tileSheetSet[tileIndex], texture_rect, 0, 0, 0, 0));
		this->maps[x][y][z].push_back(new EnemySpawner(x, y, this->gridSizeF, tileIndex, this->tileSheetSet[tileIndex], texture_rect,
			enemy_type, enemy_amout, enemy_tts, enemy_md));

	}
}

void TileMap::removeTile(const int x, const int y, const int z, const int type)
{
	//Take two indicies from the mouse position in the grid and remove a tile at that position if the internal tilemap array allows it.
	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (!this->maps[x][y][z].empty())
		{
			/*Ok to remove tile*/
			if (type >= 0)
			{
				if (this->getType(x, y, z) == type)
				{
					delete this->maps[x][y][z][this->maps[x][y][z].size() - 1];
					this->maps[x][y][z].pop_back();
				}
				
			}
			else
			{
				delete this->maps[x][y][z][this->maps[x][y][z].size() - 1];
				this->maps[x][y][z].pop_back();
			}
		

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
	type
	gridPos x y ,layer,
	tilesheet index
	Texture rect x y,
	collision
	tile_specific...
	*/
	

	//if (!this->box->show())
	//{
	//	return;
	//}
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

						out_file << x << " " << y << " " << z << " " << this->maps[x][y][z][k]->getAsString() <<std::endl; //Make Sure this last space is not save!!
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
		this->maxSizeWorldF.x = static_cast<float>(size.x * gridSize);
		this->maxSizeWorldF.y = static_cast<float>(size.y * gridSize);
		//this->maxMapSize.x = gridSize * width;
		//this->maxMapSize.y = gridSize * height;
		this->clear();
		this->quadtree = new QuadTree<Tile>(sf::FloatRect(0, 0, this->gridSizeF * this->maxSize.x, this->gridSizeF * this->maxSize.y));
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
		while (in_file >> x >> y >> z >> type)
		{
			if (type == TileTypes::ENEMYSPAWN)
			{
				//amout, timee, max dist
				int enemy_type = 0;
				int enemy_am = 0;
				int enemy_tts = 0;
				int enemy_md = 0;
				in_file >>index>> trX >> trY  >> enemy_type >> enemy_am >> enemy_tts >>enemy_md ;


				this->maps[x][y][z].push_back(
					new EnemySpawner(
						x, y,
						this->gridSizeF,
						index,
						this->tileSheetSet[index],
						sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
						enemy_type,
						enemy_am,
						enemy_tts,
						enemy_type
					));
			}
			else
			{
				in_file >>index>> trX >> trY >> collision;

				Tile* tile = new RegularTile(
					x, y,
					this->gridSizeF,
					index,
					this->tileSheetSet[index],
					sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
					collision,
					type);
				this->maps[x][y][z].push_back(tile);
				if (collision)
				{
					//std::cout << "dui" << "\n";
					this->quadtree->insert(tile);
					//this->quadtree->printAllTiles();

				}
			}
				
		}
	
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
	}
	in_file.close();


}

void TileMap::updateWorldBoundSColision(Entity* entity, const float& dt)
{
}

void TileMap::updateTileCollision(Entity* entity, const float& dt)
{

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

	int range = 10;
	sf::Vector2i entityGridPos = entity->getGridPosition(this->gridSizeI);
	sf::Vector2f entityVelocity = entity->getVelocity();
	//std::cout << "x: " << entityVelocity.x << "y:" << entityVelocity.y << std::endl;

	sf::FloatRect entityBounds(static_cast<float>((entityGridPos.x - range) * this->gridSizeI),
		static_cast<float>((entityGridPos.y - range) * this->gridSizeI),
		static_cast<float>((2 * range + 1) * this->gridSizeI),
		static_cast<float>((2 * range + 1) * this->gridSizeI));

	//std::cout << "entity bounds" << entityBounds.getPosition().x << " " << entityBounds.getPosition().y << std::endl;
	std::vector<Tile*> potentialColliders;
	this->quadtree->query(entityBounds, potentialColliders, entityVelocity);

	std::sort(potentialColliders.begin(), potentialColliders.end(), [](const Tile* a, const Tile* b) {
		return a->getGlobalBounds().left < b->getGlobalBounds().left;
		}
	);

	/*for (auto& i : potentialColliders)
	{
		sf::Vector2f pos = i->getPosition();
		std::cout << "Potential Colliders Tiles at position: (" << pos.x << ", " << pos.y << ")" << std::endl;
	}*/
	int count = 0;
	for (Tile* tile : potentialColliders) {
		if (tile != NULL) {

			tile->update();
			sf::FloatRect playerBounds = entity->getGlobalBounds();
			sf::FloatRect wallBounds = tile->getGlobalBounds();
			sf::FloatRect nextPositionBound = entity->getNextPositionBounds(dt);

			if (wallBounds.left + wallBounds.width < playerBounds.left && entityVelocity.x>0) //walk left
			{
				continue;
			}

			if (wallBounds.left > playerBounds.left + playerBounds.width)
			{
				//std::cout << "Break the loop��" << std::endl;
				break;

			}
			count++;
			if (tile->getCollision() &&
				tile->intersects(nextPositionBound))
			{
				//Bottom collision
				if (playerBounds.top < wallBounds.top &&
					playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height)
				{
					entity->stopVelocityY();

					entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
				}
				//Top collision
				else if (playerBounds.top > wallBounds.top &&
					playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height)
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

void TileMap::updateTiles(Entity* entity, const float& dt, EnemySystem& enemySystem)
{
	this->layer = 0;

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

	//Tiles
	this->fromX = entity->getGridPosition(this->gridSizeI).x - 10;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxSize.x)
	{
		this->fromX = this->maxSize.x;
	}

	this->toX = entity->getGridPosition(this->gridSizeI).x + 10;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxSize.x)
	{
		this->toX = this->maxSize.x;
	}

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 10;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->maxSize.y)
	{
		this->fromY = this->maxSize.y;
	}


	this->toY = entity->getGridPosition(this->gridSizeI).y + 10;

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
			for (int k = 0; k < this->maps[x][y][this->layer].size(); k++)
			{

				this->maps[x][y][this->layer][k]->update();
				if (this->maps[x][y][this->layer][k]->getType() == TileTypes::ENEMYSPAWN)
				{
				/*	std::cout << "deleted!" << std::endl;
					delete this->maps[x][y][this->layer][k];
					this->maps[x][y][this->layer].pop_back();
					return;
					*/
					EnemySpawner* es = dynamic_cast<EnemySpawner*> (this->maps[x][y][this->layer][k]);
					if (es)
					{
						if (!es->getSpawned())
						{
							enemySystem.createEnemy(RAT, x * this->gridSizeF, y * this->gridSizeF);
							es->setSpawned(true);
						}
						//std::cout << "Spawned!" << std::endl;
					}
				}
			}



		}

	}
}

const int TileMap::getType(const int x, const int y, const int z) const
{
	return this->maps[x][y][this->layer].back()->getType();
}



void TileMap::update(Entity* entity, const float& dt)
{
	//this->updateTileCollision(entity, dt);

}


void TileMap::render(sf::RenderTarget& target,const int range_x, const int range_y, const sf::Vector2i& gridPosition, sf::Shader* shader, sf::Vector2f playerPosition, const bool show_collision)
{
	
	this->layer = 0;
	this->fromX = gridPosition.x - range_x;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxSize.x)
	{
		this->fromX = this->maxSize.x;
	}

	this->toX = gridPosition.x + range_x;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxSize.x)
	{
		this->toX = this->maxSize.x;
	}

	this->fromY = gridPosition.y - range_y;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->maxSize.y)
	{
		this->fromY = this->maxSize.y;
	}


	this->toY = gridPosition.y + range_y;

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
					if (this->maps[x][y][this->layer][k] != NULL)
					{

						if (this->maps[x][y][this->layer][k]->getType() == TileTypes::DOODAD)
						{
							this->deferredRenderStack.push(this->maps[x][y][this->layer][k]);
						}
						else
						{
							if (shader)
							{
								this->maps[x][y][this->layer][k]->render(target, shader, playerPosition);

							}
							else
							{
								this->maps[x][y][this->layer][k]->render(target);
							}
						}

						if (show_collision)
						{
							if (this->maps[x][y][this->layer][k]->getCollision())
							{
								this->collisionBox.setPosition(this->maps[x][y][this->layer][k]->getPosition());
								target.draw(this->collisionBox);

							}
						}
						if (this->maps[x][y][this->layer][k]->getType() == TileTypes::ENEMYSPAWN)
						{
							this->collisionBox.setPosition(this->maps[x][y][this->layer][k]->getPosition());
							target.draw(this->collisionBox);
						}
					}
				
				
				}	
		}

	}
	//this->quadtree->draw(target);
	
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

void TileMap::renderDeferred(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPosition)
{
	while (!this->deferredRenderStack.empty())
	{
		if (shader)
		{
			deferredRenderStack.top()->render(target,shader,playerPosition);

		}
		else
		{

			deferredRenderStack.top()->render(target);
		}
		deferredRenderStack.pop();
	}
}
