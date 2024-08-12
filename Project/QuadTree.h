#ifndef QUADTREE_H
#define QUADTREE_H


#include "TileMap.h"




class QuadTree {

private:
    class QuadTreeNode {
    public:
        std::vector<Tile*> objects;
        QuadTreeNode* children[4]; // 四个象限
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
            // 如果当前节点已细分，尝试将对象插入子节点
            if (children[0] != nullptr) {
                int index = getChildIndex(object);
                if (index != -1) {
                    children[index]->insert(object);
                    return;
                }
            }

            // 如果未细分或对象无法适合子节点，存储在当前节点
            objects.push_back(object);

            // 如果对象数量超过阈值且尚未细分，则进行细分
            if (objects.size() > MAX_OBJECTS && children[0] == nullptr) {
                subdivide();
                // 重新分配对象到子节点
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
            // 如果范围不相交，则直接返回
            
            if (!bounds.intersects(range)) {
                return;
            }

            // 查找与范围相交的对象
            for (auto& object : objects) {
                if (range.contains(object->getPosition())) {
                    results.push_back(object);
                }
            }

            // 递归查询子节点
            if (children[0] != nullptr) {
                for (int i = 0; i < 4; ++i) {
                    children[i]->queryRange(range, results);
                }
            }
        }

    private:
        // 将节点分割为四个子节点
        void subdivide() {
            float halfWidth = bounds.width / 2.0f;
            float halfHeight = bounds.height / 2.0f;

            children[0] = new QuadTreeNode({ bounds.left, bounds.top, halfWidth, halfHeight });
            children[1] = new QuadTreeNode({ bounds.left + halfWidth, bounds.top, halfWidth, halfHeight });
            children[2] = new QuadTreeNode({ bounds.left, bounds.top + halfHeight, halfWidth, halfHeight });
            children[3] = new QuadTreeNode({ bounds.left + halfWidth, bounds.top + halfHeight, halfWidth, halfHeight });
        }

        // 根据对象的位置确定它应该插入到哪个子节点中
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

        // 打印当前节点的所有 Tile
        for (const auto& tile : node->objects) {
            sf::Vector2f pos = tile->getPosition();
            std::cout << "Tile at position: (" << pos.x << ", " << pos.y << ")" << std::endl;
        }

        // 递归打印子节点
        for (int i = 0; i < 4; ++i) {
            if (node->children[i] != nullptr) {
                printNode(node->children[i]);
            }
        }
    }
    QuadTreeNode* root; // 四叉树的根节点
public:
 
    QuadTree() = default;
    QuadTree(const sf::FloatRect& bounds);
    virtual ~QuadTree();

    // 插入一个 Tile 对象到四叉树
    void insert(Tile* tile);

    // 查询指定区域内的所有碰撞对象
    void query(const sf::FloatRect& range, std::vector<Tile*>& results);

    // 清空四叉树
    void clear();
    //遍历四叉树
    void printAllTiles() const;


};

#endif

