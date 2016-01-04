#include "qzuescombobox.h"

QZuesComboBox::QZuesComboBox(QWidget *parent)
	: QComboBox(parent)
{
	//make the combobox can be styled using custom qss
	QStyledItemDelegate* itemDelegate = new QStyledItemDelegate(this);
	setItemDelegate(itemDelegate);
}

QZuesComboBox::~QZuesComboBox()
{

}
