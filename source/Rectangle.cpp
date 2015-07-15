#include "Rectangle.h"

Rectangle::Rectangle(void) :
	RigidBody(4, 64)
{
	m_vertices[0] = -0.5f;
	m_vertices[1] = 0.5f;
	m_vertices[2] = 0.5f;
	m_vertices[3] = 0.5f;
	m_vertices[4] = 0.5f;
	m_vertices[5] = -0.5f;
	m_vertices[6] = -0.5f;
	m_vertices[7] = -0.5f;

	calculateCenterOfMass();

	m_position[0] = 0.5;
	m_position[1] = 0.5;
	m_momentum = 0.005;
	m_scale = 0.5;
	m_velocity[1] = 0.0000;
}

void Rectangle::act(float* u, float* v) {
	

}

Rectangle::~Rectangle(void)
{
}
