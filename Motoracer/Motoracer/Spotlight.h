#include <GL/glut.h>   
#include <math.h>
#include "Point.h"
class Spotlight{
private:
	void spotLight();
public:
	Spotlight(GLenum l,Point c);
	Spotlight(GLenum l, Point pos, Point dir, Point c);
	Point position;
	Point direction;
	Point color;
	float angle;
	float exp;
	GLenum light;
	void draw();
};