#include <math.h>
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include "graphics.h"

using namespace std;

GLfloat Graphics::ambient_light[] = { 0.5f, 0.5f, 0.5f, 0.6f };
GLfloat Graphics::light_position[] = { 1.0f, -2.0f, -2.0f, 1.0f };
//GLfloat Graphics::light_position[] = { -1.0f, 0.0f, 0.0f, 2.0f };
GLfloat Graphics::diffuseMaterial[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat Graphics::mat_specular[] = { 0.7f, 0.7f, 0.7f, 1.0f };

static const GLfloat size = 0.2f;

#define pik 0.1570796f
#define pi2 6.283184f

Graphics::Graphics() {
}

Graphics::~Graphics() {
    if (glIsList(torus)) glDeleteLists(torus, 1);
    if (glIsList(xcubes)) glDeleteLists(xcubes, 1);
}

void Graphics::drawXCubes() {
    glCallList(xcubes);
}

void Graphics::drawTorus() {
    glCallList(torus);
}

void Graphics::genLists() {
    if (glIsList(torus)) glDeleteLists(torus, 1);
    if (glIsList(xcubes)) glDeleteLists(xcubes, 1);
    
    torus = glGenLists(1);
    glNewList(torus, GL_COMPILE);
    DrawO();
    glEndList();
    
    xcubes = glGenLists(1);
    glNewList(xcubes, GL_COMPILE);
    DrawX();
    glEndList();
}

void Graphics::cube3d(GLfloat t, GLfloat x, GLfloat y, GLfloat z) {
    /* tampa */
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(x, y, z);
    glVertex3f(x, y, z - t);
    glVertex3f(x + t, y, z - t);
    glVertex3f(x + t, y, z);
    glEnd();
    /* base */
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(x, y - t, z);
    glVertex3f(x, y - t, z - t);
    glVertex3f(x + t, y - t, z - t);
    glVertex3f(x + t, y - t, z);
    glEnd();
    /* esquerda */
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(x, y, z);
    glVertex3f(x, y, z - t);
    glVertex3f(x, y - t, z - t);
    glVertex3f(x, y - t, z);
    glEnd();
    /* direita */
    glBegin(GL_QUADS);
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glVertex3f(x + t, y, z);
    glVertex3f(x + t, y, z - t);
    glVertex3f(x + t, y - t, z - t);
    glVertex3f(x + t, y - t, z);
    glEnd();
    /* frente */
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f(x, y, z);
    glVertex3f(x + t, y, z);
    glVertex3f(x + t, y - t, z);
    glVertex3f(x, y - t, z);
    glEnd();
    /* trás */
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, -1.0f);
    glVertex3f(x,     y,     z - t);
    glVertex3f(x + t, y,     z - t);
    glVertex3f(x + t, y - t, z - t);
    glVertex3f(x    , y - t, z - t);
    glEnd();
}

void Graphics::DrawGrid(void) {
    glColor3f(0.0f, 0.5f, 0.0f);
    /* Em cima
     Vertical */
    glTranslatef(-0.4f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f(-0.05f, -1.1f, 0.0f);
    glVertex3f( 0.05f, -1.1f, 0.0f);
    glVertex3f( 0.05f, 1.1f, 0.0f);
    glVertex3f(-0.05f, 1.1f, 0.0f);
    glEnd();
    /* esquerdo */
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.05f, -1.1f, 0.0f);
    glVertex3f(-0.05f, 1.1f, 0.0f);
    glVertex3f(-0.05f, 1.1f, -size);
    glVertex3f(-0.05f, -1.1f, -size);
    glEnd();
    /* direito */
    glBegin(GL_QUADS);
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glVertex3f( 0.05f, -1.1f, 0.0f);
    glVertex3f( 0.05f, 1.1f, 0.0f);
    glVertex3f( 0.05f, 1.1f, -size);
    glVertex3f( 0.05f, -1.1f, -size);
    glEnd();
    /* cima */
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, -1.0f);
    glVertex3f(-0.05f, -1.1f, 0.0f);
    glVertex3f( 0.05f, -1.1f, 0.0f);
    glVertex3f( 0.05f, -1.1f, -size);
    glVertex3f(-0.05f, -1.1f, -size);
    glEnd();
    /* baixo */
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f(-0.05f, 1.1f, 0.0f);
    glVertex3f( 0.05f, 1.1f, 0.0f);
    glVertex3f( 0.05f, 1.1f, -size);
    glVertex3f(-0.05f, 1.1f, -size);
    glEnd();
    
    glTranslatef( 0.8f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f(-0.05f, -1.1f, 0.0f);
    glVertex3f( 0.05f, -1.1f, 0.0f);
    glVertex3f( 0.05f, 1.1f, 0.0f);
    glVertex3f(-0.05f, 1.1f, 0.0f);
    glEnd();
    /* esquerdo */
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.05f, -1.1f, 0.0f);
    glVertex3f(-0.05f, 1.1f, 0.0f);
    glVertex3f(-0.05f, 1.1f, -size);
    glVertex3f(-0.05f, -1.1f, -size);
    glEnd();
    /* direito */
    glBegin(GL_QUADS);
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glVertex3f( 0.05f, -1.1f, 0.0f);
    glVertex3f( 0.05f, 1.1f, 0.0f);
    glVertex3f( 0.05f, 1.1f, -size);
    glVertex3f( 0.05f, -1.1f, -size);
    glEnd();
    /* cima */
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, -1.0f);
    glVertex3f(-0.05f, -1.1f, 0.0f);
    glVertex3f( 0.05f, -1.1f, 0.0f);
    glVertex3f( 0.05f, -1.1f, -size);
    glVertex3f(-0.05f, -1.1f, -size);
    glEnd();
    /* baixo */
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f(-0.05f, 1.1f, 0.0f);
    glVertex3f( 0.05f, 1.1f, 0.0f);
    glVertex3f( 0.05f, 1.1f, -size);
    glVertex3f(-0.05f, 1.1f, -size);
    glEnd();
    
    /* Horizontal */
    glTranslatef(-0.4f, -0.4f, 0.0f);
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f(-1.15f, -0.05f, 0.0f);
    glVertex3f(-1.15f, 0.05f, 0.0f);
    glVertex3f( 1.15f, 0.05f, 0.0f);
    glVertex3f( 1.15f, -0.05f, 0.0f);
    glEnd();
    /* esquerdo */
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-1.15f, -0.05f, 0.0f);
    glVertex3f(-1.15f, 0.05f, 0.0f);
    glVertex3f(-1.15f, 0.05f, -size);
    glVertex3f(-1.15f, -0.05f, -size);
    glEnd();
    /* direito */
    glBegin(GL_QUADS);
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glVertex3f( 1.15f, -0.05f, 0.0f);
    glVertex3f( 1.15f, 0.05f, 0.0f);
    glVertex3f( 1.15f, 0.05f, -size);
    glVertex3f( 1.15f, -0.05f, -size);
    glEnd();
    /* cima */
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, -1.0f);
    glVertex3f(-1.15f, -0.05f, 0.0f);
    glVertex3f( 1.15f, -0.05f, 0.0f);
    glVertex3f( 1.15f, -0.05f, -size);
    glVertex3f(-1.15f, -0.05f, -size);
    glEnd();
    /* baixo */
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f(-1.15f, 0.05f, 0.0f);
    glVertex3f( 1.15f, 0.05f, 0.0f);
    glVertex3f( 1.15f, 0.05f, -size);
    glVertex3f(-1.15f, 0.05f, -size);
    glEnd();
    
    glTranslatef( 0.0f, 0.8f, 0.0f);
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f(-1.15f, -0.05f, 0.0f);
    glVertex3f(-1.15f, 0.05f, 0.0f);
    glVertex3f( 1.15f, 0.05f, 0.0f);
    glVertex3f( 1.15f, -0.05f, 0.0f);
    glEnd();
    /* esquerdo */
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-1.15f, -0.05f, 0.0f);
    glVertex3f(-1.15f, 0.05f, 0.0f);
    glVertex3f(-1.15f, 0.05f, -size);
    glVertex3f(-1.15f, -0.05f, -size);
    glEnd();
    /* direito */
    glBegin(GL_QUADS);
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glVertex3f( 1.15f, -0.05f, 0.0f);
    glVertex3f( 1.15f, 0.05f, 0.0f);
    glVertex3f( 1.15f, 0.05f, -size);
    glVertex3f( 1.15f, -0.05f, -size);
    glEnd();
    /* cima */
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, -1.0f);
    glVertex3f(-1.15f, -0.05f, 0.0f);
    glVertex3f( 1.15f, -0.05f, 0.0f);
    glVertex3f( 1.15f, -0.05f, -size);
    glVertex3f(-1.15f, -0.05f, -size);
    glEnd();
    /* baixo */
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f(-1.15f, 0.05f, 0.0f);
    glVertex3f( 1.15f, 0.05f, 0.0f);
    glVertex3f( 1.15f, 0.05f, -size);
    glVertex3f(-1.15f, 0.05f, -size);
    glEnd();
}

void Graphics::cilindro(GLfloat r, GLfloat h) {
    int poligonos = 0;
    GLfloat u;
    GLfloat x, z;
    
    glBegin(GL_QUADS);
    for (u = 0.0f; u < pi2; u += pik) {
        x = r * cos(u);
        z = r * sin(u);
        /* \ */
        glNormal3f( cos(u), 0.0f, sin(u));
        glVertex3f(r * cos(u), - h / 2, r * sin(u));
        glVertex3f(r * cos(u+pik), -h/2, r * sin(u+pik));
        glVertex3f(r * cos(u+pik), h/2, r * sin(u+pik));
        glVertex3f(r * cos(u), h / 2, r * sin(u));
        poligonos++;
    }
    glEnd();
    
    /* x = rcosu, y = v, z = rsinu */
#ifdef DEBUG
    cout << "poligonos x / 2 = " << poligonos << endl;
#endif
}

void Graphics::DrawX(void) {
    /*
     float a;
    
     for (a = 0.0; a <= 0.5; a += 0.08) {
     cube3d(0.08, -0.04, a - 0.2, 0.0);
     cube3d(0.08, a - 0.2, -0.04, 0.0);
     } */
    glRotatef(45.0, 0.0, 0.0, 1.0);
    cilindro(0.05f, 0.6f);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    cilindro(0.05f, 0.6f);
}

#define r 0.08f
#define a 0.18f
void Graphics::DrawO(void) {
    GLfloat v, u;
    register GLfloat cosu, cosv, sinu, sinv, rsinu;
    register GLfloat sinvpik, rsinupik, cosupik;
    register GLfloat cosvpik, rcosua, rcosupika;
    register GLfloat x, y;
    register int poligonos = 0;
    
    glBegin(GL_QUADS);
    for (v = 0.0f; v < pi2; v += pik) {
        for (u = 0.0f; u < pi2;u += pik) {
            poligonos++;
            /* polígono */
            /* normalO(u, v); */
            cosu = cos(u);
            cosv = cos(v);
            sinu = sin(u);
            sinv = sin(v);
            rsinu = r*sinu;
            sinvpik = sin(v+pik);
            rsinupik = r*sin(u+pik);
            cosupik = cos(u+pik);
            cosvpik = cos(v+pik);
            rcosua = r*cosu+a;
            rcosupika = r*cosupik+a;
            x = cosu*cosv;
            y = cosu*sinv;
            /* z = sinu; */
            glNormal3f(x, y, sinu);
            
            glVertex3f(rcosua*cosv, rcosua*sinv, rsinu);
            glVertex3f(rcosua*cosvpik, rcosua*sinvpik, rsinu);
            glVertex3f(rcosupika*cosvpik, rcosupika*sinvpik, rsinupik);
            glVertex3f(rcosupika*cosv, rcosupika*sinv, rsinupik);
        }
    }
    glEnd();
#ifdef DEBUG
    cout << "poligonos zero = " << poligonos << endl;
#endif
}

void Graphics::DrawBox(void) {
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glBegin(GL_QUADS);
    /* baixo */
    glTranslatef(0.0f, 0.0f, -size);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f(-0.3f, -0.3f, 0.0f);
    glVertex3f( 0.3f, -0.3f, 0.0f);
    glVertex3f( 0.3f, 0.3f, 0.0f);
    glVertex3f(-0.3f, 0.3f, 0.0f);
    /* cima */
    glTranslatef( 0.0f, 0.0f, size);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f(-0.3f, -0.3f, 0.0f);
    glVertex3f( 0.3f, -0.3f, 0.0f);
    glVertex3f( 0.3f, 0.3f, 0.0f);
    glVertex3f(-0.3f, 0.3f, 0.0f);
    /* lados */
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.3f, -0.3f, 0.0f);
    glVertex3f(-0.3f, 0.3f, 0.0f);
    glVertex3f(-0.3f, 0.3f, -size);
    glVertex3f(-0.3f, -0.3f, -size);

    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f( 0.3f, -0.3f, 0.0f);
    glVertex3f( 0.3f, 0.3f, 0.0f);
    glVertex3f( 0.3f, 0.3f, -size);
    glVertex3f( 0.3f, -0.3f, -size);

    glNormal3f( 0.0f, -1.0f, 0.0f);
    glVertex3f(-0.3f, -0.3f, 0.0f);
    glVertex3f( 0.3f, -0.3f, 0.0f);
    glVertex3f( 0.3f, -0.3f, -size);
    glVertex3f(-0.3f, -0.3f, -size);

    glNormal3f( 0.0f, -1.0f, 0.0f);
    glVertex3f(-0.3f, 0.3f, 0.0f);
    glVertex3f( 0.3f, 0.3f, 0.0f);
    glVertex3f( 0.3f, 0.3f, -size);
    glVertex3f(-0.3f, 0.3f, -size);
    glEnd();
    
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
}

void Graphics::loadIdentity(void) {
    glLoadIdentity();
    glTranslatef( 0.0f, 0.0f, -3.0f);
    //glRotatef(20.0f,-1.0f, 0.0f, 0.0f);
    //glTranslatef( 0.0f, 2.3f, 0.0f);
}
