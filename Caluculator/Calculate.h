#pragma once

#include <vector>

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

// �V���O���g���N���X�Ƃ��Ď����������A��X

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

	// ���͂��ꂽ�{�^���ɉ����āA�v�Z���ʂ�Ԃ��B
	double ExecCalc(char Manipulator);

	//void SetCCalculatePointer(CCalculate* CCalculatePointer);

	//CCalculate* GetCCalculatePointer();

private:

	/// <summary>
	/// ���Z���s
	/// </summary>
	/// <param name="dNum1">�I�y�����h1</param>
	/// <param name="dNum2">�I�y�����h2</param>
	/// <param name="eOperator">���Z�q</param>
	/// <returns>�v�Z����</returns>
	double ExecCaluc(double dNum1, double dNum2, EOperator eOperator);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="Num1"></param>
	/// <param name="Num2"></param>
	/// <returns></returns>
	double Add(double Num1, double Num2);

	// �����ꂽ�{�^����ۑ�����x�N�^�[
	std::vector<char> m_ManipulationHistory;

	// View1�ɕ\�������ׂ��l
	double m_View1;

	// �q�X�g���[�ɕ\�������ׂ�������
	char* m_History;

};