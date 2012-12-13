#ifndef road_class
#define road_class
#include "Point.h"
class Road{
private:
	Point start;
	Point end;
	float width;
	float length;
	float rotX;
	float rotY;
	float rotZ;
public:
	Road();
	Road(Point s, Point e);
	Road(const Road& r);
	void Draw();
	void setRotations(float x, float y, float z);
	float turn;
};
#endif