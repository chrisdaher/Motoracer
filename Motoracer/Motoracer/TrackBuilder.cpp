#include "TrackBuilder.h"
int roadwidth=10;
int roadlength=20;
int turnConstant = 10;
TrackBuilder::TrackBuilder(){}
Track TrackBuilder::buildTrack(){
	Track track;
	Point start(-10, -0.4, -4);
	//first horizontal
	Point currentPoint(start);
	Point nextPoint(5*roadlength, -0.4, (currentPoint.z+roadwidth));
	Road* road= new Road(Point(currentPoint), Point(nextPoint));
	track.addRoad(Road(*road));

	nextPoint.x -= roadlength;

	//first vertical
	currentPoint.x = nextPoint.x + roadwidth;
	currentPoint.z -= roadwidth;
	nextPoint.x += currentPoint.x+roadlength;
	nextPoint.z-= roadwidth;
	road = new Road(Point(currentPoint), Point(nextPoint));
	road->setRotations(0,180,0);
	track.addRoad(Road(*road));

	nextPoint.x -= roadlength;

	//second horizontal
	currentPoint.z = start.z - (nextPoint.x- currentPoint.x) - 2*roadwidth;
	currentPoint.x += roadwidth;
	nextPoint.x += 5*roadlength;
	nextPoint.z = currentPoint.z + roadwidth;
	road = new Road(Point(currentPoint), Point(nextPoint));
	track.addRoad(Road(*road));

	nextPoint.x-=roadlength;

	//second vertical
	currentPoint.x = nextPoint.x + 1*roadwidth;
	currentPoint.z = nextPoint.z+ 1*roadwidth;
	nextPoint.x += currentPoint.x + roadlength;
	road = new Road(Point(currentPoint), Point(nextPoint));
	road->setRotations(0,0,0);
	track.addRoad(Road(*road));

	nextPoint.x-=roadlength;

	//long horizontal back to start
	float temp = nextPoint.x;
	nextPoint.x = currentPoint.x - roadwidth +roadlength;
	currentPoint.z += temp - currentPoint.x;
	currentPoint.x = start.x;
	nextPoint.z = currentPoint.z + roadwidth;	
	road = new Road(Point(currentPoint), Point(nextPoint));
	track.addRoad(Road(*road));
	nextPoint.x -= roadlength;

	//last vertical back to start
	nextPoint.x = currentPoint.z - start.z - 2*roadwidth;
	nextPoint.z = start.z + 2*roadwidth;
	currentPoint.x = start.x - roadwidth;
	currentPoint.z = start.z + roadwidth;
	road = new Road(Point(currentPoint), Point(nextPoint));
	road->setRotations(0,0,0);
	track.addRoad(Road(*road));


	currentPoint.x = start.x - 2*roadwidth;
	currentPoint.z = start.z + roadwidth;
	road = new Road(Point(currentPoint), Point(start));
	track.addRoad(Road(*road));
	
	return track;
}

list<Wall> TrackBuilder::buildWalls(){
	list<Wall> walls;
	walls.push_back(Wall(Point(-30,-0.5,-9.5), Point(80,0,-9)));
	walls.push_back(Wall(Point(-10,-0.5,11), Point(100,0,11.9)));

	walls.push_back(Wall(Point(80,-0.5,-109), Point(80.1,0,-9.5)));
	walls.push_back(Wall(Point(100,-0.5,-89), Point(100.1,0,11.9)));

	walls.push_back(Wall(Point(80,-0.5,-109.9), Point(270.1,0,-109)));
	walls.push_back(Wall(Point(100,-0.5,-89.9), Point(250.1,0,-89)));

	walls.push_back(Wall(Point(270,-0.5,-109.9), Point(270.5,0,180)));
	walls.push_back(Wall(Point(250,-0.5,-89), Point(250.5,0,161.9)));

	walls.push_back(Wall(Point(-30,-0.5,180), Point(270,0,180.9)));
	walls.push_back(Wall(Point(-10,-0.5,161), Point(250,0,161.9)));

	walls.push_back(Wall(Point(-30,-0.5,180), Point(270,0,180.9)));
	walls.push_back(Wall(Point(-10,-0.5,161), Point(250,0,161.9)));

	walls.push_back(Wall(Point(-30.1,-0.5,-9), Point(-30,0,180.9)));
	walls.push_back(Wall(Point(-10.1,-0.5,11), Point(-10,0,161)));
	return walls;
}



void TrackBuilder::buildCollectables(vector<Point> positions){
	for(int i=0; i< positions.size(); i++){
		Collectable* c = new Collectable(positions[i]);
		collectables.push_back(Collectable(*c));
	}
}