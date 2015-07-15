#pragma once
using namespace std;

#include <cmath>
#include <iostream>
#include <GL/glut.h>

#define IX(i,j) ((i)+(m_N+2)*(j))
#define FOR_EACH_CELL for ( i=1 ; i<=m_N ; i++ ) { for ( j=1 ; j<=m_N ; j++ ) {
#define END_FOR }}

class RigidBody
{
public:
	float * u;
	float * v;

	RigidBody(int vertexCount, int N);

	bool pointInPolygon(float x, float y);

	void accumulate(float* u, float* v);

	void calculateVelocityField(void);

	void reset (void);

	void draw(void);

	~RigidBody(void);

private:
	int m_vertexCount;
	int m_N;

	void updateVertices(void);

protected:
	int m_mass;
	float m_scale;
	float * m_vertices;
	float * m_currentvertices;
	float * m_position;
	float * m_velocity;
	float m_rotation;
	float m_momentum;

	void calculateMass(void);
	void calculateCenterOfMass(void);
};

