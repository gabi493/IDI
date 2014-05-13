#include <QLabel>
#include <QString>
#include <QChar>


class MiClase : public QObject {

	Q_OBJECT	//Macro de Qt

	public:
		MiClase();
		String s;

	public slots:
	//Metodos publicos
		char getChar(int, String);
		void setChar(int, char);
		
	
	signals:
	//Signals
		void letrasMayusMinus(int);
	
	private:
	//Parte privada de la clase
		
}
