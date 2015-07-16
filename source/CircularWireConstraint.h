#pragma once

#include "Particle.h"
#include "IConstraint.h"
#include <vector>

class CircularWireConstraint : public IConstraint
{
public:
	CircularWireConstraint(Particle *p, const Vec2f & center, const double radius);

	virtual float getC();
	virtual float getCdot();
	virtual std::vector<Vec2f> getJ();
	virtual std::vector<Vec2f> getJdot();

	virtual void draw();

private:

	Particle * const m_p;
	Vec2f const m_center;
	double const m_radius;
};