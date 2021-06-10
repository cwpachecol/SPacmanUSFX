#include "ParedGalactico.h"

ParedGalactico::ParedGalactico(bool _isElectrica, int tipo, Tile* _tile, Texture* _paredTextura, int _posicionX, int _posicionY, int _ancho, int _alto, int _anchoPantalla, int _altoPantalla)
:Pared(tipo,  _tile,  _paredTextura,  _posicionX, _posicionY,  _ancho,  _alto,  _anchoPantalla,  _altoPantalla)
{
	isElectrica = _isElectrica;
	tileActual = _tile;
	isGalactico = true;
	state = 0;
}

void ParedGalactico::update() {
	if (isElectrica) {
		velocidadPacman = 5;
		if (cont2 <= notElectricTime) {
			cont2++;
			if (cont2 >= notElectricTime) {
				cont1 = 0;
				setTexture(11);
				state = 1;
			}
		}
		else {
			if (cont1 <= electricTime) {
				cont1++;
				if (cont1 >= electricTime) {
					cont2 = 0;
					setTexture(10);
					state = 0;
					for (auto tile : tileGraph->get4Vecinos(tileActual)) {
						if (tile != nullptr && tile->getPacman() != nullptr && tile->getPacman()->getState() == 2) {
							tile->getPacman()->setVelocidadPatron(velocidadPacman);
							tile->getPacman()->setState(0);
						}
					}
				}
			}
		}
	}
	if (state == 1) {
		for (auto tile : tileGraph->get4Vecinos(tileActual)) {
			if (tile != nullptr && tile->getPacman() != nullptr) {
				tile->getPacman()->setState(2);
				tile->getPacman()->setVelocidadPatron(0);
			}
		}
	}
}