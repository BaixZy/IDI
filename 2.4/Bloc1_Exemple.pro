TEMPLATE    = app
QT         += opengl 

INCLUDEPATH +=  /usr/include/glm

FORMS += MyForm.ui

HEADERS += MyForm.h MyGLWidget.h MyLineEdit.h

SOURCES += main.cpp \
        MyForm.cpp MyGLWidget.cpp MyLineEdit.cpp
