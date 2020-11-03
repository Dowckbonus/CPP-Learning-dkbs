#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "GameObject.hpp"

#define OBJECT_WIDTH 15 // ����Ŀ�
#define OBJECT_HEIGHT 15 // ����ĸ�

//QUADTREE DEFINITION

typedef std::list<GameObject>::iterator LIT;

class QuadTreeNode
{
public:
	void clear() // �ݹ���յ�ǰ����
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

	void insert(GameObject object) // ��һ��������뵱ǰ�ڵ���������
	{
		if (nodes[0])
		{
			int index = getIndex(object);
			if (~index) // �ܱ��ӽڵ������ͱ��ӽڵ�����
			{
				nodes[index]->insert(object);
				return;
			}
		}
		objects.push_back(object); // ˵�� object �������޲�ȷ��
		if (objects.size() > QuadTreeNode::MAX_OBJECTS && level < QuadTreeNode::MAX_LEVELS)
		{
			if (!nodes[0]) // ������ܷ���, �ͷ���
			{
				split();
			}
			for (LIT lit = objects.begin(); lit != objects.end();) // �����������޲�ȷ���������б�, ������������뵽��Ӧ���ӽڵ���ȥ
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
			} // �����Ƴ� list �������� ��6�� ��һ����, ΪʲôҪ�Ƴ�? ��Ϊһ���Ĳ����ڵ��е� objects ��Ҫ����Ϊ�����κ������е������б�, ��Ȼ lit �Ѿ����˹���, �Ǿ�Ҫ�Ӹ��ڵ�(����ǰ�ڵ�)���Ƴ���lit
		}
	}

	std::list<GameObject> retrieve(GameObject& object) // ��ȡ�����������ܻᷢ����ײ�������б�
	{
		std::list<GameObject> ans;
		int index;
		if (nodes[0] && ~(index = getIndex(object)))
		{
			ans = nodes[index]->retrieve(object);
		}
		for (LIT lit = objects.begin(); lit != objects.end(); lit++) // �������޲�ȷ��������϶�Ҫ����. ������ȫ�ڱ�������е�����Ͳ���Ҫ������
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
	int level; // ��ʾ��ǰ�ڵ��������Ĳ��������
	std::list<GameObject> objects; // ��ǰ�ڵ��а������������޲�ȷ���������б�(���Ͷ�����޿����н����������б�)
	Bound bound; // ��ǰ�ڵ�����Ͻ�����Ϳ���
	QuadTreeNode* nodes[4]; // ��������˵Ļ�, �� nodes Ӧ�����ĸ�Ԫ��, ���û����, �Ǿ�ֻ�� 0 ��Ԫ��
	const static int MAX_OBJECTS = 5; // ��ʾ�����ǰ��������г���10������Ļ�, ��ǰ�����Ҫ����
	const static int MAX_LEVELS = 5; // ��ʾ�Ĳ������ 5�����

	void split() // ��ǰ�ڵ���ѳ��ĸ��ӽڵ�
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
	
	int getIndex(GameObject& object) // ��ȡ���������ĸ����ޣ�I II III IV �ֱ��Ӧ nodes[0]��nodes[1]��nodes[2]��nodes[3]��, �����ǡ�������κ�һ�����޵Ļ�(������������), ����-1
	{
		int ans = -1; // Ĭ�Ϸ��� -1
		float hmid = bound.x + bound.w / 2.0, vmid = bound.y + bound.h / 2.0; // ˮƽ���е㡢��ֱ���е�
		if (object.x + object.radius < hmid) // ������������� II��III ����
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
		else if (object.x > hmid) // ������������� I��IV ����
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