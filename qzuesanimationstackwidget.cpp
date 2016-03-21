#include "qzuesanimationstackwidget.h"

QZuesAnimationStackWidget::QZuesAnimationStackWidget(QWidget *parent)
	: QWidget(parent), m_currentIndex(-1), animationDuration(1)
{
	animationTypes = STACK_WIDGET_ANIMATION_NORMAL;
}

QZuesAnimationStackWidget::~QZuesAnimationStackWidget()
{

}

int QZuesAnimationStackWidget::addWidget(QWidget * widget)
{
	int _index = -1;
	if (widget != NULL)
	{
		widget->setParent(this);
		widget->hide();
		widgets<<widget;
		_index = widgets.count()-1;
	}
	//we should display the first widget
	if (_index == 0)
	{
		switchWidget(widgets[0]);
	}
	return _index;
}

int QZuesAnimationStackWidget::insertWidget(int index, QWidget * widget)
{
	int _index = -1;
	if (widget != NULL)
	{
		if (index > widgets.count())
		{
			widgets << widget;
			_index = widgets.count() - 1;
		}
		else
		{
			widgets.insert(index, widget);
			_index = index;
		}
		widget->setParent(this);
		widget->hide();
	}
	//we should display the first widget
	if (_index == 0)
	{
		switchWidget(widgets[0]);
	}
	return _index;
}

void QZuesAnimationStackWidget::removeWidget(QWidget * widget)
{
	if (widget != NULL)
	{
		int _index = widgets.indexOf(widget);
		if (_index == m_currentIndex)
		{
			//the current widget will be removed,so we display the next widget
			QWidget *nw = nextWidget(_index);
			if (nw != NULL)
			{
				switchWidget(nw);
			}
		}
		widgets.removeAt(_index);
		widget->hide();
		widget->setParent(NULL);
		widget->deleteLater();
		m_currentIndex = widgets.indexOf(widget);
	}
}

void QZuesAnimationStackWidget::setCurrentIndex(int index)
{
	if (index <0 || index >= widgets.count() || index == m_currentIndex)
	{
		return;
	}
	switchWidget(widgets[index]);
}

void QZuesAnimationStackWidget::setCurrentWidget(QWidget * widget)
{
	int index = widgets.indexOf(widget);
	if (widget == NULL || index == -1)
	{
		return;
	}
	switchWidget(widget);
}

int QZuesAnimationStackWidget::indexOf(QWidget * widget) const
{
	int _index = -1;
	for (int i = 0; i < widgets.count(); ++ i)
	{
		if (widget == widgets[i])
		{
			_index = i;
			break;
		}
	}
	return _index;
}

QWidget * QZuesAnimationStackWidget::currentWidget() const
{
	QWidget *_widget = NULL;
	if (m_currentIndex != -1)
	{
		_widget = widgets[m_currentIndex];
	}
	return _widget;
}

int QZuesAnimationStackWidget::count() const
{
	return widgets.count();
}

int QZuesAnimationStackWidget::currentIndex() const
{
	return m_currentIndex;
}

void QZuesAnimationStackWidget::switchWidget(QWidget*nextWidget)
{
	//nextWidget is null, quit directly
	if (nextWidget == NULL)
	{
		return;
	}
	if (animationTypes.testFlag(STACK_WIDGET_ANIMATION_NORMAL))
	{	
		//display like QStackWidget
		nextWidget->resize(size());
		nextWidget->setMinimumSize(size());
		nextWidget->setMaximumSize(size());
		nextWidget->move(QPoint(0,0));
		nextWidget->show();
		if (m_currentIndex >=0 && m_currentIndex < widgets.count())
		{
			QWidget *currentWidget = widgets[m_currentIndex];
			currentWidget->hide();
		}
	}
	else
	{
		qDebug() << "next widget " << nextWidget << "size before add animation:" << nextWidget->size();
		if (m_currentIndex >= 0 && m_currentIndex < widgets.count())
		{
			QWidget *currentWidget = widgets[m_currentIndex];
			loadAnimation(currentWidget, nextWidget);
		}
		else
		{
			loadAnimation(NULL, nextWidget);
		}
		qDebug() << "next widget " << nextWidget << "size after add animation:" << nextWidget->size();
		/*nextWidget->resize(size());
		nextWidget->setMinimumSize(size());
		nextWidget->setMaximumSize(size());
		nextWidget->move(QPoint(0, 0));*/
		nextWidget->show();
		qDebug() << "next widget "<<nextWidget<<"size after show:" << nextWidget->size();
		parallelGroup.start(/*QAbstractAnimation::DeleteWhenStopped*/);
	}
	m_currentIndex = widgets.indexOf(nextWidget);
}

QWidget * QZuesAnimationStackWidget::nextWidget(int currentIndex)
{
	QWidget *_nextWidget = NULL;
	int count = widgets.count();
	if (count > 0)
	{
		_nextWidget = widgets[(currentIndex + 1) % count];
	}
	return _nextWidget;
}

void QZuesAnimationStackWidget::resizeEvent(QResizeEvent *event)
{
	//resize the current displayed widget when container size changing
	if (m_currentIndex != -1 && m_currentIndex>=0 && m_currentIndex<widgets.count())
	{
		QWidget *currentWidget = widgets[m_currentIndex];
		currentWidget->resize(event->size());
		currentWidget->setMinimumSize(event->size());
		currentWidget->setMaximumSize(event->size());
	}
}

StackWidgetAnimationTypes QZuesAnimationStackWidget::getAnimationTypes() const
{
	return animationTypes;
}

void QZuesAnimationStackWidget::setAnimationTypes(StackWidgetAnimationTypes val)
{
	animationTypes = val;	
}

void QZuesAnimationStackWidget::loadAnimation(QWidget  *currentWidget, QWidget*nextWidget)
{
	parallelGroup.clear();
	sequentialGroup.clear();
	if (currentWidget != NULL)
	{
		//apply hide animation on currentWidget
		if (animationTypes.testFlag(STACK_WIDGET_ANIMATION_GRADIENT))
		{
			//add opacity gradient animation
			QGraphicsOpacityEffect *opacityEffect = qobject_cast<QGraphicsOpacityEffect*>(currentWidget->graphicsEffect());
			if (opacityEffect == NULL)
			{
				opacityEffect = new QGraphicsOpacityEffect;
				currentWidget->setGraphicsEffect(opacityEffect);
			}
			QPropertyAnimation *opacityAnimation = new QPropertyAnimation;
			opacityAnimation->setTargetObject(opacityEffect);
			opacityAnimation->setStartValue(1.0);
			opacityAnimation->setEndValue(0.0);
			opacityAnimation->setPropertyName("opacity");
			opacityAnimation->setDuration(animationDuration * 1000);
			connect(opacityAnimation, &QPropertyAnimation::finished, this, [=](){
				delete opacityAnimation;
			});
			parallelGroup.addAnimation(opacityAnimation);
		}
		if (animationTypes.testFlag(STACK_WIDGET_ANIMATION_DOWN) || animationTypes.testFlag(STACK_WIDGET_ANIMATION_TOP) || animationTypes.testFlag(STACK_WIDGET_ANIMATION_RIGHT) || animationTypes.testFlag(STACK_WIDGET_ANIMATION_LEFT))
		{
			//add pos animation,top<donw<right<left
			QPropertyAnimation *posAnimation = new QPropertyAnimation;
			QPoint currentPos = currentWidget->pos();
			posAnimation->setTargetObject(currentWidget);
			posAnimation->setStartValue(currentPos);
			//add pos change animation-donw to top
			if (animationTypes.testFlag(STACK_WIDGET_ANIMATION_TOP))
			{
				currentPos.setY(-height());
			}
			//add pos change animation-top to down
			if (animationTypes.testFlag(STACK_WIDGET_ANIMATION_DOWN))
			{
				currentPos.setY(height());
			}
			//add pos change animation-left to right
			if (animationTypes.testFlag(STACK_WIDGET_ANIMATION_RIGHT))
			{
				currentPos.setX(width());
			}
			//add pos change animation-right to left
			if (animationTypes.testFlag(STACK_WIDGET_ANIMATION_LEFT))
			{
				currentPos.setX(-width());
			}
			posAnimation->setEndValue(currentPos);
			posAnimation->setPropertyName("pos");
			posAnimation->setDuration(animationDuration * 1000);
			connect(posAnimation, &QPropertyAnimation::finished, this, [=](){
				delete posAnimation;
			});
			parallelGroup.addAnimation(posAnimation);
		}
		if (animationTypes.testFlag(STACK_WIDGET_ANIMATION_SIZE))
		{
			//add size change animation
			QPropertyAnimation *sizeAnimation = new QPropertyAnimation;
			//currentWidget->resize(size());
			sizeAnimation->setTargetObject(currentWidget);
			sizeAnimation->setStartValue(size());
			sizeAnimation->setEndValue(QSize(0, 0));
			sizeAnimation->setPropertyName("size");
			sizeAnimation->setDuration(animationDuration * 1000);
			connect(sizeAnimation, &QPropertyAnimation::finished, this, [=](){
				delete sizeAnimation;
				currentWidget->hide();
			});
			parallelGroup.addAnimation(sizeAnimation);
		}
	}
	if (nextWidget != NULL)
	{
		//apply display animation on nextWidget
		if (animationTypes.testFlag(STACK_WIDGET_ANIMATION_GRADIENT))
		{
			//add opacity gradient animation
			QGraphicsOpacityEffect *opacityEffect = qobject_cast<QGraphicsOpacityEffect*>(nextWidget->graphicsEffect());
			if (opacityEffect == NULL)
			{
				opacityEffect = new QGraphicsOpacityEffect;
				nextWidget->setGraphicsEffect(opacityEffect);
			}
			QPropertyAnimation *opacityAnimation = new QPropertyAnimation;
			opacityAnimation->setTargetObject(opacityEffect);
			opacityAnimation->setStartValue(0.0);
			opacityAnimation->setEndValue(1.0);
			opacityAnimation->setPropertyName("opacity");
			opacityAnimation->setDuration(animationDuration * 1000);
			connect(opacityAnimation, &QPropertyAnimation::finished, this, [=](){
				delete opacityAnimation;
			});
			parallelGroup.addAnimation(opacityAnimation);
		}
		if (animationTypes.testFlag(STACK_WIDGET_ANIMATION_DOWN) || animationTypes.testFlag(STACK_WIDGET_ANIMATION_TOP) || animationTypes.testFlag(STACK_WIDGET_ANIMATION_RIGHT) || animationTypes.testFlag(STACK_WIDGET_ANIMATION_LEFT))
		{
			//add pos animation,top<donw<right<left
			QPropertyAnimation *posAnimation = new QPropertyAnimation;
			QPoint currentPos = QPoint(0,0);
			posAnimation->setTargetObject(nextWidget);
			//add pos change animation-donw to top
			if (animationTypes.testFlag(STACK_WIDGET_ANIMATION_TOP))
			{
				currentPos.setY(height());
			}
			//add pos change animation-top to down
			if (animationTypes.testFlag(STACK_WIDGET_ANIMATION_DOWN))
			{
				currentPos.setY(-height());
			}
			//add pos change animation-left to right
			if (animationTypes.testFlag(STACK_WIDGET_ANIMATION_RIGHT))
			{
				currentPos.setX(-width());
			}
			//add pos change animation-right to left
			if (animationTypes.testFlag(STACK_WIDGET_ANIMATION_LEFT))
			{
				currentPos.setX(width());
			}
			posAnimation->setStartValue(currentPos);
			posAnimation->setEndValue(QPoint(0,0));
			posAnimation->setPropertyName("pos");
			posAnimation->setDuration(animationDuration * 1000);
			connect(posAnimation, &QPropertyAnimation::finished, this, [=](){
				delete posAnimation;
			});
			parallelGroup.addAnimation(posAnimation);
		}
		if (animationTypes.testFlag(STACK_WIDGET_ANIMATION_SIZE))
		{
			//add size change animation
			QPropertyAnimation *sizeAnimation = new QPropertyAnimation;
			sizeAnimation->setTargetObject(nextWidget);
			nextWidget->resize(QSize(0,0));
			sizeAnimation->setStartValue(QSize(0, 0));
			sizeAnimation->setEndValue(size());
			sizeAnimation->setPropertyName("size");
			sizeAnimation->setDuration(animationDuration * 1000);
			connect(sizeAnimation, &QPropertyAnimation::finished, this, [=](){
				delete sizeAnimation;
			});
			parallelGroup.addAnimation(sizeAnimation);
		}
	}
}

int QZuesAnimationStackWidget::getAnimationDuration() const
{
	return animationDuration;
}

void QZuesAnimationStackWidget::setAnimationDuration(int val)
{
	animationDuration = val;
}
