#include "game.h"
#include <iostream>

using namespace std;

Game::Game() {
    T0 = 0;
    Frames = 0;
    mat_shininess = new GLfloat(1);
    mat_shininess[0] = 50.0;
    graphics = new Graphics();
    
    SDL_Init(SDL_INIT_VIDEO);
    
    screen = SDL_SetVideoMode(450, 450, 16, SDL_VIDEO_OPENGL|SDL_WINDOW_RESIZABLE);
    
    if ( ! screen ) {
        cerr << "Couldn't set 450x450 GL video mode" << endl;
        //MessageBox(NULL, "Couldn't set 450x450 GL video mode", "Video Init Error!", MB_OK);
        SDL_Quit();
        exit(2);
    }
    SDL_WM_SetCaption("Tic Tac Toe", "TTT");
}

Game::~Game() {
    if (graphics) delete graphics;
    SDL_Quit();
}

void Game::idle() {
    
}

void Game::run() {
    newGame();
    
    reshape(screen->w, screen->h);
    clearMatrix();
    while (true) {
        SDL_Event event;
        
        idle();
        while ( SDL_PollEvent(&event) ) {
            switch(event.type) {
                case SDL_VIDEORESIZE:
                screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 16,
                SDL_OPENGL|SDL_RESIZABLE);
                if ( screen ) {
                    reshape(screen->w, screen->h);
                } else {
                    /* Uh oh, we couldn't set the new video mode?? */;
                }
                break;
                case SDL_VIDEOEXPOSE:
                draw();
                break;
                case SDL_QUIT:
                return;
                case SDL_KEYDOWN:
                keys = event.key.keysym.sym;
                if ( keys == SDLK_n ) {
                    newGame();
                } else if ( keys == SDLK_ESCAPE ) {
                    return;
                } else if ( keys == SDLK_UP ) {
                    selected.y--;
                } else if ( keys == SDLK_DOWN ) {
                    selected.y++;
                } else if ( keys == SDLK_LEFT ) {
                    selected.x--;
                } else if ( keys == SDLK_RIGHT ) {
                    selected.x++;
                } else if ( keys == SDLK_SPACE ) {
                    if (!win) {
                        if (matriz[selected.x][selected.y] == '\0') {
                            if (player == 1) {
                                matriz[selected.x][selected.y] = 'x';
                                player++;
                            } else {
                                matriz[selected.x][selected.y] = 'o';
                                player--;
                            }
                        }
                    }
                    if (validaGanhador()) {
                        win = true;
                    }
                }
                break;
            }
        }
        if (selected.x < 0)
            selected.x = 0;
        else if (selected.x > 2)
            selected.x = 2;
        else if (selected.y < 0)
            selected.y = 0;
        else if (selected.y > 2)
            selected.y = 2;
        
        draw();
    }
}

void Game::newGame() {
    clearMatrix();
    player = 1;
    win = false;
    local_ganhador.p.y = 0;
    local_ganhador.p.x = 0;
    local_ganhador.s.y = 0;
    local_ganhador.s.x = 0;
    local_ganhador.t.y = 0;
    local_ganhador.t.x = 0;
}

void Game::clearMatrix() {
    register unsigned short int y, x;
    for(y = 0; y < 3; y++) {
        for(x = 0; x < 3; x++) {
            matriz[x][y] = '\0';
        }
    }
    selected.x = 1;
    selected.y = 1;
}

int Game::validaGanhador() {
    register unsigned short int loop;
    for (loop = 0; loop < 3; loop++) {
        // -
        if ((matriz[loop][0] == matriz[loop][1]) && (matriz[loop][0] == matriz[loop][2])) {
            if (matriz[loop][0] != '\0') {
                if (matriz[loop][0] == 'x') {
                    local_ganhador.p.x = loop;
                    local_ganhador.p.y = 0;
                    local_ganhador.s.x = loop;
                    local_ganhador.s.y = 1;
                    local_ganhador.t.x = loop;
                    local_ganhador.t.y = 2;
                    return 1;
                } else if (matriz[loop][0] == 'o') {
                    local_ganhador.p.x = loop;
                    local_ganhador.p.y = 0;
                    local_ganhador.s.x = loop;
                    local_ganhador.s.y = 1;
                    local_ganhador.t.x = loop;
                    local_ganhador.t.y = 2;
                    return 2;
                }
            }
        }
        // |
        if ((matriz[0][loop] == matriz[1][loop]) && (matriz[0][loop] == matriz[2][loop])) {
            if (matriz[0][loop] != '\0') {
                if (matriz[0][loop] == 'x') {
                    local_ganhador.p.x = 0;
                    local_ganhador.p.y = loop;
                    local_ganhador.s.x = 1;
                    local_ganhador.s.y = loop;
                    local_ganhador.t.x = 2;
                    local_ganhador.t.y = loop;
                    return 1;
                } else if (matriz[0][loop] == 'o') {
                    local_ganhador.p.x = 0;
                    local_ganhador.p.y = loop;
                    local_ganhador.s.x = 1;
                    local_ganhador.s.y = loop;
                    local_ganhador.t.x = 2;
                    local_ganhador.t.y = loop;
                    return 2;
                }
            }
        }
    }
    // /
    if ((matriz[0][0] == matriz[1][1]) && (matriz[0][0] == matriz[2][2])) {
        if (matriz[0][0] != '\0') {
            local_ganhador.p.x = 0;
            local_ganhador.p.y = 0;
            local_ganhador.s.x = 1;
            local_ganhador.s.y = 1;
            local_ganhador.t.x = 2;
            local_ganhador.t.y = 2;
            if (matriz[0][0] == 'x')
                return 1;
            else if (matriz[0][0] == 'o')
                return 2;
        }
    }
    // \ o
    if ((matriz[0][2] == matriz[1][1]) && (matriz[0][2] == matriz[2][0])) {
        if (matriz[0][2] != '\0') {
            local_ganhador.p.x = 2;
            local_ganhador.p.y = 0;
            local_ganhador.s.x = 1;
            local_ganhador.s.y = 1;
            local_ganhador.t.x = 0;
            local_ganhador.t.y = 2;
            if (matriz[0][2] == 'x')
                return 1;
            else if (matriz[0][2] == 'o')
                return 2;
        }
    }
    return 0;
}

void Game::reshape(int width, int height) {
    graphics->genLists();
    
    glShadeModel(GL_SMOOTH);
    //glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClearDepth(1.0f);
    /* Prevent A Divide By Zero By */
    if (height == 0) {
        height = 1;
    }
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    /* Calculate The Aspect Ratio Of The Window */
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    
    /* Luz */
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_LIGHT0, GL_AMBIENT, graphics->ambient_light);
    glLightfv(GL_LIGHT0, GL_POSITION, graphics->light_position);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, graphics->diffuseMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, graphics->mat_specular);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_COLOR_MATERIAL);
}

void Game::draw() {
    register unsigned short int x, y;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    graphics->loadIdentity();
    graphics->DrawGrid();
    for(y = 0; y < 3; y++) {
        for(x = 0; x < 3; x++) {
            if (matriz[x][y] != '\0') {
                graphics->loadIdentity();
                if (x == 0) {
                    glTranslatef(-0.8f, 0.0f, 0.0f);
                } else if (x == 2) {
                    glTranslatef( 0.8f, 0.0f, 0.0f);
                }
                if (y == 0) {
                    glTranslatef(0.0f, 0.8f, 0.0f);
                } else if (y == 2) {
                    glTranslatef(0.0f, -0.8f, 0.0f);
                }
                if (!win)
                    glColor3f(0.2f, 0.5f, 0.8f);
                else {
                    if (((local_ganhador.p.x == x) && (local_ganhador.p.y == y))
                    || ((local_ganhador.s.x == x) && (local_ganhador.s.y == y))
                    || ((local_ganhador.t.x == x) && (local_ganhador.t.y == y))) {
                        glColor3f(0.7f, 0.0f, 0.0f);
                    } else
                        glColor3f(0.2f, 0.5f, 0.8f);
                }
                
                if (matriz[x][y] == 'x') {
                    glRotatef(loop, 0.0f, 1.0f, 0.0f);
                    graphics->drawXCubes();
                    //DrawX();
                } else if (matriz[x][y] == 'o') {
                    glRotatef(loop, 0.0f, -1.0f, 0.0f);
                    graphics->drawTorus();
                    //DrawO();
                }
            }
            graphics->loadIdentity();
            if (x == 0) {
                glTranslatef(-0.8f, 0.0f, 0.0f);
            } else if (x == 2) {
                glTranslatef( 0.8f, 0.0f, 0.0f);
            }
            if (y == 0) {
                glTranslatef(0.0f, 0.8f, 0.0f);
            } else if (y == 2) {
                glTranslatef(0.0f, -0.8f, 0.0f);
            }
            if ((selected.x == x) && (selected.y == y)) {
                graphics->DrawBox();
            }
        }
    }
    // Calcula o n£mero de frames por segundo.
    Frames++;
    
    register GLint t = SDL_GetTicks();
    register GLfloat seconds = (t - T0) / 1000.0f;
    register GLfloat fps = Frames / seconds;
    
    if (t - T0 >= 5000) {
#ifdef DEBUG
        cout << Frames << " frames in " << seconds << " seconds = " << fps << " FPS" << endl;
#endif
        T0 = t;
        Frames = 0;
    }
    
    if (seconds) {
        loop += (120.0f / (1.0f + fps));
        if (loop >= 360.0f)
            loop -= 360.0f;
    }
    SDL_GL_SwapBuffers();
    //SDL_Delay(1);
}
