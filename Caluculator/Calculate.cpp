#include "pch.h"
#include "Calculate.h"

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
	m_ManipulationViewTermination(0)
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
	// "√"が押された時の場合
	if (Manipulator == 'R')
	{
		double Result = 0.0; // root計算結果

		// 入力数字の平方根計算
		Result = sqrt(atof(&m_ManipulationView1[0]));

		this->ResetManipulationView1();

		// double →　配列への変換処理
		snprintf(m_ManipulationView1,MAX_MANIPULATE_LENGTH,"%f",Result);

		return m_ManipulationView1;
	}

	// "←"が押された時の場合
	if (Manipulator == 'B')
	{
		if (m_ManipulationViewTermination > 0)
		{
			--m_ManipulationViewTermination;
		}

		m_ManipulationView1[m_ManipulationViewTermination] = 0x00;
		return m_ManipulationView1;
	}
	// 小数点が押された場合
	// 初めに押された場合は、入力を無視する。
	if (m_ManipulationViewTermination == 0 && Manipulator == '.')
	{
		return m_ManipulationView1;
	}

	// 既に'.'が押されていれば、入力を無視する。
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

	// 0が初めに押された場合
	if (m_ManipulationViewTermination == 1 && m_ManipulationView1[0] == '0')
	{
		// 二回目以降の0入力は無視する
		if (Manipulator == '0')
		{
			return m_ManipulationView1;
		}
		// 0以外の数字が押されたときには、初めに入力した0を削除する。
		else if (Manipulator - 0x31 >= 0 && Manipulator - 0x39 <= 0)
		{
			--m_ManipulationViewTermination;
		}
	}

	// 配列の後ろに押されたボタンの数字を追加していく
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

void CCalculate::ResetManipulationView1()
{
	m_ManipulationViewTermination = 0;
	for (int i = 0; i < MAX_MANIPULATE_LENGTH; ++i)
	{
		m_ManipulationView1[i] = 0x00;
	}
}
