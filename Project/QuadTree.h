#ifndef QUADTREE_H
#define QUADTREE_H


#include "TileMap.h"




class QuadTree {

private:
    class QuadTreeNode {
    public:
        std::vector<Tile*> objects;
        QuadTreeNode* children[4]; 
        sf::FloatRect bounds;
        int MAX_OBJECTS = 4;

        QuadTreeNode(const sf::FloatRect& bounds) : bounds(bounds) {
            for (int i = 0; i < 4; ++i) {
                children[i] = nullptr;
            }
        }

        ~QuadTreeNode() {
            for (int i = 0; i < 4; ++i) {
                delete children[i];
            }
        }

        void insert(Tile* object) {
            
            if (children[0] != nullptr) {
                int index = getChildIndex(object);
                if (index != -1) {
                    children[index]->insert(object);
                    return;
                }
            }

            
            objects.push_back(object);

            
            if (objects.size() > MAX_OBJECTS && children[0] == nullptr) {
                subdivide();
               
                for (auto it = objects.begin(); it != objects.end();) {
                    int index = getChildIndex(*it);
                    if (index != -1) {
                        children[index]->insert(*it);
                        it = objects.erase(it);
                    }
                    else {
                        ++it;
                    }
                }
            }
        }

        void queryRange(const sf::FloatRect& range, std::vector<Tile*>& results) {
            // if the range is not intersect, return
            
            if (!bounds.intersects(range)) {
                return;
            }

            // find the tile that intersect with the range
            for (auto& object : objects) {
                if (range.contains(object->getPosition())) {
                    results.push_back(object);
                }
            }

            // recusively find the child node
            if (children[0] != nullptr) {
                for (int i = 0; i < 4; ++i) {
                    children[i]->queryRange(range, results);
                }
            }
        }

    private:
        // subdivide to 4 childnode 
        void subdivide() {
            float halfWidth = bounds.width / 2.0f;
            float halfHeight = bounds.height / 2.0f;

            children[0] = new QuadTreeNode({ bounds.left, bounds.top, halfWidth, halfHeight });
            children[1] = new QuadTreeNode({ bounds.left + halfWidth, bounds.top, halfWidth, halfHeight });
            children[2] = new QuadTreeNode({ bounds.left, bounds.top + halfHeight, halfWidth, halfHeight });
            children[3] = new QuadTreeNode({ bounds.left + halfWidth, bounds.top + halfHeight, halfWidth, halfHeight });
        }

        // insert the node upon its position
        int getChildIndex(Tile* object) {
            int index = -1;
            float midX = bounds.left + bounds.width / 2.0f;
            float midY = bounds.top + bounds.height / 2.0f;

            bool topQuadrant = (object->getPosition().y < midY);
            bool bottomQuadrant = (object->getPosition().y >= midY);

            if (object->getPosition().x < midX) {
                if (topQuadrant) {
                    index = 0;
                }
                else if (bottomQuadrant) {
                    index = 2;
                }
            }
            else if (object->getPosition().x >= midX) {
                if (topQuadrant) {
                    index = 1;
                }
                else if (bottomQuadrant) {
                    index = 3;
                }
            }

            return index;
        }
    };

    void printNode(QuadTreeNode* node) const {
        if (node == nullptr) {
            return;
        }

        // print all the node that been inserted
        for (const auto& tile : node->objects) {
            sf::Vector2f pos = tile->getPosition();
            std::cout << "Tile at position: (" << pos.x << ", " << pos.y << ")" << std::endl;
        }

        // recursively print the node position
        for (int i = 0; i < 4; ++i) {
            if (node->children[i] != nullptr) {
                printNode(node->children[i]);
            }
        }
    }
    QuadTreeNode* root; //its root node
public:
 
    QuadTree() = default;
    QuadTree(const sf::FloatRect& bounds);
    virtual ~QuadTree();

    
    void insert(Tile* tile);

    
    void query(const sf::FloatRect& range, std::vector<Tile*>& results);


    void clear();
   
    void printAllTiles() const;


};

#endif

