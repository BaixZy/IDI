
//#include <GL/glew.h>
#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffers();

  //INICIALIZO VARIABLE UNIFORM
  //float miescala = 0.3f; //flotante -> Declaracion en el .hh
  //glUniform1f (scaleLoc, miescala); //Aqui se inicializa la variable uniform

}

void MyGLWidget::paintGL ()
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  /*Codigo original de la sesion 3
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer
  //Me actualiza la matriz siempre antes de pintar se coloca
  modelTransform ();

  // Activem l'Array a pintar 
  glBindVertexArray(VAO1);
 
  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, 6);
  
  // Desactivem el VAO
  glBindVertexArray(0);
  */
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  //Pintem la casa VAO1
  
 // glViewport (0, 0, ample/2, alt/2);
  // Activem l'Array a pintar 
  modelTransformObj1();
  glBindVertexArray(VAO1);
 
  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, 9);
  
  // Desactivem el VAO
  glBindVertexArray(0);
  //Pintem el triangle VAO2
 // glViewport (ample/2, alt/2, ample/2, alt/2);
  
  modelTransformObj2();
  glBindVertexArray(VAO2);
  glDrawArrays(GL_TRIANGLES, 0, 3);  // 3 vértices para el triángulo
  glBindVertexArray(0); //Desactivem VAO
}

void MyGLWidget::resizeGL (int w, int h)
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif
}


void MyGLWidget::keyPressEvent (QKeyEvent *e) {
    makeCurrent (); //Esto siempre se pone
    switch (e->key()) {
    /*  case Qt::Key_S :
        miescala += 0.1;
        glUniform1f (scaleLoc, miescala);
        break;
      case Qt::Key_D :
        miescala -= 0.1;
        glUniform1f (scaleLoc, miescala); //scaleLoc = miescala se le asigana a un flotante
        break;
    */
    //Exercici 1 i 2
      case Qt::Key_Left :
        tx -= 0.1;
        break;

      case Qt::Key_Right :
        tx += 0.1;
        break;
      case Qt::Key_P:
            anguloObj1 += M_PI / 6;  // Incrementa 30 grados para obj1
            anguloObj2 -= M_PI / 6;  // Decrementa 30 grados para obj2
            break;
            
      case Qt::Key_Up :
        ty += 0.1;
       // angulo += 1;
       /* Exercici 4-5
       esclx += 0.1;
       escly += 0.1;
       esclx += 0.1;
       escly += 0.05;
       */
               
        break;

      case Qt::Key_Down :
        ty -= 0.1;
       /*Exercici 4-5
       esclx -= 0.1;
       escly -= 0.1;
       -----------------
       esclx -= 0.1;
       escly -= 0.05;
       */
       // angulo -= 1;
        break;
      

      default: e->ignore (); // propagar al pare
}
  update (); //Esto siempre se pone
}


void MyGLWidget::creaBuffers ()
{
  /* Codigo original de la sesion 3
  glm::vec3 Vertices[3];  // Tres vèrtexs amb X, Y i Z
  //Cuadrado
  Vertices[0] = glm::vec3(-1.0, -1.0, 0.0);
  Vertices[1] = glm::vec3(0.0, 1.0, 0.0);
  Vertices[2] = glm::vec3(1.0, -1.0, 0.0);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO1); //Nos asignará un(indicado por el 1) VAO
  glBindVertexArray(VAO1); //Activame el VAO actual

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO1;
  glGenBuffers(1, &VBO1); //Nos asigna un VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO1); //Activa el VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); //Indico el bloque de datos a pasar a la GPU
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0); //Asignara 3 floats al vertexLoc(apuntador de la variable entrada)
  glEnableVertexAttribArray(vertexLoc); //Activamos

  // Desactivem el VAO
  glBindVertexArray(0);
  */
  glm::vec3 Vertices1[9];  // Tres vèrtexs amb X, Y i Z
  //Casita -> VAO1
  Vertices1[0] = glm::vec3(-1.0, -1.0, 0.0);
  Vertices1[1] = glm::vec3(-1.0, 0.0, 0.0);
  Vertices1[2] = glm::vec3(0.0, -1.0, 0.0);
  Vertices1[3] = glm::vec3(-1.0, 0.0, 0.0);
  Vertices1[4] = glm::vec3(0.0, 0.0, 0.0);
  Vertices1[5] = glm::vec3(0.0, -1.0, 0.0);
  Vertices1[6] = glm::vec3(-1.0, 0.0, 0.0);
  Vertices1[7] = glm::vec3(0.0, 0.0, 0.0);
  Vertices1[8] = glm::vec3(-0.5, 1.0, 0.0);
  
  //Triángulo -> VAO2
  glm::vec3 Vertices2[3];
  Vertices2[0] = glm::vec3(0.0, 0.0, 0.0);
  Vertices2[1] = glm::vec3(1.0, 0.0, 0.0);
  Vertices2[2] = glm::vec3(0.5, 1.0, 0.0);


  //1 VAO
  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO1); //Nos asignará un(indicado por el 1) VAO
  glBindVertexArray(VAO1); //Activame el VAO actual

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO1;
  glGenBuffers(1, &VBO1); //Nos asigna un VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO1); //Activa el VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices1), Vertices1, GL_STATIC_DRAW); //Indico el bloque de datos a pasar a la GPU
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0); //Asignara 3 floats al vertexLoc(apuntador de la variable entrada)
  glEnableVertexAttribArray(vertexLoc); //Activamos

  // Desactivem el VAO
  //glBindVertexArray(0); Al activar un VAO nuevo se desactiva el anterior.
  
  glGenVertexArrays(1, &VAO2); //Nos asignará un(indicado por el 1) VAO
  glBindVertexArray(VAO2); //Activame el VAO actual
  
  GLuint VBO2;

  // Creació del buffer amb les dades dels vèrtexs
  glGenBuffers(1, &VBO2); //Nos asigna un VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO2); //Activa el VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), Vertices2, GL_STATIC_DRAW); //Indico el bloque de datos a pasar a la GPU
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0); //Asignara 3 floats al vertexLoc(apuntador de la variable entrada)
  glEnableVertexAttribArray(vertexLoc); //Activamos
  
  glBindVertexArray(0); //Desactivar VAO

}

//Las TG se van acumulando las matrices ya que las funciones devuelven matrices. SI quiero hacer escalado+rotacion hago una operacion  y luego utilzo la matriz resultante.
/*void MyGLWidget::modelTransform () {
    //Exercici 1 i 2
    glm::mat4 TG (1.0); // Matriu de transformació, inicialment identitat
    //TG = glm::rotate(TG,float(M_PI/4), glm::vec3 (0.0, 0.0, 1.0)); //Roto en un ángulo d 45 grados en el eje z
    TG = glm::scale(TG, glm::vec3(esclx,escly,esclz));
    TG = glm::translate (TG, glm::vec3 (tx, ty, 0.0));
    TG = glm::rotate(TG,angulo, glm::vec3 (0.0, 0.0, 1.0));
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
    

    //Esta funcion actualiza la matriz siempre antes de pintar
} */

void MyGLWidget::modelTransformObj1() {
    glm::mat4 TG(1.0);  // Matriz identidad
    // Aplica una rotación sobre el centro del objeto obj1
    TG = glm::translate(TG, glm::vec3(-0.5, 0.0, 0.0));  // Traslada al origen del obj1
    TG = glm::rotate(TG, anguloObj1, glm::vec3(0.0, 0.0, 1.0));  // Rota obj1 en sentido positivo
    TG = glm::translate(TG, glm::vec3(0.5, 0.0, 0.0));  // Vuelve a la posición original
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);  // Pasa la matriz de transformación al shader
}

void MyGLWidget::modelTransformObj2() {
    glm::mat4 TG(1.0);  // Matriz identidad
    // Aplica una rotación sobre el centro del objeto obj2
    TG = glm::translate(TG, glm::vec3(-0.5, 0.0, 0.0));  // Traslada al origen del obj2
    TG = glm::rotate(TG, anguloObj2, glm::vec3(0.0, 0.0, 1.0));  // Rota obj2 en sentido negativo
    TG = glm::translate(TG, glm::vec3(0.5, 0.0, 0.0));  // Vuelve a la posición original
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);  // Pasa la matriz de transformación al shader
}


void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  //scaleLoc =glGetUniformLocation (program->programId(), "scl");
  transLoc = glGetUniformLocation (program->programId(), "TG"); //TG transloc = mat4
}
