#include "AngularSpringForce.h"


AngularSpringForce::AngularSpringForce(Particle *p1, Particle * p2, Particle * p3, double angle, double ks, double kd) :
	m_p1(p1), m_p2(p2), m_p3(p3), m_angle(angle), m_ks(ks), m_kd(kd)
{
	particles.push_back(p1);
	particles.push_back(p2);
	particles.push_back(p3);
}

void AngularSpringForce::apply()
{
	Vec2f posdif12 = (m_p1->m_Position - m_p2->m_Position);
	Vec2f posdif32 = (m_p3->m_Position - m_p2->m_Position);

	// length of both vectors
	float length12 = sqrt(posdif12[0] * posdif12[0] + posdif12[1] * posdif12[1]);
	float length32 = sqrt(posdif32[0] * posdif32[0] + posdif32[1] * posdif32[1]);
	float length12Sqr = posdif12[0] * posdif12[0] + posdif12[1] * posdif12[1];
	float length32Sqr = posdif32[0] * posdif32[0] + posdif32[1] * posdif32[1];

	// dot product  
	float dot = (posdif12[0] * posdif32[0] + posdif12[1] * posdif32[1]);

	// square of cosine of the needed angle    
	float cosSqr = dot * dot / length12Sqr / length32Sqr;

	// this is a known trigonometric equality:
	// cos(alpha * 2) = [ cos(alpha) ]^2 * 2 - 1
	float cos2 = 2 * cosSqr - 1;

	// Here's the only invocation of the heavy function.
	// It's a good idea to check explicitly if cos2 is within [-1 .. 1] range
	const float pi = 3.141592f;

	float alpha2 =
		(cos2 <= -1) ? pi :
		(cos2 >= 1) ? 0 :
		acosf(cos2);

	float rslt = alpha2 / 2;

	float rs = rslt * 180. / pi;


	// Now revolve the ambiguities.
	// 1. If dot product of two vectors is negative - the angle is definitely
	// above 90 degrees. Still we have no information regarding the sign of the angle.

	// NOTE: This ambiguity is the consequence of our method: calculating the cosine
	// of the double angle. This allows us to get rid of calling sqrt.

	if (dot < 0)
		rs = 180 - rs;

	// 2. Determine the sign. For this we'll use the Determinant of two vectors.

	//rs = (int)floor(rs + 0.5);
	float det = (posdif12[0] * posdif32[1] - posdif12[1] * posdif32[0]);
	if (det < 0)
	{
		rs = -rs;
	}

	//the angle is from -180 to +180, there are 2 points where it wants to go
	float restAngle = 0;
	if (rs < 0)
	{
		restAngle = rs + m_angle;
	}
	else
	{
		restAngle = rs - m_angle;
	}

	Vec2f veldif12 = (m_p1->m_Velocity - m_p2->m_Velocity);
	Vec2f veldif32 = (m_p3->m_Velocity - m_p2->m_Velocity);
	
	m_p1->m_Force[0] -= ((m_ks*restAngle) / length12*posdif12[1]) + (m_kd*veldif12[0]);
	m_p1->m_Force[1] += ((m_ks*restAngle) / length12*posdif12[0]) - (m_kd*veldif12[1]);
	m_p3->m_Force[0] += ((m_ks*restAngle) / length32*posdif32[1]) - (m_kd*veldif32[0]);
	m_p3->m_Force[1] -= ((m_ks*restAngle) / length32*posdif32[0]) + (m_kd*veldif32[1]);
}

void AngularSpringForce::draw()
{
	// Draw forces
	glBegin( GL_LINES );
	glColor3f(0.6, 0.2, 0.8);
	glVertex2f(m_p1->m_Position[0], m_p1->m_Position[1] );
	glVertex2f(m_p2->m_Position[0], m_p2->m_Position[1] );
	glVertex2f(m_p2->m_Position[0], m_p2->m_Position[1] );
	glVertex2f(m_p3->m_Position[0], m_p3->m_Position[1] );
	glEnd();
}

AngularSpringForce::~AngularSpringForce(void)
{
}
