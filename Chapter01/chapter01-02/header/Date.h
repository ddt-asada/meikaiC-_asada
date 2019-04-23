//============================================================================
// ファイル名	：Date.h
// 来歴			：2019/04/16 新規作成 K.Asada
// 				：2019/04/18 関数追加 K.Asada
// 				：2019/04/23 定数クラス実装に伴う修正 K.Asada
// 概要			：日付を管理するクラス（ヘッダ）
//============================================================================

#ifndef ___Class_Date
#define ___Class_Date

#include <string>
#include <iostream>
#include "../header/DateConstant.h"

//============================================================================
// クラス名	：Date
// 概要		：日付を管理するクラス
//============================================================================
class Date {

private:
	int year;		// 年（西暦）
	int month;		// 月
	int day;		// 日

	static int dayMax[];		// 各月の最大日数

	// 関数名	：	DaysOfYear
	// 概要		：	平年or閏年を判定し、それに応じた日数を返す
	// 引数		：	int year			判定したい年
	// 戻り値	：	判定後の日数
	static int DaysOfYear(int year);

	// 関数名	：	DaysOfMonth
	// 概要		：	年月ごとの日数を判定し、それに応じた日数を返す
	// 引数		：	int year			判定したい年
	// 				int month			判定したい月
	// 戻り値	：	判定後の日数
	static int DaysOfMonth(int year, int month);

public:

	// 関数名	：	JudgeLeapYear
	// 概要		：	平年or閏年を判定し、判定結果を返す
	// 引数		：	int year			判定したい年
	// 戻り値	：	判定結果
	static bool JudgeLeapYear(int year){
		// 閏年かどうかを求め、判定結果を返却
		return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	// デフォルトコンストラクタ
	Date();
	// コンストラクタ
	Date(int year, int month = DateConstant::MIN_MONTH, int day = DateConstant::MIN_DAY);

	// 関数名	：	JudgeLeapYear
	// 概要		：	平年or閏年を判定し、判定結果を返す
	// 引数		：	なし
	// 戻り値	：	判定結果
	bool JudgeLeapYear() const{
		// 判定関数を呼び出し、結果を返す
		return JudgeLeapYear(this->year);
	}

	// 関数名	：	GetYear
	// 概要		：	年のゲッタ
	// 引数		：	なし
	// 戻り値	：	年
	int GetYear() const{
		// メンバの年を返却
		return this->year;
	}

	// 関数名	：	GetMonth
	// 概要		：	月のゲッタ
	// 引数		：	なし
	// 戻り値	：	月
	int GetMonth() const{
		// メンバの月を返却
		return this->month;
	}

	// 関数名	：	GetDay
	// 概要		：	日のゲッタ
	// 引数		：	なし
	// 戻り値	：	日
	int GetDay() const{
		// メンバの日を返却
		return this->day;
	}

	// 関数名	：	SetYMD
	// 概要		：	年月日を一括設定するセッタ
	// 引数		：	int year	設定する年
	// 			：	int month	設定する月
	// 			：	int day		設定する日
	// 戻り値	：	なし
	void SetYMD(int year, int month, int day);

	// 関数名	：	SetYear
	// 概要		：	年のセッタ
	// 引数		：	設定する年
	// 戻り値	：	なし
	void SetYear(int year) {
		// メンバの年をセット
		this->year = year;
	}

	// 関数名	：	SetMonth
	// 概要		：	月のセッタ
	// 引数		：	なし
	// 戻り値	：	月
	void SetMonth(int month) {
		// メンバの月をセット
		this->month = month;
	}

	// 関数名	：	SetDay
	// 概要		：	日のセッタ
	// 引数		：	なし
	// 戻り値	：	年
	void SetDay(int day) {
		// メンバの日をセット
		this->day = day;
	}

	// 関数名	：	PrecedingDay
	// 概要		：	前日の日付を返却する
	// 引数		：	なし
	// 戻り値	：	前日の日付
	Date PrecedingDay() const;

	// 関数名	：	FollowingDay
	// 概要		：	翌日の日付を返却する
	// 引数		：	なし
	// 戻り値	：	翌日の日付
	Date FollowingDay() const;

	// 関数名	：	DayOfYear
	// 概要		：	年内の経過日数を返却する
	// 引数		：	なし
	// 戻り値	：	1月1日からの経過日数
	int DayOfYear() const;

	// 関数名	：	DayOfWeek
	// 概要		：	曜日を返却（日曜を０、土曜日を６とし、対応した数字で返却）
	// 引数		：	なし
	// 戻り値	：	曜日を表す数字
	int DayOfWeek() const;

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
	Date operator++(int);

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
	friend Date operator+(int addDay, const Date& originDay);

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

	// 関数名	：	AdjustMonths
	// 概要		：	不正な月を正しい月へ調整する関数
	// 引数		：	int& adjustYear		調整対象の年
	// 			：	int& adjustMoth	調整対象の月
	// 戻り値	：	なし
	void AdjustMonths(int& adjustYear, int& adjustMoth) const;

	// 関数名	：	AdjustDays
	// 概要		：	不正な日を正しい日へ調整する関数
	// 引数		：	int& adjustYear		調整対象の年
	// 			：	int& adjustMoth		調整対象の月
	// 			：	int& adjustDay		調整対象の日
	// 戻り値	：	なし
	void AdjustDays(int& adjustYear, int& adjustMoth, int& adjustDay) const;
};

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
std::istream& operator>>(std::istream& s, Date& day);

#endif
