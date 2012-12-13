#include <GL/glut.h>

class Material{
private:
	static float engine[3][4];
	static float seat[3][4];
	static float cylinder[3][4];
	static float rubber[3][4];
	static float white[3][4];
	static float fuel[3][4];
	static void setMaterial(float type[3][4], float shinyness);
public:
	Material();
	static void setEngine();
	static void setSeat();
	static void setCylinder();
	static void setRubber();
	static void setWhite();
	static void setFuel();
	static void setColor(float r, float g, float b);
};
