#include "qzuesnavigator.h"

QZuesNavigator::QZuesNavigator(QWidget *parent)
	: QWidget(parent), m_backgroundColor(QColor(18, 35, 52)), m_foreroundColor(QColor(255, 255, 255)), m_slipperColor(QColor("#544332")), m_currentItemIndex(-1)
{
	m_slipper = new QWidget(this);
	m_slipper->setStyleSheet(QString("background-color:%1;").arg(m_slipperColor.name()));
	m_labelContainer = new QWidget(this);
	m_slipper->stackUnder(m_labelContainer);
	QHBoxLayout *_mainLayout = new QHBoxLayout(m_labelContainer);
	_mainLayout->setMargin(0);
	_mainLayout->setSpacing(0);
	m_labelContainer->setLayout(_mainLayout);
	m_slipperAnimation.setTargetObject(m_slipper);
	m_slipperAnimation.setPropertyName("pos");
	m_slipperAnimation.setDuration(200);
	m_slipperAnimation.setEasingCurve(QEasingCurve::OutExpo);
	for (int i = 0; i < 10; ++ i)
	{
		QZuesNavigatorItem item(QString("item").arg(i));
		appendItem(item);
	}
}

QZuesNavigator::~QZuesNavigator()
{

}

int QZuesNavigator::insertItem(QZuesNavigatorItem item, int index /*= -1*/)
{
	if (index < 0 || index >= m_items.count())
	{
		return appendItem(item);
	}
	else
	{
		m_items.insert(index, item);
	}
	if (m_currentItemIndex == -1)
	{
		m_currentItemIndex = 0;
	}
	updateUi();
	return index;
}

int QZuesNavigator::appendItem(QZuesNavigatorItem item)
{
	m_items << item;
	if (m_currentItemIndex == -1)
	{
		m_currentItemIndex = 0;
	}
	updateUi();
	return m_items.count() - 1;
}

void QZuesNavigator::removeItem(int index)
{
	if (index >= 0 && index <m_items.count())
	{
		m_items.removeAt(index);
	}
}

void QZuesNavigator::removeAllItem()
{
	m_items.clear();
}

QZuesNavigatorItem & QZuesNavigator::itemAt(int index)
{
	if (index >= 0 && index < m_items.count())
	{
		return m_items[index];
	}
	else
	{
		return QZuesNavigatorItem("");
	}
}

int QZuesNavigator::count()
{
	return m_items.count();
}

void QZuesNavigator::setColor(QColor backgroundColor, QColor slipperColor, QColor wordsColor)
{
	m_backgroundColor = backgroundColor;
	m_foreroundColor = wordsColor;
	m_slipperColor = slipperColor;
	m_slipper->setStyleSheet(QString("background-color:%1;").arg(m_slipperColor.name()));
	for (int i = 0;m_labelContainer->layout()->count(); ++ i)
	{
		m_labelContainer->layout()->itemAt(i)->widget()->setStyleSheet(QString("color:%1;").arg(m_foreroundColor.name()));
	}
	repaint();
}

bool QZuesNavigator::eventFilter(QObject *watched, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonRelease&& watched->metaObject()->className() == QString("QLabel"))
	{
		QLabel *_target = qobject_cast<QLabel*>(watched);
		if (m_slipperAnimation.state() == QAbstractAnimation::Running)
		{
			m_slipperAnimation.stop();
		}
		QPoint _pos = _target->pos();
		QPoint _startPos = m_slipper->pos();
		m_slipperAnimation.setStartValue(_startPos);
		m_slipperAnimation.setEndValue(_pos);
		m_slipperAnimation.start();
		QZuesNavigatorItem &item = findItem(_target);
		m_currentItemIndex = m_items.indexOf(item);
		emit signalSelectItemChanged(item);
	}
	return QWidget::eventFilter(watched, event);
}

void QZuesNavigator::updateUi()
{
	int _count = m_labelContainer->layout()->count();
	while (_count > 0)
	{
		delete m_labelContainer->layout()->takeAt(0)->widget();
		-- _count;
	}
	for (int i = 0; i < m_items.count(); ++ i)
	{
		m_labelContainer->layout()->addWidget(newItem(m_items[i]));
	}
	QTimer::singleShot(100, [&](){
		m_slipper->move(m_items[m_currentItemIndex].m_label->pos());
	});
	
}

void QZuesNavigator::ajustSize()
{
	QRect _rect = contentsRect();
	m_labelContainer->resize(_rect.size());
	if (m_items.count()>0)
	{
		m_slipper->show();
		m_slipper->resize(_rect.width() / m_items.count(), _rect.height());
	}
	else
	{
		m_slipper->hide();
	}
	
}

QLabel * QZuesNavigator::newItem(QZuesNavigatorItem &item)
{
	QRect _rect = m_labelContainer->contentsRect();
	QSize _size(_rect.width()/m_items.count(),_rect.height());
	QLabel *_itemWidget = new QLabel(item.getDisplayText());
	_itemWidget->setMaximumSize(_size);
	_itemWidget->setMinimumSize(_size);
	_itemWidget->setAlignment(Qt::AlignCenter);
	_itemWidget->installEventFilter(this);
	_itemWidget->setStyleSheet(QString("color:%1;").arg(m_foreroundColor.name()));
	item.m_label = _itemWidget;
	return _itemWidget;
}

QZuesNavigatorItem& QZuesNavigator::findItem(QLabel *label)
{
	for (int i = 0; i < m_items.count(); ++ i)
	{
		if (m_items[i].m_label == label)
		{
			return m_items[i];
		}
	}
	return QZuesNavigatorItem("");
}

void QZuesNavigator::resizeEvent(QResizeEvent *event)
{
	ajustSize();
	updateUi();
}

void QZuesNavigator::paintEvent(QPaintEvent *event)
{
	QPainter _painter(this);
	_painter.fillRect(rect(), QBrush(m_backgroundColor));
}

QZuesNavigatorItem::QZuesNavigatorItem(QString content, QVariant userData)
	:m_displayText(content), m_data(userData)
{

}
