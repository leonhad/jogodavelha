#ifndef _graphics_h
#define _graphics_h

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
    /** desenha um quadrado para seleção */
    void DrawBox(void);
    /** calcula as distancias padrão do bloco */
    void loadIdentity(void);
    void genLists();
    /** Desenha um # na tela */
    void DrawGrid(void);
    
    void drawXCubes();
    void drawTorus();
};

#endif

