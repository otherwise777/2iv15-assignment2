#pragma once

#include "Particle.h"
#include "IConstraint.h"

class HorizontalWireConstraint: public IConstraint
{
public:
	HorizontalWireConstraint(Particle *p, float height);
	
	virtual float getC();
	virtual float getCdot();
	virtual std::vector<Vec2f> getJ();
	virtual std::vector<Vec2f> getJdot();
		
	virtual void draw();

	~HorizontalWireConstraint(void);
private:
	Particle * m_p;
	float m_height;
};

