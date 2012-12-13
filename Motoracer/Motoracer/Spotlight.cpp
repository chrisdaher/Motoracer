#include "Spotlight.h"

Spotlight::Spotlight(GLenum l, Point c): light(l), color(c){angle = 25; exp = 20;}
Spotlight::Spotlight(GLenum l, Point pos, Point dir, Point c): light(l), color(c), position(pos), direction(dir){angle = 25; exp = 20;}

void Spotlight::spotLight(){
    /*
    a, b and c -- x, y and z co-ordinates for light position
    d, e and f -- x, y and z co-ordinates for spot light position
    */
    GLfloat mat_specular[] = { color.x, color.y, color.z, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { position.x, position.y, position.z, 1.0 };
    GLfloat spotDir[] = { direction.x, direction.y, direction.z };
    glClearColor (1, 1, 1, 0.0);
    glShadeModel (GL_SMOOTH);
    //glLightfv(GL_LIGHT1,GL_SPECULAR,mat_specular);
		glLightfv(light,GL_DIFFUSE,mat_specular);
    glLightfv(light,GL_POSITION,light_position);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    // Definig spotlight attributes
    glLightf(light,GL_SPOT_CUTOFF,angle);
    glLightf(light,GL_SPOT_EXPONENT,exp);
    glLightfv(light,GL_SPOT_DIRECTION,spotDir);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
}

void Spotlight::draw(){
	spotLight();
}