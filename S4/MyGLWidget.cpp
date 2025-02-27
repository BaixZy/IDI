// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>


#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}


void MyGLWidget:: initializeGL ( ) {
    //Añadimos mi codigo que se añade al codigo del padre -> BL2GLWidget.
     BL2GLWidget::initializeGL();
     //Actividad 1
    // projectTransform(); //Llamamos a project transfomr
    // viewTransform(); //Llamamos a view transform y se le añaden estas lineas al "padre"     
     
     //Actividad 4 cargar modelo
     glEnable (GL_DEPTH_TEST); //Algoritmo de Z-Buffer;     
     creaBuffers();
}    

 void MyGLWidget::carregaShaders () {
    BL2GLWidget::carregaShaders(); //Llama al código del padre BL2GLWIDGET
   
    //Añadimos una linea que se sobreescribira en el codigo del padre BL2Glwidget
   // projLoc = glGetUniformLocation (program->programId(), "PRJ");
   // viewLoc = glGetUniformLocation (program->programId(), "VM");
   transHomer = glGetUniformLocation (program->programId(), "TG");
   
 }
 
 void MyGLWidget:: keyPressEvent (QKeyEvent *event) {
 	makeCurrent();
  	switch (event->key()) {
    		case Qt::Key_R: { // escalar a més gran
      		angulo_h += 45;
      		break;
    		}
    default: event->ignore(); break;
    }
  update();
}
 
//Actividad 4 modelos
void MyGLWidget::creaBuffers () {
    //Hay que sobreescribir el código del padre porque queremos pintar a Homer y no la casa
   m.load ("models/HomerProves.obj");


  // Creació del Vertex Array Object per pintar
   glGenVertexArrays(1, &VAO_Homer);
   glBindVertexArray(VAO_Homer);

   GLuint VBO_Homer[2];
   glGenBuffers(2, VBO_Homer);
   glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[0]);
   glBufferData (GL_ARRAY_BUFFER,sizeof(GLfloat) * m.faces ().size () * 3 * 3, m.VBO_vertices (), GL_STATIC_DRAW); // posició

   // Activem l'atribut vertexLoc
   glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
   glEnableVertexAttribArray(vertexLoc);

   glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[1]);
   glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat)* m.faces ().size () * 3 * 3, m.VBO_matdiff (), GL_STATIC_DRAW); // color

   glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
   glEnableVertexAttribArray(colorLoc);

glBindVertexArray (0);
}

void MyGLWidget::paintGL () {
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     modelTransformH();
     glBindVertexArray (VAO_Homer);
     // pintem
     glDrawArrays(GL_TRIANGLES, 0, m.faces ().size () * 3);
     glBindVertexArray (0);
}



/*
//Actividad 1
void MyGLWidget::projectTransform () {
    // glm::perspective (FOV en radians, ra window, znear, zfar)
    glm::mat4 Proj = glm::perspective (float(M_PI)/2.0f, 1.0f, 0.4f, 3.0f);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
} 


//Actividad 2 - 3
void MyGLWidget::viewTransform () {
    // glm::lookAt (OBS, VRP, UP)
    glm::mat4 View = glm::lookAt (glm::vec3(0,0,1),
    glm::vec3(0,0,0), glm::vec3(1,0,0));
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
} 
*/
//Actividad 5
void MyGLWidget::modelTransformH() {
   glm::mat4 TG(1.0);
   TG = glm::rotate(TG,angulo_h,glm::vec3(0.0,1.0,0.0));
   glUniformMatrix4fv (transHomer, 1, GL_FALSE, &TG[0][0]);
}


MyGLWidget::~MyGLWidget() {
}


