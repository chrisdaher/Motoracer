#include <cstdio>
#include <stdarg.h>
#include <iostream>
#include <string>
#include "Player.h"
#include "Map.h"
#include <GL/glut.h>
#include <sstream>

using namespace std;
static int currentIndex = 0;
Player::Player(Point position, Point direction){
	initPlayer(position, direction);
	playerIndex = ++currentIndex;
	currentLap=0;
	bestLap=10000;
	lapTime=0;
	collectableTimeLeft = 0;
	isWinner = false;
}
Player::Player(){
	
  Point p1(0,0,0);
  Point p2(0,0,-1);
	initPlayer(p1, p2);
	bestLap=10000;
	playerIndex = ++currentIndex;
	currentLap=0;
	lapTime=0;
	collectableTimeLeft = 0;
	isWinner = false;
}
void Player::initPlayer(Point& position, Point& direction){
	bike = new Bike(position, direction, Point());
	camera = new Camera();
	camera->AttachTo(bike->position, bike->direction, bike->angle);
}

void Player::renderView(){
	if(isDone){
		camera->Detach();
	}
	camera->Render();
	DrawHud();
}


void Player::handleKeyboard(unsigned char key, bool keyUp){
	if(!isDone){
		if(playerIndex==1){
				switch (key) 
				{
					case ']':
						if(!keyUp)
						{
							bike->isHighbeam = !bike->isHighbeam;
						}
						break;
				}
		}

		if(playerIndex==2){
			switch(key){
				case 'a' :
					if(!keyUp){
						bike->turnLeft();
					}
					else{
						bike->noTurn();
					}
					break;
				case 'd' :	
					if(!keyUp){
						bike->turnRight();
					}
					else{
						bike->noTurn();
					}
					break;
				case 'w' :
					if(!keyUp){
						bike->accelerate();
					}
					else{
						bike->decelerate();
					}
					break;
				case 's' :
					if(!keyUp){
						bike->reverse();
					}
					else{
						bike->decelerate();
					}
					break;
				case 'q':
					if(!keyUp)
					{
						bike->isHighbeam = !bike->isHighbeam;
					}
					break;
				
			}
		}
	}
}

void Player::handleSpecial(int key, bool keyUp){
	if(!isDone){
		if(playerIndex==1){
			 switch(key) {
				case GLUT_KEY_LEFT : 
					if(!keyUp){
						bike->turnLeft();
					}
					else{
						bike->noTurn();
					}
					break;
				case GLUT_KEY_RIGHT :	
					if(!keyUp){
						bike->turnRight();
					}
					else{
						bike->noTurn();
					}
					break;
				case GLUT_KEY_UP :
					if(!keyUp){
						bike->accelerate();
					}
					else{
						bike->decelerate();
					}
					break;
				case GLUT_KEY_DOWN :
					if(!keyUp){
						bike->reverse();
					}
					else{
						bike->decelerate();
					}
					break;
			}
		}
	}
}

void drawstrply(float x, float y, char* format, ...)
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

void Player::draw(){
	if(currentCollectable!=NULL && collectableTimeLeft==0){
		undoEffect();
	}
	bike->drawBike();

}

void Player::DrawHud(){
	glPushMatrix();
 	glLoadIdentity();
	glTranslatef(0,0,-5);
  
  // FIXME
  std::stringstream ssSpeed;
  ssSpeed.precision(0);
  ssSpeed << (int)((bike->velocity)*(100));

  std::stringstream ssLap;
  ssLap << currentLap;
	ssLap << " / ";
	ssLap << Map::laps;


  std::stringstream ssTime;
  ssTime << Map::currentTime;

	std::stringstream currentLapTime;
	currentLapTime << lapTime;

	std::stringstream bestLapTime;
	
	if(bestLap==10000){
		bestLapTime << 0;
	}
	else{
		bestLapTime << bestLap;
	}

  std::stringstream collTime;
  std::stringstream collType;
  collTime.str("");
  if (currentCollectable && collectableTimeLeft != 0){
    collTime << collectableTimeLeft;
    switch (currentCollectable->apply){
    case Collectable::Flip:
      collType << "Flip!";
      break;
    case Collectable::SpeedUp:
      collType << "Speed Up!";
      break;
    case Collectable::SlowDown:
      collType << "Slow Down!";
      break;
    };
    
  }

	if(isDone){
		std::stringstream ssFinalTime;
		ssFinalTime << finishTime;
		drawstrply(0,1, "you have finished with a time of: %s", ssFinalTime.str().c_str());
	}

	if(isWinner){
		drawstrply(0,1.2, "You Won!!!");
	}
	
  drawstrply(-1.0f,1.8f, "%s km/h", ssSpeed.str().c_str());
  drawstrply(-0.0f, 1.8f, "Lap #%s", ssLap.str().c_str());
  drawstrply(1.0f, 1.8f, "%ss", ssTime.str().c_str());  

	drawstrply(-4,1.8f, "Total Lap Time: %s", currentLapTime.str().c_str());
	drawstrply(-4,1.4f, "Best Lap Time: %s", bestLapTime.str().c_str());
  if (!collTime.str().empty()){
    drawstrply(2.0f, 1.8f, "Effect: T-%s", collTime.str().c_str());  
    drawstrply(3.0f, 1.8f, "Type: %s", collType.str().c_str());  
  }
	glPopMatrix();
}

bool Player::checkLapping(Point lappos){
	if(!isDone){
		if( lappos.x + 5 > bike->position.x  && lappos.x - 5 < bike->position.x &&
			lappos.z + 5 > bike->position.z  && lappos.z - 5 < bike->position.z
			&& Map::currentTime> lapTime +10)
		{
			lapTime=Map::currentTime;
			if(lapTime<bestLap)
			{
				bestLap=lapTime;
			}
			currentLap++;
		}
	}
	return currentLap==Map::laps;
}

void Player::doEffect(Collectable c){
	currentCollectable = new Collectable(c);
	collectableTimeLeft = currentCollectable->duration;
	Collectable::Effect e = currentCollectable->apply;
	switch(e){
	case Collectable::SpeedUp:
			bike->speedLimit *=1.5;
			break;
	case Collectable::SlowDown:
			bike->speedLimit /=2;
			if(bike->velocity>=bike->speedLimit){
				bike->velocity=bike->speedLimit;
			}
			break;
		case Collectable::Flip:
			bike->flip(180);
			bike->velocity = -bike->velocity;
			break;
	}
}

void Player::undoEffect(){
	Collectable::Effect e = currentCollectable->apply;
	switch(e){
		case Collectable::SpeedUp:
			bike->speedLimit /=1.5;
			if(bike->velocity>=bike->speedLimit){
				bike->velocity=bike->speedLimit;
			}
			break;
		case Collectable::SlowDown:
			bike->speedLimit *=2;
			break;
		case Collectable::Flip:
			bike->flip(180);
			bike->velocity = -bike->velocity;
			break;
	}
	currentCollectable=NULL;
}
