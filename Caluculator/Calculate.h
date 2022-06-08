#pragma once

#include <vector>

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

	//void SetCCalculatePointer(CCalculate* CCalculatePointer);

	//CCalculate* GetCCalculatePointer();

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

	// 押されたボタンを保存するベクター
	std::vector<char> m_ManipulationHistory;

	// View1に表示されるべき値
	double m_View1;

	// ヒストリーに表示されるべき文字列
	char* m_History;

};