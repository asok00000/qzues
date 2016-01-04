#include "qzuestest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QZuesTest w;
	w.show();
	return a.exec();
}
