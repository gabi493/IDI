#include <QApplication>

#include "MyForm.h"	//Para poder usar mis signals/slots 

int main(int argc, char **argv) {
	QApplication a(argc, argv);
	MyForm form;
	form.show();
	return a.exec();
}
