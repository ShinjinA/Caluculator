#pragma once

#include <vector>
#include <iterator>

#define MAX_MANIPULATE_LENGTH 10

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
		// m_ManipulationHistoryTermination��0
	void ResetManipulationHistory();

	// m_ManipulationHistoryTermination���T�[�`���ăZ�b�g����B
	void SearchManipulationHistoryTermination();

	// m_ManipulationView1Termination���T�[�`���ăZ�b�g����B
	void SearchManipulationView1Termination();

	// m_ManipulationHistory��m_ManipulationTermination�ȍ~��0x00�ɂ���B
	void SetNullAfterHistoryTermination();

	// m_ManipulationView1��m_ManipulationTermination�ȍ~��0x00�ɂ���B
	void SetNullAfterView1Termination();

	// �����ꂽ�{�^����ۑ�����z��iView1�ɕ\���j
	// [1]�@�I�[����(0x00)
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