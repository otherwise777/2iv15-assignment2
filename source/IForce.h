#pragma once

#include "Particle.h"

#include <glut.h>
#include <vector>

class IForce
{
 public:
	 virtual void apply() = 0;
	 virtual void draw() = 0;

	 std::vector<Particle*> particles;
};
