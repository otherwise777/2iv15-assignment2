#include "Rectangle.h"

Rectangle::Rectangle(void) :
	RigidBody(4, 64)
{
	m_vertices[0] = -0.8f;
	m_vertices[1] = 0.1f;
	m_vertices[2] = 0.8f;
	m_vertices[3] = 0.1f;
	m_vertices[4] = 0.8f;
	m_vertices[5] = -0.1f;
	m_vertices[6] = -0.8f;
	m_vertices[7] = -0.1f;

	calculateCenterOfMass();

	m_position[0] = 0.1;
	m_position[1] = 0.5;
	m_momentum = 0.005;
	m_scale = 0.25;
	m_velocity[1] = 0.0000;
}

Rectangle::~Rectangle(void)
{
}
