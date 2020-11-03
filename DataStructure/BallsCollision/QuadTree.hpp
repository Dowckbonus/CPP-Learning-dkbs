#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "GameObject.hpp"

#define OBJECT_WIDTH 15 // 物体的宽
#define OBJECT_HEIGHT 15 // 物体的高

//QUADTREE DEFINITION

typedef std::list<GameObject>::iterator LIT;

class QuadTreeNode
{
public:
	void clear() // 递归清空当前区域
	{
		objects.clear();
		if (nodes[0])
		{
			for (int i = 0; i < 4; i++)
			{
				nodes[i]->clear();
				nodes[i] = 0;
			}
		}
	}

	void insert(GameObject object) // 将一个物体插入当前节点代表的区域
	{
		if (nodes[0])
		{
			int index = getIndex(object);
			if (~index) // 能被子节点消化就被子节点消化
			{
				nodes[index]->insert(object);
				return;
			}
		}
		objects.push_back(object); // 说明 object 所在象限不确定
		if (objects.size() > QuadTreeNode::MAX_OBJECTS && level < QuadTreeNode::MAX_LEVELS)
		{
			if (!nodes[0]) // 如果还能分裂, 就分裂
			{
				split();
			}
			for (LIT lit = objects.begin(); lit != objects.end();) // 遍历所在象限不确定的物体列表, 将所有物体插入到相应的子节点中去
			{
				int index = getIndex(*lit);
				if (~index)
				{
					nodes[index]->insert(*lit);
					lit = objects.erase(lit);
				}
				else
				{
					++lit;
				}
			} // 这里移除 list 的做法和 【6】 是一样的, 为什么要移除? 因为一个四叉树节点中的 objects 需要保持为不在任何象限中的物体列表, 既然 lit 已经有了归属, 那就要从父节点(即当前节点)中移除掉lit
		}
	}

	std::list<GameObject> retrieve(GameObject& object) // 获取和入参物体可能会发生碰撞的物体列表
	{
		std::list<GameObject> ans;
		int index;
		if (nodes[0] && ~(index = getIndex(object)))
		{
			ans = nodes[index]->retrieve(object);
		}
		for (LIT lit = objects.begin(); lit != objects.end(); lit++) // 所在象限不确定的物体肯定要加上. 但是完全在别的象限中的物体就不需要加上了
		{
			ans.push_back(*lit);
		}
		return ans;
	}

	void setLevel(int level) { this->level = level; }
	void setBound(Bound bound) { this->bound = bound; }

	QuadTreeNode()
	{
		memset(nodes, 0, sizeof(nodes));
	}

	QuadTreeNode(int level, Bound bound)
	{
		this->level = level;
		this->bound = bound;
		memset(nodes, 0, sizeof(nodes));
	}

	~QuadTreeNode() { clear(); }

private:
	int level; // 表示当前节点所处的四叉树的深度
	std::list<GameObject> objects; // 当前节点中包含的所在象限不确定的物体列表(即和多个象限可能有交集的物体列表)
	Bound bound; // 当前节点的左上角坐标和宽、高
	QuadTreeNode* nodes[4]; // 如果分裂了的话, 则 nodes 应该有四个元素, 如果没分裂, 那就只有 0 个元素
	const static int MAX_OBJECTS = 5; // 表示如果当前区域如果有超过10个物体的话, 则当前区域就要分裂
	const static int MAX_LEVELS = 5; // 表示四叉树最多 5层深度

	void split() // 当前节点分裂出四个子节点
	{
		float w = bound.w / 2.0;
		float h = bound.h / 2.0;
		float x = bound.x;
		float y = bound.y;
		nodes[0] = new QuadTreeNode(level + 1, Bound(x + w, y, w, h)); // I 
		nodes[1] = new QuadTreeNode(level + 1, Bound(x, y, w, h)); // II
		nodes[2] = new QuadTreeNode(level + 1, Bound(x, y + h, w, h)); // III
		nodes[3] = new QuadTreeNode(level + 1, Bound(x + w, y + h, w, h)); // IV
	}
	
	int getIndex(GameObject& object) // 获取物体属于哪个象限（I II III IV 分别对应 nodes[0]、nodes[1]、nodes[2]、nodes[3]）, 如果不恰好属于任何一个象限的话(例如横跨多个象限), 返回-1
	{
		int ans = -1; // 默认返回 -1
		float hmid = bound.x + bound.w / 2.0, vmid = bound.y + bound.h / 2.0; // 水平的中点、垂直的中点
		if (object.x + object.radius < hmid) // 如果物体能落在 II、III 象限
		{
			if (object.y + object.radius / 2.0 < vmid)
			{
				return 1;
			}
			else if (object.y > vmid)
			{
				return 2;
			}
		}
		else if (object.x > hmid) // 如果物体能落在 I、IV 象限
		{
			if (object.y + object.radius / 2.0 < vmid)
			{
				return 0;
			}
			else if (object.y > vmid)
			{
				return 3;
			}
		}
		return ans;
	}
};
#endif