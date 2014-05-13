#include "MiClase.h"


class MiClase : public QObject {

	Q_OBJECT		//Macro de Qt

	public:
		String s;
		MiClase() {
		}

	public slots:		//Metodos publicos
		char getChar(int n, String st) {
			return st[n];
		}
		void setChar(int, char) {
			
		}
		
	
	signals:		//Signals
		void letrasMayusMinus(int);
	
	private:		//Parte privada de la clase
		
}
