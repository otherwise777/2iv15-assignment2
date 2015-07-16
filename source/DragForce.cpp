#include "DragForce.h"

DragForce::DragForce(Particle *p, double factor) :
	m_p(p), m_factor(factor) {}

void DragForce::apply()
{
	m_p -> m_Velocity *= m_factor;
}

void DragForce::draw() {}