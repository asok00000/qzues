#ifndef QZUESTEST_H
#define QZUESTEST_H

#include <QtWidgets/QMainWindow>
#include "ui_qzuestest.h"

class QZuesTest : public QMainWindow
{
	Q_OBJECT

public:
	QZuesTest(QWidget *parent = 0);
	~QZuesTest();
private slots:
	void on_btnReset_clicked();
private:
	Ui::QZuesTestClass ui;
};

#endif // QZUESTEST_H
