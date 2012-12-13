#ifndef pointclass
#define pointclass
class Point{
	public:
		float x;
		float y;
		float z;

		Point();
		Point(float X, float Y, float Z);
		Point(const Point& p);
		const float getX() const;
		const float getY() const;
		const float getZ() const;
		void setX(float X);
		void setY(float Y);
		void setZ(float Z);
		Point operator+ (Point p);
		bool operator== (Point p);
};
#endif
