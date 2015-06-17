#include "VectorField.h"
#include "FieldToolbox.h"

#define CREATE_DIM1 (new Vec2f[(a_NumCells+2)*(a_NumCells+2)])
#define CREATE_DIM2 (new Vec2f[(CopyField->m_NumCells+2)*(CopyField->m_NumCells+2)])
#define CREATE_DIM  (new Vec2f[(m_NumCells+2)*(m_NumCells+2)])
#define IX_DIM(i,j) ((i)+(m_NumCells+2)*(j))
#define ITER_DIM    for(int i = 1; i <= m_NumCells; i++){ for(int j = 1; j <= m_NumCells; j++){
#define ENDITER_DIM }}

VectorField::VectorField(int a_NumCells, float a_Viscosity, float a_Dt)
: m_NumCells(a_NumCells), m_Field(CREATE_DIM1), m_Viscosity(a_Viscosity), m_Dt(a_Dt)
{
	for(int i = 0; i < (m_NumCells+2)*(m_NumCells+2); i++) 
		m_Field[i][0] = m_Field[i][1] = 0.f;
}

VectorField::VectorField(VectorField *CopyField)
: m_NumCells(CopyField->m_NumCells), m_Field(CREATE_DIM2), m_Viscosity(CopyField->m_Viscosity), m_Dt(CopyField->m_Dt)
{
	for(int i = 0; i < (m_NumCells+2)*(m_NumCells+2); i++){
		m_Field[i][0] = (*CopyField)[i][0];
		m_Field[i][1] = (*CopyField)[i][1];
	}
}

VectorField::~VectorField(void)
{
	delete m_Field;
}

void 
VectorField::TimeStep(VectorField *a_SrcField, VectorField *VelocityField)
{
	AddField(a_SrcField);
	Advection(VelocityField);	// Add this function
	//VorticityConfinement();	// Add this function
	//Projection();				// Add this function
}

void
VectorField::AddField(VectorField *a_SrcField)
{
	for(int i=0; i<((m_NumCells+2)*(m_NumCells+2)); i++) {
		m_Field[i][0] += m_Dt*((*a_SrcField)[i][0]);
		m_Field[i][1] += m_Dt*((*a_SrcField)[i][1]);
	}
}

void VectorField::Advection(VectorField *VelocityField)
{
	ITER_DIM

	// Previous position of center
	Vec2f w2 = Vec2f(i, j) - m_Dt * m_Field[IX_DIM(i, j)];

	// Calculate the weights for each pixel
	float xd = w2[0] - (int)w2[0];
	float yd = w2[1] - (int)w2[1];
	
	// Get surrounding cells
	Vec2f v00 = VelocityField->m_Field[IX_DIM(i, j)];
	Vec2f v10 = VelocityField->m_Field[IX_DIM(i + 1, j)];
	Vec2f v01 = VelocityField->m_Field[IX_DIM(i, j + 1)];
	Vec2f v11 = VelocityField->m_Field[IX_DIM(i + 1, j + 1)];

	Vec2f c0 = v00 * (1 - xd) + v10 * xd;
	Vec2f c1 = v01 * (1 - xd) + v11 * xd;

	Vec2f c = c0 * (1 - yd) + c1 * yd;

	m_Field[IX_DIM(i, j)] = c;

	ENDITER_DIM
}

