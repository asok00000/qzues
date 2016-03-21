#ifndef QZUESLABEL_H
#define QZUESLABEL_H

#include <QLabel>
#include <QWidget>
#include <QTimerEvent>
#include <QPainter>
#include "QZuesGlobal.h"
/*!
*\class QZuesLabel
*\brief An extended Label Widget inherited from QLabel
*\details Provide more powerful functions
*\author Hu chunhua
*\version 1.0
*\date 2015-11-27 17:36:51
*\note modification:
*\date
*/
class QZuesLabel : public QLabel
{
	Q_OBJECT
	Q_ENUMS(LabelType)
public:
	QString getPlaceholdText() const;
	void setPlaceholdText(QString val);
public:
	QZuesLabel(QWidget *parent);
	~QZuesLabel();
	QString text();
	LabelType getType() const;
	void setType(LabelType val);
	int getStepLength() const;
	void setStepLength(int val);
public slots:
	void setText(const QString & content);
protected:
	virtual void paintEvent(QPaintEvent *event) override;
	virtual void resizeEvent(QResizeEvent *event) override;

	virtual void enterEvent(QEvent *event) override;
	virtual void leaveEvent(QEvent *event) override;

	virtual void timerEvent(QTimerEvent *event) override;

private:
	QString m_contetnt;
	QString m_placeholdText;
	LabelType m_type;
	int m_maqueeTimerId;
	int m_maqueeSpeed;
	int m_stepLength;
	QRect m_contentsRect;
};

#endif // QZUESLABEL_H
