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
	
	QHBoxLayout *cH = new QHBoxLayout(&F);			//Crea un contenidornidor horitzontal

	QLineEdit *le = new QLineEdit(&F);			//Afegeix una caixa de text
	cH->addWidget(le);

	QSpacerItem *sp = new QSpacerItem(100, 20);		//Afegeix un espai (horitzontal, vertical)
	cH->addItem(sp);

	QVBoxLayout *cV = new QVBoxLayout(&F);			//Crea un contrnidor vertical
	cH->addLayout(cV);

	QPushButton *ok = new QPushButton("D'acord", &F);	//Afegeix un boto
	cV->addWidget(ok);

	QPushButton *surt = new QPushButton("Sortir", &F);	//Afegeix un altre boto
	cV->addWidget(surt);

	F.show();
	return a.exec();
}
