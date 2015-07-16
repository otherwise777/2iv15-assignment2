#include "ConstraintSolver.h"

void ConstraintSolver::Calculate(std::vector<Particle*> pVector, std::vector<IConstraint*> constraints, float ks, float kd)
{
	
	// Assign particle identifiers
	for (unsigned int i = 0; i < pVector.size(); i++) {
		pVector[i] -> id = i;
	}

	Matrix q = Matrix::Matrix(pVector.size() * 2);
	Matrix qDot = Matrix::Matrix(pVector.size() * 2);
	Matrix Q = Matrix::Matrix(pVector.size() * 2);
	Matrix W = Matrix::Matrix(pVector.size() * 2, pVector.size() * 2);

	for (unsigned int i = 0; i < pVector.size(); i++)
	{
		q.setValue(i * 2 + 0, pVector[i]->m_Position[0]);
		q.setValue(i * 2 + 1, pVector[i]->m_Position[1]);
		qDot.setValue(i * 2 + 0, pVector[i]->m_Velocity[0]);
		qDot.setValue(i * 2 + 1, pVector[i]->m_Velocity[1]);
		Q.setValue(i * 2 + 0, pVector[i]->m_Force[0]);
		Q.setValue(i * 2 + 1, pVector[i]->m_Force[1]);
	}

	Matrix C = Matrix::Matrix(constraints.size());
	Matrix CDot = Matrix::Matrix(constraints.size());
	for (unsigned int i = 0; i < constraints.size(); i++)
	{
		C.setValue(i, constraints[i]->getC());
		CDot.setValue(i, constraints[i]->getCdot());
	}

	Matrix J = Matrix::Matrix(constraints.size(), pVector.size() * 2);
	Matrix JDot = Matrix::Matrix(constraints.size(), pVector.size() * 2);
	Matrix JT = Matrix::Matrix(pVector.size() * 2, constraints.size());
	for (unsigned int i = 0; i < constraints.size(); i++)
	{
		vector<Vec2f> jac = constraints[i]->getJ();
		vector<Vec2f> jacDot = constraints[i]->getJdot();
		vector<Particle*> particles = constraints[i]->particles;
		for (unsigned  j = 0; j < particles.size(); j++)
		{
			for (unsigned int k = 0; k < 2; k++)
			{
				J.setValue(i, particles[j]->id * 2 + k, jac[j][k]);
				JT.setValue(particles[j]->id * 2 + k, i, jac[j][k]);
				JDot.setValue(i, particles[j]->id * 2 + k, jacDot[j][k]);
			}
		}
	}
	
	Matrix JW = J * W;
	Matrix JWJT = JW * JT;

	Matrix JDotqDot = Matrix::Matrix(qDot.size());
	Matrix JWQ = Matrix::Matrix(Q.size());
	JDotqDot = JDot * qDot;
	JDotqDot = JDotqDot * -1;
	JWQ = JW * Q;

	Matrix CStrength = Matrix::Matrix(constraints.size());
	Matrix CDotDamping = Matrix::Matrix(constraints.size());
	CStrength = C * ks;
	CDotDamping = CDot * kd;

	Matrix JWJTLambda = Matrix::Matrix(constraints.size());
	JWJTLambda = JDotqDot - JWQ - CStrength - CDotDamping;

	double* JWJTLambdaDouble = new double[JWJTLambda.size()];
	for (unsigned int i = 0; i < JWJTLambda.size(); i++)
	{
		JWJTLambdaDouble[i] = JWJTLambda.getValue(i);
	}
	
	double* lambda = new double[constraints.size()];

	int stepSize = 100;
	ConjGrad(constraints.size(), &JWJT, lambda, JWJTLambdaDouble, 1e-30f, &stepSize);
	
	Matrix lambdaFloat = Matrix::Matrix(constraints.size());
	for (unsigned int i = 0; i < constraints.size(); i++)
	{
		lambdaFloat.setValue(i, lambda[i]);
	}

	Matrix Qhat = JT * lambdaFloat;

	for (unsigned int i = 0; i < pVector.size(); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			pVector[i]->m_Force[j] += Qhat.getValue(2 * i + j);
		}
	}

	free(lambda);	
}