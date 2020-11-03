#ifndef SFMLCANVAS_H
#define SFMLCANVAS_H

#include "qsfmlwidget.h"
#include "QuadTree.hpp"

class SFMLCanvas : public QSFMLWidget
{
public:

    explicit SFMLCanvas(QWidget *Parent = 0);

    void onInit() override;
    void onUpdate() override;

    std::vector<GameObject> m_balls;
    unsigned int m_ballscount;
    unsigned int m_thouCount = 0;
    std::vector<sf::Sprite> m_vsp;
    sf::Clock m_delta;
private:
    sf::Texture m_tex;
    sf::Sprite m_sprite;
};

#endif // SFMLCANVAS_H
