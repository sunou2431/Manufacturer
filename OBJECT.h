#ifndef _DEF_OBJECT_H_
#define _DEF_OBJECT_H_

//�w�b�_�[�t�@�C��
#include "DxLib.h"
#include <string.h>
#include <windows.h>

//�֐�
void gpUpdataKey(int*);
void selectminigame(void);
void filesele_play(void);
void filesele_make(void);
void tetomari(void);
int GamePlay(int);

//�z��
typedef struct{ 
    int x, y;  // ���W�i�[�p�ϐ� 
	int cr;
	char name[128];  // ���ږ��i�[�p�ϐ� 
} MenuElement_t ;
typedef struct{
	int Data[4][4][4];
}Block;

#endif 