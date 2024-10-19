#version 330 core

in vec3 vertex;
in vec3 suelo_ver;
in vec3 color;

uniform mat4 TG;
uniform mat4 TG_suelo;
//uniform mat4 PRJ; //Proyección capturarlo en carrega shaders
//uniform mat4 VM; //View Matrix

out vec3 fcolor;

void main()  {
    fcolor = color;
   // gl_Position = PRJ*VM*TG * vec4 (vertex, 1.0); //Coordenadas 3D a 2D -> Prj  PRJ ->glm perspective/ortogonal y VM y tg igual sclae/rotate/translate
  // gl_Position = TG*vec4 (vertex, 1.0);
  
  if (vertex.y == -1.0) { // Suponiendo que los vértices del suelo están en Y = -1
        gl_Position = TG_suelo * vec4(suelo_ver, 1.0); // Aplica la transformación del suelo
    } else {
        gl_Position = TG * vec4(vertex, 1.0); // Aplica la transformación de Homer
    }

}
