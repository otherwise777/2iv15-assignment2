#pragma once
#include <Vector>
#include <glut.h>

#include "Particle.h"


class IConstraint
{
 public:
	 virtual float getC() = 0;
	 virtual float getCdot() = 0;
	 virtual std::vector<Vec2f> getJ() = 0;
	 virtual std::vector<Vec2f> getJdot() = 0;
	 
	 std::vector<Particle*> particles;

	 virtual void draw() = 0;
};