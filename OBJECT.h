#ifndef _DEF_OBJECT_H_
#define _DEF_OBJECT_H_

//ヘッダーファイル
#include "DxLib.h"
#include <string.h>
#include <windows.h>

//関数
void gpUpdataKey(int*);
void selectminigame(void);
void filesele_play(void);
void filesele_make(void);
void tetomari(void);
int GamePlay(int);

//配列
typedef struct{ 
    int x, y;  // 座標格納用変数 
	int cr;
	char name[128];  // 項目名格納用変数 
} MenuElement_t ;
typedef struct{
	int Data[4][4][4];
}Block;

#endif 