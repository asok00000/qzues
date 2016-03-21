#ifndef QZUESANIMATIONSTACKWIDGET_H
#define QZUESANIMATIONSTACKWIDGET_H

#include <QWidget>
#include <QList>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "QZuesGlobal.h"
class QZuesAnimationStackWidget : public QWidget
{
	Q_OBJECT
	Q_ENUMS(StackWidgetAnimationType)
public:
	QZuesAnimationStackWidget(QWidget *parent);
	~QZuesAnimationStackWidget();
	int	addWidget(QWidget * widget);
	int	count() const;
	int	currentIndex() const;
	QWidget *	currentWidget() const;
	int	indexOf(QWidget * widget) const;
	int	insertWidget(int index, QWidget * widget);
	void	removeWidget(QWidget * widget);
	QWidget *	widget(int index) const;
	QWidget * nextWidget(int currentIndex);
	StackWidgetAnimationTypes getAnimationTypes() const;
	void setAnimationTypes(StackWidgetAnimationTypes val);
	int getAnimationDuration() const;
	void setAnimationDuration(int val);
public slots:
	void	setCurrentIndex(int index);
	void	setCurrentWidget(QWidget * widget);
protected:
	void switchWidget(QWidget*nextWidget);
	virtual void resizeEvent(QResizeEvent *) override;
	void loadAnimation(QWidget  *currentWidget,QWidget*nextWidget);
private:
	QList<QWidget*> widgets;
	int m_currentIndex;
	QParallelAnimationGroup parallelGroup;
	QSequentialAnimationGroup sequentialGroup;
	StackWidgetAnimationTypes animationTypes;
	int animationDuration;
	
};

#endif // QZUESANIMATIONSTACKWIDGET_H
