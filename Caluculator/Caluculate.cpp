#include "pch.h"
#include "Caluculate.h"

/// <summary>
/// ���Z���s
/// </summary>
/// <param name="dNum1">�I�y�����h1</param>
/// <param name="dNum2">�I�y�����h2</param>
/// <param name="eOperator">���Z�q</param>
/// <returns>�v�Z����</returns>
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
