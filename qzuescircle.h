#ifndef QZUESCIRCLE_H
#define QZUESCIRCLE_H

#include <QWidget>

class QZuesCircle : public QWidget
{
    Q_OBJECT
public:
    explicit QZuesCircle(QWidget *parent = 0);
    ~QZuesCircle();
    void setTextVisible(bool isVisible = true);

    QColor deactiveColor() const;
    void setDeactiveColor(const QColor &deactiveColor);

    QColor activeColor() const;
    void setActiveColor(const QColor &activeColor);

signals:

public slots:
    void setPercent(int percent);
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
private:
    int m_percent;
    int m_circleBorderWidth;
    QColor m_deactiveColor;
    QColor m_activeColor;
    bool m_isTextVisible;

};

#endif // QZUESCIRCLE_H
