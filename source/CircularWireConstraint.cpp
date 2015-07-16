#include "CircularWireConstraint.h"

#define PI 3.1415926535897932384626433832795

CircularWireConstraint::CircularWireConstraint(Particle *p, const Vec2f & center, const double radius) :
	m_p(p), m_center(center), m_radius(radius)
{	
	particles.push_back(m_p);
}

static void draw_circle(const Vec2f & vect, float radius)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0,1.0,0.0); 
	for (int i = 0; i < 360; i = i + 18)
	{
		float degInRad = i*PI/180;
		glVertex2f(vect[0] + cos(degInRad) * radius, vect[1] + sin(degInRad) * radius);
	}
	glEnd();
}

// C(x1, y1, x2, y2) = (x1 - x2)^2 + (y1 - y2)^2 - r^2
float CircularWireConstraint::getC() {
	Vec2f posdif = (m_p->m_Position - m_center);
	return (posdif * posdif - m_radius * m_radius);
}

float CircularWireConstraint::getCdot() {
	return (2 * (m_p->m_Position - m_center)) * (2 * m_p->m_Velocity);
}

std::vector<Vec2f> CircularWireConstraint::getJ() {
	std::vector<Vec2f> j;
	j.push_back(2 * (m_p->m_Position - m_center));
	return j;
}

std::vector<Vec2f> CircularWireConstraint::getJdot() {
	std::vector<Vec2f> jdot;
	jdot.push_back(2 * m_p->m_Velocity);
	return jdot;
}

void CircularWireConstraint::draw()
{
	draw_circle(m_center, m_radius);
}