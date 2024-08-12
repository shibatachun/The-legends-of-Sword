#include "stdafx.h"
#include "QuadTree.h"

QuadTree::QuadTree(const sf::FloatRect& bounds)
{
	this->root = root = new QuadTreeNode(bounds);
}

QuadTree::~QuadTree()
{
	delete this->root;
}

void QuadTree::insert(Tile* tile)
{
	if (this->root->bounds.contains(tile->getPosition())) {
		this->root->insert(tile);
	}
}

void QuadTree::query(const sf::FloatRect& range, std::vector<Tile*>& results)
{
	this->root->queryRange(range, results);
}

void QuadTree::clear()
{
	delete this->root;
	this->root = new QuadTreeNode(root->bounds);
}

void QuadTree::printAllTiles() const
{
	printNode(this->root);
}
