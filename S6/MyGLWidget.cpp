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

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::modelTransform () 
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::scale(transform, glm::vec3(m.escala*escala));
  transform = glm::rotate(transform,rotacio,glm::vec3(0.0,1.0,0.0));
  transform = glm::translate(transform,glm::vec3(0-m.centreBase.x, 0-m.centreBase.y, 0-m.centreBase.z));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modeloTrans(){
  glm::mat4 transform (1.0f);
  transform = glm::scale(transform, glm::vec3(escala));
  //transform = glm::scale(transform, glm::vec3(2.0,1.0,2.0));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::initializeGL () {
    BL2GLWidget::initializeGL();
    glEnable (GL_DEPTH_TEST);
    projectTransform();
    viewTransform();

}
//Actividad 3
void MyGLWidget::resizeGL (int w, int h) {
  // Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
  ra_window = float (w) / float (h);
  projectTransform();
#endif

}

void MyGLWidget::paintGL () {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport (0, 0, ample, alt);
    glBindVertexArray(VAO1);
    // Pintem l'escena
    modelTransform();
    glDrawArrays (GL_TRIANGLES, 0, m.model.faces ().size () * 3);
  
    // Desactivem el VAO
    glBindVertexArray(0);
    
    glBindVertexArray(VAO2);
    // Pintem l'escena
    modeloTrans();
    glDrawArrays (GL_TRIANGLES, 0, 6);
  
    // Desactivem el VAO
    glBindVertexArray(0);
}

void MyGLWidget::calcularCapsa_Patricio() {
  
    float minx, miny, minz, maxx, maxy, maxz;
    //Inicialització
    minx = maxx = m.model.vertices()[0];
    miny = maxy = m.model.vertices()[1];
    minz = maxz = m.model.vertices()[2];

    for (unsigned int i = 3; i < m.model.vertices().size(); i += 3) {
        minx = fmin(minx, m.model.vertices()[i+0]);
        maxx = fmax(maxx, m.model.vertices()[i+0]);

        miny = fmin(miny, m.model.vertices()[i+1]);
        maxy = fmax(maxy, m.model.vertices()[i+1]);

        minz = fmin(minz, m.model.vertices()[i+2]);
        maxz = fmax(maxz, m.model.vertices()[i+2]);
    }

    m.minim = glm::vec3(minx, miny, minz);
    m.maxim = glm::vec3(maxx, maxy, maxz);
    m.centre = glm::vec3((m.minim + m.maxim) / 2.f);
    m.centreBase = glm::vec3((minx + maxx)/2.f, miny, (minz + maxz)/2.f);
    m.amplada = maxx - minx;
    m.profunditat = maxz - minz;
    m.alcada = maxy - miny;
    m.escala = 4./(maxy-miny);
}

void MyGLWidget::creaBuffers() {
  m.model.load ("./models/Patricio.obj");
  calcularCapsa_Patricio();
  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);
  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO1;
  glGenBuffers(1, &VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData (GL_ARRAY_BUFFER,sizeof(GLfloat) * m.model.faces().size() * 3 * 3, m.model.VBO_vertices(), GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO2;
  glGenBuffers(1, &VBO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData (GL_ARRAY_BUFFER,sizeof(GLfloat) * m.model.faces().size() * 3 * 3, m.model.VBO_matdiff(), GL_STATIC_DRAW);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
  //Dibuja el suelo
  glm::vec3 Vertices2[6];
  Vertices2[0] = glm::vec3(-2.5, 0.0, 2.5);
  Vertices2[1] = glm::vec3(-2.5, 0.0, -2.5);
  Vertices2[2] = glm::vec3(2.5, 0.0, 2.5);
  Vertices2[3] = glm::vec3(-2.5, 0.0, -2.5);
  Vertices2[4] = glm::vec3(2.5, 0.0, 2.5);
  Vertices2[5] = glm::vec3(2.5, 0.0, -2.5);

  glGenVertexArrays(1, &VAO2);
  glBindVertexArray(VAO2);
  
  GLuint VBO3;
  glGenBuffers(1, &VBO3);
  glBindBuffer(GL_ARRAY_BUFFER, VBO3);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), Vertices2, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders() { 
        BL2GLWidget::carregaShaders(); // cridem primer al mètode de BL2GLWidget
        projLoc = glGetUniformLocation (program->programId(), "PRJ");
        viewLoc = glGetUniformLocation (program->programId(), "VM");
}

//Apartado 1
void MyGLWidget::calcula(glm::vec3 punt_minim, glm::vec3 punt_maxim) {
  centre.x = (punt_maxim.x+punt_minim.x)/2;
  centre.y = (punt_maxim.y+punt_minim.y)/2;
  centre.z = (punt_maxim.z+punt_minim.z)/2;
  radi = (glm::distance(punt_maxim, punt_minim))/2; 
}
void MyGLWidget::projectTransform () {
        calcula(glm::vec3(-2.5,0.0,-2.5),glm::vec3(2.5,4.0,2.5));
        glm::mat4 Proj;
        znear = 2*radi-radi;
        zfar = 2*radi+radi;
        FOV = 2 * (glm::asin(radi/(2*radi)));
        left   = -radi;
        right  = radi;
        bottom = -radi;
        top    =  radi;

        if (prespectiva) {
            if (ra_window < 1) FOV = 2 *(glm::atan(glm::tan(glm::asin(radi/(2*radi)))/(ra_window))); 
             Proj = glm::perspective (FOV, ra_window, znear, zfar);
        }
        else { //resize ortogonal
          if (ra_window > 1) {
            left = -radi*ra_window;
            right = radi*ra_window;
          }
          else {
            bottom = -radi/ra_window;
            top = radi/ra_window;
          }
          Proj = glm::ortho(left, right, bottom, top, znear, zfar);
      }
        
       // glm::mat4 Proj = glm::perspective (float(M_PI)/2.0f, 1.0f, 0.4f, 3.0f);
        glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform () {
    VRP = centre;
    OBS = VRP + 2*radi*glm::vec3(0,0,1);
    UP = glm::vec3(0,1,0);
    glm::mat4 View = glm::lookAt (OBS, VRP, UP);
   // glm::mat4 View = glm::lookAt (glm::vec3(0,0,1), glm::vec3(0,0,0), glm::vec3(0,1,0));
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S: { // escalar a més gran
      escala += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      escala -= 0.05;
      break;
    }
    case Qt::Key_R: {
        rotacio += M_PI/4;
        break;
    }
    case Qt::Key_O : {
            if(prespectiva) prespectiva = false;
            else prespectiva = true;
            projectTransform();
            break;
    }
    default: event->ignore(); break;
  }
  update();
}
