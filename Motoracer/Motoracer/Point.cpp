#include "Point.h"
Point::Point(){
	x=0;
	y=0;
	z=0;
}
Point::Point(float X, float Y, float Z){
	x = X;
	y = Y;
	z = Z;
}

Point::Point(const Point& p){
	x = p.getX();
	y = p.getY();
	z = p.getZ();
}

const float Point::getX() const{
	return x;
}

const float Point::getY() const{
	return y;
}

const float Point::getZ() const{
	return z;
}
void Point::setX(float X){
	x = X;
}

void Point::setY(float Y){
	y = Y;
}

void Point::setZ(float Z){
	z = Z;
}
Point Point::operator+ (Point p){
	Point temp;
	temp.x = this->x + p.x;
	temp.y = this->y + p.y;
	temp.z = this->z + p.z;
	return temp;
}

bool Point::operator== (Point p){
		return (this->x == p.x &&	this->y == p.y	&& this->z == p.z);
}