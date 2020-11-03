#include "sfmlcanvas.h"
#include "Game.cpp"
#include <vector>

SFMLCanvas::SFMLCanvas(QWidget *Parent) : QSFMLWidget(Parent), m_ballscount(0)
{
    
}

void SFMLCanvas::onInit() //设置小球材质
{   
    m_delta.restart().asSeconds();
    this->setFramerateLimit(60);
    if(!m_tex.loadFromFile("red_circle.png"))
    {
        //ui->textBrowser->insertPlainText("Fail to find texture");
    }
    m_sprite.setTexture(m_tex);
}

void SFMLCanvas::onUpdate()
{
  
    // 向量数组存储所有小球精灵
    if (!m_balls.empty() && m_vsp.empty()) {
        for (GameObject& index : m_balls)
        {
            sf::Sprite sptemp;
            sptemp.setTexture(m_tex);
            sptemp.setPosition({ index.x,index.y });
            //index->posv += index->velocity;
            m_vsp.push_back(sptemp);
            //RenderWindow::draw(sptemp);
        }
        //delete[] m_balls;
    }

    // 通过向量数组绘制每一个精灵图形，并调用函数更新小球原始存储数组
    if (!m_vsp.empty())
    {
        for (sf::Sprite sptemp : m_vsp)
        {
            RenderWindow::draw(sptemp);
        }
        if (this->parent()->findChild<QComboBox*>("comboBox")->currentIndex() == 0)
            m_balls = Game::NaiveUpdate(this, m_balls);
        else
            m_balls = Game::QuadTreeUpdate(this, m_balls);
    }
    m_vsp.clear();
    // 执行碰撞判断
    // 执行碰撞处理
    //RenderWindow::draw(m_sprite);
}