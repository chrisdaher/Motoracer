#ifndef collectable_class
#define collectable_class
#include "Point.h"
#include <GL/glut.h>

class Collectable{
public:
	enum Effect{
		SpeedUp,
		SlowDown,
		Flip,
		None
	};
	static float rot;
	Point position;
	Effect apply;
	int duration;
	Collectable(Point p, Collectable::Effect e= Collectable::None);
	Collectable(Collectable* c);
	void Draw();
	bool operator==(const Collectable& lhs);
	bool checkColliding(Point p);
	
};
#endif
