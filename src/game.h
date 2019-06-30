#ifndef _game_H
#define	_game_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if defined(HAVE_WINDOWS_H) && defined(_WIN32)
    #include <windows.h>
#endif
#ifdef HAVE_GL_GL_H
    #include <GL/gl.h>
    #include <GL/glu.h>
#elif defined(HAVE_OPENGL_GL_H)
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #error no gl.h
#endif

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
    // vari�veis utilizadas para verifica��o dos frames por segundo.
    GLint T0;
    GLint Frames;
    GLfloat *mat_shininess;
    Graphics *graphics;
    SDL_Surface *screen;
    SDLKey keys;

    
    Point selected;
    Winner local_ganhador;
    
    // Vari�veis para o jogo.
    char matriz[3][3];
    int player;
    bool win;
    GLfloat loop;
    
    void idle();
    
    /** new window size or exposure */
    void reshape(int width, int height);
    /** Se nenhum ganhador retorna 0, sen�o o n�mero do ganhador. */
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

