#ifndef ADDINFO_H
#define ADDINFO_H

#include <QWidget>
namespace Ui {class AddInfo;};

class AddInfo : public QWidget
{
	Q_OBJECT

public:
	AddInfo(QWidget *parent = 0);
	~AddInfo();

private:
	Ui::AddInfo *ui;
};

#endif // ADDINFO_H
