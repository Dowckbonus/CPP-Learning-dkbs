#include "qsfmlwidget.h"

QSFMLWidget::QSFMLWidget(QWidget *parent) : QWidget(parent), m_initialized(false)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    setFocusPolicy(Qt::StrongFocus);
}

QPaintEngine *QSFMLWidget::paintEngine() const
{
    return NULL;
}

void QSFMLWidget::showEvent(QShowEvent *event)
{
    if(m_initialized == false)
    {
        sf::RenderWindow::create(reinterpret_cast<sf::WindowHandle>(winId()));

        onInit();

        connect(&m_timer, SIGNAL(timeout()), this, SLOT(repaint()));
        m_timer.start();
        m_initialized = true;
    }
}

void QSFMLWidget::paintEvent(QPaintEvent *event)
{
    RenderWindow::clear();
    onUpdate();
    RenderWindow::display();
}

void QSFMLWidget::onInit()
{
    // To be overridden
}

void QSFMLWidget::onUpdate()
{
    // To be overridden
}
