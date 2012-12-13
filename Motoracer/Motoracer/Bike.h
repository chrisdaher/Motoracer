#include "Point.h"
#include "CarDrawer.h"
#include "camera.h"
namespace Motion{
  enum MotionEffect{
    accel,
    reverse,
    none
  };
}
class Bike{
	private:
		void accel();
		void decel();
    Motion::MotionEffect state;
	public:
		Camera* camera;
		Point position;
		Point direction;
		Point angle;
		float speedLimit;
		bool isHighbeam;
		float velocity;
		float acceleration;
		enum DIR{
			LEFT,
			RIGHT,
			NONE
		};

		DIR currDir;		

		CarDrawer carDrawer;
		//Point ViewDir;
		bool ViewDirChanged;
		Bike();
		Bike(Point p, Point rA, Point a);
		Bike(const Bike& bike);
		const Point& getPosition() const;
		void setPosition(const Point& p);
		void setCamera(Camera& c);
		void setPosition(float X, float Y, float Z);
		void drawBike();
		void setVelocity();
		void move();
		void accelerate();
		void decelerate();
		void reverse();
		void rev();
		void moveForward(float Distance);
		void moveBackward(float Distance);
		void turnLeft();
		void turnRight();
		void flip(float a);
		void noTurn();
		void turnR();
		void turnL();
		void strafeRight();
		void strafeLeft();
		void GetViewDir();
		void reset();
};

