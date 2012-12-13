#include <GL/glut.h>   
#include <math.h>
#include "CarDrawer.h"
#include "Texture.h"
#include "Material.h"
bool isSolid = true;
double const PI = 4*atan(1.0);
float prevPosition;
float direction;
int CarDrawer::rot = 0;

void drawBox(GLfloat size, GLenum type)
{
  GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

  for (i = 5; i >= 0; i--) {
    glBegin(type);
    glNormal3fv(&n[i][0]);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3fv(&v[faces[i][0]][0]);

  glTexCoord2f(1.0f, 0.0f);
  glVertex3fv(&v[faces[i][1]][0]);

  glTexCoord2f(1.0f, 1.0f);
  glVertex3fv(&v[faces[i][2]][0]);

  glTexCoord2f(0.0f, 1.0f);
  glVertex3fv(&v[faces[i][3]][0]);
  glEnd();
  }
}

void solidCube(GLdouble size)
{
  drawBox(size, GL_QUADS);
}



CarDrawer::CarDrawer(){
	prevPosition = 0.0f;
	currentWheelRotation =0;
}
CarDrawer::CarDrawer(Point& p, Point& angle, float* v){
		position = &p;
		rotationAngle = &angle;
		velocity = v;
		currentWheelRotation =0;
		prevPosition = 0.0f;
		Point color(1,1,1);
}

void CarDrawer::drawWheel(double x, double y, double z)
{
	double angle;
	double wheelInnerRadius = 0.06;
	double wheelOuterRadius = 0.3; 

	Material::setRubber();
	//Wheel
	glPushMatrix();
	//glColor3f(0.1,0.1,0.1);
	Material::setColor(0.1f,0.1f,0.1f);
	glTranslatef (x, y, z);
	if(isSolid)
	{
		glutSolidTorus(wheelInnerRadius,wheelOuterRadius,32,32); 
	}
	else
	{
		glutWireTorus(wheelInnerRadius,wheelOuterRadius,32,32);
	}

	//rim
	glPushMatrix();
	angle = PI/2;
	//glColor3f(.7,0.7,0.7);
	Material::setColor(0.7f,0.7f,0.7f);
	glTranslatef (cos(angle)*wheelOuterRadius, sin(angle)*wheelOuterRadius, 0.0);
	glRotatef(90,sin(angle),cos(angle),0.0);		
	gluCylinder(gluNewQuadric(), 0.02, 0.02, wheelOuterRadius*2, 15, 10);
	glPopMatrix();
	

	//rim
	glPushMatrix();
	glColor3f(.7,0.7,0.7);
	Material::setColor(0.7f,0.7f,0.7f);
	angle = PI/4;
	glTranslatef (cos(angle)*wheelOuterRadius, sin(angle)*wheelOuterRadius, 0.0);
	glRotatef(90,1,0,0.0);		
	glRotatef(-45,0,1,0.0);	
	gluCylinder(gluNewQuadric(), 0.02, 0.02, wheelOuterRadius*2, 15, 10);
	glPopMatrix();

	//rim
	glPushMatrix();
	glColor3f(.7,0.7,0.7);
	Material::setColor(0.7f,0.7f,0.7f);
	angle = 3*PI/4;
	glTranslatef (cos(angle)*wheelOuterRadius, sin(angle)*wheelOuterRadius, 0.0);
	glRotatef(90,1,0,0.0);		
	glRotatef(45,0,1,0.0);		
	gluCylinder(gluNewQuadric(), 0.02, 0.02, wheelOuterRadius*2, 15, 10);
	glPopMatrix();
	glPopMatrix();
	
}

void CarDrawer::drawFront(bool isHighbeam){
	double heightOfHandle = 1;

	glPushMatrix();
	glTranslatef(1.0, 0.0, 0);
	
	//draw axel that goes through the rims of the wheel
	glPushMatrix();
	glColor3f(.7,0.7,0.7);
	Material::setColor(0.7f,0.7f,0.7f);
	glTranslatef(0.0, 0.0, -0.1);
	gluCylinder(gluNewQuadric(), 0.02, 0.02, 0.2, 15, 10);
	glPopMatrix();

	//draw 1 shaft that connects to the handles
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.08);
	glColor3f(.7,0.7,0.7);
	Material::setColor(0.7f,0.7f,0.7f);
	glRotatef(-90,1,0.0,0.0);		
	glRotatef(-25,0,1,0.0);		
	gluCylinder(gluNewQuadric(), 0.02, 0.02, heightOfHandle, 15, 10);
	glPopMatrix();

	//draw another shaft that connects to the handles
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.08);
	glRotatef(-90,1,0.0,0.0);		
	glRotatef(-25,0,1,0.0);		
	gluCylinder(gluNewQuadric(), 0.02, 0.02, heightOfHandle, 15, 10);
	glPopMatrix();
	
	//draw the bar that will connect the two handles
	glPushMatrix();
	glColor3f(1,1,1);
	Material::setColor(1.0f,1.0f,1.0f);
	glTranslatef(sin(-5*PI/36), cos(-5*PI/36), -0.3);
	gluCylinder(gluNewQuadric(), 0.02, 0.02, 0.64, 15, 10);
	glPopMatrix();

	//draw the 1st handle bar
	glPushMatrix();
	glColor3f(.1,0.1,0.1);
	Material::setColor(0.1f,0.1f,0.1f);
	glTranslatef(sin(-5*PI/36), cos(-5*PI/36), -0.35);
	gluCylinder(gluNewQuadric(), 0.04, 0.04, 0.1, 15, 10);
	gluDisk(gluNewQuadric(), 0, 0.04, 15,10);
	glPopMatrix();

	//draw the 2nd handle bar
	glPushMatrix();
	glTranslatef(sin(-5*PI/36), cos(-5*PI/36), 0.3);
	gluCylinder(gluNewQuadric(), 0.04, 0.04, 0.1, 15, 10);
	gluDisk(gluNewQuadric(), 0, 0.04, 15,10);
	glPopMatrix();

	//draw front light
	glPushMatrix();


	glTranslatef(0.7*sin(-5*PI/36), 0.7*cos(-5*PI/36), -0.08);
	gluCylinder(gluNewQuadric(), 0.01, 0.01, 0.16, 15, 10);
	glTranslatef(0.0, 0.0, 0.08);
	glRotatef(90,0.0,1.0,0.0);
	
	glColor3f(1,1,1);
	Material::setColor(1.0f,1.0f,1.0f);
	Point color(1,1,1);
	Point start;
	Point dir(0,-1,2);
	Spotlight slight(light, start, dir, color); 
	if(isHighbeam)
	{
		slight.direction.y = -0.1;
		slight.angle = 35;
		slight.exp = 10;
	}
	slight.draw();
	gluCylinder(gluNewQuadric(), 0.0, 0.15, 0.15, 15, 10);
	glPopMatrix();

	glPopMatrix();


}
void CarDrawer::drawCore()
{
	double heightOfHandle = 2;
	glPushMatrix();
	glTranslatef(-1.0, 0.0, 0);

	//two bars going between the wheels to hold the core of the car
	glPushMatrix();
	glColor3f(.7,0.7,0.7);
	Material::setColor(0.7f,0.7f,0.7f);
	glTranslatef(0.0, 0.0, -0.08);
	glRotatef(90,0.0,1.0,0.0);		
	gluCylinder(gluNewQuadric(), 0.02, 0.02, heightOfHandle, 15, 10);
	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.08);
	glRotatef(90,0.0,1.0,0.0);		
	gluCylinder(gluNewQuadric(), 0.02, 0.02, heightOfHandle, 15, 10);
	glPopMatrix();

	glPopMatrix();

	//Engine
	glPushMatrix();
	glTranslatef(0.3,0.12,0.0);
	glColor3f(.6,0.6,0.6);
	Material::setColor(0.6f,0.6f,0.6f);

	glPushMatrix();
	glScalef(2,1,1.5);
	Material::setEngine();
	glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, Texture::getFuelId());
	/*
	if(isSolid){
		glutSolidCube(0.2);
	}
	else{
		glutWireCube(0.2);
	}
	*/
	solidCube(0.2f);
	
	glPopMatrix();

	glTranslatef(0.0,0.08,0.0);
	//Cylinder 1
	glColor3f(.1,0.1,0.1);
	Material::setColor(0.1f,0.1f,0.1f);
	glPushMatrix();
	glTranslatef(0.08,0.0,0.0);
	glRotatef(-90,1,0,0);
	glRotatef(25,0,1,0);
	gluCylinder(gluNewQuadric(), 0.08, 0.13, 0.25, 15, 10);
	glPopMatrix();

	//Cylinder 2
	glPushMatrix();
	glTranslatef(-0.08,0.0,0.0);
	glRotatef(-90,1,0,0);
	glRotatef(-25,0,1,0);
	gluCylinder(gluNewQuadric(), 0.08, 0.11, 0.25, 15, 10);
	glPopMatrix();

	glPopMatrix();

	//Gas Tank
	glPushMatrix();
	glColor3f(0,0,0.8);
	Material::setFuel();
	glTranslatef(0.1,0.62,0.0);
	glScalef(3,1,1);
	GLUquadric *qobj4 = gluNewQuadric(); 

	gluQuadricTexture(qobj4,GL_TRUE); 

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,Texture::getEngineId());

	gluSphere(qobj4,0.2,15,10); 

	gluDeleteQuadric(qobj4); 
	glDisable(GL_TEXTURE_2D);
	
	/*
	if(isSolid)
	{
		glutSolidSphere(0.2,15,10);
	}
	else
	{
		glutWireSphere(0.2,15,10);
	}
	*/
	glPopMatrix();

	//Seat
	glPushMatrix();
	glTranslatef(-0.3, 0.75,0.0);
	glRotatef(20,0,0,1);
	glScalef(1,0.1,1);
	Material::setSeat();
	GLUquadric *qobj = gluNewQuadric(); 

	gluQuadricTexture(qobj,GL_TRUE); 

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,Texture::getSeatId());

	gluSphere(qobj,0.3,15,10); 

	gluDeleteQuadric(qobj); 
	glDisable(GL_TEXTURE_2D);
	/*
	if(isSolid)
	{
		glutSolidSphere(0.3,15,10);
	}
	else
	{
		glutWireSphere(0.3,15,10);
	}
	*/
	glPopMatrix();

	//Seat extension
	glPushMatrix();
	glTranslatef(-0.4, 0.7,0.0);
	glScalef(1,0.1,1);
	Material::setSeat();
	GLUquadric *qobj1 = gluNewQuadric(); 
	gluQuadricTexture(qobj1,GL_TRUE); 

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,Texture::getSeatId());

	gluSphere(qobj1,0.3,15,10); 

	gluDeleteQuadric(qobj1); 
	glDisable(GL_TEXTURE_2D);
	/*
	if(isSolid)
	{
		glutSolidSphere(0.3,15,10);
	}
	else
	{
		glutWireSphere(0.3,15,10);
	}
	*/
	glPopMatrix();
	
	//two bars going from rear wheel to gas tank
	glPushMatrix();
	glColor3f(.7,0.7,0.7);
	Material::setColor(0.7f,0.7f,0.7f);
	glTranslatef(-1.0, 0.0, -0.08);
	glRotatef(90,0.0,1.0,0.0);		
	glRotatef(-35,1,0.0,0.0);	
	gluCylinder(gluNewQuadric(), 0.02, 0.02, 1.2, 15, 10);
	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(-1.0, 0.0, 0.08);
	glRotatef(90,0.0,1.0,0.0);
	glRotatef(-35,1,0.0,0.0);	
	gluCylinder(gluNewQuadric(), 0.02, 0.02, 1.2, 15, 10);
	glPopMatrix();
	
	//two bars going from front wheel to gas tank
	glPushMatrix();
	glTranslatef(1.0, 0.0, -0.08);
	glRotatef(-90,0.0,1.0,0.0);		
	glRotatef(-35,1,0.0,0.0);	
	gluCylinder(gluNewQuadric(), 0.02, 0.02, 1.2, 15, 10);
	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.08);
	glRotatef(-90,0.0,1.0,0.0);
	glRotatef(-35,1,0.0,0.0);	
	gluCylinder(gluNewQuadric(), 0.02, 0.02, 1.2, 15, 10);
	glPopMatrix();

	//Exaust
	GLUquadric *qobj3 = gluNewQuadric(); 
	gluQuadricTexture(qobj3,GL_TRUE); 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,Texture::getEngineId());

	glPushMatrix();
	glColor3f(.7,0.7,0.7);
	Material::setColor(0.7f,0.7f,.7f);
	glPushMatrix();
	glTranslatef(0.3, 0.12, 0.15);
	glRotatef(-90,0.0,1.0,0.0);
	gluCylinder(qobj3, 0.05, 0.05, 0.6, 15, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 0.12, -0.15);
	glRotatef(-90,0.0,1.0,0.0);
	gluCylinder(qobj3, 0.05, 0.05, 0.6, 15, 10);
	glPopMatrix();

	glColor3f(.6,0.6,0.6);	
	Material::setColor(.6f,.6f,.6f);
	//Exaust extension
	glPushMatrix();
	glTranslatef(-0.3, 0.12, 0.18);
	glRotatef(-90,0.0,1.0,0.0);			
	gluCylinder(qobj3, 0.08, 0.08, 0.6, 15, 10);
	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(-0.3, 0.12, -0.18);
	glRotatef(-90,0.0,1.0,0.0);
	gluCylinder(qobj3, 0.08, 0.08, 0.6, 15, 10);
	glPopMatrix();

	glPopMatrix();
	gluDeleteQuadric(qobj3); 
	glDisable(GL_TEXTURE_2D);
}

void CarDrawer::drawTrailerHitch()
{
	glPushMatrix();
	glTranslatef(-1.0,0.0 ,0.0);
	glColor3f(.1,0.1,0.1);
	Material::setColor(0.1f,0.1f,0.1f);
	//Trailer Hitch
	glPushMatrix();

	//two bars going from rear wheel to hold the trailer hitch
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.08);
	glRotatef(-90,0.0,1.0,0.0);		
	gluCylinder(gluNewQuadric(), 0.02, 0.02, 0.5, 15, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.08);
	glRotatef(-90,0.0,1.0,0.0);		
	gluCylinder(gluNewQuadric(), 0.02, 0.02, 0.5, 15, 10);
	glPopMatrix();

	//bars to hold the trailer hitch
	glTranslatef(-0.5, 0.0, -0.08);	
	glPushMatrix();
	gluCylinder(gluNewQuadric(), 0.02, 0.02, 0.16, 15, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.08);
	glRotatef(-90,1.0,0.0,0.0);		
	gluCylinder(gluNewQuadric(), 0.02, 0.04, 0.05, 15, 10);
	glPopMatrix();


	glPopMatrix();

	glPopMatrix();
}
void CarDrawer::drawTrailer()
{
	Material::setColor(0.0f,0.0f, 0.8f);
	glPushMatrix();
	glTranslatef(-1.5,0.05,0.0);
	glColor3f(.8,0.8,0.8);
	Material::setColor(0.8f,0.8f,0.8f);
	//two bars that go from the trailer hitch to the trailer
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.04);
	glRotatef(-90,0.0,1.0,0.0);		
	gluCylinder(gluNewQuadric(), 0.02, 0.02, 0.5, 15, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.04);
	glRotatef(-90,0.0,1.0,0.0);		
	gluCylinder(gluNewQuadric(), 0.02, 0.02, 0.5, 15, 10);
	glPopMatrix();
	
	//the trailer
	glColor3f(0,0,0.7);
	Material::setColor(0.0f,0.0f,0.7f);
	glTranslatef(-1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(1,0.5,1);
	if(isSolid){	
	glutSolidCube(1.0);
	}
	else{
	glutWireCube(1.0);
	}
	glPopMatrix();
	direction = 0;
	if((position->getX()- prevPosition)!=0){
		direction = (position->getX()- prevPosition)/abs(position->getX()- prevPosition);
	}
	glRotatef(currentWheelRotation*-90, 0,0,1);
	drawWheel(0,0,0.57);
	drawWheel(0,0,-0.57);
	glPopMatrix();
}
void CarDrawer::draw(bool isHighbeam)
{	

	glPushMatrix();
	glTranslatef(position->getX(), position->getY(), position->getZ());
	glRotatef(rotationAngle->x,1,0,0);
	glRotatef(rotationAngle->y,0,1,0);
	glRotatef(rotationAngle->z,0,0,1);
	glTranslatef(1, -0.2, 0);
	glPushMatrix();
	glPopMatrix();
	//glRotatef(-10,0,1,0);
	glPushMatrix();
		glTranslatef(1.0f, 0.0f, 0.0f);

		currentWheelRotation += *velocity;
		direction = 0;
		if((position->getX()- prevPosition)!=0){
			direction = (position->getX()- prevPosition)/abs(position->getX()- prevPosition);
		}
		glRotatef(currentWheelRotation*-90, 0,0,1);
		drawWheel(0.0f,0.0f,0.0f);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.0f, 0.0f, 0.0f);
		glRotatef(currentWheelRotation*-90, 0,0,1);
		drawWheel(0.0f,0.0f,0.0f);
	glPopMatrix();
	drawFront(isHighbeam);
	drawCore();
	drawTrailerHitch();
	drawTrailer();
			
	glPopMatrix();
	prevPosition = position->getX();
}
