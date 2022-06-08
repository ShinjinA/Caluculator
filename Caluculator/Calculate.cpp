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
	m_History(NULL),
	m_View1(0.0)
{

}

CCalculate::~CCalculate()
{

}

double CCalculate::ExecCalc(char Manipulator)
{
	m_View1 = 0.0;

	// 0~9のボタンが押された時
	if (Manipulator <= 9 && Manipulator >= 0)
	{
		// ベクターの最終要素に押された数字を追加
		m_ManipulationHistory.push_back(Manipulator);

		// 表示すべき値を計算
		for (int i = 0; i < m_ManipulationHistory.size(); ++i)
		{
			m_View1 += (double)m_ManipulationHistory[i] * (Exponentiation(10, (m_ManipulationHistory.size() - i - 1)));
		}
	}

	// C1ボタンが押された時の処理
	else if (Manipulator == 12)
	{
		for (; m_ManipulationHistory.size() != 0;)
		{
			m_ManipulationHistory.erase(m_ManipulationHistory.begin());
		}
	}

	// 数字以外のボタンが押された場合の処理。
	else
	{

	}

	return m_View1;
}

//void CCalculate::SetCCalculatePointer(CCalculate* CCalculatePointer)
//{
//	m_CalculatePointer = CCalculatePointer;
//}
//
//CCalculate* CCalculate::GetCCalculatePointer()
//{
//	return m_CalculatePointer;
//}

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
