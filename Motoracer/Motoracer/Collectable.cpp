#include <stdlib.h>
#include <time.h>
#include "Collectable.h"
#include "Texture.h"
#include "Material.h"
bool isSet=false;
float Collectable::rot =0;
Collectable::Collectable(Point p, Collectable::Effect e){
	position = p;
	if(!isSet){
		isSet = true;
		srand ( time(NULL) );
	}
	if(e=Collectable::None){
		int rando = rand();
		apply = (Effect) (rando % 3);
	}
	else{
		apply = e;
	}
	switch(apply){
	case Collectable::Flip:
		duration = 2;
		break;
	case Collectable::SpeedUp:
		duration = 2;
		break;
	case Collectable::SlowDown:
		duration = 2;
		break;
	default:
		duration =0;
		break;
	}
}

Collectable::Collectable(Collectable* c){
	position = c->position;
	apply = c->apply;
	duration = c->duration;
}

void Collectable::Draw(){
	float color[3] = {0.0, 0.0, 0.0};
		switch(apply){
			case Collectable::Flip:
				color[0]=1.0;
				break;
			case Collectable::SpeedUp:
				color[1]=1.0;
				break;
			case Collectable::SlowDown:
				color[2]=1.0;
				break;
			}
	
	glPushMatrix();
		glTranslatef(position.x, 1, position.z);
		rot+=1;
		glRotatef(rot, 0, 1,0);
		Material::setColor(color[0], color[1], color[2]);
		GLUquadric *qobj = gluNewQuadric(); 

		gluQuadricTexture(qobj,GL_TRUE); 

		glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D,Texture::getSeatId());
		
		gluSphere(qobj,1,15,10); 

		gluDeleteQuadric(qobj); 
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

bool Collectable::checkColliding(Point p){
	if(p.x > position.x-1  && p.x < position.x+1 &&
		p.z > position.z-1  && p.z < position.z+1)
	{
		return true;
	}
	return false;
}

bool Collectable::operator==(const Collectable& lhs){
	return (this->position == lhs.position);
}
