#pragma once

#include "Particle.h"
#include "IConstraint.h"

class RodConstraint: public IConstraint 
{

public:
	RodConstraint(Particle *p1, Particle * p2);
	RodConstraint(Particle *p1, Particle * p2, double dist);
	

	virtual float getC();
	virtual float getCdot();
	virtual std::vector<Vec2f> getJ();
	virtual std::vector<Vec2f> getJdot();
		
	virtual void draw();

private:
	Particle* m_p1;
	Particle* m_p2;
	float m_dist;

};