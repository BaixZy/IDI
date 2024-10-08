#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include "glm/glm.hpp"
#include <QKeyEvent> //Incluimos esto para interaccion con QT
#include "glm/gtc/matrix_transform.hpp" //Incluimos esto para las funciones de la glm(Escalado,ROtacion,Translacion)

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();
    
  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();
 
    // resize - Es cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);  

    //Interact with QT
    virtual void keyPressEvent (QKeyEvent * e);

    void modelTransform(); //Declaro un método nuevo para realizar TG

  private:
    void creaBuffers ();
    void carregaShaders ();
    
    // attribute locations
    GLuint vertexLoc; //unsigned int
    GLuint scaleLoc;
    GLuint transLoc;
    //float miescala = 0.3f; //inicializo aqui porque voy autilizarlo en varios puntos del programa
    float tx = 0;
    float ty = 0;


    // Program
    QOpenGLShaderProgram *program;

    GLuint VAO1;
    GLint ample, alt;
};
