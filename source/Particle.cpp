#include "Particle.h"
#include <glut.h>

Particle::Particle(const Vec2f & ConstructPos) :
	m_ConstructPos(ConstructPos), m_Position(Vec2f(0.0, 0.0)), m_Velocity(Vec2f(0.0, 0.0)), RigidBody(4, 64)
{
	m_vertices[0] = -0.1f;
	m_vertices[1] = 0.1f;
	m_vertices[2] = 0.1f;
	m_vertices[3] = 0.1f;
	m_vertices[4] = 0.1f;
	m_vertices[5] = -0.1f;
	m_vertices[6] = -0.1f;
	m_vertices[7] = -0.1f;

	m_scale = 0.1;

	m_Position = m_ConstructPos;
	m_position[0] = m_Position[0];
	m_position[1] = m_Position[1];

	calculateCenterOfMass();
}

Particle::~Particle(void)
{
}

void Particle::reset()
{
	m_Position = m_ConstructPos;
	m_Velocity = Vec2f(0.0, 0.0);
}

void Particle::drawSpeed() {
	glColor3f(0.000, 1.000, 0.000); 
	glBegin(GL_LINES);
	glVertex2f(m_Position[0], m_Position[1]);
	glVertex2f(m_Position[0] + m_Velocity[0], m_Position[1] + m_Velocity[1]);
	glEnd();
}

void Particle::drawForce() {
	glColor3f(0.000, 0.000, 1.000); 
	glBegin(GL_LINES);
	glVertex2f(m_Position[0], m_Position[1]);
	glVertex2f(m_Position[0] + m_Force[0] * 10, m_Position[1] + m_Force[1] * 10);
	glEnd();
}

void Particle::draw()
{
	m_Position[0] = m_position[0];
	m_Position[1] = m_position[1];

	m_Velocity[0] += m_velocity[0];
	m_Velocity[1] += m_velocity[1];

	const double h = 0.03;
	glColor3f(1.000, 0.000, 0.000); 
	glBegin(GL_QUADS);
	glVertex2f(m_Position[0]-h/2.0, m_Position[1]-h/2.0);
	glVertex2f(m_Position[0]+h/2.0, m_Position[1]-h/2.0);
	glVertex2f(m_Position[0]+h/2.0, m_Position[1]+h/2.0);
	glVertex2f(m_Position[0]-h/2.0, m_Position[1]+h/2.0);
	glEnd();
}
