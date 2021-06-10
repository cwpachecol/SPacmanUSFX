#include "Pared.h"

Pared::Pared(int _tipo, Tile* _tile, Texture* _paredTextura, int _posicionX, int _posicionY, int _ancho, int _alto, int _anchoPantalla, int _altoPantalla):
GameObject(_paredTextura, _posicionX, _posicionY, _ancho, _alto, _anchoPantalla, _altoPantalla){
	setTexture(_tipo);
	tileActual = _tile;
	if (tileActual != nullptr) {
		tileActual->setPared(this);

		posicionX = tileActual->getPosicionX() * Tile::anchoTile;
		posicionY = tileActual->getPosicionY() * Tile::altoTile;
	}
	else {
		posicionX = 0;
		posicionY = 0;
	}
	altoClip = 140;
	anchoClip = 140;
};


void Pared::setTile(Tile* _tileNuevo) {
	if (tileActual != nullptr)
		tileActual->setPared(nullptr);

	tileActual = _tileNuevo;

	if (tileActual != nullptr) {
		tileActual->setPared(this);

		posicionX = tileActual->getPosicionX() * Tile::anchoTile;
		posicionY = tileActual->getPosicionY() * Tile::altoTile;
	}
};

void Pared::render()
{
	if (visible) {
		SDL_Rect rect = { posicionX, posicionY, ancho, alto };
		SDL_Rect clip = { 0 + frameX * anchoClip, 0 + frameY * altoClip, anchoClip, altoClip };
		textura->render(posicionX, posicionY, &clip, &rect);
	}
};

void Pared::setTexture(int tipoTextura)
{
	if (tipoTextura % 4 == 0)
		frameY = trunc(tipoTextura / 4) - 1;
	else
		frameY = trunc(tipoTextura / 4);
	frameX = (tipoTextura - frameY * 4) - 1;;
}



