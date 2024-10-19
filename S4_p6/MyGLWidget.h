// MyGLWidget.h
#include "BL2GLWidget.h"
#include "model.h" //Funciones de carga de modelo

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

    virtual void initializeGL ( );
    virtual void carregaShaders (); //Va a sobrescribir a la clase BL2GLWIDGET
    //virtual void modelTransform ();
    virtual void keyPressEvent (QKeyEvent *event);
    
    
    //Modelos

    //Sobreescribiremos al padre
     virtual void creaBuffers ();

     virtual void paintGL();

     //Creamos una nueva función
      void projectTransform (); //Actividad 1
      void viewTransform(); //Actividad 2
      void modelTransformH();
      void modelTransformSuelo();

     // GLuint projLoc; //Puntero al uniform mat4 de la matriz proyección
     // GLuint viewLoc; //Puntero al uniform mat4 de la matriz view
      GLuint transHomer;
      GLuint VAO_Homer;
      GLuint VAO_tierra;
      
      
      float angulo_h = 0;
      Model m;
  private:
    int printOglError(const char file[], int line, const char func[]);
};
