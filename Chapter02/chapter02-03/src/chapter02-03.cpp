//============================================================================
// ファイル名  : chapter02-02.cpp
// 来歴        : 2019/04/25 新規作成 K.Asada
// 概要        : 以下の3種類の関数を作成し、動作確認
//             :   ・ 任意のnビットを1にした値を返す関数
//             :   ・ 任意のnビットを0にした値を返す関数
//             :   ・ 任意のnビットを反転した値を返す関数
//============================================================================

#include <iostream>
#define BITCOUNT 8

using namespace std;

// 関数名	：	SetBit
// 概要		：	任意のビットを1にする関数
// 引数		：	unsigned int targetBit	対象の値
// 			：	int resetPos			任意のビット
// 戻り値	：	ビットを立てた後の値
unsigned int SetBit(unsigned int targetBit, int resetPos);

// 関数名	：	ResetBit
// 概要		：	任意のビットを0にする関数
// 引数		：	unsigned int targetBit	対象の値
// 			：	int resetPos			任意のビット
// 戻り値	：	ビットを下げた後の値
unsigned int ResetBit(unsigned int targetBit, int resetPos);

// 関数名	：	ReverseBit
// 概要		：	任意のビットを反転させる関数
// 引数		：	unsigned int targetBit	対象の値
// 			：	int resetPos			任意のビット
// 戻り値	：	ビットを反転後の値
unsigned int ReverseBit(unsigned int targetBit, int resetPos);

// 関数名	：	BitInfo
// 概要		：	ビットを表示する関数
// 引数		：	unsigned int showBit		確認対象のビット
// 戻り値	：	回転後のビット
void BitInfo(unsigned int showBit);

int main() {
	unsigned int targetBit = 0b10101011100010111111000101010010;	// 確認対象のビット
	unsigned int setBit = 0;					// 1を立てたビット
	unsigned int resetBit = 0;					// 0を下げたビット
	unsigned int reverseBit = 0;				// 反転させたビット
	int setPos= 4;								// ビットを立てる位置
	int resetPos = 9;							// ビットを下げる位置
	int reversePos =2;							// ビットを反転させる位置

	// 初期状態を確認
	cout << "ビット操作前：";
	// ビット操作前の状態を確認
	BitInfo(targetBit);

	// ビットを立てる
	setBit = SetBit(targetBit, setPos);
	// ビット操作後であることを出力
	cout << "ビット操作後：";
	// ビットを立てるた後の状態を確認
	BitInfo(setBit);

	// ビットを下げる
	resetBit = ResetBit(targetBit, resetPos);
	// ビット操作後であることを出力
	cout << "ビット操作後：";
	// ビットを下げたの状態を確認
	BitInfo(resetBit);

	// ビットを反転
	reverseBit = ResetBit(targetBit, reversePos);
	// ビット操作後であることを出力
	cout << "ビット操作後：";
	// ビットを反転後の状態を確認
	BitInfo(reverseBit);

	return 0;
}

// 関数名	：	SetBit
// 概要		：	任意のビットを1にする関数
// 引数		：	unsigned int targetBit	対象の値
// 			：	int resetPos			任意のビット
// 戻り値	：	ビットを立てた後の値
unsigned int SetBit(unsigned int targetBit, int setPos){
	// 任意のビットを立てて返す
	return (targetBit | (0x00000001 << (setPos - 1)));
}

// 関数名	：	ResetBit
// 概要		：	任意のビットを0にする関数
// 引数		：	unsigned int targetBit	対象の値
// 			：	int resetPos			任意のビット
// 戻り値	：	ビットを下げた後の値
unsigned int ResetBit(unsigned int targetBit, int resetPos){
	// 任意のビットを下げて返す
	return (targetBit & (0xFFFFFFFF ^ (0x00000001 << (resetPos - 1))));
}

// 関数名	：	ReverseBit
// 概要		：	任意のビットを反転させる関数
// 引数		：	unsigned int targetBit	対象の値
// 			：	int resetPos			任意のビット
// 戻り値	：	ビットを反転後の値
unsigned int ReverseBit(unsigned int targetBit, int resetPos){
	// 任意のビットを反転させて返す
	return (targetBit ^ (0x00000001 << (resetPos - 1)));
}

// 関数名	：	BitInfo
// 概要		：	ビットを表示する関数
// 引数		：	unsigned int showBit		確認対象のビット
// 戻り値	：	回転後のビット
void BitInfo(unsigned int showBit){
	unsigned int chkBit = 0x01;			// チェック用のビット

	// ビットを走査
	for(int i = ((sizeof(showBit) * BITCOUNT) - 1); i >= 0; i--){
		// ビットチェック
		if((showBit >> i) & chkBit){
			// ビットがたっていたら1を表示
			cout << '1';

		// ビットが下がっていたら0を表示
		} else {
			// ビットを表示
			cout << '0';
		}
	}

	// すべての表示が終わったら改行
	cout << '\n';
}
