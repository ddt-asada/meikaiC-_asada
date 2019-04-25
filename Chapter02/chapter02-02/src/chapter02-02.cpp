//============================================================================
// ファイル名  : chapter02-02.cpp
// 来歴        : 2019/04/25 新規作成 K.Asada
// 概要        : 右にnビット回転した値を返す関数と
//               左にnビット回転した値を返す関数を作成する
//               ※回転とは、ビットの最上位と最下位がつながってると考えること
//============================================================================

#include <iostream>
#define BITCOUNT 8

using namespace std;

// 関数名	：	BitRRotate
// 概要		：	右に任意のビット回転した値を返す関数
// 引数		：	unsigned int rotateBit		回転させる値
// 			：	int rotateCount				シフトするビット数
// 戻り値	：	回転後のビット
unsigned int BitRRotate(unsigned int rotateBit, int rotateCount);

// 関数名	：	BitLRotate
// 概要		：	左に任意のビット回転した値を返す関数
// 引数		：	unsigned int rotateBit		回転させる値
// 			：	int rotateCount				シフトするビット数
// 戻り値	：	回転後のビット
unsigned int BitLRotate(unsigned int rotateBit, int rotateCount);

// 関数名	：	BitInfo
// 概要		：	ビットを表示する関数
// 引数		：	unsigned int showBit		確認対象のビット
// 戻り値	：	回転後のビット
void BitInfo(unsigned int showBit);

int main() {
	unsigned int targetBit = 0b10101011100010111111000101010010;	// 確認対象のビット
	unsigned int rRotateBit = 0;					// 右回転後のビット
	unsigned int lRotateBit = 0;					// 左回転後のビット

	// 初期状態を確認
	cout << "ビット操作前：";
	// ビット操作前の状態を確認
	BitInfo(targetBit);

	// 右回転
	rRotateBit = BitRRotate(targetBit, 5);
	// 右回転後であることを出力
	cout << "右回転後：";
	// 右回転後の状態を確認
	BitInfo(rRotateBit);

	// 左回転
	lRotateBit = BitLRotate(targetBit, 7);
	// 左回転後であることを出力
	cout << "左回転後：";
	// 左回転後の状態を確認
	BitInfo(lRotateBit);

	return 0;
}

// 関数名	：	BitRRotate
// 概要		：	右に任意のビット回転した値を返す関数
// 引数		：	unsigned int rotateBit		回転させる値
// 			：	int rotateCount				シフトするビット数
// 戻り値	：	回転後のビット
unsigned int BitRRotate(unsigned int rotateBit, int rotateCount){
	unsigned int resultBit = 0;		// 回転後のビット

	// 右に引数で受けただけ回転
	resultBit = (rotateBit >> rotateCount) | (rotateBit << ((sizeof(rotateBit) * BITCOUNT) - rotateCount));

	// 回転後のビットを返却
	return resultBit;
}

// 関数名	：	BitLRotate
// 概要		：	左に任意のビット回転した値を返す関数
// 引数		：	unsigned int rotateBit		回転させる値
// 			：	int rotateCount				シフトするビット数
// 戻り値	：	回転後のビット
unsigned int BitLRotate(unsigned int rotateBit, int rotateCount){
	unsigned int resultBit = 0;		// 回転後のビット

	// 右に引数で受けただけ回転
	resultBit = (rotateBit << rotateCount) | (rotateBit >> ((sizeof(rotateBit) * BITCOUNT) - rotateCount));

	// 回転後のビットを返却
	return resultBit;
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
