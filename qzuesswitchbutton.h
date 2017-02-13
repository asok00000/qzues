#ifndef QZUESSWITCHBUTTON_H
#define QZUESSWITCHBUTTON_H

#include <QWidget>
#include <QRect>
class QZuesSwitchButton : public QWidget
{
    Q_OBJECT
public:
    explicit QZuesSwitchButton(QWidget *parent = 0);
	void setBackgroundColor(QColor color);
	void setText(QString on,QString off);
	void setForegroundColor(QColor color);
	void setSwitchColor(QColor onColor,QColor offColor);
	void setState(bool isOn);
signals:
	void signalStateChanged(bool isOn);
	void signalClicked(bool isOn);
protected:
	void paintEvent(QPaintEvent *event);
	void timerEvent(QTimerEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	virtual void resizeEvent(QResizeEvent *event) override;
private:
	void changeState();
private:
    int m_currentX;
	int m_padding;
	int m_animationTimerId;
	bool m_isChecked;
	QRect m_switchRect;
	QColor m_backgroundColor, m_foregroundColor, m_switchColorOn, m_switchColorOff;
	QString m_onText, m_offText;
};

#endif // QZUESSWITCHBUTTON_H
