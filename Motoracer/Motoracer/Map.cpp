#include <algorithm>
#include "Map.h"
#include "TrackBuilder.h"
#include "Texture.h"
#include "Material.h"
#include <GL/glut.h>
int Map::laps=4;
int Map::currentTime = 0;
int prevTime=0;
vector<Point> toReplace;
using namespace std;

void drawBox2(GLfloat size, GLenum type)
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

void solidCube2(GLdouble size)
{
  drawBox2(size, GL_QUADS);
}


vector<Point> getCollectablePositions(){
	vector<Point> positions;
	positions.push_back(Point(20,0,-2));
	positions.push_back(Point(40,0,2));

	positions.push_back(Point(90,0,-40));

	positions.push_back(Point(100,0,-100));

	positions.push_back(Point(255,0,0));

	positions.push_back(Point(100,0,165));
	return positions;
}
Map::Map(){
	TrackBuilder tb;
	track = tb.buildTrack();
	tb.buildCollectables(getCollectablePositions());
	walls = tb.buildWalls();
	collectables = tb.collectables;
	player1.bike->position = Point(5,0,-2);
	player1.bike->carDrawer.light = GL_LIGHT1;
	player2.bike->position = Point(5,0,2);
	player2.bike->carDrawer.light = GL_LIGHT2;
	Lappos.x = -0;
	Lappos.y = -0.4;
	Lappos.z = 0;
}

void Map::reset(){
	TrackBuilder tb;
	track = tb.buildTrack();
	tb.buildCollectables(getCollectablePositions());
	walls = tb.buildWalls();
	collectables = tb.collectables;
	player1.bike->position = Point(0,0,-2);
	player1.bike->carDrawer.light = GL_LIGHT1;
	player1.bike->reset();
	player2.bike->position = Point(0,0,2);
	player2.bike->carDrawer.light = GL_LIGHT2;
	player2.bike->reset();
	Lappos.x = -0;
	Lappos.y = -0.4;
	Lappos.z = 0;
}
void Map::idle(){
	int cTime = glutGet(GLUT_ELAPSED_TIME);
  
  //  Calculate time passed
  int timeInterval = cTime - prevTime;
  
  if(timeInterval > 1000)
  {
	  currentTime++;
		player1.collectableTimeLeft--;
		player2.collectableTimeLeft--;
		if( (player1.collectableTimeLeft== 1 || player2.collectableTimeLeft==1)){
			for(int i=0; i< toReplace.size(); i++){
				collectables.push_back(Collectable(toReplace[i]));
			}
		}
		toReplace.clear();
	  prevTime = cTime;
  }
	list<Collectable> toRemove;
	for(list<Collectable>::iterator i= collectables.begin(); i != collectables.end();i++){
		if(i->checkColliding(player1.bike->position)){
			player1.doEffect((*i));
			toRemove.push_back(*i);
		}
		else if(i->checkColliding(player2.bike->position)){
			player2.doEffect((*i));
			toRemove.push_back(*i);
		}
	}
	for(list<Collectable>::iterator i= toRemove.begin(); i != toRemove.end();i++){
		collectables.remove(*i);
		toReplace.push_back(i->position);
	}
	player1.bike->move();
	player2.bike->move();
	checkLapping();
	for(list<Wall>::iterator i= walls.begin(); i != walls.end();i++){
		if(i->checkCollision(player1.bike->position)){
			if(player1.bike->velocity > 0){
				player1.bike->velocity = -player1.bike->velocity/2;//.1;
				player1.bike->moveBackward(1);
			}
			else{
				player1.bike->velocity = abs(player1.bike->velocity)/2;
				player1.bike->moveForward(1);
			}
		}
		if(i->checkCollision(player2.bike->position)){
			if(player2.bike->velocity >0){
				player2.bike->velocity = -player2.bike->velocity/2;//.1;
				player2.bike->moveBackward(1);
			}
			else{
				player2.bike->velocity = abs(player2.bike->velocity)/2;
				player2.bike->moveForward(1);
			}
		}
	}
}

void Map::handleKeyboard(unsigned char key, bool keyUp){
	switch(key){
		case 'r':
			reset();
			break;
		default:
			player1.handleKeyboard(key, keyUp);
			player2.handleKeyboard(key, keyUp);
			break;
	}

}

void Map::handleSpecial(int key, bool keyUp){
	player1.handleSpecial(key, keyUp);
	player2.handleSpecial(key, keyUp);
}

void Map::Draw(){
	
	track.DrawTrack();
	displayMap();
	for(list<Collectable>::iterator i= collectables.begin(); i != collectables.end();i++){
		i->Draw();
	}
	
	for(list<Wall>::iterator i= walls.begin(); i != walls.end();i++){
		i->Draw();
	}
	
	player1.draw();
	player2.draw();
	
}

void Map::renderPlayer1(){
	player1.renderView();
}

void Map::renderPlayer2(){
	player2.renderView();
}

void Map::displayMap(){
	glPushMatrix();
		Material::setColor(0.1f,0.6f,0.1f);
		//glColor3f(0,1,0);
		glTranslatef(0, -5, 0);
		glRotatef(90, 1,0,0);
	/*
		glEnable(GL_TEXTURE_2D);
		//glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		//glEnable(GL_TEXTURE_GEN_T);
		int id = Texture::getEngineId();
		glBindTexture(GL_TEXTURE_2D,id);

		glTranslatef(80, -5, 20);
		glScalef(1000,0.1,1000);
		solidCube2(1);
		//glutSolidCube(1);
		//glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		//glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_2D);
		*/
		//glRectf(1000,1000, -1000, -1000);
		//glEnable(GL_TEXTURE_2D);
		//glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		//glEnable(GL_TEXTURE_GEN_T);
		//int id = Texture::getEngineId();
		//glBindTexture(GL_TEXTURE_2D,id);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);
			glVertex2f(-1000,-1000);
			glTexCoord2f(0,1);
			glVertex2f(1000,-1000);
			glTexCoord2f(1,1);
			glVertex2f(1000,1000);
			glTexCoord2f(1,0);
			glVertex2f(-1000,1000);
		}
		glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		glDisable(GL_TEXTURE_GEN_T);
	glPopMatrix();
	glPushMatrix();
		glScalef(0,0,0);
		glutSolidCube(0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1,-0.6,0);
	Material::setColor(0.8,0.8,0.8);
		glScalef(1,0.2,18);
		glutSolidCube(1);
	glPopMatrix();
}

void Map::checkLapping(){
	if(player1.checkLapping(Lappos)){
		if(!player2.isDone){
			player1.isWinner = true;
		}
		if(!player1.isDone){
			player1.finishTime = currentTime;
		}
		player1.isDone = true;
		player1.bike->noTurn();
		player1.bike->decelerate();
		
	}
	if(player2.checkLapping(Lappos)){
		if(!player1.isDone){
			player2.isWinner = true;
		}
		if(!player2.isDone){
			player2.finishTime = currentTime;
		}
		player2.isDone = true;
		player2.bike->noTurn();
		player2.bike->decelerate();
		
	}
}
