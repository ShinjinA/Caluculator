#include "pch.h"
#include "Calculate.h"
#include "CalculatorDlg.h"

// BaseのExponent乗を返す
int Exponentiation(int Base, int Exponent)
{
	int Result = 1;
	for (int i = 0; i < Exponent; ++i)
	{
		Result *= Base;
	}
	return Result;
}

CCalculate::CCalculate() :
	m_ManipulationView1{ 0x00 },
	m_ManipulationHistory{ 0x00 },
	m_ManipulationView1Termination(0),
	m_ManipulationHistoryTermination(0),
	m_LatestManipulator(0x00),
	m_CalcResult(0.0),
	m_Errorflg(false)
{
	// 何もしない
}

CCalculate::~CCalculate()
{
	// 何もしない
}

double CCalculate::ExecCalc(char Manipulator)
{
	return 0.0;
}

char* CCalculate::SetView1(char Manipulator)
{
	// "C"が押された場合
	if (Manipulator == 'C')
	{
		this->ResetManipulationView1();
		this->ResetManipulationHistory();
		m_CalcResult = 0;
		m_LatestManipulator = 0x00;
		m_Errorflg = false;

		return m_ManipulationView1;
	}

	// エラーフラグがfalseの時のみ受け付ける
	if (!m_Errorflg)
	{
		// "±"が押された場合
		if (Manipulator == 'L')
		{
			// m_ManipulationView1が負の場合
			if (m_ManipulationView1[0] == '-')
			{
				for (int i = 0; i < m_ManipulationView1Termination; ++i)
				{
					m_ManipulationView1[i] = m_ManipulationView1[i + 1];
				}
				--m_ManipulationView1Termination;
			}
			// m_ManipulationView1が正の場合 
			else
			{
				for (int i = m_ManipulationView1Termination; i >= 0; --i)
				{
					m_ManipulationView1[i + 1] = m_ManipulationView1[i];
				}
				m_ManipulationView1[0] = '-';
				++m_ManipulationView1Termination;
			}

			return m_ManipulationView1;
		}

		// "√"が押された場合
		else if (Manipulator == 'R')
		{
			// m_ManipulationView1が空の場合
			if (m_ManipulationView1Termination == 0)
			{
				return m_ManipulationView1;
			}

			// m_ManipulationView1が負の場合
			else if (m_ManipulationView1[0] == '-')
			{
				this->ResetManipulationView1();
				snprintf(m_ManipulationView1, 4, "%s", "Err");
				m_Errorflg = true;
			}

			// 正常実行
			else
			{
				double Result = 0.0; // root計算結果

				// 配列　→　doubleへの変換処理＆入力数字の平方根計算
				Result = sqrt(atof(&m_ManipulationView1[0]));

				this->ResetManipulationView1();

				// double →　配列への変換処理
				snprintf(m_ManipulationView1, MAX_MANIPULATE_LENGTH, "%f", Result);

				this->SearchManipulationView1Termination();
				this->SetNullAfterView1Termination();
				this->SearchManipulationView1Termination();
			}

			return m_ManipulationView1;
		}

		// "←"が押された場合
		else if (Manipulator == 'B')
		{
			if (m_ManipulationView1Termination > 0)
			{
				--m_ManipulationView1Termination;
			}

			m_ManipulationView1[m_ManipulationView1Termination] = 0x00;
			return m_ManipulationView1;
		}

		// "."が押された場合
		else if (Manipulator == '.')
		{
			// 初めに押された場合は、入力を無視する。
			if (m_ManipulationView1Termination == 0)
			{
				return m_ManipulationView1;
			}

			// 既に'.'が押されていれば、入力を無視する。
			else
			{
				for (int i = 0; i < m_ManipulationView1Termination; ++i)
				{
					if (m_ManipulationView1[i] == '.')
					{
						return m_ManipulationView1;
					}
				}
			}
		}

		// 演算子が押された場合
		else if (Manipulator == 'A' || Manipulator == 'S' || Manipulator == 'M' || Manipulator == 'D' || Manipulator == 'E')
		{
			// 表示用文字を定義
			char ManipulatorDisplayed = 0x00;
			switch (Manipulator)
			{
			case 'A':
				ManipulatorDisplayed = '+';
				break;
			case 'S':
				ManipulatorDisplayed = '-';
				break;
			case 'M':
				ManipulatorDisplayed = '*';
				break;
			case 'D':
				ManipulatorDisplayed = '/';
				break;
			}

			// View1に何も入力されていない場合
			if (m_ManipulationView1Termination == 0)
			{
				// "="が押された時
				// m_CalcResultをView1に表示する
				if (Manipulator == 'E')
				{
					// double →　配列への変換処理
					snprintf(m_ManipulationView1, MAX_MANIPULATE_LENGTH, "%f", m_CalcResult);
					this->ResetManipulationHistory();

					this->SearchManipulationView1Termination();

					this->SetNullAfterView1Termination();

					this->SearchManipulationView1Termination();

					return m_ManipulationView1;
				}

				// "="以外の演算子が押された場合
				else
				{
					m_LatestManipulator = Manipulator;
					m_ManipulationHistory[m_ManipulationHistoryTermination + 1] = ManipulatorDisplayed;
				}
				return m_ManipulationView1;
			}

			// Historyに何も表示がない場合
			if (m_ManipulationHistoryTermination == 0)
			{
				if (Manipulator != 'E')
				{
					// 初めに押された場合は、計算結果に足す。
					m_CalcResult = atof(&m_ManipulationView1[0]);

					// View1をそのままHistoryにコピー
					this->ManipulationView1ToHistory();
					this->ResetManipulationView1();

					// m_ManipulationHistoryの尻に演算子を付与
					// 見やすくするため
					m_ManipulationHistory[m_ManipulationHistoryTermination] = ' ';
					m_ManipulationHistory[m_ManipulationHistoryTermination + 1] = ManipulatorDisplayed;

					m_LatestManipulator = Manipulator;
				}
				return m_ManipulationView1;
			}

			// "+"がセットされている時
			if (m_LatestManipulator == 'A')
			{
				m_CalcResult += atof(&m_ManipulationView1[0]);
			}

			// "-"がセットされている時
			else if (m_LatestManipulator == 'S')
			{
				m_CalcResult -= atof(&m_ManipulationView1[0]);
			}

			// "×"がセットされている時
			else if (m_LatestManipulator == 'M')
			{
				m_CalcResult *= atof(&m_ManipulationView1[0]);
			}

			// "÷"がセットされている時
			else if (m_LatestManipulator == 'D')
			{
				m_CalcResult /= atof(&m_ManipulationView1[0]);
			}

			// 一旦配列空にする
			this->ResetManipulationView1();
			this->ResetManipulationHistory();

			// double →　配列への変換処理
			snprintf(m_ManipulationHistory, MAX_MANIPULATE_LENGTH, "%f", m_CalcResult);

			this->SearchManipulationHistoryTermination();

			this->SetNullAfterHistoryTermination();

			this->SearchManipulationHistoryTermination();

			m_LatestManipulator = Manipulator;

			// "="が押された時
			if (Manipulator == 'E')
			{
				this->ManipulationHistoryToView1();
				this->ResetManipulationHistory();

				return m_ManipulationView1;
			}

			// "="以外の演算子が押された時
			else
			{
				// m_ManipulationHistoryの尻に演算子を付与
				// 見やすくするため
				m_ManipulationHistory[m_ManipulationHistoryTermination] = ' ';
				m_ManipulationHistory[m_ManipulationHistoryTermination + 1] = ManipulatorDisplayed;

			}
			return m_ManipulationView1;
		}

		// 0が初めに押された場合
		else if (m_ManipulationView1Termination == 1 && m_ManipulationView1[0] == '0')
		{
			// 二回目以降の0入力は無視する
			if (Manipulator == '0')
			{
				return m_ManipulationView1;
			}
			// 0以外の数字が押されたときには、初めに入力した0を削除する。
			else if (Manipulator - 0x31 >= 0 && Manipulator - 0x39 <= 0)
			{
				--m_ManipulationView1Termination;
			}
		}

		// 配列の後ろに押されたボタンの数字を追加していく
		if (m_ManipulationView1Termination < MAX_MANIPULATE_LENGTH)
		{
			m_ManipulationView1[m_ManipulationView1Termination] = Manipulator;
			++m_ManipulationView1Termination;
		}
	}
	return m_ManipulationView1;
}

char* CCalculate::GetView1()
{
	return m_ManipulationView1;
}

char* CCalculate::GetHistory()
{
	return m_ManipulationHistory;
}

int CCalculate::GetView1Size()
{
	return m_ManipulationView1Termination;
}

void CCalculate::ManipulationView1ToHistory()
{
	this->ResetManipulationHistory();
	m_ManipulationHistoryTermination = m_ManipulationView1Termination;
	for (int i = 0; i < MAX_MANIPULATE_LENGTH; ++i)
	{
		m_ManipulationHistory[i] = m_ManipulationView1[i];
	}
}

void CCalculate::ManipulationHistoryToView1()
{
	this->ResetManipulationView1();
	m_ManipulationView1Termination = m_ManipulationHistoryTermination;
	for (int i = 0; i < MAX_MANIPULATE_LENGTH; ++i)
	{
		m_ManipulationView1[i] = m_ManipulationHistory[i];
	}
}

void CCalculate::ResetManipulationView1()
{
	m_ManipulationView1Termination = 0;
	for (int i = 0; i < MAX_MANIPULATE_LENGTH; ++i)
	{
		m_ManipulationView1[i] = 0x00;
	}
}

void CCalculate::ResetManipulationHistory()
{
	m_ManipulationHistoryTermination = 0;
	for (int i = 0; i < MAX_MANIPULATE_LENGTH + 2; ++i)
	{
		m_ManipulationHistory[i] = 0x00;
	}
}

void CCalculate::SearchManipulationHistoryTermination()
{
	// m_ManipulationHistoryTerminationの設定
	for (int i = MAX_MANIPULATE_LENGTH; i >= 0; --i)
	{
		if (m_ManipulationHistory[i] != 0x00 && m_ManipulationHistory[i] != 0x30)
		{
			m_ManipulationHistoryTermination = i + 1;
			return;
		}
	}

	// 0x00,または'0'でないbyteが見つからなかった場合
	m_ManipulationHistoryTermination = 0;
}

void CCalculate::SearchManipulationView1Termination()
{
	// m_ManipulationView1Terminationの設定
	for (int i = MAX_MANIPULATE_LENGTH; i >= 0; --i)
	{
		if (m_ManipulationView1[i] != 0x00 && m_ManipulationView1[i] != 0x30)
		{
			m_ManipulationView1Termination = i + 1;
			return;
		}
	}

	// 0x00,または'0'でないbyteが見つからなかった場合
	m_ManipulationView1Termination = 0;
}

void CCalculate::SetNullAfterHistoryTermination()
{
	int ManipulationTerminationBuf = m_ManipulationHistoryTermination;
	if (m_ManipulationHistory[m_ManipulationHistoryTermination - 1] == '.')
	{
		--ManipulationTerminationBuf;
	}
	for (int i = ManipulationTerminationBuf; i < MAX_MANIPULATE_LENGTH; ++i)
	{
		m_ManipulationHistory[i] = 0x00;
	}
}

void CCalculate::SetNullAfterView1Termination()
{
	int ManipulationTerminationBuf = m_ManipulationView1Termination;
	if (m_ManipulationView1[m_ManipulationView1Termination - 1] == '.')
	{
		--ManipulationTerminationBuf;
	}
	for (int i = ManipulationTerminationBuf; i < MAX_MANIPULATE_LENGTH; ++i)
	{
		m_ManipulationView1[i] = 0x00;
	}
}
