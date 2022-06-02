#pragma once

/// <summary>
/// 演算子
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
	/// コンストラクタ
	/// </summary>
	CCaluculate();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CCaluculate();

	/// <summary>
	/// 演算実行
	/// </summary>
	/// <param name="dNum1">オペランド1</param>
	/// <param name="dNum2">オペランド2</param>
	/// <param name="eOperator">演算子</param>
	/// <returns>計算結果</returns>
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