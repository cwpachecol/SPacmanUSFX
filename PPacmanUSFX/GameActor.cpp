#include "GameActor.h"


TileGraph* GameObject::tileGraph = nullptr;

GameActor::GameActor()
{
	textura = nullptr;
	posicionX = 0;
	posicionY = 0;
	alto = 0;
	ancho = 0;
	visible = true;
	eliminar = false;
	enMovimiento = false;

	numeroFrame = 0;
	contadorFrames = 0;
	framesMovimiento = 1;
	colisionador = new SDL_Rect({ 0, 0, ancho, alto });

}

GameActor::GameActor(Texture* _textura)
{
	textura = _textura;
	posicionX = _posicionX;
	posicionY = _posicionY;
	alto = 0;
	ancho = 0;
	visible = true;
	eliminar = false;
	enMovimiento = false;
	numeroObjetosCreados++;
	idObjeto = numeroObjetosCreados;


	numeroFrame = 0;
	contadorFrames = 0;
	framesMovimiento = 1;
	colisionador = new SDL_Rect({ _posicionX, _posicionY, ancho, alto });


}

GameActor::GameActor(Texture* _textura, int _posicionX, int _posicionY)
{
}

void GameObject::render()
{
	SDL_Rect* cuadroAnimacion = new SDL_Rect({ 25 * numeroFrame, 0, getAncho(), getAlto() });

	// Renderizar en la pantalla
	textura->render(getPosicionX(), getPosicionY(), cuadroAnimacion);
}

bool GameObject::revisarColision(const SDL_Rect* _otroColisionador)
{
	if (_otroColisionador->x > colisionador->x + colisionador->w) {
		return false;
	}

	if (_otroColisionador->y > colisionador->y + colisionador->h) {
		return false;
	}

	if (_otroColisionador->x + _otroColisionador->w < colisionador->x) {
		return false;
	}

	if (_otroColisionador->y + _otroColisionador->h < colisionador->y) {
		return false;
	}

	return true;
}

bool GameObject::revisarColision(const SDL_Rect* _colisionador1, const SDL_Rect* _colisionador2)
{
	if (_colisionador1->x > _colisionador2->x + _colisionador2->w) {
		return false;
	}

	if (_colisionador1->y > _colisionador2->y + _colisionador2->h) {
		return false;
	}

	if (_colisionador1->x + _colisionador1->w < _colisionador2->x) {
		return false;
	}

	if (_colisionador1->y + _colisionador1->h < _colisionador2->y) {
		return false;
	}

	return true;
}

void GameObject::update() {
	contadorFrames++;
	numeroFrame = contadorFrames / 8;

	if (numeroFrame > framesMovimiento - 1) {
		numeroFrame = 0;
		contadorFrames = 0;
	}

}