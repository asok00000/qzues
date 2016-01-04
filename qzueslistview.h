#ifndef QZUESLISTVIEW_H
#define QZUESLISTVIEW_H

#include <QListView>
#include <QPainter>
/*!
*\class QZuesListView
*\brief An extended List Widget inherited from QListView
*\details Provide more powerful functions
*\author Hu chunhua
*\version 1.0
*\date 2015-11-27 17:36:51
*\note modification:
*\date
*/
class QZuesListView : public QListView
{
	Q_OBJECT

public:
	QZuesListView(QWidget *parent);
	~QZuesListView();
	QString getEmptyTips() const;
	void setEmptyTips(QString val);
protected:
	virtual void paintEvent(QPaintEvent *event) override;
private:
	QString m_emptyTips;
};

#endif // QZUESLISTVIEW_H
