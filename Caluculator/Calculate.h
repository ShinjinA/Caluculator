#pragma once

#include <vector>
#include <iterator>

#define MAX_MANIPULATE_LENGHT 20

/// <summary>
/// 演算子
/// </summary>
enum EOperator
{
	Add = 0,
	Sub,
	Mul,
	Div,
};

// シングルトンクラスとして実装したい、後々

class CCalculate
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CCalculate();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CCalculate();

	// 入力されたボタンに応じて、計算結果を返す。
	double ExecCalc(char Manipulator);

	int SetView1(char Manipulator);

	char* GetView1();

	int GetView1Size();

	// View1のクリア（クリアボタン）
	bool ClearView1();

private:

	/// <summary>
	/// 演算実行
	/// </summary>
	/// <param name="dNum1">オペランド1</param>
	/// <param name="dNum2">オペランド2</param>
	/// <param name="eOperator">演算子</param>
	/// <returns>計算結果</returns>
	double ExecCaluc(double dNum1, double dNum2, EOperator eOperator);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="Num1"></param>
	/// <param name="Num2"></param>
	/// <returns></returns>
	double Add(double Num1, double Num2);

	// 押されたボタンを保存する配列（View1に表示）
	char m_ManipulationView1[MAX_MANIPULATE_LENGHT];

	// 配列の入力されたボタンの終端
	char m_ManipulationViewTermination;

	// 押されたボタンを保存する配列（History）
	char m_ManipulationHistory[MAX_MANIPULATE_LENGHT];

	// 計算結果
	long double m_CalcResult;

	// m_ManipulationView1をすべて0x00にリセット
	// m_ManipulationViewTerminationを0
	void ResetManipulationView1();

};