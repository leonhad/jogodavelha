#ifndef _graphics_h
#define _graphics_h

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

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

class Graphics {
public:
    static GLfloat ambient_light[];
    static GLfloat light_position[];
    static GLfloat diffuseMaterial[];
    static GLfloat mat_specular[];
    GLuint torus;
    GLuint xcubes;

private:
    void cube3d(GLfloat t, GLfloat x, GLfloat y, GLfloat z);
    void cilindro(GLfloat r, GLfloat h);
    /** Desenha um X na tela */
    void DrawX(void);
    /** Desenha um torus na tela */
    void DrawO(void);

public:
    Graphics();
    ~Graphics();
    /** desenha um quadrado para sele��o */
    void DrawBox(void);
    /** calcula as distancias padr�o do bloco */
    void loadIdentity(void);
    void genLists();
    /** Desenha um # na tela */
    void DrawGrid(void);
    
    void drawXCubes();
    void drawTorus();
};

#endif

