#ifndef GAME_CPP
#define GAME_CPP

#include "ui_mainwindow.h"
#include <cmath>
#include <list>
#include <vector>
#include "GameObject.hpp"
#include "QuadTree.hpp"

class Game
{
public:
	static std::vector<GameObject> Start(Ui::MainWindow* ui, unsigned int ballcount) //游戏初始化 随机生成小球(坐标等参数)
	{
		SFMLCanvas* _canvas = ui->widget;
		unsigned int xsize = _canvas->getSize().x;
		unsigned int ysize = _canvas->getSize().y;
		std::vector<GameObject> vballs(ballcount);
		//GameObject* balls = new GameObject[ballcount];
		int ID = 0;
		for (GameObject& ball : vballs)
		{
			ball.x = ball.radius + rand() % (xsize - (int)ball.radius);
			ball.y = ball.radius + rand() % (ysize - (int)ball.radius);
			ball.velocity.x = pow(-1.f, rand() % 2) * ((float)(rand() % 100)/90.f + 0.01f);
			ball.velocity.y = pow(-1.f, rand() % 2) * ((float)(rand() % 100)/90.f + 0.01f);
			ball.setId(ID++);
		}
		return vballs;
	}

	static std::vector<GameObject> NaiveUpdate(SFMLCanvas* widget, std::vector<GameObject>& vballs) //每帧执行 朴素遍历
	{
		unsigned int xsize = widget->getSize().x;
		unsigned int ysize = widget->getSize().y;
		for (GameObject& ball : vballs)
		{
			ball.x += ball.velocity.x;
			ball.y += ball.velocity.y;
			if (ball.x < ball.radius || ball.x > xsize + ball.radius)
				ball.velocity.x = -ball.velocity.x;
			if (ball.y < ball.radius || ball.y > ysize - ball.radius)
				ball.velocity.y = -ball.velocity.y;
			for (GameObject& colball : vballs)
			{
				if (colball.id == ball.id)
					continue;
				if (Simulation::CollisionJudge(ball, colball)) 
				{
					Simulation::CollisionProcess(ball, colball);

					QLCDNumber* lcdnumber = widget->parent()->findChild<QLCDNumber*>("lcdNumber");
					int count = lcdnumber->intValue() + 1;
					lcdnumber->display(count);
				}
				widget->m_thouCount += 1;
				if (widget->m_thouCount > 999)
				{
					widget->m_thouCount = 0;
					QLCDNumber* lcdnumber_2 = widget->parent()->findChild<QLCDNumber*>("lcdNumber_2");
					int count = lcdnumber_2->intValue() + 1;
					lcdnumber_2->display(count);
				}
			}
		}
		
		return vballs;
	}

	static std::vector<GameObject> QuadTreeUpdate(SFMLCanvas* widget, std::vector<GameObject> vballs) //四叉树遍历
	{
		float xsize = widget->getSize().x;
		float ysize = widget->getSize().y;
		QuadTreeNode quad;
		quad.clear();
		quad.setLevel(0);
		quad.setBound(Bound(0, 0, xsize, ysize));
		for (GameObject& ball : vballs)
		{
			ball.x += ball.velocity.x;
			ball.y += ball.velocity.y;
			if (ball.x < ball.radius || ball.x > xsize + ball.radius)
				ball.velocity.x = -ball.velocity.x;
			if (ball.y < ball.radius || ball.y > ysize - ball.radius)
				ball.velocity.y = -ball.velocity.y;
			quad.insert(ball);
		}
		for (GameObject& ball : vballs)
		{
			std::list<GameObject> candidate = quad.retrieve(ball);
			for (LIT lit = candidate.begin(); lit != candidate.end(); lit++)
			{
				if (ball == *lit)
					continue;
				if (Simulation::CollisionJudge(ball, *lit))
				{
					Simulation::CollisionProcess(ball, *lit);

					QLCDNumber* lcdnumber = widget->parent()->findChild<QLCDNumber*>("lcdNumber");
					int count = lcdnumber->intValue() + 1;
					lcdnumber->display(count);
				}
				widget->m_thouCount += 1;
				if (widget->m_thouCount > 999)
				{
					widget->m_thouCount = 0;
					QLCDNumber* lcdnumber_2 = widget->parent()->findChild<QLCDNumber*>("lcdNumber_2");
					int count = lcdnumber_2->intValue() + 1;
					lcdnumber_2->display(count);
				}
			}
		}

		return vballs;
	}

	static void End(GameObject *balls) //结束
	{
		delete[] balls;
	}

};



#endif
