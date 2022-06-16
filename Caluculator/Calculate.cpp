#include "pch.h"
#include "Calculate.h"

// Base��Exponent���Ԃ�
int Exponentiation(int Base, int Exponent)
{
	int Result = 1;
	for (int i = 0; i < Exponent; ++i)
	{
		Result *= Base;
	}
	return Result;
}

CCalculate::CCalculate() :
	m_ManipulationView1{ 0x00 },
	m_ManipulationHistory{ 0x00 },
	m_ManipulationViewTermination(0)
{
	// �������Ȃ�
}

CCalculate::~CCalculate()
{
	// �������Ȃ�
}

double CCalculate::ExecCalc(char Manipulator)
{
	return 0.0;
}

char* CCalculate::SetView1(char Manipulator)
{
	// "��"�������ꂽ���̏ꍇ
	if (Manipulator == 'R')
	{
		double Result = 0.0; // root�v�Z����

		// ���͐����̕������v�Z
		Result = sqrt(atof(&m_ManipulationView1[0]));

		this->ResetManipulationView1();

		// double ���@�z��ւ̕ϊ�����
		snprintf(m_ManipulationView1,MAX_MANIPULATE_LENGTH,"%f",Result);

		return m_ManipulationView1;
	}

	// "��"�������ꂽ���̏ꍇ
	if (Manipulator == 'B')
	{
		if (m_ManipulationViewTermination > 0)
		{
			--m_ManipulationViewTermination;
		}

		m_ManipulationView1[m_ManipulationViewTermination] = 0x00;
		return m_ManipulationView1;
	}
	// �����_�������ꂽ�ꍇ
	// ���߂ɉ����ꂽ�ꍇ�́A���͂𖳎�����B
	if (m_ManipulationViewTermination == 0 && Manipulator == '.')
	{
		return m_ManipulationView1;
	}

	// ����'.'��������Ă���΁A���͂𖳎�����B
	if (Manipulator == '.')
	{
		for (int i = 0; i < m_ManipulationViewTermination; ++i)
		{
			if (m_ManipulationView1[i] == '.')
			{
				return m_ManipulationView1;
			}
		}
	}

	// 0�����߂ɉ����ꂽ�ꍇ
	if (m_ManipulationViewTermination == 1 && m_ManipulationView1[0] == '0')
	{
		// ���ڈȍ~��0���͖͂�������
		if (Manipulator == '0')
		{
			return m_ManipulationView1;
		}
		// 0�ȊO�̐����������ꂽ�Ƃ��ɂ́A���߂ɓ��͂���0���폜����B
		else if (Manipulator - 0x31 >= 0 && Manipulator - 0x39 <= 0)
		{
			--m_ManipulationViewTermination;
		}
	}

	// �z��̌��ɉ����ꂽ�{�^���̐�����ǉ����Ă���
	if (m_ManipulationViewTermination < MAX_MANIPULATE_LENGTH)
	{
		m_ManipulationView1[m_ManipulationViewTermination] = Manipulator;
		++m_ManipulationViewTermination;
	}

	return m_ManipulationView1;
}

char* CCalculate::GetView1()
{
	return m_ManipulationView1;
}

int CCalculate::GetView1Size()
{
	return m_ManipulationViewTermination;
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
	for (int i = 0; i < MAX_MANIPULATE_LENGTH; ++i)
	{
		m_ManipulationView1[i] = 0x00;
	}
}
