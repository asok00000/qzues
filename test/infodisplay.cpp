#include "infodisplay.h"
#include "ui_infodisplay.h"

InfoDisplay::InfoDisplay(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::InfoDisplay();
	ui->setupUi(this);
}

InfoDisplay::~InfoDisplay()
{
	delete ui;
}

