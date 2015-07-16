#include "PointConstraint.h"


PointConstraint::PointConstraint(Particle *p, Vec2f position) :
	m_p(p), m_position(position)
{
	particles.push_back(p);
}

float PointConstraint::getC() {
	return (m_p -> m_Position - m_position) * (m_p -> m_Position - m_position);
}

float PointConstraint::getCdot() {
	return (2 * (m_p -> m_Position - m_position)) * m_p -> m_Velocity;
}

std::vector<Vec2f> PointConstraint::getJ() {
	std::vector<Vec2f> j;
	j.push_back(2 * (m_p -> m_Position - m_position));
	j.push_back(2 * (m_position - m_p -> m_Position));
	return j;
}

std::vector<Vec2f> PointConstraint::getJdot() {
	std::vector<Vec2f> jdot;
	jdot.push_back(m_p -> m_Velocity);
	jdot.push_back(-1 * m_p -> m_Velocity);
	return jdot;
}

void PointConstraint::draw()
{
	/*
	glEnable( GL_POINT_SMOOTH );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glPointSize( 6.0 );
	glBegin( GL_POINTS );
	glColor3f(0.8, 0.7, 0.6);
	glVertex2f( m_position[0], m_position[1] );
	glEnd();
	*/
}

PointConstraint::~PointConstraint(void)
{
}
