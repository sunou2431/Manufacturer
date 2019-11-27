#include "OBJECT.h"
#include "make.h"

void del(char filename[100]);

void filesele_make(void){
	reset:
	int Key[256];
	int i = 0;
	int j = 0;
	int page_max;
	int page = 0;
	int count = 0;
	boolean delmode = false;
	char fname[50][8][100];
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;

	MenuElement_t Menusele[13] = {
		{250,40,GetColor(0,0,0),"遊ぶ"},
		{200,80,GetColor(0,0,0),"作る"},
		{200,120,GetColor(0,0,0),"ミニゲーム"},
		{200,160,GetColor(0,0,0),"終了"},
		{200,200,GetColor(0,0,0),"終了"},
		{200,240,GetColor(0,0,0),"終了"},
		{200,280,GetColor(0,0,0),"終了"},
		{200,320,GetColor(0,0,0),"終了"},
		{200,380,GetColor(0,0,0),"次へ"},
		{200,420,GetColor(0,0,0),"前へ"},
		{200,460,GetColor(0,0,0),"作る"},
		{200,500,GetColor(0,0,0),"戻る"},
		{200,540,GetColor(0,0,0),"削除"}
	};

	hFind = FindFirstFile("MapData\\*.*", &win32fd);//win32にフォルダ指定
	if (hFind == INVALID_HANDLE_VALUE) {//エラーが発生したら終了
		return;
	}

	do{//fnameにfile名をコピー
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
	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && Key[KEY_INPUT_ESCAPE] == 0){
		//計算処理
		gpUpdataKey(Key);
		if(Key[KEY_INPUT_DOWN] == 1){//下キーが押されたら下に行く処理
			do{
				count++;
				count = count % 13;
			}while(strlen(fname[page][count]) == 0 && count <= 7);
		}
		if(Key[KEY_INPUT_UP] == 1){//上キーが押されたら上に行く処理
			do{
				count = count += 12;
				count = count % 13;
			}while(strlen(fname[page][count]) == 0 && count <= 7);
		}
		if(Key[KEY_INPUT_LEFT] == 1){
				if(page == 0){
					page = page_max;
				}
				else{
					page--;
				}
		}
		if(Key[KEY_INPUT_RIGHT] == 1){
				if(page == page_max){
					page = 0;
				}
				else{
					page++;
				}
		}
		if(Key[KEY_INPUT_SPACE] == 1 || Key[KEY_INPUT_RETURN] == 1){
			if(count <= 7 && delmode == false){
				make(fname[page][count]);
				goto reset;
			}
			if(count <= 7 && delmode == true){
				del(fname[page][count]);
				goto reset;
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
				make("");		
				goto reset;
			}
			if(count == 11){
				return;
			}
			if(count == 12){
				if(delmode == false){
					delmode = true;
				}
				else{
					delmode = false;
				}
			}
		}
		for(i = 0;i <= 12;i++){
			if(delmode == false){
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
				if(i == 12){
					strcpy_s(Menusele[i].name,"削除");
				}
			}
			else{
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
				if(i == 12){
					strcpy_s(Menusele[i].name,"削除しない");
				}
			}
		}

		//描画処理
		for(i = 0;i <= 12;i++){
			DrawFormatString(Menusele[i].x,Menusele[i].y,Menusele[i].cr,Menusele[i].name);//文字の表示
		}
		if(delmode == true){
			DrawFormatString(500,50,GetColor(255,255,255),"削除中");
		}

	 }
	 FindClose(hFind);
	 return;
}
void del(char filename[100]){
	int Key[256];
	int i = 0;
	int count = 0;
	char dummy[124];
	MenuElement_t Menusele[2] = {
		{250,80,GetColor(0,0,0),"削除する"},
		{200,120,GetColor(0,0,0),"削除しない"}
	};
	Key[KEY_INPUT_SPACE] = 1;
	Key[KEY_INPUT_RETURN] = 1;

	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0){
		//計算処理
		gpUpdataKey(Key);
		if(Key[KEY_INPUT_DOWN] == 1){//下キーが押されたら下に行く処理
			count = 1;
		}
		if(Key[KEY_INPUT_UP] == 1){//上キーが押されたら上に行く処理
			count = 0;
		}
		if(Key[KEY_INPUT_SPACE] == 1 || Key[KEY_INPUT_RETURN] == 1){
			if(count == 0){
//				strcpy_s(dummy, sizeof(dummy),"MapData\\");
//				strcat_s(dummy, sizeof(filename) - strlen(filename) - 1, filename);
				strcpy(dummy,"MapData\\");
				strcat(dummy,filename);
				remove(dummy);
			}
			return;
		}
		for(i = 0;i <= 1;i++){
			if(i == count){
				Menusele[i].x = 250;
				Menusele[i].cr = GetColor(255,0,255);
			}
			else{
				Menusele[i].x = 200;
				Menusele[i].cr = GetColor(255,255,255);
			}
		}
		//描画処理
		DrawFormatString(200,40,GetColor(255,255,255),"本当に削除しますか？");
		for(i = 0;i <= 1;i++){
			DrawFormatString(Menusele[i].x,Menusele[i].y,Menusele[i].cr,Menusele[i].name);//文字の表示
		}
		DrawFormatString(500,50,GetColor(255,255,255),"削除中");
	}
	return;
}