#include "qzueslistview.h"

QZuesListView::QZuesListView(QWidget *parent)
	: QListView(parent), m_emptyTips("")
{

}

QZuesListView::~QZuesListView()
{

}

QString QZuesListView::getEmptyTips() const
{
	return m_emptyTips;
}

void QZuesListView::setEmptyTips(QString val)
{
	if (m_emptyTips != val)
	{
		m_emptyTips = val;
		update();
	}
}

void QZuesListView::paintEvent(QPaintEvent *event)
{
	QListView::paintEvent(event);
	if (model()==NULL ||  (model() && model()->rowCount() <= 0))
	{
		QPainter painter(this->viewport());
		painter.drawText(this->viewport()->contentsRect(), Qt::AlignCenter | Qt::TextWrapAnywhere, m_emptyTips);
	}
}
