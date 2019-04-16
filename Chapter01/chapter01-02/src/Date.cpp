//============================================================================
// ファイル名  : Date.h
// 来歴        : 2019/04/16 新規作成 K.Asada
// 概要        : 日付を管理するクラス（ソース）
//============================================================================

#include <ctime>
#include <sstream>
#include <iostream>
#include "header/Date.h"

using namespace std;

// 各月の最大日数
int Date::dayMax[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// 関数名	：	DaysOfYear
// 概要		：	平年or閏年を判定し、それに応じた日数を返す
// 引数		：	int year			判定したい年
// 戻り値	：	判定後の日数
int Date::DaysOfYear(int year){
	// 渡された年度の日数を返す
	return 365 + JudgeLeapYear(year);
}

// 関数名	：	DaysOfMonth
// 概要		：	年月ごとの日数を判定し、それに応じた日数を返す
// 引数		：	int year			判定したい年
// 				int month			判定したい月
// 戻り値	：	判定後の日数
int Date::DaysOfMonth(int year, int month){
	// 渡された年月の日数を返す
	return dayMax[month - 1] + (month == 2 && JudgeLeapYear(year));
}

// 関数名	：	JudgeLeapYear
// 概要		：	平年or閏年を判定し、判定結果を返す
// 引数		：	int year			判定したい年
// 戻り値	：	判定結果
bool Date::JudgeLeapYear(int year){
	// 閏年かどうかを求め、判定結果を返却
	return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

// デフォルトコンストラクタ
Date::Date(){
	time_t currentTime = time(NULL);					// 現在の暦時刻を取得
	struct tm* localTime = localtime(&currentTime);	// 要素別の時刻に変換

	// 現在年を取得、メンバへセット
	this->year = localTime->tm_year + 1900;
	// 現在月を取得、メンバへセット
	this->month = localTime->tm_mon + 1;
	// 現在日を取得、メンバへセット
	this->day = localTime->tm_mday;
}

// コンストラクタ
Date::Date(int year, int month, int day){
	// 日付を設定
	SetYMD(year, month, day);
}

// 関数名	：	JudgeLeapYear
// 概要		：	平年or閏年を判定し、判定結果を返す
// 引数		：	なし
// 戻り値	：	判定結果
bool Date::JudgeLeapYear() const{
	// 判定関数を呼び出し、結果を返す
	return JudgeLeapYear(this->year);
}

// 関数名	：	SetYMD
// 概要		：	年月日を一括設定するセッタ
// 引数		：	int year	設定する年
// 			：	int month	設定する月
// 			：	int day		設定する日
// 戻り値	：	なし
void Date::SetYMD(int year, int month, int day) {
	// メンバの年をセット
	this->year = year;
	// メンバの月をセット
	this->month = month;
	// メンバの日をセット
	this->day = day;
}

// 関数名	：	PrecedingDay
// 概要		：	前日の日付を返却する
// 引数		：	なし
// 戻り値	：	前日の日付
Date Date::PrecedingDay() const{
	// 日付算出用に現在の日付オブジェクトをコピー
	Date tempDay(*this);

	// 前日の日付を求め、返却
	return --tempDay;
}

// 関数名	：	FollowingDay
// 概要		：	翌日の日付を返却する
// 引数		：	なし
// 戻り値	：	翌日の日付
Date Date::FollowingDay() const{
	// 日付算出用に現在の日付オブジェクトをコピー
	Date tempDay(*this);

	// 翌日の日付を求め、返却
	return ++tempDay;
}

// 関数名	：	DayOfYear
// 概要		：	年内の経過日数を返却する
// 引数		：	なし
// 戻り値	：	1月1日からの経過日数
int Date::DayOfYear() const{
	int days = this->day;	// 年内の経過日数を取得

	// 年内の経過月数日付を求め、取得
	for(int i = 1; i < this->month; i++) {
		// 経過日数へ足しこんて行く
		days += DaysOfMonth(this->year, i);
	}

	// 経過日数を返却
	return days;
}

// 関数名	：	DayOfWeek
// 概要		：	曜日を返却（日曜を０、土曜日を６とし、対応した数字で返却）
// 引数		：	なし
// 戻り値	：	曜日を表す数字
int Date::DayOfWeek() const{
	int year = this->year;		// 年を取得
	int month = this->month;	// 月を取得

	// 曜日を求めるために、月数を補正する
	if((month == 1) || (month == 2)){
		// 1年分を月へ変換するため、減算
		year--;
		// 1年を月へ変換
		month += 12;
	}

	// 曜日に対応した数字を求め、返却
	return ((year + year / 4 - year / 100 + year / 400 + (13 * month + 8) / 5 + day) % 7);
}

// 関数名	：	long
// 概要		：	1970年1月1日からの経過日数を返す変換関数
// 引数		：	なし
// 戻り値	：	1970年1月1日からの経過日数
operator long() const;

// 関数名	：	operator++
// 概要		：	1日進める演算子関数（前置増分）
// 引数		：	なし
// 戻り値	：	1日後の日付
Date& operator++();

// 関数名	：	operator++
// 概要		：	1日進める演算子関数（後置増分）
// 引数		：	ダミー（処理上では利用しないが、C++の仕様上必要のため）
// 戻り値	：	1日後の日付
Date operator++();

// 関数名	：	operator--
// 概要		：	1日戻す演算子関数（前置減分）
// 引数		：	なし
// 戻り値	：	1日前の日付
Date& operator--();

// 関数名	：	operator--
// 概要		：	1日戻す演算子関数（後置減分）
// 引数		：	ダミー（処理上では利用しないが、C++の仕様上必要のため）
// 戻り値	：	1日前の日付
Date operator--(int);

// 関数名	：	operator+=
// 概要		：	任意の日数進める演算子関数（複合代入）
// 引数		：	int increaseDay	進めたい日数
// 戻り値	：	任意の日数進めた日付
Date& operator+= (int increaseDay);

// 関数名	：	operator-=
// 概要		：	任意の日数戻す演算子関数（複合代入）
// 引数		：	int decreaseDay	戻したい日数
// 戻り値	：	任意の日数戻した日付
Date& operator-= (int decreaseDay);

// 関数名	：	operator+
// 概要		：	任意の日数進める演算子関数（加算演算）
// 引数		：	int addDay	進めたい日数
// 戻り値	：	任意の日数進めた日付
Date operator+(int addDay) const;

// 関数名	：	operator+
// 概要		：	任意の日数進める随伴関数（加算演算）
// 引数		：	int addDay		進めたい日数
//			：	Date originDay	進める前の日付
// 戻り値	：	任意の日数進めた日付
friend Date operator+(int addDay, const Date& originDay) const;

// 関数名	：	operator-
// 概要		：	任意の日数戻す演算子関数（減算演算）
// 引数		：	int removeDay	戻したい日数
// 戻り値	：	任意の日数戻した日付
Date operator-(int removeDay) const;

// 関数名	：	operator-
// 概要		：	管理している日付との差分を求める演算子関数（減算演算）
// 引数		：	Date originDay	差分を求める日付
// 戻り値	：	日付の差分
long operator-(const Date& originDay) const;

// 関数名	：	operator==
// 概要		：	日付が等しいかを求める等価演算子
// 引数		：	Date compareDay	比較対象の日付
// 戻り値	：	等価判定結果
bool operator==(const Date& compareDay)const;

// 関数名	：	operator!=
// 概要		：	日付が異なっているかを求める等価演算子
// 引数		：	Date compareDay	比較対象の日付
// 戻り値	：	等価判定結果
bool operator!=(const Date& compareDay) const;

// 関数名	：	operator>
// 概要		：	日付より後かを判定する関係演算子
// 引数		：	Date compareDay	比較対象の日付
// 戻り値	：	比較判定結果
bool operator>(const Date& compareDay) const;

// 関数名	：	operator>=
// 概要		：	日付以降かを判定する関係演算子
// 引数		：	Date compareDay	比較対象の日付
// 戻り値	：	比較判定結果
bool operator>=(const Date& compareDay) const;

// 関数名	：	operator<
// 概要		：	日付より前かを判定する関係演算子
// 引数		：	Date compareDay	比較対象の日付
// 戻り値	：	比較判定結果
bool operator<(const Date&compareDay) const;

// 関数名	：	operator<=
// 概要		：	日付以前かを判定する関係演算子
// 引数		：	Date &compareDay
// 戻り値	：	比較判定結果
bool operator<=(const Date& compareDay) const;

// 関数名	：	toStringDay
// 概要		：	日付を文字列へ変換する関数
// 引数		：	なし
// 戻り値	：	日付文字列
std::string toStringDay() const;

// 関数名	：	operator<<
// 概要		：	挿入子
// 引数		：	ostream s		出力ストリーム
// 			：	const Date day	挿入する日付
// 戻り値	：	出力結果
std::ostream& operator<<(std::ostream& s, const Date& day);

// 関数名	：	operator>>
// 概要		：	抽出子
// 引数		：	istream s		入力ストリーム
// 			：	const Date day	日付の抽出先
// 戻り値	：	抽出結果
std::istream& operator>>(std::istream& s, const Date& day);
