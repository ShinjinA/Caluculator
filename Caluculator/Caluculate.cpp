#include "pch.h"
#include "Caluculate.h"

/// <summary>
/// 演算実行
/// </summary>
/// <param name="dNum1">オペランド1</param>
/// <param name="dNum2">オペランド2</param>
/// <param name="eOperator">演算子</param>
/// <returns>計算結果</returns>
double CCaluculate::ExecCaluc(double dNum1, double dNum2, EOperator eOperator)
{
	switch (eOperator)
		case EOperator::add:
			return Add(dNum1, dNum2);
}

double CCaluculate::Add(double Num1, double Num2)
{
	return Num1 + Num2;
}
