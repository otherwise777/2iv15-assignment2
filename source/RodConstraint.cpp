#include "RodConstraint.h"

RodConstraint::RodConstraint(Particle *p1, Particle * p2, double dist) :
	m_p1(p1), m_p2(p2), m_dist(dist)
{
	particles.push_back(m_p1);
	particles.push_back(m_p2);
}

RodConstraint::RodConstraint(Particle *p1, Particle * p2) :
	m_p1(p1), m_p2(p2), m_dist(sqrt((p1->m_Position - p2 -> m_Position) * (p1->m_Position - p2 -> m_Position)))
{
	particles.push_back(m_p1);
	particles.push_back(m_p2);
}

// C(x1, y1, x2, y2) = (x1 - x2)^2 + (y1 - y2)^2 - r^2
float RodConstraint::getC() {
	return ((m_p1 -> m_Position - m_p2 -> m_Position) * (m_p1 -> m_Position - m_p2 -> m_Position)) - (m_dist * m_dist);
}

float RodConstraint::getCdot() {
	return (2 * (m_p1->m_Position - m_p2->m_Position)) * (2 * (m_p1->m_Velocity - m_p2->m_Velocity));
}

std::vector<Vec2f> RodConstraint::getJ() {
	std::vector<Vec2f> j;
	j.push_back((m_p1 -> m_Position - m_p2 -> m_Position) * 2);
	j.push_back((m_p2 -> m_Position - m_p1 -> m_Position) * 2);
	return j;
}

std::vector<Vec2f> RodConstraint::getJdot() {
	std::vector<Vec2f> jdot;
	jdot.push_back((m_p1 -> m_Velocity - m_p2 -> m_Velocity) * 2);
	jdot.push_back((m_p2 -> m_Velocity - m_p1 -> m_Velocity) * 2);
	return jdot;
}

void RodConstraint::draw()
{
	glBegin( GL_LINES );
	glColor3f(0.8, 0.7, 0.6);
	glVertex2f( m_p1->m_Position[0], m_p1->m_Position[1] );
	glColor3f(0.8, 0.7, 0.6);
	glVertex2f( m_p2->m_Position[0], m_p2->m_Position[1] );
	glEnd();
}