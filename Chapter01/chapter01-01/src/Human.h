//============================================================================
// ファイル名  : Human.h
// 来歴        : 2019/04/11 新規作成 K.Asada
// 概要        : 人間の各種パラメータを管理するクラス（ヘッダ）
//============================================================================

#ifndef HUMAN_H_
#define HUMAN_H_

#include <string>

// 人間の各種パラメータを管理するクラス
class Human {

private:

//==============================================
// メンバ変数
//==============================================
	std::string fullName;		// 氏名
	int height;					// 身長
	int weight;					// 体重

public:
//===============================================
// メンバ関数
//===============================================

	// 関数名	: Human
	// 概  要	: Humanクラスのコンストラクタ
	// 引  数	: const std::string& fullName	氏名の初期化子
	// 			: int height					身長の初期化子
	//			: int weight					体重の初期化子
	// 戻り値	: なし
	Human(const std::string& fullName, int height, int weight);

	// 関数名	: GetName
	// 概  要	: 氏名のゲッタ
	// 引  数	: なし
	// 戻り値	: std::string name	氏名
	std::string GetName() const;

	// 関数名	: GetHeight
	// 概  要	: 身長のゲッタ
	// 引  数	: なし
	// 戻り値	: int height	身長
	int GetHeight() const;

	// 関数名	: GetWeight
	// 概  要	: 体重のゲッタ
	// 引  数	: なし
	// 戻り値	: int weight	体重
	int GetWeight() const;

	// 関数名	: GrowFat
	// 概  要	: メンバの体重を太らせる
	// 引  数	: int fatWeight		体重の増加値
	// 戻り値	: なし
	void GrowFat(int fatWeight);

	// 関数名	: SlimOff
	// 概  要	: メンバの体重を痩せさせる
	// 引  数	: int slimWeight	体重の減少値
	// 戻り値	: なし
	void SlimOff(int slimWeight);

};

#endif /* HUMAN_H_ */
