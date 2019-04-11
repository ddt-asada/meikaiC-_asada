//============================================================================
// ファイル名  : Human.cpp
// 来歴        : 2019/04/11 新規作成 K.Asada
// 概要        : 人間の各種パラメータを管理するクラス（ソース）
//============================================================================

#include <string>
#include <iostream>
#include "Human.h"

using namespace std;

//===============================================
// コンストラクタ
//===============================================
// 関数名	: Human
// 概  要	: Humanクラスのコンストラクタ
// 引  数	: const std::string& fullName	氏名の初期化子
// 			: int height					身長の初期化子
//			: int weight					体重の初期化子
// 戻り値	: なし
Human::Human(const std::string& fullName, int height, int weight)
				: fullName(fullName), height(height), weight(weight)
{
}

//===============================================
// メンバ関数
//===============================================
// 関数名	: GetName
// 概  要	: 氏名のゲッタ
// 引  数	: なし
// 戻り値	: std::string name	氏名
std::string Human::GetName() const
{
	// 名前を返却（処理速度を考慮し、インラインで定義）
	return fullName;
}

// 関数名	: GetHeight
// 概  要	: 身長のゲッタ
// 引  数	: なし
// 戻り値	: int height	身長
int Human::GetHeight() const
{
	// 身長を返却（処理速度を考慮し、インラインで定義）
	return height;
}

// 関数名	: GetWeight
// 概  要	: 体重のゲッタ
// 引  数	: なし
// 戻り値	: int weight	体重
int Human::GetWeight() const
{
	// 体重を返却（処理速度を考慮し、インラインで定義）
	return weight;
}

// 関数名	: GrowFat
// 概  要	: メンバの体重を太らせる
// 引  数	: int fatWeight		体重の増加値
// 戻り値	: なし
void Human::GrowFat(int fatWeight)
{
	// 体重を増加させる
	weight += fatWeight;
}

// 関数名	: SlimOff
// 概  要	: メンバの体重を痩せさせる
// 引  数	: int slimWeight	体重の減少値
// 戻り値	: なし
void Human::SlimOff(int slimWeight)
{
	// 体重を減少させる
	weight -= slimWeight;
}
