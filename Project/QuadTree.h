#ifndef QUADTREE_H
#define QUADTREE_H


#include "TileMap.h"




class QuadTree {

private:
    class QuadTreeNode {
    public:
        std::vector<Tile*> objects;
        QuadTreeNode* children[4]; // �ĸ�����
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
            // �����ǰ�ڵ���ϸ�֣����Խ���������ӽڵ�
            if (children[0] != nullptr) {
                int index = getChildIndex(object);
                if (index != -1) {
                    children[index]->insert(object);
                    return;
                }
            }

            // ���δϸ�ֻ�����޷��ʺ��ӽڵ㣬�洢�ڵ�ǰ�ڵ�
            objects.push_back(object);

            // �����������������ֵ����δϸ�֣������ϸ��
            if (objects.size() > MAX_OBJECTS && children[0] == nullptr) {
                subdivide();
                // ���·�������ӽڵ�
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
            // �����Χ���ཻ����ֱ�ӷ���
            
            if (!bounds.intersects(range)) {
                return;
            }

            // �����뷶Χ�ཻ�Ķ���
            for (auto& object : objects) {
                if (range.contains(object->getPosition())) {
                    results.push_back(object);
                }
            }

            // �ݹ��ѯ�ӽڵ�
            if (children[0] != nullptr) {
                for (int i = 0; i < 4; ++i) {
                    children[i]->queryRange(range, results);
                }
            }
        }

    private:
        // ���ڵ�ָ�Ϊ�ĸ��ӽڵ�
        void subdivide() {
            float halfWidth = bounds.width / 2.0f;
            float halfHeight = bounds.height / 2.0f;

            children[0] = new QuadTreeNode({ bounds.left, bounds.top, halfWidth, halfHeight });
            children[1] = new QuadTreeNode({ bounds.left + halfWidth, bounds.top, halfWidth, halfHeight });
            children[2] = new QuadTreeNode({ bounds.left, bounds.top + halfHeight, halfWidth, halfHeight });
            children[3] = new QuadTreeNode({ bounds.left + halfWidth, bounds.top + halfHeight, halfWidth, halfHeight });
        }

        // ���ݶ����λ��ȷ����Ӧ�ò��뵽�ĸ��ӽڵ���
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

        // ��ӡ��ǰ�ڵ������ Tile
        for (const auto& tile : node->objects) {
            sf::Vector2f pos = tile->getPosition();
            std::cout << "Tile at position: (" << pos.x << ", " << pos.y << ")" << std::endl;
        }

        // �ݹ��ӡ�ӽڵ�
        for (int i = 0; i < 4; ++i) {
            if (node->children[i] != nullptr) {
                printNode(node->children[i]);
            }
        }
    }
    QuadTreeNode* root; // �Ĳ����ĸ��ڵ�
public:
 
    QuadTree() = default;
    QuadTree(const sf::FloatRect& bounds);
    virtual ~QuadTree();

    // ����һ�� Tile �����Ĳ���
    void insert(Tile* tile);

    // ��ѯָ�������ڵ�������ײ����
    void query(const sf::FloatRect& range, std::vector<Tile*>& results);

    // ����Ĳ���
    void clear();
    //�����Ĳ���
    void printAllTiles() const;


};

#endif

