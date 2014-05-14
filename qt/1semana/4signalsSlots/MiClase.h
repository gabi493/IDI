#include <QLabel>
#include <QString>
#include <QChar>


class MiClase : public QLabel {		// public QLabel = extends QLabel de JAVA

	Q_OBJECT	//Macro de Qt


	public slots:
	//Metodos publicos
		void setTexto(const QString &texto) {
			QString newTexto(texto);
			for (int i = 0; i < newTexto.size(); ++i) {
				if (i%2 == 0) newTexto = newTexto.replace(i, 1, newTexto[i].toUpper());
				else newTexto = newTexto.replace(i, 1, newTexto[i].toLower());
			}
			texto = newTexto;
		}
		
	
	signals:
	//Signals
	
	private:
	//Parte privada de la clase
		
}
