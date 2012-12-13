#include "Wall.h"
#include "Material.h"
#include "Texture.h"
#include <GL\glut.h>
void drawBox1(GLfloat size, GLenum type)
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

  glTexCoord2f(1.0f, 0.0f);
  glVertex3fv(&v[faces[i][0]][0]);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3fv(&v[faces[i][1]][0]);

  glTexCoord2f(0.0f, 1.0f);
  glVertex3fv(&v[faces[i][2]][0]);

  glTexCoord2f(1.0f, 1.0f);
  glVertex3fv(&v[faces[i][3]][0]);
  glEnd();
  }
}

void solidCube1(GLdouble size)
{
  drawBox1(size, GL_QUADS);
}

Wall::Wall(Point s, Point e){
	start = s;
	end =e;
}

void Wall::Draw(){
	glPushMatrix();
		Material::setColor(0.5, 0.5, 0.5);
		glTranslatef((end.x + start.x)/2, start.y, (end.z + start.z)/2);
		glScalef(end.x-start.x, 1 ,end.z-start.z);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		glEnable(GL_TEXTURE_GEN_T);
		glBindTexture(GL_TEXTURE_2D,Texture::getEngineId());
		solidCube1(1);
		//glutSolidCube(1);
		glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_2D);


		/*
		glTranslatef((end.x + start.x)/2, start.y, (end.z + start.z)/2);
		glScalef(end.x-start.x, 1 ,end.z-start.z);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, Texture::getWallId());
		//solidCube1(1);
		//glutSolidCube(1);
		*/
	glPopMatrix();
}

bool Wall::checkCollision(Point point){
	if(point.x +1> start.x && point.x -1< end.x &&
		point.z +1> start.z && point.z-1 < end.z){
			return true;
	}
	return false;
}