#pragma once

/// <summary>
/// ���Z�q
/// </summary>
enum EOperator
{
	Add = 0,
	Sub,
	Mul,
	Div,
};

class CCalculate
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CCalculate();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CCalculate();

	/// <summary>
	/// ���Z���s
	/// </summary>
	/// <param name="dNum1">�I�y�����h1</param>
	/// <param name="dNum2">�I�y�����h2</param>
	/// <param name="eOperator">���Z�q</param>
	/// <returns>�v�Z����</returns>
	double ExecCaluc(double dNum1, double dNum2, EOperator eOperator);

private:

	/// <summary>
	/// 
	/// </summary>
	/// <param name="Num1"></param>
	/// <param name="Num2"></param>
	/// <returns></returns>
	double Add(double Num1, double Num2);

};