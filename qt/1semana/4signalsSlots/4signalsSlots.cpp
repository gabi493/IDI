#include <QApplication>
#include <QPushButton>
#include <QFrame>	//Per a poder utilitzar el contenidor QFrame
#include <QLayout>	//Per a poder utilitzar el 'Layout'
#include <QLineEdit>	//Per a poder utilitzar QLineEdit

#include "MiClase.h"	//Para poder usar mis signals/slots 

int main(int argc, char **argv) {
	QApplication a(argc, argv);
	QString fontFamily = "Arial";
	a.setFont(fontFamily);
	
	QFrame F(0, NULL);	//Crea un frame
	QHBoxLayout *cH = new QHBoxLayout(&F);			//Crea un contenidornidor horitzontal
	QLineEdit *le = new QLineEdit("Line Edit", &F);		//Afegeix una caixa de text
	QLabel *label_mostra = new QLabel ("Muestra", &F);	//Afegeix un label
	
	QSpacerItem *sp = new QSpacerItem(100, 20);		//Afegeix un espai (horitzontal, vertical)
	QVBoxLayout *cV = new QVBoxLayout(&F);			//Crea un contrnidor vertical
	QPushButton *ok = new QPushButton("D'acord", &F);	//Afegeix un boto
	QPushButton *surt = new QPushButton("&Sortir", &F);	//Afegeix un altre boto


	//Insertem el LineEdit(le), el SpacerItem(sp) i el VBoxLayout(cV) al layout horitzontal
	cH->addWidget(le);
	cH->addWidget(label_mostra);
	cH->addItem(sp);
	cH->addLayout(cV);

	//Insertem els PushButton(ok + surt) al layout vertical
	cV->addWidget(ok);
	cV->addWidget(surt);

	//Conectem els signals amb els slots
	a.connect(surt, SIGNAL(clicked()), F, SLOT(close()));
	a.connect(ok, SIGNAL(clicked()), label_mostra, SLOT(setTexto()));
	a.connect(le, SIGNAL(textChanged(const QString&)), label_mostra, SLOT(setText(const QString &)));


	F.show();
	return a.exec();
}
