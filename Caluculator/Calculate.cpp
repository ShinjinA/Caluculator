#include "pch.h"
#include "Caluculate.h"

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
