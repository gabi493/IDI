#include <QLabel>
#include <QString>
#include <QChar>
#include <QAbstractButton>

#include "ui_MyForm.h"

class MyForm : public QWidget {		// public QLabel = extends QLabel de JAVA

	Q_OBJECT	//Macro de Qt


	public:
		
		MyForm(QWidget *parent = 0);
	
	public slots:
	//Metodos publicos
		
	
	signals:
	//Signals
	
	private:
	//Parte privada de la clase
		Ui::MyForm ui;
		
};
