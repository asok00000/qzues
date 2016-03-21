#ifndef QZUESTEST_H
#define QZUESTEST_H

#include <QtWidgets/QMainWindow>
#include "ui_qzuestest.h"
#include "qzuesanimationstackwidget.h"
#include "addinfo.h"
#include "infodisplay.h"
class QZuesTest : public QMainWindow
{
	Q_OBJECT

public:
	QZuesTest(QWidget *parent = 0);
	~QZuesTest();
private slots:
	void on_btnReset_clicked();
	void on_btnNextPage_clicked();
private:
	void initStackWidget();
private:
	Ui::QZuesTestClass ui;
};

#endif // QZUESTEST_H
