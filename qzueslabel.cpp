#include "qzueslabel.h"

QZuesLabel::QZuesLabel(QWidget *parent)
	: QLabel(parent), m_placeholdText("..."), m_type(LABEL_TYPE_NORMAL), m_maqueeTimerId(-1), m_maqueeSpeed(100), m_contentsRect(contentsRect()), m_stepLength(5)
{

}

QZuesLabel::~QZuesLabel()
{

}

QString QZuesLabel::text()
{
	return m_contetnt;
}

void QZuesLabel::setText(const QString & content)
{
	m_contetnt = content;
	if (m_type == LABEL_TYPE_MARQUEE)
	{
		QLabel::setText("");
	}
	else
	{
		QLabel::setText(content);
	}
	
}

QString QZuesLabel::getPlaceholdText() const
{
	return m_placeholdText;
}

void QZuesLabel::setPlaceholdText(QString val)
{
	m_placeholdText = val;
}

void QZuesLabel::paintEvent(QPaintEvent *event)
{
	switch (m_type)
	{
	case LABEL_TYPE_NORMAL:
		QLabel::paintEvent(event);
		break;
	case LABEL_TYPE_AUTO_CUT:
	{
		QSize newSize = contentsRect().size();
		QFontMetrics  metrics = fontMetrics();
		int contentLength = metrics.boundingRect(m_contetnt).width();
		if (contentLength > newSize.width())
		{
			for (int j = m_contetnt.count(); j > 0; --j)
			{
				contentLength = metrics.boundingRect(m_contetnt.mid(0, j) + m_placeholdText).width();
				if (contentLength <= newSize.width())
				{
					QLabel::setText(m_contetnt.mid(0, j - 1) + m_placeholdText);
					break;
				}
			}
		}
		else
		{
			QLabel::setText(m_contetnt);
		}
		QLabel::paintEvent(event);
	}
		break;
	case LABEL_TYPE_MARQUEE:
	{
		QLabel::paintEvent(event);
		QPainter painter(this);
		painter.drawText(m_contentsRect, m_contetnt);
	}
		break;
	default:
		break;
	}
	
}

void QZuesLabel::resizeEvent(QResizeEvent *event)
{
	update();
}

void QZuesLabel::enterEvent(QEvent *event)
{
	if (m_maqueeTimerId != -1)
	{
		killTimer(m_maqueeTimerId);
	}
	m_maqueeTimerId = startTimer(m_maqueeSpeed);
}

void QZuesLabel::leaveEvent(QEvent *event)
{
	if (m_maqueeTimerId != -1)
	{
		killTimer(m_maqueeTimerId);
		m_maqueeTimerId = -1;
		m_contentsRect = contentsRect();
		update();
	}
}

void QZuesLabel::timerEvent(QTimerEvent *event)
{
	if (m_maqueeTimerId != -1 && event->timerId() == m_maqueeTimerId)
	{
		m_contentsRect.setX(m_contentsRect.x() - m_stepLength);
		m_contentsRect.setWidth(m_contentsRect.width() + m_stepLength);
		QFontMetrics  metrics = fontMetrics();
		int contentLength = metrics.boundingRect(m_contetnt).width();
		if (m_contentsRect.width() >= contentLength)
		{
			m_contentsRect = contentsRect();
		}
		update();
	}
}

LabelType QZuesLabel::getType() const
{
	return m_type;
}

void QZuesLabel::setType(LabelType val)
{
	if (val != m_type)
	{
		m_type = val;
		if (val == LABEL_TYPE_MARQUEE)
		{
			QLabel::setText("");
			m_contentsRect = contentsRect();
		}
		update();
	}
	
}

int QZuesLabel::getStepLength() const
{
	return m_stepLength;
}

void QZuesLabel::setStepLength(int val)
{
	m_stepLength = val;
}
