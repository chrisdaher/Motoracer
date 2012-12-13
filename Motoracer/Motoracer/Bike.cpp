#include "Bike.h"
#include "math.h"
#define PI 3.1415265359
#define PIdiv180 3.1415265359/180.0
#define turnRate 2.5;
	Bike::Bike(): position(0.0f, 0.0f, 0.0f),
								direction(0.0f, 0.0f, 0.0f),
								angle(0.0f, 0.0f, 0.0f),
								currDir(NONE),
								velocity(0),
								state(Motion::none),
								carDrawer(position, angle, &velocity){ViewDirChanged = false;isHighbeam = false;speedLimit=1;}
	
	Bike::Bike(Point p, Point rA, Point a) : position(p), 
																						currDir(NONE),
																						velocity(0),
																						direction(rA), 
																						angle(a), 
																						state(Motion::none),
																						carDrawer(position, angle, &velocity){ViewDirChanged = false; isHighbeam=false;speedLimit=1;}
	Bike::Bike(const Bike& bike): position(bike.position),
								  currDir(NONE),
									velocity(0),
								  direction(bike.direction),
								  angle(bike.angle),
									state(Motion::none),
								  carDrawer(position, angle, &velocity){ViewDirChanged = false; isHighbeam=false;speedLimit=1;}

	void Bike::reset(){
		isHighbeam=false;speedLimit=1;velocity=0;currDir=NONE; state= Motion::none; direction.x=0, direction.y=0, direction.z=0;angle.x=0;angle.y=0;angle.z=0;
	}
	void Bike::setCamera(Camera& c){
		camera = &c;
		camera->AttachTo(position, direction, angle);
	}
	const Point& Bike::getPosition() const
	{
		return position;
	}
	void Bike::setPosition(const Point& p)
	{
		position = p;
	}
	void Bike::setPosition(float X, float Y, float Z)
	{
		position = Point(X,Y,Z);
	}
	void Bike::drawBike()
	{
		carDrawer.draw(isHighbeam);
	}
	void Bike::strafeRight()
	{
		if (ViewDirChanged) GetViewDir();
		Point MoveVector;
		MoveVector.x = direction.x * -.1;
		MoveVector.y = direction.y * -.1;
		MoveVector.z = direction.z * -.1;
		position = position + MoveVector;
	}
	void Bike::strafeLeft()
	{
		if (ViewDirChanged) GetViewDir();
		Point MoveVector;
		MoveVector.x = direction.x * +.1;
		MoveVector.y = direction.y * +.1;
		MoveVector.z = direction.z * +.1;
		position = position + MoveVector;
	}
	void Bike::turnRight()
	{
		currDir = DIR::RIGHT;
		//rotationAxis.y = 1;
		//angle.y -= 10;
	}
	void Bike::turnR(){
		angle.y -= turnRate;
		ViewDirChanged = true;
	}
	void Bike::turnLeft()
	{
		currDir = DIR::LEFT;
		//rotationAxis.y = 1;
		//angle.y += 10;
	}
	void Bike::turnL(){
		angle.y += turnRate;
		ViewDirChanged = true;
	}
		void Bike::flip(float a){
		angle.y += a;
		ViewDirChanged = true;
	}
	void Bike::noTurn(){
		currDir = DIR::NONE;
	}
	void Bike::moveForward ( float Distance )
	{
		if (ViewDirChanged) GetViewDir();
		Point MoveVector;
		MoveVector.z = -direction.x * -Distance;
		MoveVector.y = 0.0;
		MoveVector.x = direction.z * -Distance;
				position = position + MoveVector;
	}

	void Bike::moveBackward ( float Distance )
	{
		if (ViewDirChanged) GetViewDir();
		Point MoveVector;
		MoveVector.z = -direction.x * +Distance;
		MoveVector.y = 0.0;
		MoveVector.x = direction.z * +Distance;
				position = position + MoveVector;
	}
void Bike::GetViewDir()
{
	Point Step1, Step2;
	//Rotate around Y-axis:
	Step1.x = cos( (angle.y + 90.0) * PIdiv180);
	Step1.z = -sin( (angle.y + 90.0) * PIdiv180);
	//Rotate around X-axis:
	double cosX = cos (angle.x * PIdiv180);
	Step2.x = Step1.x * cosX;
	Step2.z = Step1.z * cosX;
	Step2.y = sin(angle.x * PIdiv180);
	//Rotation around Z-axis not yet implemented, so:
	direction = Step2;
}
void Bike::move(){
	switch(state){
		case 0:
			accel();
			break;
		case 1:
			rev();
			break;
		default:
			decel();
			break;
	}
	switch(currDir){
		case 0:
			turnL();
			break;
		case 1:
			turnR();
			break;
		default:
			break;
	}
	moveForward(velocity);
}
void Bike::accel(){
	if(velocity<speedLimit){
		velocity+=.01;
	}
}
void Bike::accelerate(){
	state = Motion::accel;
}
void Bike::decel(){
	if(velocity > 0.001)
		velocity-= .001;
	else if(velocity > 0)
		velocity = 0;
	else if(velocity<=0)
		velocity+= .001;
}
void Bike::decelerate(){
	state = Motion::none;
}
void Bike::reverse(){
	state = Motion::reverse;
}
void Bike::rev(){
	if(velocity>0){
		velocity-= .05;
	}
	else if(velocity<=0){
		if(velocity>=-1){
			velocity-=.001;
		}
	}
}
void Bike::setVelocity(){
	
}

