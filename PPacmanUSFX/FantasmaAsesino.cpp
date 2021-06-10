#include "FantasmaAsesino.h"

FantasmaAsesino::FantasmaAsesino(Tile* _tile, Texture* _fantasmaAsesinoTextura, int _posicionX, int _posicionY, int _ancho, int _alto, int _anchoPantalla, int _altoPantalla, int _velocidadPatron) :
	
	Fantasma(_tile, _fantasmaAsesinoTextura, _posicionX, _posicionY, _ancho, _alto, _anchoPantalla, _altoPantalla, _velocidadPatron)


{

	tileActual = _tile;
	tileSiguiente = nullptr;

	if (tileActual != nullptr) {
		tileActual->setFantasma(this);
		tileSiguiente = tileGraph->getTileEn(tileActual->getPosicionX(), tileActual->getPosicionY());

		posicionX = tileActual->getPosicionX() * Tile::anchoTile;
		posicionY = tileActual->getPosicionY() * Tile::altoTile;
	}
	else {
		posicionX = 0;
		posicionY = 0;
	}
};

void FantasmaAsesino::setTile(Tile* _tileNuevo) {
	if (tileActual != nullptr)
		tileActual->setFantasma(nullptr);

	tileActual = _tileNuevo;

	if (tileActual != nullptr) {
		tileActual->setFantasma(this);

		posicionX = tileActual->getPosicionX() * Tile::anchoTile;
		posicionY = tileActual->getPosicionY() * Tile::altoTile;
	}
};

void FantasmaAsesino::update()
{
	Pacman* pacman = tileGraph->getPacman();

	if (pacman != nullptr) {

		// en este punto seguira a pacman
		if (tileActual == tileSiguiente) {
			// cnsigue el camino para seguir a pacman
			PathFinder astar(tileGraph);
			astar.SetAvoidFunction(Fantasma::AvoidInPathFinder);
			camino = astar.CalculateRoute(tileActual, pacman->getTile());

			if (camino.size() > 1) {
				tileSiguiente = camino[1];
			}
			// Lo que se desea despues es ver el NPC deberia ir
			if (posicionX < tileSiguiente->getPosicionX() * Tile::anchoTile)
				direccionActual = MOVE_RIGHT;

			else if (posicionX > tileSiguiente->getPosicionX() * Tile::anchoTile)
				direccionActual = MOVE_LEFT;

			else if (posicionY > tileSiguiente->getPosicionY() * Tile::anchoTile)
				direccionActual = MOVE_UP;

			else if (posicionY < tileSiguiente->getPosicionY() * Tile::anchoTile)
				direccionActual = MOVE_DOWN;

			

			for (auto tile : tileGraph->get4Vecinos(tileActual)) {
				if (tile->getPacman() != nullptr && VerColision(tile->getPacman()->getColision())) {
					tile->getPacman()->Delete();
				}
			}

			
		}

		// Dependiendo a la direccion de movimiento, mueve el NPC cordinadamente
		switch (direccionActual)
		{
		case MOVE_UP:
			posicionY = std::max(posicionY - velocidadPatron, tileSiguiente->getPosicionY() * Tile::altoTile);
			break;
		case MOVE_DOWN:
			posicionY = std::min(posicionY + velocidadPatron, tileSiguiente->getPosicionY() * Tile::altoTile);
			break;
		case MOVE_LEFT:
			posicionX = std::max(posicionX - velocidadPatron, tileSiguiente->getPosicionX() * Tile::anchoTile);
			break;
		case MOVE_RIGHT:
			posicionX = std::min(posicionX + velocidadPatron, tileSiguiente->getPosicionX() * Tile::anchoTile);
			break;
		}

		// Actualizar la colision
		colision.x = posicionX;
		colision.y = posicionY;
		/*setTile(tileSiguiente);*/



		// Revisa si el NPC se movio al siguiente tile, si es asi cambia su direccion
		if ((direccionActual == MOVE_DOWN || direccionActual == MOVE_UP) && posicionY == tileSiguiente->getPosicionY() * Tile::altoTile)
			setTile(tileSiguiente);

		if ((direccionActual == MOVE_LEFT || direccionActual == MOVE_RIGHT) && posicionX == tileSiguiente->getPosicionX() * Tile::anchoTile)
			setTile(tileSiguiente);
	}
}
