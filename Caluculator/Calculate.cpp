#include "pch.h"
#include "Calculate.h"
#include "CalculatorDlg.h"

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
	m_ManipulationView1Termination(0),
	m_ManipulationHistoryTermination(0),
	m_LatestManipulator(0x00)
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
	if (Manipulator == 'L')
	{
		// m_ManipulationView1�����̏ꍇ
		if (m_ManipulationView1[0] == '-')
		{
			for (int i = 0; i < m_ManipulationView1Termination; ++i)
			{
				m_ManipulationView1[i] = m_ManipulationView1[i + 1];
			}
			--m_ManipulationView1Termination;
		}
		// m_ManipulationView1�����̏ꍇ 
		else
		{
			for (int i = 0; i < m_ManipulationView1Termination; ++i)
			{
				m_ManipulationView1[i + 1] = m_ManipulationView1[i];
			}
			m_ManipulationView1[0] = '-';
			++m_ManipulationView1Termination;
		}

		return m_ManipulationView1;
	}


	// "C"�������ꂽ�ꍇ
	if (Manipulator == 'C')
	{
		this->ResetManipulationView1();
		this->ResetManipulationHistory();
		m_CalcResult = 0;
		m_LatestManipulator = 0x00;

		return m_ManipulationView1;
	}

	// "��"�������ꂽ�ꍇ
	if (Manipulator == 'R')
	{
		double Result = 0.0; // root�v�Z����

		// �z��@���@double�ւ̕ϊ����������͐����̕������v�Z
		Result = sqrt(atof(&m_ManipulationView1[0]));

		this->ResetManipulationView1();

		// double ���@�z��ւ̕ϊ�����
		snprintf(m_ManipulationView1, MAX_MANIPULATE_LENGTH, "%.1f", Result);

		// m_ManipulationViewTermination�̐ݒ�
		for (int i = MAX_MANIPULATE_LENGTH; i >= 0; --i)
		{
			if (m_ManipulationView1[i] != 0x00)
			{
				m_ManipulationView1Termination = i + 1;
				break;
			}
		}
		return m_ManipulationView1;
	}

	// "��"�������ꂽ�ꍇ
	if (Manipulator == 'B')
	{
		if (m_ManipulationView1Termination > 0)
		{
			--m_ManipulationView1Termination;
		}

		m_ManipulationView1[m_ManipulationView1Termination] = 0x00;
		return m_ManipulationView1;
	}

	// "."�������ꂽ�ꍇ
	// ���߂ɉ����ꂽ�ꍇ�́A���͂𖳎�����B
	if (m_ManipulationView1Termination == 0 && Manipulator == '.')
	{
		return m_ManipulationView1;
	}

	// ����'.'��������Ă���΁A���͂𖳎�����B
	if (Manipulator == '.')
	{
		for (int i = 0; i < m_ManipulationView1Termination; ++i)
		{
			if (m_ManipulationView1[i] == '.')
			{
				return m_ManipulationView1;
			}
		}
	}

	// ���Z�q�������ꂽ�ꍇ
	if (Manipulator == 'A' || Manipulator == 'S' || Manipulator == 'M' || Manipulator == 'D' || Manipulator == 'E')
	{
		// �\���p�������`
		char ManipulatorDisplayed = 0x00;
		switch (Manipulator)
		{
		case 'A':
			ManipulatorDisplayed = '+';
			break;
		case 'S':
			ManipulatorDisplayed = '-';
			break;
		case 'M':
			ManipulatorDisplayed = '*';
			break;
		case 'D':
			ManipulatorDisplayed = '/';
			break;
		}

		// View1�ɉ������͂���Ă��Ȃ��ꍇ
		if (m_ManipulationView1Termination == 0)
		{
			// "="�������ꂽ��
			if (Manipulator == 'E')
			{
				// double ���@�z��ւ̕ϊ�����
				snprintf(m_ManipulationView1, MAX_MANIPULATE_LENGTH, "%.20f", m_CalcResult);
				this->ResetManipulationHistory();

				this->SearchManipulationView1Termination();

				this->SetNullAfterView1Termination();

				this->SearchManipulationView1Termination();

				return m_ManipulationView1;
			}

			// "="�ȊO�̉��Z�q�������ꂽ�ꍇ
			else
			{
				m_LatestManipulator = Manipulator;
				m_ManipulationHistory[m_ManipulationHistoryTermination + 1] = ManipulatorDisplayed;
			}
			return m_ManipulationView1;
		}

		// History�ɉ����\�����Ȃ��ꍇ
		if (m_ManipulationHistoryTermination == 0)
		{
			// ���߂ɉ����ꂽ�ꍇ�́A�v�Z���ʂɑ����B
			m_CalcResult = atof(&m_ManipulationView1[0]);

			// View1�����̂܂�History�ɃR�s�[
			this->ManipulationView1ToHistory();
			this->ResetManipulationView1();

			// m_ManipulationHistory�̐K�ɉ��Z�q��t�^
			// ���₷�����邽��
			m_ManipulationHistory[m_ManipulationHistoryTermination] = ' ';
			m_ManipulationHistory[m_ManipulationHistoryTermination + 1] = ManipulatorDisplayed;

			m_LatestManipulator = Manipulator;

			return m_ManipulationView1;
		}

		// "+"���Z�b�g����Ă��鎞
		if (m_LatestManipulator == 'A')
		{
			m_CalcResult += atof(&m_ManipulationView1[0]);
		}

		// "-"���Z�b�g����Ă��鎞
		else if (m_LatestManipulator == 'S')
		{
			m_CalcResult -= atof(&m_ManipulationView1[0]);
		}

		// "�~"���Z�b�g����Ă��鎞
		else if (m_LatestManipulator == 'M')
		{
			m_CalcResult *= atof(&m_ManipulationView1[0]);
		}

		// "��"���Z�b�g����Ă��鎞
		else if (m_LatestManipulator == 'D')
		{
			m_CalcResult /= atof(&m_ManipulationView1[0]);
		}

		// ��U�z���ɂ���
		this->ResetManipulationView1();
		this->ResetManipulationHistory();

		// double ���@�z��ւ̕ϊ�����
		snprintf(m_ManipulationHistory, MAX_MANIPULATE_LENGTH, "%.20f", m_CalcResult);

		this->SearchManipulationHistoryTermination();

		this->SetNullAfterHistoryTermination();

		this->SearchManipulationHistoryTermination();

		m_LatestManipulator = Manipulator;

		// "="�������ꂽ��
		if (Manipulator == 'E')
		{
			this->ManipulationHistoryToView1();
			this->ResetManipulationHistory();

			return m_ManipulationView1;
		}

		// "="�ȊO�̉��Z�q�������ꂽ��
		else
		{
			// m_ManipulationHistory�̐K�ɉ��Z�q��t�^
			// ���₷�����邽��
			m_ManipulationHistory[m_ManipulationHistoryTermination] = ' ';
			m_ManipulationHistory[m_ManipulationHistoryTermination + 1] = ManipulatorDisplayed;

		}
		return m_ManipulationView1;
	}

	// 0�����߂ɉ����ꂽ�ꍇ
	if (m_ManipulationView1Termination == 1 && m_ManipulationView1[0] == '0')
	{
		// ���ڈȍ~��0���͖͂�������
		if (Manipulator == '0')
		{
			return m_ManipulationView1;
		}
		// 0�ȊO�̐����������ꂽ�Ƃ��ɂ́A���߂ɓ��͂���0���폜����B
		else if (Manipulator - 0x31 >= 0 && Manipulator - 0x39 <= 0)
		{
			--m_ManipulationView1Termination;
		}
	}

	// �z��̌��ɉ����ꂽ�{�^���̐�����ǉ����Ă���
	if (m_ManipulationView1Termination < MAX_MANIPULATE_LENGTH)
	{
		m_ManipulationView1[m_ManipulationView1Termination] = Manipulator;
		++m_ManipulationView1Termination;
	}
	return m_ManipulationView1;
}

char* CCalculate::GetView1()
{
	return m_ManipulationView1;
}

char* CCalculate::GetHistory()
{
	return m_ManipulationHistory;
}

int CCalculate::GetView1Size()
{
	return m_ManipulationView1Termination;
}

void CCalculate::ManipulationView1ToHistory()
{
	this->ResetManipulationHistory();
	m_ManipulationHistoryTermination = m_ManipulationView1Termination;
	for (int i = 0; i < MAX_MANIPULATE_LENGTH; ++i)
	{
		m_ManipulationHistory[i] = m_ManipulationView1[i];
	}
}

void CCalculate::ManipulationHistoryToView1()
{
	this->ResetManipulationView1();
	m_ManipulationView1Termination = m_ManipulationHistoryTermination;
	for (int i = 0; i < MAX_MANIPULATE_LENGTH; ++i)
	{
		m_ManipulationView1[i] = m_ManipulationHistory[i];
	}
}

void CCalculate::ResetManipulationView1()
{
	m_ManipulationView1Termination = 0;
	for (int i = 0; i < MAX_MANIPULATE_LENGTH; ++i)
	{
		m_ManipulationView1[i] = 0x00;
	}
}

void CCalculate::ResetManipulationHistory()
{
	m_ManipulationHistoryTermination = 0;
	for (int i = 0; i < MAX_MANIPULATE_LENGTH + 2; ++i)
	{
		m_ManipulationHistory[i] = 0x00;
	}
}

void CCalculate::SearchManipulationHistoryTermination()
{
	// m_ManipulationHistoryTermination�̐ݒ�
	for (int i = MAX_MANIPULATE_LENGTH; i >= 0; --i)
	{
		if (m_ManipulationHistory[i] != 0x00 && m_ManipulationHistory[i] != 0x30)
		{
			m_ManipulationHistoryTermination = i + 1;
			break;
		}
	}
}

void CCalculate::SearchManipulationView1Termination()
{
	// m_ManipulationView1Termination�̐ݒ�
	for (int i = MAX_MANIPULATE_LENGTH; i >= 0; --i)
	{
		if (m_ManipulationView1[i] != 0x00 && m_ManipulationView1[i] != 0x30)
		{
			m_ManipulationView1Termination = i + 1;
			break;
		}
	}
}

void CCalculate::SetNullAfterHistoryTermination()
{
	int ManipulationTerminationBuf = m_ManipulationHistoryTermination;
	if (m_ManipulationHistory[m_ManipulationHistoryTermination - 1] == '.')
	{
		--ManipulationTerminationBuf;
	}
	for (int i = ManipulationTerminationBuf; i < MAX_MANIPULATE_LENGTH; ++i)
	{
		m_ManipulationHistory[i] = 0x00;
	}
}

void CCalculate::SetNullAfterView1Termination()
{
	int ManipulationTerminationBuf = m_ManipulationView1Termination;
	if (m_ManipulationView1[m_ManipulationView1Termination - 1] == '.')
	{
		--ManipulationTerminationBuf;
	}
	for (int i = ManipulationTerminationBuf; i < MAX_MANIPULATE_LENGTH; ++i)
	{
		m_ManipulationView1[i] = 0x00;
	}
}
