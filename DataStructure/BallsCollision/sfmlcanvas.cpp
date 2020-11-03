#include "sfmlcanvas.h"
#include "Game.cpp"
#include <vector>

SFMLCanvas::SFMLCanvas(QWidget *Parent) : QSFMLWidget(Parent), m_ballscount(0)
{
    
}

void SFMLCanvas::onInit() //����С�����
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
  
    // ��������洢����С����
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

    // ͨ�������������ÿһ������ͼ�Σ������ú�������С��ԭʼ�洢����
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
    // ִ����ײ�ж�
    // ִ����ײ����
    //RenderWindow::draw(m_sprite);
}