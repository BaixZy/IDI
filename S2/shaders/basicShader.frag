#version 330 core

out vec4 FragColor; //Color de salida
in vec3 fcolor;

//Tamaño ventana 715x714 AltoxAncho -> ViewPort a partir del QTdesing
void main() {
   // FragColor = vec4(0, 0, 0, 1);

/* Actividad 1
       FragColor = vec4(1.);
 if (gl_FragCoord.x < 354.) {
        if (gl_FragCoord.y > 357.) FragColor = vec4(1.,0.,0.,1); //Rojo
        else FragColor = vec4(1.,1.,0.,1); //Amarillo
 }
 else {
       if (gl_FragCoord.y > 357.) FragColor = vec4(0.,0.,1.,1); //Azul
       else  FragColor = vec4(0.,1.,0.,1); //Verde
 }
 */

//Actividad2
/*if (mod(floor(gl_FragCoord.y), 20.0) > 5.0) discard;

 if (gl_FragCoord.x < 354.) {
        if (gl_FragCoord.y > 357.) FragColor = vec4(1.,0.,0.,1); //Rojo
        else FragColor = vec4(1.,1.,0.,1); //Amarillo
 }
 else {
       if (gl_FragCoord.y > 357.) FragColor = vec4(0.,0.,1.,1); //Azul
       else  FragColor = vec4(0.,1.,0.,1); //Verde
 }
*/

//Actividad 4
 FragColor = vec4(fcolor, 1.0); //Alfa 0 = opaco 1 = transparente.

}

