#pragma once

/// <summary>
/// ���Z�q
/// </summary>
enum EOperator
{ 
	add= 0,
	sub,
	mul,
	div,
};

class CCaluculate
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CCaluculate();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CCaluculate();

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