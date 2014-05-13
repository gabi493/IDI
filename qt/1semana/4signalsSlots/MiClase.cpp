#include "MiClase.h"


class MiClase : public QLabel {

	Q_OBJECT		//Macro de Qt

	public slots:		//Metodos publicos
		
		void letrasMayusMinus() {
			
		}
		
		char getChar(int n, String st) {
			return st[n];
		}
		void setChar(int n, char c) {
			
		}
		
	
	signals:		//Signals
		void letrasMayusMinus(int);
	
	private:		//Parte privada de la clase
		
}
