				//Posem els fiters de capçalera necessaris
#include <QApplication>		//Permet declarar una QApplication
#include <QPushButton>		//Permet declarar un QPushButton

int main(int argc, char **argv) {		//Programa principal
	QApplication a(argc, argv);		//Aplicacio en Qt que conte la meva interficie
	QPushButton hello("Hello Qt!", 0);	//Boto amb el text "Hello Qt!" que sera la meva interficie

	hello.resize(150, 30);			//Metode per a determinar la mida del boto

	hello.show();				//Mostrar el boto
	
	return a.exec();			//El meu programa (main) executa el metode que posa en marxa 
						//l'aplicacio "a" de Qt (exec) i retorna el valor que gneri en acabar
}
