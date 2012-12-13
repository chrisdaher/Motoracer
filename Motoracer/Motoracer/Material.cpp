#include "Material.h"
float Material::engine[3][4] = { {0.24725f,0.1995f,0.0745f,1}, {0.75164f, 0.60648f, 0.22648f, 1}, {0.628281f, 0.555802f, 0.366065f, 1}};
float Material::seat[3][4] = { {0,0,0,1}, {0.5, 0, 0, 1}, {0.7, 0.6, 0.6, 1}};
float Material::cylinder[3][4] = { {0.25f,0.25f,0.25f,1}, {0.4, 0.4, 0.4, 1}, {0.774597f, 0.774597f, 0.774597f, 1}};
float Material::rubber[3][4] = { {0.02f,0.02f,0.02f,1}, {0.01f, 0.01f, 0.01f, 1}, {0.4, 0.4, 0.4, 1}};
float Material::white[3][4] = { {0,0,0,1}, {1, 1, 1, 1}, {0.7, 0.7, 0.7, 1}};
float Material::fuel[3][4] = { {0,0.05,0,1}, {0.4, 0.5, 0.4, 1}, {0.4, 0.7, 0.4, 1}};

Material::Material(){}
void Material::setMaterial(float type[3][4], float shinyness)
{
	
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
 
  glDisable(GL_COLOR_MATERIAL);
  glMaterialfv(GL_FRONT, GL_AMBIENT, type[0]);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, type[1]);
  glMaterialfv(GL_FRONT, GL_SPECULAR, type[2]);
  glMaterialf(GL_FRONT, GL_SHININESS,shinyness);
  

}
void Material::setEngine()
{
	setMaterial(engine, 0.4f*128);
}

void Material::setSeat()
{
	setMaterial(seat, 0.25f*128);
}

void Material::setCylinder()
{
  setMaterial(cylinder,0.6f*128);
}

void Material::setRubber()
{
  setMaterial(rubber,0.78125f*128);
}

void Material::setWhite()
{
  setMaterial(white,0.25f*128);
}

void Material::setFuel()
{
  setMaterial(fuel,0.078125f*128);
}
void Material::setColor(float r, float g, float b)
{
	float color[3][4] = { {r,g,b,1}, {r, g, b, 1}, {r, g, b, 1}};
	setMaterial(color, 0.25f*128);
}