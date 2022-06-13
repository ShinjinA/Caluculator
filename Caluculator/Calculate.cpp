#include "pch.h"
#include "Calculate.h"

int Exponentiation(int Base, int Exponent)
{
	int Result = 1;
	for (int i = 0; i < Exponent; ++i)
	{
		Result *= 10;
	}
	return Result;
}

CCalculate::CCalculate() :
	m_ManipulationView1{ 0x00 },
	m_ManipulationHistory{ 0x00 },
	m_ManipulationViewTermination(0)
{

}

CCalculate::~CCalculate()
{

}

double CCalculate::ExecCalc(char Manipulator)
{
	//m_CalcResult = 0.0;

	//// 0~9�̃{�^���������ꂽ��
	//if (Manipulator <= 9 && Manipulator >= 0)
	//{
	//	// �x�N�^�[�̍ŏI�v�f�ɉ����ꂽ������ǉ�
	//	m_ManipulationHistory.push_back(Manipulator);

	//	// �\�����ׂ��l���v�Z
	//	for (int i = 0; i < m_ManipulationHistory.size(); ++i)
	//	{
	//		m_CalcResult += (double)m_ManipulationHistory[i] * (Exponentiation(10, (m_ManipulationHistory.size() - i - 1)));
	//	}
	//}

	// C1�{�^���������ꂽ���̏���
	if (Manipulator == 12)
	{
	

	}

	// �����ȊO�̃{�^���������ꂽ�ꍇ�̏����B
	else
	{

	}

	return m_CalcResult;
}

int CCalculate::SetView1(char Manipulator)
{
	if (m_ManipulationViewTermination < MAX_MANIPULATE_LENGHT)
	{
		m_ManipulationView1[m_ManipulationViewTermination] = Manipulator;
		++m_ManipulationViewTermination;
	}
	return m_ManipulationViewTermination;
}

char* CCalculate::GetView1()
{
	return m_ManipulationView1;
}

int CCalculate::GetView1Size()
{
	return m_ManipulationViewTermination;
}

bool CCalculate::ClearView1()
{

	return false;
}


/// <summary>
/// ���Z���s
/// </summary>
/// <param name="dNum1">�I�y�����h1</param>
/// <param name="dNum2">�I�y�����h2</param>
/// <param name="eOperator">���Z�q</param>
/// <returns>�v�Z����</returns>
double CCalculate::ExecCaluc(double dNum1, double dNum2, EOperator eOperator)
{
	switch (eOperator)
		case EOperator::Add:
			return Add(dNum1, dNum2);
}

double CCalculate::Add(double Num1, double Num2)
{
	return Num1 + Num2;
}

void CCalculate::ResetManipulationView1()
{
	m_ManipulationViewTermination = 0;
	for (int i = 0; i < MAX_MANIPULATE_LENGHT; ++i)
	{
		m_ManipulationView1[i] = 0x00;
	}
}
