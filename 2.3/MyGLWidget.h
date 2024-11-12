#include "BL2GLWidget.h"
#include "model.h"

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

  private:
    int printOglError(const char file[], int line, const char func[]);
    virtual void carregaShaders();
    virtual void initializeGL ();
    virtual void paintGL ();
    virtual void resizeGL (int w, int h);
    virtual void creaBuffers();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void modelTransform ();
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    void calcula(glm::vec3 punt_minim, glm::vec3 punt_maxim);
    void calcularCapsa_Patricio();
    void modeloTrans();
    void projectTransform ();
    void viewTransform ();
    GLuint projLoc,viewLoc,VAO1,VAO2;
    //Model m;
    glm::vec3 centre;
    glm::vec3 OBS;
    glm::vec3 VRP;
    glm::vec3 UP;
    GLint ample, alt;
    float znear;
    float zfar;
    float ra_window = 1;
    float FOV;
    float radi = 0.0;
    float rotacio = 0.0;
    float anglee;
    float left;
    float right;  
    float bottom;
    float top;
    float psi;    // Ψ
      float theta;  // θ
      float phi;    // φ
      
    struct Ratoli {
      bool inici_accio;
      glm::vec2 pos_inicial;    // pos x i y d'on hem clicat 
      float sensitibity;        // suavitzador del moviment amb el ratolí [opcional]
      float invertir_moviment;  //[] amb shift + click  el movient del ratoli es invertit 
      bool modo_freestyle;      //[]
    };
    
    Ratoli ratoli;

    struct Figura {
      Model model;
      glm::vec3 minim;
      glm::vec3 maxim;
      glm::vec3 centre;
      glm::vec3 centreBase;
      float amplada;
      float profunditat;
      float alcada;
      float escala;
      float angle; 
    };

    Figura m;
    bool prespectiva = true;
};
