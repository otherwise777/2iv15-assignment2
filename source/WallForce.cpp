#include "WallForce.h"
#include <iostream>
using namespace std;

WallForce::WallForce(Particle *p1, double x) : m_p1(p1), m_x(x)
{
	particles.push_back(p1);
}


void WallForce::apply()
{
	//check if the particle goes beyond the border
	Vec2f l = m_p1->m_Position;
	if (l[0] < m_x) {
		//cout << "test";
		m_p1->m_Velocity[0] *= -0.9 ;
		if (m_p1->m_Force[0] < 0) {
			m_p1->m_Force[0] *= -1;
		}
		
	}
	//m_p1->m_Force -= f; //this moves point 1
}

void WallForce::draw()
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(m_x,-1);
	glVertex2f(m_x, 1);
	glEnd();
}
