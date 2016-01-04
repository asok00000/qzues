#include "qzuestest.h"

QZuesTest::QZuesTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.lblZues->setType(LABEL_TYPE_MARQUEE);
	ui.txtZues->setText("testssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss");
}

QZuesTest::~QZuesTest()
{

}

void QZuesTest::on_btnReset_clicked()
{
	ui.txtZues->reset();
}
