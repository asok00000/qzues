#include "qzuesimage.h"
#include <QDebug>
#include <QCursor>
QZuesImage::QZuesImage(QWidget *parent) : QWidget(parent),m_edge(3)
{
    m_lblDesc = new QLabel(this);
    m_lblDesc->setStyleSheet("background-color:RGBA(0,0,0,33)");
    m_lblDesc->setVisible(false);
    m_moveAnimation.setPropertyName("pos");
    m_moveAnimation.setTargetObject(m_lblDesc);


}

QZuesImage::~QZuesImage()
{
    m_lblDesc->deleteLater();
    m_lblDesc = 0;
}

void QZuesImage::setImage(QString path)
{
    QPixmap pixmap(path);
    setImage(pixmap);
}

void QZuesImage::setImage(QImage image)
{
    setImage(QPixmap::fromImage(image));
}

void QZuesImage::setImage(QPixmap pixmap)
{
    m_pixMap = pixmap;
    update();
}

void QZuesImage::setDescription(QString description)
{
    m_lblDesc->setText(description);
}

void QZuesImage::setDescripStyle(QString style)
{
    m_lblDesc->setStyleSheet(style);
}

void QZuesImage::setAnimationDuration(int msec)
{
    m_moveAnimation.setDuration(msec);
}

void QZuesImage::setDescriptionAlignment(Qt::Alignment align)
{
    m_lblDesc->setAlignment(align);
}

void QZuesImage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.drawPixmap(this->rect(),m_pixMap);
}

void QZuesImage::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    m_lblDesc->setVisible(true);
    MouseDirect direct = getMouseDirect(mapFromGlobal(QCursor::pos()));
    switch (direct)
    {
    case DIRECT_TOP:
        m_lblDesc->move(0,-m_lblDesc->height());
        break;
    case DIRECT_RIGHT:
        m_lblDesc->move(m_lblDesc->width(),0);
        break;
    case DIRECT_BOTTOM:
        m_lblDesc->move(0,m_lblDesc->height());
        break;
    case DIRECT_LEFT:
        m_lblDesc->move(-m_lblDesc->width(),0);
        break;
    default:
        break;
    }
    m_moveAnimation.setStartValue(m_lblDesc->pos());
    m_moveAnimation.setEndValue(QPoint(0,0));
    m_moveAnimation.start();
}

void QZuesImage::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    m_moveAnimation.setStartValue(m_lblDesc->pos());
    MouseDirect direct = getMouseDirect(mapFromGlobal(QCursor::pos()));
    switch (direct)
    {
    case DIRECT_TOP:
        m_moveAnimation.setEndValue(QPoint(0,-m_lblDesc->height()));;
        break;
    case DIRECT_RIGHT:
        m_moveAnimation.setEndValue(QPoint(m_lblDesc->width(),0));
        break;
    case DIRECT_BOTTOM:
        m_moveAnimation.setEndValue(QPoint(0,m_lblDesc->height()));
        break;
    case DIRECT_LEFT:
        m_moveAnimation.setEndValue(QPoint(-m_lblDesc->width(),0));
        break;
    default:
        break;
    }
    m_moveAnimation.start();
}

void QZuesImage::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    m_lblDesc->resize(this->size());
}

void QZuesImage::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit signalClicked();
}

void QZuesImage::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit signalDbClicked();
}

QZuesImage::MouseDirect QZuesImage::getMouseDirect(QPoint pos)
{
    if(pos.x() >= -m_edge && pos.x() <=m_edge)
        return DIRECT_LEFT;
    if(pos.y() >= -m_edge && pos.y() <=m_edge)
        return DIRECT_TOP;
    if(pos.x() >= this->width()-m_edge && pos.x() <=this->width()+m_edge)
        return DIRECT_RIGHT;
    if(pos.y() >= this->height()-m_edge && pos.y() <=this->height()+m_edge)
        return DIRECT_BOTTOM;
    return DIRECT_LEFT;

}
