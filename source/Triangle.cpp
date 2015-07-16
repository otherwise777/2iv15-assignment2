#include "Triangle.h"

Triangle::Triangle(void) :
	RigidBody(3, 64)
{
	m_vertices[0] = 0.4f;
	m_vertices[1] = 0.5f;
	m_vertices[2] = 0.6f;
	m_vertices[3] = 0.6f;
	m_vertices[4] = 0.6f;
	m_vertices[5] = 0.4f;

	calculateCenterOfMass();
	calculateMass();

	cout << "Mass of object" << m_mass << endl;

	m_scale = 1;
	m_momentum = 0;
	m_velocity[1] = 0;
}

Triangle::~Triangle(void)
{
}
