#pragma once

#include "Particle.h"
#include "IForce.h"
#include "SpringForce.h"
#include <vector>

class MouseForce : public IForce
{
public:
	MouseForce();

	virtual void draw();
	virtual void apply();

	void setMousePosition(const Vec2f & mouse);
	Vec2f getMousePosition();
	void setEnabled(bool enabled);
	bool getEnabled();

	void clear();

	void setParticle(Particle * p);
private:
	Particle * m_p;
	std::vector<IForce*> forces;
	
	Vec2f m_position;
	bool m_enabled;
	double  m_ks, m_kd; // spring strength constants
};