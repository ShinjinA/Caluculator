#pragma once

#include <vector>
#include <iterator>

#define MAX_MANIPULATE_LENGHT 20

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

	int SetView1(char Manipulator);

	char* GetView1();

	int GetView1Size();

	// View1�̃N���A�i�N���A�{�^���j
	bool ClearView1();

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

	// �����ꂽ�{�^����ۑ�����z��iView1�ɕ\���j
	char m_ManipulationView1[MAX_MANIPULATE_LENGHT];

	// �z��̓��͂��ꂽ�{�^���̏I�[
	char m_ManipulationViewTermination;

	// �����ꂽ�{�^����ۑ�����z��iHistory�j
	char m_ManipulationHistory[MAX_MANIPULATE_LENGHT];

	// �v�Z����
	long double m_CalcResult;

	// m_ManipulationView1�����ׂ�0x00�Ƀ��Z�b�g
	// m_ManipulationViewTermination��0
	void ResetManipulationView1();

};