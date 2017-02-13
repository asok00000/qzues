#include "qzuesswitchbutton.h"

#include <QPainter>
#include <QTimerEvent>
#include <QDebug>
#include <QMouseEvent>
QZuesSwitchButton::QZuesSwitchButton(QWidget *parent)
	: QWidget(parent), m_animationTimerId(-1),
	m_isChecked(false), m_padding(2), m_currentX(2),
	m_onText("ON"), m_offText("OFF"),
	m_backgroundColor(QColor::fromRgb(112, 123, 134)),
	m_foregroundColor(QColor::fromRgb(255, 255, 255)),
	m_switchColorOn(QColor::fromRgb(172, 83, 94)),
	m_switchColorOff(QColor::fromRgb(72, 83, 94))
{
    m_switchRect.setX(0);
    m_switchRect.setY(0);
    m_switchRect.setWidth(0);
    m_switchRect.setHeight(0);
}

void QZuesSwitchButton::setBackgroundColor(QColor color)
{
	m_backgroundColor = color;
	repaint();
}

void QZuesSwitchButton::setText(QString on, QString off)
{
	m_onText = on;
	m_offText = off;
	repaint();
}

void QZuesSwitchButton::setForegroundColor(QColor color)
{
	m_foregroundColor = color;
	repaint();
}

void QZuesSwitchButton::setSwitchColor(QColor onColor, QColor offColor)
{
	m_switchColorOn = onColor;
	m_switchColorOff = offColor;
	repaint();
}

void QZuesSwitchButton::setState(bool isOn)
{
	if (m_isChecked != isOn)
	{
		changeState();
	}
}

void QZuesSwitchButton::paintEvent(QPaintEvent *event)
{
    QPainter _painter(this);
	_painter.setRenderHint(QPainter::Antialiasing);
	_painter.setRenderHint(QPainter::TextAntialiasing);
	_painter.save();
	_painter.setPen(Qt::NoPen);
	_painter.setBrush(QBrush(m_backgroundColor, Qt::SolidPattern));
	_painter.drawRoundedRect(rect(), m_switchRect.width() / 2, m_switchRect.width()/2);
	//_painter.drawRect(rect());
	_painter.restore();
	_painter.save();
	_painter.setPen(QPen(m_foregroundColor));
	if (m_isChecked)
	{
		_painter.drawText(width() / 2 - fontMetrics().width(m_onText), height() / 2 + fontMetrics().height() / 2, m_onText);
	}
	else
	{
		_painter.drawText(width()/2, height()/2+fontMetrics().height()/2, m_offText);
	}
	_painter.restore();
	m_switchRect.setRect(m_currentX, m_padding, m_switchRect.width(), m_switchRect.height());
	_painter.save();
	_painter.setPen(Qt::NoPen);
	if (m_isChecked)
	{
		_painter.setBrush(QBrush(m_switchColorOn, Qt::SolidPattern));
	} 
	else
	{
		_painter.setBrush(QBrush(m_switchColorOff, Qt::SolidPattern));
	}
	_painter.drawRoundedRect(m_switchRect, m_switchRect.width() / 2, m_switchRect.width() / 2);
	_painter.restore();
	
    QWidget::paintEvent(event);
}

void QZuesSwitchButton::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == m_animationTimerId)
    {
		if (m_isChecked)
		{
			++m_currentX;
		}
		else
		{
			--m_currentX;
		}
		if (m_currentX + m_switchRect.width() >= this->width() - m_padding || m_currentX <= m_padding)
        {
            killTimer(m_animationTimerId);
            m_animationTimerId = -1;
        }
        repaint();
    }
}

void QZuesSwitchButton::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button()==Qt::LeftButton)
    {
		changeState();
		emit signalClicked(m_isChecked);
    }
}

void QZuesSwitchButton::resizeEvent(QResizeEvent *event)
{
	QSize _currentSize = event->size();
	int _switchHeight= _currentSize.height() - m_padding * 2;
	int _switchWidth = _switchHeight;
	m_switchRect.setRect(m_currentX, m_padding, _switchWidth, _switchHeight);
}

void QZuesSwitchButton::changeState()
{
	m_animationTimerId = startTimer(5);
	m_isChecked = !m_isChecked;
	emit signalStateChanged(m_isChecked);
}
