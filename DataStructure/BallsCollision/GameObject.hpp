#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include <SFML/Graphics.hpp>

class Bound // 矩形沙盒
{
public:
	float x, y, w, h; // (x, y) 是左上角坐标, w 是宽度, h 是高度
	Bound(float x = 0, float y = 0, float w = 0, float h = 0) :x(x), y(y), w(w), h(h) {}
};

class GameObject: public Bound
{
public:
	float radius;
	int id;
	sf::Vector2f velocity;
	GameObject() : radius(7.5f), velocity(0, 0) {}
	void setId(int id) { this->id = id; }
	bool operator == (const GameObject& o) { return id == o.id; }
};

class Simulation
{
public:
	static bool CollisionJudge(GameObject& ball1, GameObject& ball2) //碰撞判断
	{
		bool colliding = false;
		float gapx = ball1.velocity.x - ball2.velocity.x;
		float gapy = ball1.velocity.y - ball2.velocity.y;

		float distx = ball1.x - ball2.x - gapx;
		float disty = ball1.y - ball2.y - gapy;
		colliding = ((distx * distx) + (disty * disty)) < (ball1.radius * ball2.radius);
		return colliding;
	}

	static void CollisionProcess(GameObject& ball1, GameObject& ball2) //碰撞处理
	{
		float spring = 0.9f;
		float distx = ball2.x - ball1.x;
		float disty = ball2.y - ball1.y;
		float misDist = ball1.radius + ball2.radius;
		float angle = atan2(disty, distx);
		float tx = ball1.x + cos(angle) * misDist;
		float ty = ball1.y + sin(angle) * misDist;
		float ax = (tx - ball2.x) * spring;
		float ay = (ty - ball2.y) * spring;
		ball1.velocity -= {ax, ay};
		ball2.velocity += {ax, ay};
	}

	static void BulletHit(GameObject& bullet, GameObject& ball) //子弹命中
	{

	}
};

#endif