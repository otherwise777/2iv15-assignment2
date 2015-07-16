#include "MouseForce.h"

MouseForce::MouseForce() :
	m_p(new Particle(Vec2f(0,0))), m_position(Vec2f(0, 0)), m_kd(1.0), m_ks(2.0), m_enabled(false)
{	
}

void MouseForce::draw()
{
	for (unsigned int i = 0; i < forces.size(); i++) 
	{
		forces[i] -> draw();

		for (unsigned int n = 0; n < forces[i] ->particles.size(); n++) {
			forces[i] ->particles[n] -> draw();
		}
	}
}

void MouseForce::setEnabled(bool enabled)
{
	if(m_enabled && !enabled) {
		m_p = new Particle(Vec2f(0, 0));
	}

	m_enabled = enabled;
}

bool MouseForce::getEnabled() {
	return m_enabled;
}

void MouseForce::setMousePosition(const Vec2f & mouse)
{
	m_position = mouse;

	if (getEnabled()) {
		m_p -> m_Position = m_position;	
	}
}

Vec2f MouseForce::getMousePosition() {
	return m_position;
}

void MouseForce::setParticle(Particle* p)
{
	forces.push_back(new SpringForce(p, m_p, 0, m_ks, m_kd));
}

void MouseForce::clear() 
{
	forces.clear();
}

void MouseForce::apply()
{
	for (unsigned int i = 0; i < forces.size(); i++) 
	{
		forces[i] -> apply();
	}
}