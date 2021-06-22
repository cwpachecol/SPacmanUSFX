#pragma once
#include "GameActor.h"
class GamePawn :
    public GameActor
{
private:
protected:
public:
    // Constructores y destructores
    GamePawn();
    GamePawn(Texture* _textura);
    GamePawn(Texture* _textura, int _posicionX, int _posicionY);

    //Metodos accesores
    //Metodos varios

    //Metodos virtuales, redefinidos o sobrecargados
    virtual void render();
    virtual void update();
    virtual void handleEvent(SDL_Event* event);
    virtual void deleteGameObject();
    virtual void free();

};

