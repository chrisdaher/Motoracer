#include "Point.h"
#include "Spotlight.h"
class CarDrawer{
	private:
		Point* position;
		Point* rotationAngle;
		void drawWheel(double x, double y, double z);
		void drawFront(bool isHighbeam);
		void drawCore();
		void drawTrailerHitch();
		void drawTrailer();
	public:
		static bool isHighbeam;
		float currentWheelRotation;
		GLenum light;
		float* velocity;
		static int rot;
		CarDrawer();
		CarDrawer(Point& p, Point& angle, float* v);
		//setParams(const Point& p, const Point& rA, const float& angle);
		void draw(bool isHighbeam);
};
