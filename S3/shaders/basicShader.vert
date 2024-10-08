#version 330 core

in vec3 vertex;
//uniform float scl;
uniform mat4 TG; //Translacion/Rotacion/Escalado siempre matrices 4x4


void main()  {
    //gl_Position = vec4 (vertex*scl, 1.0); //Proyección de cada vertice
    gl_Position = TG * vec4 (vertex, 1.0); //no *scl porque esta incluido el escalado en el TG
}
