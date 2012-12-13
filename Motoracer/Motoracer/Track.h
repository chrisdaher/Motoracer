#ifndef track_class
#define track_class
#include<vector>
#include"Point.h"
#include"Road.h"
using namespace std;
class Track{
private:
	 vector<Road> roads;
public:
	Track();
	void addRoad(Road road);
	void DrawTrack();
};
#endif
