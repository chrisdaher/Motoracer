#include <GL/glut.h>
#include <math.h>
#include "Road.h"
#include "Material.h"
#include "Texture.h"
#define M_PI 3.14
Road::Road() : start(0.0f, 0.0f, 0.0f), end(0.0f,0.0f,0.0f){rotX=0; rotY= 90; rotZ=0;turn =0;}
Road::Road(Point s, Point e) : width(e.z-s.z), length(e.x-s.x){this->Road::Road(); start = s; end = e;}
Road::Road(const Road& r){
	this->Road::Road(r.start, r.end);
	width = r.width;
	length = r.length;
	rotX = r.rotX;
	rotY = r.rotY;
	rotZ = r.rotZ;
	turn = r.turn;
}
void drawSphere(GLfloat r, float angle){

}

void Road::setRotations(float x, float y, float z){
	rotX = x;
	rotY = y;
	rotZ = z;
}

void Road::Draw(){
	glPushMatrix();
	glTranslatef(start.x, start.y-0.4, (end.z + start.z)/2);
	glColor3f(0,0,0);
	if(rotY==90)
	{
		glScalef(length,0.1,width);
	}
	else
	{
		glScalef(width, 0.1, length);
	}
	
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
	glRotatef(rotZ, 0, 0, 1);
	if(turn==0){
		GLUquadric *qobj = gluNewQuadric(); 

    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluQuadricTexture(qobj, GL_TRUE);

		gluQuadricTexture(qobj,GL_TRUE); 
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, Texture::getRoadId());
		gluCylinder(qobj, 1, 1, 1, 50, 50);
		gluDeleteQuadric(qobj); 
		glDisable(GL_TEXTURE_2D);
	}
	else{
		//drawSphere(2,2, 20, 45);
	}
	glPopMatrix();
}
