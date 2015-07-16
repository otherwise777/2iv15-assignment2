#pragma once

#include "IForce.h"

class AngularSpringForce :
	public IForce
{
public:
		
	AngularSpringForce(Particle *p1, Particle * p2, Particle * p3, double angle, double ks, double kd);

	virtual void apply();

	virtual void draw();

	~AngularSpringForce(void);

private:

	Particle * const m_p1;   // particle 1
	Particle * const m_p2;   // particle 2 
	Particle * const m_p3;   // particle 2 
	double const m_angle;    // rest angle
	double const m_ks, m_kd; // spring strength constants
};

