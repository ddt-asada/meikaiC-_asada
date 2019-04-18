//============================================================================
// ファイル名	：chapter01-02.cpp
// 来歴			：2019/04/18 新規作成 K.Asada
// 概要			：オブジェクト生成時に不正な日付が与えられた場合、
//				  正しい日付に補正するクラスを作成し、動作を確認する
//============================================================================

#include <iostream>
#include "../header/Date.h"

using namespace std;

// 関数名	：	DisplayDayInfo
// 概要		：	日付オブジェクトの情報を表示する関数
// 引数		：	Date dispDate	表示したい日付オブジェクト
// 戻り値	：	なし
void DisplayDayInfo(Date dispDate);

int main() {
	Date successDate = Date(2019, 4, 18);		// 正常な年月日で初期化
	Date invalideDate = Date(2000, -100, 1000);	// 不正な年月日で初期化

	// 情報を表示
	DisplayDayInfo(successDate);

	// 不正な年月日でも正常に初期化されるか確認
	DisplayDayInfo(invalideDate);

	return 0;
}

// 関数名	：	DisplayDayInfo
// 概要		：	日付オブジェクトの情報を表示する関数
// 引数		：	Date dispDate	表示したい日付オブジェクト
// 戻り値	：	なし
void DisplayDayInfo(Date dispDate){
	// 日付を表示
	cout << "・日付" << dispDate << "に関する情報\n";
	// 年内経過日数を表示
	cout << "　年内経過日数は" << dispDate.DayOfYear() << "日\n";
	// 1970年1月1日からの経過日数を表示
	cout << "　1970年1月1日の" << long(dispDate) << "日後\n";
	// 閏年かどうかを表示
	cout << "　その年は閏年で" << (dispDate.JudgeLeapYear() ? "ある" : "はない。") << '\n';
}
