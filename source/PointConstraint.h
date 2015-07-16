#pragma once
#include "iconstraint.h"
class PointConstraint :
	public IConstraint
{
public:
	PointConstraint(Particle *p, Vec2f position);

	virtual float getC();
	virtual float getCdot();
	virtual std::vector<Vec2f> getJ();
	virtual std::vector<Vec2f> getJdot();
		
	virtual void draw();

	~PointConstraint(void);

private:
	Particle* m_p;
	Vec2f m_position;

};

