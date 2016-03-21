#ifndef INFODISPLAY_H
#define INFODISPLAY_H

#include <QWidget>
namespace Ui {class InfoDisplay;};

class InfoDisplay : public QWidget
{
	Q_OBJECT

public:
	InfoDisplay(QWidget *parent = 0);
	~InfoDisplay();

private:
	Ui::InfoDisplay *ui;
};

#endif // INFODISPLAY_H
