#include "qzuestest.h"
#include <QTimer>
QZuesTest::QZuesTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.lblZues->setType(LABEL_TYPE_MARQUEE);
	ui.txtZues->setText("testssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss");
	StackWidgetAnimationTypes animationTypes = STACK_WIDGET_ANIMATION_GRADIENT;
	animationTypes |= STACK_WIDGET_ANIMATION_TOP;
	animationTypes |= STACK_WIDGET_ANIMATION_SIZE;
	ui.stkTest->setAnimationTypes(animationTypes);
	//ui.stkTest->setAnimationDuration(10);
	QTimer::singleShot(1000, [&](){
		initStackWidget();
	});
	

}

QZuesTest::~QZuesTest()
{

}

void QZuesTest::on_btnReset_clicked()
{
	ui.txtZues->reset();
}

void QZuesTest::on_btnNextPage_clicked()
{
	QWidget*nxtWidget = ui.stkTest->nextWidget(ui.stkTest->currentIndex());
	ui.stkTest->setCurrentWidget(nxtWidget);
}

void QZuesTest::initStackWidget()
{
	InfoDisplay *infos = new InfoDisplay(this);
	qDebug()<< ui.stkTest->addWidget(infos);
	AddInfo *addInfo = new AddInfo(this);
	qDebug() << ui.stkTest->addWidget(addInfo);
}
