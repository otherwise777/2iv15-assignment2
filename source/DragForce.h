#pragma once

#include "Particle.h"
#include "IForce.h"

class DragForce: public IForce
{
public:
	DragForce(Particle *p, double factor);

	virtual void apply();

	virtual void draw();

private:

	Particle * const m_p;   // particle 1
	double const m_factor; // spring strength constants
};
