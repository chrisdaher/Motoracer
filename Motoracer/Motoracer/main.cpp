
#include <string>
#include <cstdio>
#include <sstream>
#include <stdarg.h>
#include <GL/glut.h>   
#include <math.h>
#include "Map.h"
#include "Texture.h"

//bool isSolid=true;
bool isOrtho=false;
static float angleOfView = 40;
static int currentW;
static int currentH;
bool isMenu = true;
bool isControl = false;
int currMenu = 0;
//void glDisplayLines(void);  

// Initiliaze the OpenGL window

bool LightEnabled;
float TorusRotated = 0.0;

bool isWire = false;

int frameCount;
int previousTime;
float fpsCntr;
Map map;
bool enableLight;
float counter =0;
//static GLfloat MatSpec[] = {1.0,1.0,1.0,1.0};
//static GLfloat MatShininess[] = {45.0};
static GLfloat LightPos[] = {1.0,5.0,1.0,0.0};

	GLfloat mat_emission[] = {1.0, 1.0, 0.0, 1.0};
	GLfloat no_mat[] = {0, 0, 0, 0};
	//GLfloat light_pos[4] = {0.0, 0.0, 0.0, 1.0};
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	//GLfloat light_position[] = { 0.0, 0.2, 0.2, 1.0 };
	GLfloat white_light[] = { .8, .8, 0.8, 0.5 };
	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

	static GLfloat rightspotlightpos[] = {1.0f,1.0f,1.0f,1.0f};


void SetupLighting()
{
   GLfloat ambientLight[]={0.1,0.1,0.1,1.0};    	             // set ambient light parameters
   glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);

   GLfloat diffuseLight[]={0.8,0.8,0.8,1.0};    	             // set diffuse light parameters
   glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);

   GLfloat specularLight[]={0.5,0.5,0.5,1.0};  	               // set specular light parameters
   glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight);

   GLfloat lightPos[]={0.0,30.0,60.0,0.0};      	              // set light position
   glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

   GLfloat specularReflection[]={1.0,1.0,1.0,1.0};  	          // set specularity
   glMaterialfv(GL_FRONT, GL_SPECULAR, specularReflection);
   glMateriali(GL_FRONT,GL_SHININESS,128);

   glEnable(GL_LIGHT0);                         	              // activate light0
   glEnable(GL_LIGHTING);                       	              // enable lighting
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight); 	     // set light model
   glEnable(GL_COLOR_MATERIAL);                 	              // activate material
   glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_NORMALIZE);                      	              // normalize normal vectors
}

void drawstrMenu(float x, float y, char* format, bool focused, ...)
{
	  va_list args;
  char buffer[255], *s;
  
  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);
  GLvoid *font_style = (focused) ?  GLUT_BITMAP_TIMES_ROMAN_24 : GLUT_BITMAP_HELVETICA_12;
  glRasterPos2f(x, y);
  for (s = buffer; *s; s++)
    glutBitmapCharacter(font_style, *s);
}

void drawstr(float x, float y, char* format, ...)
{
  va_list args;
  char buffer[255], *s;
  
  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);
  GLvoid *font_style =  	GLUT_BITMAP_HELVETICA_12;
  glRasterPos2f(x, y);
  for (s = buffer; *s; s++)
    glutBitmapCharacter(font_style, *s);
}

void drawstrold(float x, float y, char* format, ...)
{
  va_list args;
  char buffer[255], *s;
  
  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);
  GLvoid *font_style = GLUT_BITMAP_HELVETICA_12;
  glRasterPos2i(x, y);
  for (s = buffer; *s; s++)
    glutBitmapCharacter(font_style, *s);
}

void setFps()
{
  //  Increase frame count
  frameCount++;
  
  //  Get the number of milliseconds since glutInit called
  //  (or first call to glutGet(GLUT ELAPSED TIME)).
  int currentTime = glutGet(GLUT_ELAPSED_TIME);
  
  //  Calculate time passed
  int timeInterval = currentTime - previousTime;
  
  if(timeInterval > 1000)
  {
    //  calculate the number of frames per second
    fpsCntr = frameCount / (timeInterval / 1000.0f);
    
    //  Set time
    previousTime = currentTime;
    
    //  Reset frame count
    frameCount = 0;
  }
}

float toRadians(float degrees){
	float radians;
	radians = degrees * 3.1415926/ 180;
	return radians;
}

  GLuint loadTexture(char * filename, int width, int height)
  {
    GLuint texture;
    unsigned char * data;
    FILE * file;
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );
    glGenTextures(1, &texture );            
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);
    return texture;
  
  }
  

void init(void)
{
	glEnable (GL_LINE_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(-4.0f, 4.0f);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	//glEnable(GL_LIGHT3);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lmodel_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lmodel_ambient);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lmodel_ambient);
	LightEnabled=true;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);
	glutGameModeString("990x768:32@75");
	SetupLighting();
  
  Texture::setEngineId(loadTexture("textures/engine22.raw", 256, 256));
  Texture::setSeatId(loadTexture("textures/seat.raw", 256, 256));
  Texture::setFuelId(loadTexture("textures/fuel.raw", 256, 256));
  Texture::setRoadId(loadTexture("textures/road.raw", 256, 256));
	Texture::setSkyId(loadTexture("textures/sky.raw", 256, 256));
	Texture::setGrassId(loadTexture("textures/grass.raw", 256, 256));
	Texture::setWallId(loadTexture("textures/wall1.raw", 256, 256));
  
}

void display1(void)
{	
	//gluLookAt (eyeX,eyeY, eyeZ, atX, atY, atZ, 0.0, 10, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//spot(b->position.x,b->position.y+0.5,b->position.z,b->position.x+0.1,b->position.y,b->position.z);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0,0.75,1,1);
	glLoadIdentity();
	map.renderPlayer1();
	//glPushMatrix();
		//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
		//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		//glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		map.Draw();

	//glPopMatrix();
	
	glDisable(GL_LINE_STIPPLE);				
	glFlush(); 
	glutSwapBuffers();
	
}

void display2(void)
{	
	//gluLookAt (eyeX,eyeY, eyeZ, atX, atY, atZ, 0.0, 10, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//spot(b->position.x,b->position.y+0.5,b->position.z,b->position.x+0.1,b->position.y,b->position.z);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(1,1,1,1);
	glLoadIdentity();
	map.renderPlayer1();
	glPushMatrix();
		//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
		//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		//glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		map.Draw();

	glPopMatrix();
	glClearColor(1,1,1,1);
	glDisable(GL_LINE_STIPPLE);				
	glFlush(); 
	glutSwapBuffers();
	
}

void idleFunc()
{
	if(!isMenu){
		map.idle();
	}
	glutPostRedisplay();
  //  setFps();
}

void reshape (int x, int y)
{
	
	if (y == 0 || x == 0) return;
	glViewport(0,0,x,y); 
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	gluPerspective(angleOfView,(GLdouble)x/(GLdouble)y,0.001,100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int height;
int width;
void drawMenu()
{
	glClearColor(0.0,0.8,1,1);
	
	if (!isControl){
		glColor3f(0,0,0);
		drawstrMenu(1,0, "Start Game",  currMenu == 0);
		glColor3f(0,0,0);
		drawstrMenu(1.0f, -0.2f, "Controls", currMenu == 1);
		glColor3f(0,0,0);
		drawstrMenu(1, -0.4f, "Exit", currMenu == 2);
	}
	else
	{
		glColor3f(0,0,0);
		drawstrMenu(0.3f,0, "Player 1",  false);
		drawstrMenu(0.3f,-0.2f, "Movement: UP, DOWN, LEFT, RIGHT",  false);
		drawstrMenu(0.3f,-0.4f, "Highbeam toggle: ]",  false);
		glColor3f(0,0,0);
		drawstrMenu(1.0f, 0.0f, "Player 2", false);
		drawstrMenu(1.0f, -0.2f, "Movement: A, S, D, W", false);
		drawstrMenu(1.0f, -0.4f, "Highbeam toggle: Q", false);
		drawstrMenu(0.6f, -0.6f, "Reset Game: r", false);
		glColor3f(0,0,0);
		drawstrMenu(0.6f, -0.8f, "Return to main menu: BACKSPACE", false);
	}
}
    void resize(int w, int h){
         width=w;
         height=h;
    }

    void draw(void){
		if (!isMenu)
		{
			glClearColor(0,0.75,1,1);
         glEnable(GL_SCISSOR_TEST);
         /*
          * LEFT VIEW PORT
          */
         glMatrixMode(GL_PROJECTION);
         glLoadIdentity();
         glViewport(0, 0, (float)width , height/2);
         gluPerspective(45, ((float)width)/((float)height/2), 1, 2000);
         glMatrixMode(GL_MODELVIEW);
         glScissor(0, 0, (float)width , height/2);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_COLOR_MATERIAL);
		 glClearColor(0,0.75,1,1);
         glLoadIdentity();
				 map.renderPlayer2();
				 map.Draw();
			glClearColor(0,0.75,1,1);
				 	glDisable(GL_LINE_STIPPLE);		
         /*
          * THE SECOND VIEW PORT
          */
         glMatrixMode(GL_PROJECTION);
         glLoadIdentity();
         glViewport(0, (float)height/2, width , height/2);
         gluPerspective(45, ((float)width)/((float)height/2), 1, 2000);
         glMatrixMode(GL_MODELVIEW);
         glScissor(0, ((float)height/2), width , height/2);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		 glClearColor(0,0.75,1,1);
         glLoadIdentity();

				 map.renderPlayer1();
				 map.Draw();

         glDisable(GL_SCISSOR_TEST);
		}
		else{
			glPushMatrix();
			{
				glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				drawMenu();
			}
			glPopMatrix();
		}
         glFlush();
         glutSwapBuffers();
    }


void keyboard (unsigned char key, int x, int y)
{
	if (!isMenu){
	switch(key){
		case 27:
			exit(0);
			break;
		default:
			map.handleKeyboard(key);
			break;
	}
	glutPostRedisplay();
	}
	else if (!isControl){
		if (key == 13)
		{
			if (currMenu == 0){
				isMenu = false;
				isControl = false;
			}
			else if (currMenu == 1) { //controls
				isControl = true;
			}
			else if (currMenu == 2)
			{
				exit(0);
			}
		}
		else if (key == 27)
		{
			exit(0);
		}
	}
	else if (isControl)
	{
		if (key == 8){
			isControl = false;
		}
	}
}

void specialKey(int key, int x, int y) { 
	if (!isMenu){
		glLoadIdentity();
		map.handleSpecial(key);
		glutPostRedisplay();
	}
	else
	{
		if (key == GLUT_KEY_UP && !isControl)
		{
			currMenu--;
			if (currMenu <0) currMenu = 0;
		}
		else if (key == GLUT_KEY_DOWN && !isControl)
		{
			currMenu++;
			if (currMenu > 2) currMenu = 2;
		}
		else if (key == 32 && !isControl)
		{
			isMenu = false;
		}
	}
}

void keyUp(unsigned char key, int x, int y) { 
  glLoadIdentity();
		map.handleKeyboard(key, true);
	glutPostRedisplay();
}

void SpecKeyUp(int key, int x, int y){
	if(key == GLUT_KEY_F1){
		LightEnabled = !LightEnabled;
		if(LightEnabled){
			glEnable(GL_LIGHT0);
		}
		else{
			glDisable(GL_LIGHT0);
		}
	}
	glLoadIdentity();
		map.handleSpecial(key, true);
	glutPostRedisplay();
}

void fps_display()
{
  return;
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1,1,1);
  glLoadIdentity();
  
  glPushMatrix();
  
  std::stringstream ss;
  ss << fpsCntr;
  std::string currFps = ss.str();
  drawstr(0,0, "FPS: %s", currFps.c_str());
  glPopMatrix();
  
  glutSwapBuffers();
  glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);	
	glutInitWindowSize (700,700);	
	GLuint parent = glutCreateWindow("Motoracer");	
	init ();
	glutDisplayFunc(draw);	
	glutReshapeFunc(resize);		
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKey);
	glutKeyboardUpFunc(keyUp);
	glutSpecialUpFunc(SpecKeyUp);
	glutIdleFunc(idleFunc);
	
  //	glutCreateSubWindow(parent, 0, 0, 700, 40);
  //  glutDisplayFunc(fps_display);
 
	

  glutMainLoop();
	return 0;
}
