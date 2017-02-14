#ifndef QZUESNAVIGATOR_H
#define QZUESNAVIGATOR_H

#include <QWidget>
#include <QVariant>
#include <QList>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>
#include <QPropertyAnimation>
#include <QEvent>
#include <QTimer>
struct QZuesNavigatorItem
{
public:
	QZuesNavigatorItem(QString content,QVariant userData = QVariant());
	QString getDisplayText() const { return m_displayText; }
	void setDisplayText(QString val) { m_displayText = val; }
	QVariant getData() const { return m_data; }
	void setData(QVariant val) { m_data = val; }
	friend class QZuesNavigator;
	bool operator==(const QZuesNavigatorItem &item)
	{
		return (m_label == item.m_label);
	}
private:
	QString m_displayText;
	QVariant m_data;
	QLabel *m_label;
};
class QZuesNavigator : public QWidget
{
	Q_OBJECT

public:
	QZuesNavigator(QWidget *parent);
	~QZuesNavigator();
	int insertItem(QZuesNavigatorItem item, int index = -1);
	int appendItem(QZuesNavigatorItem item);
	void removeItem(int index);
	void removeAllItem();
	QZuesNavigatorItem &itemAt(int index);
	/*int indexOf(QZuesNavigatorItem item);*/
	int count();
	void setColor(QColor backgroundColor,QColor slipperColor,QColor wordsColor);
signals:
	void signalSelectItemChanged(QZuesNavigatorItem item);
private:
	void updateUi();
	void ajustSize();
	QLabel *newItem(QZuesNavigatorItem &item);
	QZuesNavigatorItem& findItem(QLabel *label);
private:
	QList<QZuesNavigatorItem> m_items;
	QWidget *m_slipper;
	QWidget *m_labelContainer;
	QPropertyAnimation m_slipperAnimation;
	QColor m_backgroundColor, m_slipperColor, m_foreroundColor;
	int m_currentItemIndex;
protected:
	virtual void resizeEvent(QResizeEvent *event) override;
	virtual void paintEvent(QPaintEvent *event) override;
	virtual bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // QZUESNAVIGATOR_H
