#include <iostream>
#include <GL/glut.h>   
#include <math.h>
#include"Track.h"
#include"Material.h"
using namespace std;

Track::Track() : roads(vector<Road>()){}
void Track::addRoad(Road road){
	roads.push_back(road);
}
void Track::DrawTrack(){
	glPushMatrix();
	glColor3f(1,1,1);
	Material::setColor(0.1,0.1,0.1);
	for(int i=0; i<roads.size(); i++){
		roads[i].Draw();
	}
	glPopMatrix();
}

