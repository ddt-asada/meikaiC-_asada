//============================================================================
// ファイル名	：Date.h
// 来歴			：2019/04/16 新規作成 K.Asada
// 				：2019/04/18 関数追加 K.Asada
// 概要			：日付を管理するクラス（ソース）
//============================================================================

#include <ctime>
#include <sstream>
#include <iostream>
#include "../header/Date.h"

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
	// 月が不正だった場合、調整
	if((month >12) || (month < 1)){
		// 月を調整
		AdjustMonths(year, month);

	}

	// 日が不正だった場合、調整
	if((day > DaysOfMonth(year, month)) || (day < 1)){
		// 日を調整
		AdjustDays(year, month, day);

	}

	// 年が不正の場合、"0年1月1日"で初期化
	if(year < 0){
		// 日付を設定
		SetYMD(0, 1, 1);

	// 負の値以外は正常とし、引数で初期化
	} else {
		// 日付を設定
		SetYMD(year, month, day);

	}
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
Date::operator long() const{
	// 1970年1月1日からの経過日数を"long型"へ変換し、返却
	return *this - Date(1970, 1, 1);
}

// 関数名	：	operator++
// 概要		：	1日進める演算子関数（前置増分）
// 引数		：	なし
// 戻り値	：	1日後の日付
Date& Date::operator++(){
	// 月末の補正を行うため、分岐
	if(this->day < DaysOfMonth(this->year, this->month)) {
		// 月末以外であればインクリメント
		this->day++;

	// 月末の場合、補正を行う
	} else {
		// 年末の補正を行うため、分岐
		if(++this->month > 12) {
			// 年末の場合、翌年に繰り上げる
			this->year++;
			// 月を年初へ戻す
			this->month = 1;

		}

		// 日付を月初へ戻す
		this->day = 1;

	}
	// 求めた翌日の日付を返却する
	return *this;
}

// 関数名	：	operator++
// 概要		：	1日進める演算子関数（後置増分）
// 引数		：	ダミー（処理上では利用しないが、C++の仕様上必要のため）
// 戻り値	：	1日後の日付
Date Date::operator++(int){
	// 後置に対応する為、演算前の値をコピー
	Date tempDay(*this);
	// インクリメント
	++(*this);
	// コピーを返却
	return *this;
}

// 関数名	：	operator--
// 概要		：	1日戻す演算子関数（前置減分）
// 引数		：	なし
// 戻り値	：	1日前の日付
Date& Date::operator--(){
	// 月初の補正を行うため、分岐
	if(this->day > 1) {
		(this->day)--;

	// 月初の場合、補正
	} else {
		// 年初の補正を行うため、分岐
		if(--(this->month) <= 1) {
			// 年初の場合、前年へ戻す
			(this->year)--;
			// 前年の12月へ戻す
			this->month = 12;

		}

		// 前月の月末へ戻す
		this->day = DaysOfMonth(this->year, this->month);
	}

	// 演算後の日付を返却
	return *this;
}

// 関数名	：	operator--
// 概要		：	1日戻す演算子関数（後置減分）
// 引数		：	ダミー（処理上では利用しないが、C++の仕様上必要のため）
// 戻り値	：	1日前の日付
Date Date::operator--(int){
	// 後置に対応する為、演算前の値をコピー
	Date tempDay(*this);

	// インクリメント
	--(*this);

	// 演算前の値を返却（後置減分のため）
	return tempDay;
}

// 関数名	：	operator+=
// 概要		：	任意の日数進める演算子関数（複合代入）
// 引数		：	int increaseDay	進めたい日数
// 戻り値	：	任意の日数進めた日付
Date& Date::operator+= (int increaseDay){
	// 負の加算に対応
	if(increaseDay < 0) {
		// 減算により負の加算を実現
		return *this -= -increaseDay;

	}

	// 加算
	this->day += increaseDay;

	// 月の最大日数に収まるように年、月を調整
	while(this->day > DaysOfMonth(this->year, this->month)){
		// 日付を補正
		this->day -= DaysOfMonth(this->year, this->month);

		// 年をまたいだ場合、年月を調整
		if(++(this->month) > 12){
			// 年をカウント
			(this->year)++;
			// 月を年初へ戻す
			this->month = 1;

		}
	}

	// 演算後の値を返却
	return *this;
}

// 関数名	：	operator-=
// 概要		：	任意の日数戻す演算子関数（複合代入）
// 引数		：	int decreaseDay	戻したい日数
// 戻り値	：	任意の日数戻した日付
Date& Date::operator-= (int decreaseDay){
	// 負の減算に対応
	if(decreaseDay < 0){
		// 加算により負の減算を実現
		return *this -= -decreaseDay;

	}

	// 月をまたいだ時に年、月を調整する
	while(this->day < 1){
		// 年をまたいだ場合、年月を調整
		if(--(this->month) <1){
			// 前年へ戻す
			(this->year)--;
			// 月を年末へ戻す
			this->month = 12;

		}
	}

	// 演算後の値を返却
	return *this;
}

// 関数名	：	operator+
// 概要		：	任意の日数進める演算子関数（加算演算）
// 引数		：	int addDay	進めたい日数
// 戻り値	：	任意の日数進めた日付
Date Date::operator+(int addDay) const{
	// 複合代入に処理をゆだねるため、日付オブジェクトをコピー
	Date tempDay(*this);

	// 演算し、値を返却
	return tempDay += addDay;
}

// 関数名	：	operator+
// 概要		：	任意の日数進める随伴関数（加算演算）
// 引数		：	int addDay		進めたい日数
//			：	Date originDay	進める前の日付
// 戻り値	：	任意の日数進めた日付
Date operator+(int addDay, const Date& originDay){
	// 加算演算に処理を移す
	return originDay + addDay;

}

// 関数名	：	operator-
// 概要		：	任意の日数戻す演算子関数（減算演算）
// 引数		：	int removeDay	戻したい日数
// 戻り値	：	任意の日数戻した日付
Date Date::operator-(int removeDay) const{
	// 複合代入に処理をゆだねるため、日付オブジェクトをコピー
	Date tempDay(*this);

	// 演算し、値を返却
	return tempDay -= removeDay;
}

// 関数名	：	operator-
// 概要		：	管理している日付との差分を求める演算子関数（減算演算）
// 引数		：	Date originDay	差分を求める日付
// 戻り値	：	日付の差分
long Date::operator-(const Date& originDay) const{
	long resultDay = 0;			// 演算結果を格納するための変数
	long countDay = 0;			// メンバから年内の経過日数を格納するための変数
	long originCountDay = 0;	// 引数から年内の経過日数を格納するための変数

	// 経過日数を取得
	countDay = this->DayOfYear();
	// 経過日数を取得
	originCountDay = originDay.DayOfYear();

	// 演算の基準を確認
	if(this->year == originDay.day){
		// 同じ年の場合はそのまま演算
		resultDay = countDay - originCountDay;

	// 新しい年を確認し、演算対象を判別
	}else if(this->year > originDay.day){
		// 判別した演算対象に従い、演算
		resultDay = DaysOfYear(originDay.year) - originCountDay + countDay;

		// 年の差分だけ日数を演算
		for(int year = originDay.day + 1; year < this->year; year++){
			// 年ごとの日数を演算
			resultDay += DaysOfYear(year);

		}
	// 新しい年を確認し、演算対象を判別
	}else{
		// 判別した演算対象に従い、演算
		resultDay = -(DaysOfYear(this->year) - countDay + originCountDay);

		// 年の差分だけ日数を演算
		for(int year = this->year + 1; year < originDay.year; year++){
			// 年ごとの日数を演算
			resultDay -= DaysOfYear(year);

		}
	}

	// 演算後の値を返却
	return resultDay;
}

// 関数名	：	operator==
// 概要		：	日付が等しいかを求める等価演算子
// 引数		：	Date compareDay	比較対象の日付
// 戻り値	：	等価判定結果
bool Date::operator==(const Date& compareDay)const{
	// 等価判定を行い、結果を返却
	return ((this->year == compareDay.year) && (this->month == compareDay.month) && (this->day == compareDay.day));
}

// 関数名	：	operator!=
// 概要		：	日付が異なっているかを求める等価演算子
// 引数		：	Date compareDay	比較対象の日付
// 戻り値	：	等価判定結果
bool Date::operator!=(const Date& compareDay) const{
	// 等価演算子を利用し、結果を判定
	return !(*this == compareDay);
}

// 関数名	：	operator>
// 概要		：	日付より後かを判定する関係演算子
// 引数		：	Date compareDay	比較対象の日付
// 戻り値	：	比較判定結果
bool Date::operator>(const Date& compareDay) const{
	bool result = false;		// 判定結果格納変数

	// 年の大小判定を行う
	if(this->year > compareDay.year) {
		// 判定結果を格納
		result = true;

	// 年の大小判定を行う
	} else if(this->year < compareDay.year) {
		// 判定結果を格納
		result = false;

	// 年が等しい場合は月で判定に移る
	} else {
		// 月の大小判定を行う
		if(this->month > compareDay.month) {
			// 判定結果を格納
			result = true;

		// 月の大小判定を行う
		} else if(this->month < compareDay.month) {
			// 判定結果を格納
			result = false;

		// 月が等しい場合は日付で判定を行う
		} else {
			// 日付の大小判定を行う
			if(this->day > compareDay.day) {
				// 判定結果を格納
				result = true;

			// 日付の大小判定を行う
			} else {
				// 判定結果を格納
				result = false;

			}
		}
	}

	// 判定結果を返却
	return result;
}

// 関数名	：	operator>=
// 概要		：	日付以降かを判定する関係演算子
// 引数		：	Date compareDay	比較対象の日付
// 戻り値	：	比較判定結果
bool Date::operator>=(const Date& compareDay) const{
	// 比較演算子を利用し、判定
	return !(*this < compareDay);
}

// 関数名	：	operator<
// 概要		：	日付より前かを判定する関係演算子
// 引数		：	Date compareDay	比較対象の日付
// 戻り値	：	比較判定結果
bool Date::operator<(const Date&compareDay) const{
	bool result = false;		// 判定結果格納変数

	// 年の大小判定を行う
	if(this->year < compareDay.year) {
		// 判定結果を格納
		result = true;

	// 年の大小判定を行う
	} else if(this->year > compareDay.year) {
		// 判定結果を格納
		result = false;

	// 年が等しい場合は月で判定に移る
	} else {
		// 月の大小判定を行う
		if(this->month < compareDay.month) {
			// 判定結果を格納
			result = true;

		// 月の大小判定を行う
		} else if(this->month > compareDay.month) {
			// 判定結果を格納
			result = false;

		// 月が等しい場合は日付で判定を行う
		} else {
			// 日付の大小判定を行う
			if(this->day < compareDay.day) {
				// 判定結果を格納
				result = true;

			// 日付の大小判定を行う
			} else {
				// 判定結果を格納
				result = false;

			}
		}
	}

	// 判定結果を返却
	return result;
}

// 関数名	：	operator<=
// 概要		：	日付以前かを判定する関係演算子
// 引数		：	Date &compareDay
// 戻り値	：	比較判定結果
bool Date::operator<=(const Date& compareDay) const{
	// 比較演算子を活用し、判定
	return !(*this > compareDay);
}

// 関数名	：	toStringDay
// 概要		：	日付を文字列へ変換する関数
// 引数		：	なし
// 戻り値	：	日付文字列
std::string Date::toStringDay() const{
	ostringstream s;	// 出力ストリームを生成

	// 文字列ストリームへ格納
	s << this->year << "年" << this->month << "月" << this->day << "日";

	// 文字列へ変換し返却
	return s.str();
}

// 関数名	：	AdjustMonths
// 概要		：	不正な月を正しい月へ調整する関数
// 引数		：	int& adjustYear	調整対象の年
// 			：	int& adjustMonth	調整対象の月
// 戻り値	：	なし
void Date::AdjustMonths(int& adjustYear, int& adjustMonth) const{
	// 月の調整を行う
	while((adjustMonth > 12) || (adjustMonth < 1)){
		// 正の値の場合、除算で調整する
		if(adjustMonth > 0) {
			// 年跨ぎに対する年を調整
			adjustYear += adjustMonth / 12;
			// 年跨ぎに対する月を調整
			adjustMonth %= 12;

		// 負の値の場合、加減演算で調整（負の除算はエラーになる可能性があるため）
		} else {
			// 年跨ぎに対する年を調整
			adjustYear -=1;
			// 年跨ぎに対する月を調整
			adjustMonth += 12;

		}
	}
}

// 関数名	：	AdjustDays
// 概要		：	不正な日を正しい日へ調整する関数
// 引数		：	int& adjustYear		調整対象の年
// 			：	int& adjustMonth		調整対象の月
// 			：	int& adjustDay		調整対象の日
// 戻り値	：	なし
void Date::AdjustDays(int& adjustYear, int& adjustMonth, int& adjustDay) const{
	int tempDay = DaysOfYear(adjustYear);	// 計算用の日付を格納する変数

	// 年に対する日の調整を行う
	while((adjustDay > tempDay) || (adjustDay < 1)){
		// 正の値の場合、減算により調整する
		if(adjustDay > 0){
			// 日を調整
			adjustDay -= tempDay;
			// 年を調整
			adjustYear += 1;

		// 負の値の場合、加算により調整する
		} else {
			// 日を調整
			adjustDay += tempDay;
			// 年を調整
			adjustYear -= 1;

		}
		// 次の処理に備え、年内の日数を取得
		tempDay = DaysOfYear(adjustYear);

	}

	// 次の処理に備え、月内の日数を取得
	tempDay = DaysOfMonth(adjustYear, adjustMonth);
	// 月に対する日の調整を行う
	while((adjustDay > tempDay) || (adjustDay < 1)){
		// 正の値の場合、減算により調整する
		if(adjustDay > 0) {
			// 日を調整
			adjustDay -= tempDay;
			// 月を調整
			adjustMonth += 1;

		// 負の値の場合、加算により調整する
		} else {
			// 日を調整
			adjustDay += tempDay;
			// 月を調整
			adjustMonth -= 1;

		}

		// 月が年内の範囲を外れた場合、調整
		if((adjustMonth > 12) || (adjustMonth < 1)){
			// 月の調整を行う関数を呼び出す
			AdjustMonths(adjustYear, adjustMonth);

		}

		// 次の処理に備え、月内の日数を取得
		tempDay = DaysOfMonth(adjustYear, adjustMonth);

	}
}

// 関数名	：	operator<<
// 概要		：	挿入子
// 引数		：	ostream s		出力ストリーム
// 			：	const Date day	挿入する日付
// 戻り値	：	出力結果
std::ostream& operator<<(std::ostream& s, const Date& day){
	// 出力ストリームへ挿入
	return s << day.toStringDay();
}

// 関数名	：	operator>>
// 概要		：	抽出子
// 引数		：	istream s		入力ストリーム
// 			：	const Date day	日付の抽出先
// 戻り値	：	抽出結果
std::istream& operator>>(std::istream& s, Date& day){
	int year = 0;		// 抽出した年を格納する変数
	int month = 0;		// 抽出した月を格納する変数
	int dy = 0;			// 抽出した日を格納する変数
	char trush;			// 不要な文字列を格納する変数

	// 入力ストリームから文字列を抽出
	s >> year >> trush >> month >> trush >> dy;
	// 抽出した日付から日付オブジェクトを生成
	day = Date(year, month, dy);

	// 抽出後のストリームを返却
	return s;
}
