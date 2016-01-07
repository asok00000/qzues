#include "qzuescircle.h"

#include <QPainter>
#include <QDebug>
QZuesCircle::QZuesCircle(QWidget *parent) : QWidget(parent),m_percent(0),m_circleBorderWidth(4),m_isTextVisible(true)
{
    m_deactiveColor.setNamedColor("#333333");
    m_activeColor.setNamedColor("#79c324");
}

QZuesCircle::~QZuesCircle()
{

}

void QZuesCircle::setTextVisible(bool isVisible)
{
    if(isVisible != m_isTextVisible)
    {
        m_isTextVisible = isVisible;
        update();
    }
}

void QZuesCircle::setPercent(int percent)
{
    if(percent > 100)
    {
        percent = 100;
    }
    m_percent = percent;
    update();
}



void QZuesCircle::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing|QPainter::HighQualityAntialiasing);
    QRectF rct = contentsRect();
    painter.setBrush(QBrush(QColor(0,0,0,0)));
    int radius = rct.height()>rct.width()?rct.width()/2-m_circleBorderWidth-2:rct.height()/2-m_circleBorderWidth-2;
    painter.setPen(QPen(QBrush(m_deactiveColor),m_circleBorderWidth));
    painter.drawEllipse(rct.center(),radius,radius);
    painter.setPen(QPen(QBrush(m_activeColor),m_circleBorderWidth+0.5));
    QRectF arcRct;
    arcRct.setTopLeft(QPoint(rct.width()/2-radius,rct.height()/2-radius));
    arcRct.setBottomRight(QPoint(rct.width()/2+radius,rct.height()/2+radius));
    painter.drawArc(arcRct,90*16,-360*m_percent/100*16);
    painter.restore();
    if(m_isTextVisible)
    {
        painter.drawText(rect(), Qt::AlignCenter, QString("%1%").arg(m_percent));
    }

}

QColor QZuesCircle::activeColor() const
{
    return m_activeColor;
}

void QZuesCircle::setActiveColor(const QColor &activeColor)
{
    m_activeColor = activeColor;
    update();
}

QColor QZuesCircle::deactiveColor() const
{
    return m_deactiveColor;
}

void QZuesCircle::setDeactiveColor(const QColor &deactiveColor)
{
    m_deactiveColor = deactiveColor;
    update();
}
