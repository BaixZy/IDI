TEMPLATE    = app
QT         += opengl 

INCLUDEPATH +=  /usr/include/glm /home/liang/Escritorio/IDI/S4/Model

FORMS += MyForm.ui

HEADERS += MyForm.h BL2GLWidget.h MyGLWidget.h Model/model.h

SOURCES += main.cpp MyForm.cpp \
        BL2GLWidget.cpp MyGLWidget.cpp Model/model.cpp
