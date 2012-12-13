#include <iostream>
#include "camera.h"
#include "math.h"
#include "Spotlight.h"
Camera::Camera()
{
	Position = new Point(0.0, 0.0, 0.0);
	Direction = new Point(0.0, 0.0, -1.0);
	Angle = new Point(0.0, 0.0, 0.0);
	ViewDirChanged = false;
}

void Camera::GetViewDir( void )
{
	Point Step1, Step2;
	//Rotate around Y-axis:
	Step1.x = cos( (Angle->y + 90.0) * PIdiv180);
	Step1.z = -sin( (Angle->y + 90.0) * PIdiv180);
	//Rotate around X-axis:
	double cosX = cos (Angle->x * PIdiv180);
	Step2.x = Step1.x * cosX;
	Step2.z = Step1.z * cosX;
	Step2.y = sin(Angle->x * PIdiv180);
	//Rotation around Z-axis not yet implemented, so:
	*Direction = Step2;
}
void Camera::Move (Point Direction)
{
	*Position=*Position + Direction;
}

void Camera::RotateY (float angle)
{
	Angle->y += angle;
	ViewDirChanged = true;
}

void Camera::RotateX (float angle)
{
	Angle->x += angle;
	ViewDirChanged = true;
}

void Camera::Render( void )
{
	glRotatef(-Angle->x , 1.0, 0.0, 0.0);
	glRotatef(-Angle->y+90 , 0.0, 1.0, 0.0);
	glRotatef(-Angle->z , 0.0, 0.0, 1.0);
	glTranslatef( -Position->x, -Position->y-1, -Position->z );
}

void Camera::MoveForwards( float Distance )
{
	if (ViewDirChanged) GetViewDir();
	Point MoveVector;
	MoveVector.x = Direction->x * -Distance;
	MoveVector.y = Direction->y * -Distance;
	MoveVector.z = Direction->z * -Distance;
	*Position = *Position + MoveVector;
}

void Camera::StrafeRight ( float Distance )
{
	if (ViewDirChanged) GetViewDir();
	Point MoveVector;
	MoveVector.z = -Direction->x * -Distance;
	MoveVector.y = 0.0;
	MoveVector.x = Direction->z * -Distance;
	*Position = (*Position) + MoveVector;
}
float toRads(float degrees){
	float radians;
	radians = degrees * 3.1415926/ 180;
	return radians;
}

Point Camera::getPosition(){
	Point p;
	p.x = Position->x;
	p.y = Position->y;
	p.z = Position->z ;
	return p;
}
void Camera::AttachTo(Point& p, Point& d, Point& a){	
	Position = &p;
	Direction = &d;
	Angle = &a;
}
void Camera::Detach(){
	Position = new Point(*Position);
	Direction = new Point(*Direction);
	Angle = new Point(*Angle);
}