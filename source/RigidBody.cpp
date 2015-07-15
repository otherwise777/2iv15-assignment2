#include "RigidBody.h"

RigidBody::RigidBody(int vertexCount, int N)
{
	m_N = N;
	int size = (N+2)*(N+2);

	m_vertexCount = vertexCount;

	m_vertices = (float *) malloc ( m_vertexCount * 2 * sizeof(float));
	m_currentvertices = (float *) malloc ( m_vertexCount * 2 * sizeof(float));
	m_position = (float *) malloc ( 2 * sizeof(float));
	m_velocity = (float *) malloc ( 2 * sizeof(float));
	u = (float *) malloc ( size * sizeof(float));
	v = (float *) malloc ( size * sizeof(float));

	m_scale = 1;
	m_position[0] = 0;
	m_position[1] = 0;
	m_velocity[0] = 0;
	m_velocity[1] = 0;
	m_rotation = 0;
	m_momentum = 0;
}

bool RigidBody::pointInPolygon(float x, float y) {
	int i, j;
	bool c = false;
	for (i = 0, j = m_vertexCount - 1; i < m_vertexCount; j = i++) {
		if (((m_currentvertices[i * 2 + 1] >= y) != (m_currentvertices[j * 2 + 1] >= y)) && 
			(x <= ((m_currentvertices[j * 2] - m_currentvertices[i * 2]) * (y - m_currentvertices[i * 2 + 1]) / (m_currentvertices[j * 2 + 1] - m_currentvertices[i * 2 + 1]) + m_currentvertices[i * 2])))
			c = !c;
	}
	return c;
}

void RigidBody::accumulate(float* u, float* v) {
	float h = 1.0f/m_N;

	int i, j;
	float x, y;
	
	float vel[] = {0, 0};
	m_momentum = 0;
	FOR_EACH_CELL
		x = (i-0.5f)*h;
		y = (j-0.5f)*h;

		vel[0] += u[IX(i, j)] / (m_mass * 100);
		vel[1] += v[IX(i, j)] / (m_mass * 100);

		m_momentum += (x - m_position[0]) * u[IX(i, j)] / (m_mass * 100);
		m_momentum += (y - m_position[1]) * v[IX(i, j)] / (m_mass * 100);
	END_FOR

	float diff[] = {m_velocity[0] - (vel[0] / m_mass), m_velocity[1] - (vel[1] / m_mass)};
	m_velocity[0] += diff[0] * 0.004f;
	m_velocity[1] += diff[1] * 0.004f;

		cout << m_velocity;
}

void RigidBody::calculateVelocityField(void)
{
	float h = 1.0f/m_N;

	float x;
	float y;

	int i, j;
	FOR_EACH_CELL
		x = (i-0.5f)*h;
		y = (j-0.5f)*h;

		u[IX(i,j)] = 0;
		v[IX(i,j)] = 0;
		if (pointInPolygon(x, y)){
			u[IX(i,j)] = (m_momentum * (x - m_position[0]) + m_velocity[0]) * 10;
			v[IX(i,j)] = (m_momentum * (y - m_position[1]) + m_velocity[1]) * 10;
		} 
	END_FOR
}
void RigidBody::calculateMass(void)
{
	float h = 1.0f/m_N;

	int i, j;
	float x, y;
	m_mass = 0;
	FOR_EACH_CELL
		x = (i-0.5f)*h;
		y = (j-0.5f)*h;

		if (pointInPolygon(x, y)){
			m_mass++;
		} 
	END_FOR
}

void RigidBody::calculateCenterOfMass(void)
{
	float centroid[2] = {0, 0};
	double signedArea = 0.0;
	float x0 = 0.0; // Current vertex X
	float y0 = 0.0; // Current vertex Y
	float x1 = 0.0; // Next vertex X
	float y1 = 0.0; // Next vertex Y
	float a = 0.0;  // Partial signed area

	// For all vertices except last
	int i=0;
	for (i=0; i < m_vertexCount-1; ++i)
	{
		x0 = m_vertices[i * 2];
		y0 = m_vertices[i * 2 + 1];
		x1 = m_vertices[(i + 1) * 2];
		y1 = m_vertices[(i + 1) * 2 + 1];
		a = x0*y1 - x1*y0;
		signedArea += a;
		centroid[0] += (x0 + x1)*a;
		centroid[1] += (y0 + y1)*a;
	}

	// Do last vertex
	x0 = m_vertices[i * 2];
	y0 = m_vertices[i * 2 + 1];
	x1 = m_vertices[0];
	y1 = m_vertices[1];
	a = x0*y1 - x1*y0;
	signedArea += a;
	centroid[0] += (x0 + x1)*a;
	centroid[1] += (y0 + y1)*a;

	signedArea *= 0.5;
	centroid[0] /= (6.0*signedArea);
	centroid[1] /= (6.0*signedArea);

	// set center of mass as rotation middle
	for (int i = 0; i < m_vertexCount; i++)
	{
		m_vertices[i * 2] -= centroid[0];
		m_vertices[i * 2 + 1] -= centroid[1];
	}

	m_position[0] += centroid[0];
	m_position[1] += centroid[1];

	updateVertices();
}

void RigidBody::updateVertices(void)
{
	for (int i = 0; i < m_vertexCount; i++) {

		// apply rotation
		m_currentvertices[i * 2] = (m_vertices[i * 2] * cos(m_rotation) + m_vertices[i * 2 + 1] * sin(m_rotation));
		m_currentvertices[i * 2 + 1] = (-m_vertices[i * 2] * sin(m_rotation) + m_vertices[i * 2 + 1] * cos(m_rotation));

		// apply scale
		m_currentvertices[i * 2] *= m_scale;
		m_currentvertices[i * 2 + 1] *= m_scale;

		// apply translation
		m_currentvertices[i * 2] +=  m_position[0];
		m_currentvertices[i * 2 + 1] +=  m_position[1];
	}
}

void RigidBody::reset(void) {
	m_position[0] = 0.5;
	m_position[1] = 0.5;
	m_velocity[0] = 0;
	m_velocity[1] = 0;
	m_momentum = 0;
	m_rotation = 0;
}

void RigidBody::draw(void)
{
	m_position[0] += m_velocity[0];
	m_position[1] += m_velocity[1];
	m_rotation += m_momentum;

	updateVertices();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	for (int i = 0; i < m_vertexCount; i++) {
		glVertex2f(m_currentvertices[i * 2], m_currentvertices[i * 2 + 1]);
	}
	glEnd();

	// Draw center of mass
	glPointSize(5.0f);
	glBegin(GL_POINTS);	
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(m_position[0], m_position[1]);
	glEnd();
}

RigidBody::~RigidBody(void)
{
}
