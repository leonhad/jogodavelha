//
// File:   game.h
// Author: leonardo.costa
//
// Created on 1 de Agosto de 2006, 08:32
//

#ifndef _game_H
#define	_game_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include "graphics.h"

struct Point {
    int x;
    int y;
};

struct Winner {
    Point p;
    Point s;
    Point t;
};

class Game {
private:
    // variáveis utilizadas para verificação dos frames por segundo.
    GLint T0;
    GLint Frames;
    GLfloat *mat_shininess;
    Graphics *graphics;
    SDL_Surface *screen;
    SDLKey keys;

    
    Point selected;
    Winner local_ganhador;
    
    // Variáveis para o jogo.
    char matriz[3][3];
    int player;
    bool win;
    GLfloat loop;
    
    void idle();
    
    /** new window size or exposure */
    void reshape(int width, int height);
    /** Se nenhum ganhador retorna 0, senão o n£mero do ganhador. */
    int validaGanhador();
    
    void draw();
    
    void newGame();
    
    void clearMatrix();
    
public:
    Game();
    ~Game();
    void run();
};

#endif	/* _game_H */

