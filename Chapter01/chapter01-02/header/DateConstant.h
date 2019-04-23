//============================================================================
// ファイル名	：DateConstant.h
// 来歴			：2019/04/23 新規作成 K.Asada
// 概要			：日付関連の定数クラス
//============================================================================

class DateConstant {
public:
	static const int MIN_YEAR = 0;				// 最小年

	static const int MAX_MONTH = 12;			// 最大月
	static const int MIN_MONTH = 1;			// 最小月

	static const int MAX_LEAP_DAY = 366;		// 閏年の最大日
	static const int MAX_NORMAL_DAY = 365;		// 平年の最大日
	static const int MIN_DAY = 1;				// 最小日

	static const int JUDGE_PLUS_MINUS = 0;		// 正負を判定するための基準値

	// 各月を表す列挙体
	enum MONTH_NUM : const int{
		JAN = 1,			// 1月
		FEB = 2,			// 2月
		MAR = 3,			// 3月
		APR = 4,			// 4月
		MAY = 5,			// 5月
		JUN = 6,			// 6月
		JUL = 7,			// 7月
		AUG = 8,			// 8月
		SEP = 9,			// 9月
		OCT = 10,			// 10月
		NOV = 11,			// 11月
		DEC = 12			// 12月
	};
};
