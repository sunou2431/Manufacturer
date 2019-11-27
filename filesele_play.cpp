#include "OBJECT.h"

void filesele_play(void){
	int Key[256];
	int i = 0;
	int j = 0;
	int page_max;
	int page = 0;
	int count = 0;
	char dummy[120];
	char fname[50][8][100];
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;

	MenuElement_t Menusele[11] = {
		{250,40,GetColor(0,0,0),"�V��"},
		{200,80,GetColor(0,0,0),"���"},
		{200,120,GetColor(0,0,0),"�~�j�Q�[��"},
		{200,160,GetColor(0,0,0),"�I��"},
		{200,200,GetColor(0,0,0),"�I��"},
		{200,240,GetColor(0,0,0),"�I��"},
		{200,280,GetColor(0,0,0),"�I��"},
		{200,320,GetColor(0,0,0),"�I��"},
		{200,360,GetColor(0,0,0),"����"},
		{200,400,GetColor(0,0,0),"�O��"},
		{200,440,GetColor(0,0,0),"�߂�"}
	};

	hFind = FindFirstFile("MapData\\*.*", &win32fd);//win32�Ƀt�H���_�w��
	if (hFind == INVALID_HANDLE_VALUE) {//�G���[������������I��
		return;
	}

	do{//fname��file�����R�s�[
		if(win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		}
		else{
			strcpy_s(fname[j][i],win32fd.cFileName);
			i++;
			if(i == 8){
				i = 0;
				j++;
			}
		}
	}while (FindNextFile(hFind, &win32fd));
	if(i == 0){
		i = 8;
		j--;
	}
	for(;i != 8;i++){
		strcpy_s(fname[j][i],"");
	}
	page_max = j;

	gpUpdataKey(Key);
	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && Key[KEY_INPUT_ESCAPE] != 1){
		//�v�Z����
		gpUpdataKey(Key);
		if(Key[KEY_INPUT_DOWN] == 1){//���L�[�������ꂽ�牺�ɍs������
			do{
				count++;
				count = count % 11;
			}while(strlen(fname[page][count]) == 0 && count <= 7);
		}
		if(Key[KEY_INPUT_UP] == 1){//��L�[�������ꂽ���ɍs������
			do{
				count = count += 10;
				count = count % 11;
			}while(strlen(fname[page][count]) == 0 && count <= 7);
		}
		if(Key[KEY_INPUT_LEFT] == 1){
		}
		if(Key[KEY_INPUT_RIGHT] == 1){
		}
		if(Key[KEY_INPUT_SPACE] == 1 || Key[KEY_INPUT_RETURN] == 1){
			if(count >= 0 && count <= 7){
				strcpy_s(dummy,"MapData\\");
				strcat_s(dummy, sizeof(fname[page][count]) - strlen(fname[page][count]) - 1,fname[page][count]);
				GamePlay(FileRead_open(dummy));
				return;
			}
			if(count == 8){
				if(page == page_max){
					page = 0;
				}
				else{
					page++;
				}
			}
			if(count == 9){
				if(page == 0){
					page = page_max;
				}
				else{
					page--;
				}
			}
			if(count == 10){
				return;
			}
		}
		for(i = 0;i <= 10;i++){
			if(i <= 7){
				strcpy_s(Menusele[i].name,fname[page][i]);
			}
			if(i == count){
				Menusele[i].x = 250;
				Menusele[i].cr = GetColor(255,0,255);
			}
			else{
				Menusele[i].x = 200;
				Menusele[i].cr = GetColor(255,255,255);
			}
		}

		//�`�揈��
		for(i = 0;i <= 10;i++){
			DrawFormatString(Menusele[i].x,Menusele[i].y,Menusele[i].cr,Menusele[i].name);//�����̕\��
		}

	 }
	 FindClose(hFind);
	 return;
}