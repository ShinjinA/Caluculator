#pragma once

#include <vector>
#include <iterator>

#define MAX_MANIPULATE_LENGTH 20

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

enum EManipulator
{

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

	// m_ManipulationView1�ɐ�����ǉ�����
	char* SetView1(char Manipulator);

	// m_ManipulationView1��Get�֐�
	char* GetView1();

	// m_ManipulationHistory��Get�֐�
	char* GetHistory();

	// m_ManipulationViewTermination��Get�֐�
	int GetView1Size();

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

	/// <summary>
	/// m_ManipulationView1��m_ManipulationHistory�ɃR�s�[����
	/// </summary>
	void ManipulationView1ToHistory();

	/// <summary>
	/// m_ManipulationHistory��m_ManipulationView1�ɃR�s�[����
	/// </summary>
	void ManipulationHistoryToView1();

	// m_ManipulationView1�����ׂ�0x00�Ƀ��Z�b�g
	// m_ManipulationViewTermination��0
	void ResetManipulationView1();

	// m_ManipulationView1�����ׂ�0x00�Ƀ��Z�b�g
	void ResetManipulationHistory();

	// �����ꂽ�{�^����ۑ�����z��iView1�ɕ\���j
	char m_ManipulationView1[MAX_MANIPULATE_LENGTH + 1];

	// �����ꂽ�{�^����ۑ�����z��iHistory�j
	// [1]�@�I�[����(0x00)
	// [2]�@���Z�q�L���p
	char m_ManipulationHistory[MAX_MANIPULATE_LENGTH + 3];

	// �v�Z����
	long double m_CalcResult;

	// m_ManipulationView1�ɓ��͂��ꂽ�����̗v�f��
	char m_ManipulationView1Termination;

	// m_ManipulationHistory�Ɋi�[���ꂽ�����̗v�f��
	char m_ManipulationHistoryTermination;

	// ���O�ɉ����ꂽ���Z�q
	char m_LatestManipulator;

};