#ifndef QZUESIMAGE_H
#define QZUESIMAGE_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include <QPropertyAnimation>
class QZuesImage : public QWidget
{
    enum MouseDirect
    {
        DIRECT_LEFT=0,
        DIRECT_RIGHT,
        DIRECT_TOP,
        DIRECT_BOTTOM
    };

    Q_OBJECT
public:
    explicit QZuesImage(QWidget *parent = 0);
    ~QZuesImage();
    void setImage(QString path);
    void setImage(QImage image);
    void setImage(QPixmap pixmap);
    void setDescription(QString description);
    void setDescripStyle(QString style);
    void setAnimationDuration(int msec);
    void setDescriptionAlignment(Qt::Alignment align);
signals:
    void signalClicked();
    void signalDbClicked();
public slots:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
private:
    MouseDirect getMouseDirect(QPoint pos);
private:
    QLabel *m_lblDesc;
    QPixmap m_pixMap;
    QPropertyAnimation m_moveAnimation;
    int m_edge;
};

#endif // QZUESIMAGE_H
