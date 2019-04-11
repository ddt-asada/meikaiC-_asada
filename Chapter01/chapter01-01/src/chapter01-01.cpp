//============================================================================
// ファイル名  : chapter01-01.cpp
// 来歴        : 2019/04/11 新規作成 K.Asada
// 概要        : コンストラクタ初期化子の動きを確認するためのプログラム
//============================================================================

#include <iostream>
#include <string>
#include "Human.h"

using namespace std;

int main() {

	string myName;		// 自分の名前（テスト用）
	int myWeight;		// 自分の体重（テスト用）
	int myHeight;		// 自分の身長（テスト用）
	int plusWeight;		// 体重の増分（テスト用）
	int minusWeight;	// 体重の減分（テスト用）

	myName = "浅田 知嗣";		// 自分の名前を設定
	myWeight = 55;				// 自分の体重を設定
	myHeight = 111;				// 自分の身長を設定

	// 自己ステータス管理用のオブジェクトを作成
	Human asada(myName, myHeight, myWeight);

	// 現在の名前を確認する
	cout << "名前：" << asada.GetName() << '\n';
	// 現在の体重を確認する
	cout << "現在の体重：" << asada.GetWeight() << '\n';
	// 現在の身長を確認する
	cout << "現在の身長：" << asada.GetHeight() << '\n';

	// 何キロ太ったかを記録
	plusWeight = 20;

	// 太ったことを通知
	cout << plusWeight << "キロ太りました。\n";
	// 自己ステータスへ反映
	asada.GrowFat(plusWeight);
	// 現在の体重を確認する
	cout << "現在の体重：" << asada.GetWeight() << '\n';
	// 現在の身長を確認する
	cout << "現在の身長：" << asada.GetHeight() << '\n';


	// 何キロやせたかを記録
	minusWeight = 50;
	// 痩せたことを通知
	cout << minusWeight << "キロ痩せました。\n";
	// 自己ステータスへ反映
	asada.SlimOff(minusWeight);
	// 現在の体重を確認する
	cout << "現在の体重：" << asada.GetWeight() << '\n';
	// 現在の身長を確認する
	cout << "現在の身長：" << asada.GetHeight() << '\n';

	// プログラムの終了を通知
	return 0;
}
