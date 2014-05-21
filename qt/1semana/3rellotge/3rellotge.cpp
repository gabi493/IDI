#include <QApplication>
#include <QFrame>
#include <QLabel>
#include <QWidget>
#include <QLCDNumber>
#include <QDial>
#include <QLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>


int main( int argc, char ** argv) {
		// Creem tots els components
	QApplication app(argc, argv);
	QFrame *w = new QFrame();
	QVBoxLayout *mainLayout = new QVBoxLayout(w);

	QHBoxLayout *cH0 = new QHBoxLayout();		//cH0

	QVBoxLayout *cV1 = new QVBoxLayout();				//Hours:
	QLabel *hours = new QLabel ("Hours");							//hName
	QLCDNumber *hLCD = new QLCDNumber();							//hLCD
	QDial *hDial = new QDial(NULL);								//hDial
	hDial->setRange(0, 23);

	QVBoxLayout *cV2 = new QVBoxLayout();				//Minutes:
	QLabel *minutes = new QLabel ("Minutes"); 						//mName
	QLCDNumber *mLCD = new QLCDNumber();							//mLCD
	QDial *mDial = new QDial(NULL);								//mDial
	mDial->setRange(0, 59);

	QSpacerItem *sp1 = new QSpacerItem(20, 100);			//sp1


	QHBoxLayout *cHexit = new QHBoxLayout();	//exit
	QPushButton *exit = new QPushButton("&Exit", w);		//eButton


		//Insertem el hName, hLCD i hDial al cV1
	cV1->addWidget(hours);
	cV1->addWidget(hLCD);
	cV1->addWidget(hDial);

		//Insertem el mName, mLCD i mDial al cV2
	cV2->addWidget(minutes);
	cV2->addWidget(mLCD);
	cV2->addWidget(mDial);

		//Insertem cV1, cV2 i sp1 al cH0;
	cH0->addLayout(cV1);
	cH0->addLayout(cV2);
	cH0->addItem(sp1);

		//Insertem el space i el exit al cHexit
	cHexit->addItem(new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
	cHexit->addWidget(exit);

		//Insertem el cH0 i cHexit al mainLayout
	mainLayout->addLayout(cH0);
	mainLayout->addLayout(cHexit);


		// Afegim els signals i slots
	app.connect(exit, SIGNAL(clicked()), w, SLOT(close()));
	app.connect(hDial, SIGNAL(valueChanged(int)), hLCD, SLOT(display(int)));
	app.connect(mDial, SIGNAL(sliderMoved(int)), mLCD, SLOT(display(int)));

	w->show();
	return app.exec();
}
