#pragma once
#include "GameObject.h"
#include "TileGraph.h"

class Pared :
    public GameObject
{
private:
    Tile* tileActual;
    int frameX;
    int frameY;
    int altoClip;
    int anchoClip;
public:
    Pared(int tipo, Tile* _tile, Texture* _paredTextura, int _posicionX, int _posicionY);
    Tile* getTile() { return tileActual; }
    void setTile(Tile* _tileNuevo);
    void render() override;
    void setTexture(int tipoTextura);
};

