#ifndef QZUESCOMBOBOX_H
#define QZUESCOMBOBOX_H

#include <QComboBox>
#include <QStyledItemDelegate>
/*!
*\class QZuesComboBox
*\brief An extended Combo Box Widget inherited from QComboBox
*\details Provide more powerful functions
*\author Hu chunhua
*\version 1.0
*\date 2015-11-30 10:36:21
*\note modification:
*\date
*/
class QZuesComboBox : public QComboBox
{
	Q_OBJECT

public:
	QZuesComboBox(QWidget *parent);
	~QZuesComboBox();

private:
	
};

#endif // QZUESCOMBOBOX_H
