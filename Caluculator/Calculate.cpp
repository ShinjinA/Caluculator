#include "pch.h"
#include "Calculate.h"
#include "CalculatorDlg.h"

// BaseのExponent乗を返す
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
	// 何もしない
}

CCalculate::~CCalculate()
{
	// 何もしない
}

double CCalculate::ExecCalc(char Manipulator)
{
	return 0.0;
}

char* CCalculate::SetView1(char Manipulator)
{
	// "C"が押された場合
	if (Manipulator == 'C')
	{
		this->ResetManipulationView1();
		this->ResetManipulationHistory();
		m_CalcResult = 0;
		m_LatestManipulator = 0x00;

		return m_ManipulationView1;
	}

	// "√"が押された場合
	if (Manipulator == 'R')
	{
		double Result = 0.0; // root計算結果

		// 配列　→　doubleへの変換処理＆入力数字の平方根計算
		Result = sqrt(atof(&m_ManipulationView1[0]));

		this->ResetManipulationView1();

		// double →　配列への変換処理
		snprintf(m_ManipulationView1, MAX_MANIPULATE_LENGTH, "%f", Result);

		// m_ManipulationViewTerminationの設定
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

	// "←"が押された場合
	if (Manipulator == 'B')
	{
		if (m_ManipulationView1Termination > 0)
		{
			--m_ManipulationView1Termination;
		}

		m_ManipulationView1[m_ManipulationView1Termination] = 0x00;
		return m_ManipulationView1;
	}

	// "."が押された場合
	// 初めに押された場合は、入力を無視する。
	if (m_ManipulationView1Termination == 0 && Manipulator == '.')
	{
		return m_ManipulationView1;
	}

	// 既に'.'が押されていれば、入力を無視する。
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

	// 演算子が押された場合
	if (Manipulator == 'A' || Manipulator == 'S' || Manipulator == 'M' || Manipulator == 'D' || Manipulator == 'E')
	{
		// Historyに何も表示がない場合
		if (m_ManipulationHistoryTermination == 0)
		{
			// 初めに押された場合は、計算結果に足す。
			m_CalcResult = atof(&m_ManipulationView1[0]);

			// View1をそのままHistoryにコピー
			this->ManipulationView1ToHistory();
			this->ResetManipulationView1();

			// m_ManipulationHistoryの尻に演算子を付与
			// 見やすくするため
			m_ManipulationHistory[m_ManipulationHistoryTermination] = ' ';
			m_ManipulationHistory[m_ManipulationHistoryTermination + 1] = Manipulator;

			m_LatestManipulator = Manipulator;

			return m_ManipulationView1;
		}

		// "+"が押された時
		if (m_LatestManipulator == 'A')
		{
			m_CalcResult += atof(&m_ManipulationView1[0]);
		}

		// "-"が押された時
		if (m_LatestManipulator == 'S')
		{
			m_CalcResult -= atof(&m_ManipulationView1[0]);
		}

		// "×"が押された時
		if (m_LatestManipulator == 'M')
		{
			m_CalcResult *= atof(&m_ManipulationView1[0]);
		}

		// "÷"が押された時
		if (m_LatestManipulator == 'D')
		{
			m_CalcResult /= atof(&m_ManipulationView1[0]);
		}

		// 一旦配列空にする
		this->ResetManipulationView1();
		this->ResetManipulationHistory();

		// double →　配列への変換処理
		snprintf(m_ManipulationHistory, MAX_MANIPULATE_LENGTH, "%f", m_CalcResult);

		// m_ManipulationHistoryTerminationの設定
		for (int i = MAX_MANIPULATE_LENGTH; i >= 0; --i)
		{
			if (m_ManipulationHistory[i] != 0x00)
			{
				m_ManipulationHistoryTermination = i + 1;
				break;
			}
		}

		m_LatestManipulator = Manipulator;
		
		// "="が押された時
		if (Manipulator == 'E')
		{
			this->ManipulationHistoryToView1();
			this->ResetManipulationHistory();

			return m_ManipulationView1;
		}

		// m_ManipulationHistoryの尻に演算子を付与
		// 見やすくするため
		m_ManipulationHistory[m_ManipulationHistoryTermination] = ' ';
		m_ManipulationHistory[m_ManipulationHistoryTermination + 1] = Manipulator;

		return m_ManipulationView1;
	}

	// 0が初めに押された場合
	if (m_ManipulationView1Termination == 1 && m_ManipulationView1[0] == '0')
	{
		// 二回目以降の0入力は無視する
		if (Manipulator == '0')
		{
			return m_ManipulationView1;
		}
		// 0以外の数字が押されたときには、初めに入力した0を削除する。
		else if (Manipulator - 0x31 >= 0 && Manipulator - 0x39 <= 0)
		{
			--m_ManipulationView1Termination;
		}
	}

	// 配列の後ろに押されたボタンの数字を追加していく
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

/// <summary>
/// 演算実行
/// </summary>
/// <param name="dNum1">オペランド1</param>
/// <param name="dNum2">オペランド2</param>
/// <param name="eOperator">演算子</param>
/// <returns>計算結果</returns>
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
