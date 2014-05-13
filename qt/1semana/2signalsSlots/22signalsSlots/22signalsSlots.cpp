#include <QApplication>
#include <QPushButton>
#include <QFrame>	//Per a poder utilitzar el contenidor QFrame
#include <QLayout>	//Per a poder utilitzar el 'Layout'
#include <QLineEdit>	//Per a poder utilitzar QLineEdit

int main(int argc, char **argv) {
	QApplication a(argc, argv);
	QString fontFamily = "Arial";
	a.setFont(fontFamily);
	
	QFrame F(0, NULL);	//Crea un frame
	
	QVBoxLayout *cV = new QVBoxLayout(&F);			//Crea un contenidornidor horitzontal

	QLineEdit *le = new QLineEdit(&F);			//Afegeix una caixa de text
	cV->addWidget(le);

	QSpacerItem *sp = new QSpacerItem(100, 20);		//Afegeix un espai (horitzontal, vertical)
	cV->addItem(sp);

	QPushButton *ok = new QPushButton("D'acord", &F);	//Afegeix un boto
	cV->addWidget(ok);

	QPushButton *surt = new QPushButton("Sortir", &F);	//Afegeix un altre boto
	cV->addWidget(surt);

	F.show();
	return a.exec();
}
