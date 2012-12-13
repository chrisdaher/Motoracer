#ifndef wall_class
#define wall_class
#include "Point.h"

class Wall{
public:
	Point start;
	Point end;
	Wall(Point s, Point e);
	void Draw();
	bool checkCollision(Point point);
};
#endif