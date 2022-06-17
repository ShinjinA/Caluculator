#pragma once

#include <vector>
#include <iterator>

#define MAX_MANIPULATE_LENGTH 10

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

enum EManipulator
{

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

	// m_ManipulationView1に数字を追加する
	char* SetView1(char Manipulator);

	// m_ManipulationView1のGet関数
	char* GetView1();

	// m_ManipulationHistoryのGet関数
	char* GetHistory();

	// m_ManipulationViewTerminationのGet関数
	int GetView1Size();

private:

	/// <summary>
	/// m_ManipulationView1をm_ManipulationHistoryにコピーする
	/// </summary>
	void ManipulationView1ToHistory();

	/// <summary>
	/// m_ManipulationHistoryをm_ManipulationView1にコピーする
	/// </summary>
	void ManipulationHistoryToView1();

	// m_ManipulationView1をすべて0x00にリセット
	// m_ManipulationViewTerminationを0
	void ResetManipulationView1();

	// m_ManipulationView1をすべて0x00にリセット
		// m_ManipulationHistoryTerminationを0
	void ResetManipulationHistory();

	// m_ManipulationHistoryTerminationをサーチしてセットする。
	void SearchManipulationHistoryTermination();

	// m_ManipulationView1Terminationをサーチしてセットする。
	void SearchManipulationView1Termination();

	// m_ManipulationHistoryのm_ManipulationTermination以降を0x00にする。
	void SetNullAfterHistoryTermination();

	// m_ManipulationView1のm_ManipulationTermination以降を0x00にする。
	void SetNullAfterView1Termination();

	// 押されたボタンを保存する配列（View1に表示）
	// [1]　終端文字(0x00)
	char m_ManipulationView1[MAX_MANIPULATE_LENGTH + 1];

	// 押されたボタンを保存する配列（History）
	// [1]　終端文字(0x00)
	// [2]　演算子記憶用
	char m_ManipulationHistory[MAX_MANIPULATE_LENGTH + 3];

	// 計算結果
	long double m_CalcResult;

	// m_ManipulationView1に入力された数字の要素数
	char m_ManipulationView1Termination;

	// m_ManipulationHistoryに格納された数字の要素数
	char m_ManipulationHistoryTermination;

	// 直前に押された演算子
	char m_LatestManipulator;

};