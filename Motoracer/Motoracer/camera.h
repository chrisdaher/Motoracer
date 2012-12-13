#ifndef camera_class
#define camera_class
#include <gl/glut.h> 		// Need to include it here because the GL* types are required
#include "Point.h"
#define PI 3.1415265359
#define PIdiv180 3.1415265359/180.0

class Camera
{
private:
	Point direction;	
	void GetViewDir ( void );
public:
	Point* Position;
	Point* Direction;		
	Point* Angle;
	bool ViewDirChanged;
	Camera();
	void Render ( void );
	void Move ( Point Direction );
	void RotateX ( float Angle );
	void RotateY ( float Angle );
	void RotateZ ( float Angle );
	void MoveForwards ( GLfloat Distance );
	void StrafeRight ( GLfloat Distance );
	void RotateAroundY(float Distance);
	void AttachTo(Point& p, Point& d, Point& a);
	void Detach();
	Point getPosition();
};
#endif