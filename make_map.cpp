#include "DxLib.h"
#include "make_object.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "make_object.h"

using namespace std;

void output_map(void)
{
	char map_name[100];
	bool space_sw;
	int InputHandle ;
	char root[100]="MapData\\";

	HANDLE hFind;
	WIN32_FIND_DATA win32fd;

	do{
		do{
			space_sw=true;
			InputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ;
			SetActiveKeyInput( InputHandle ) ;
			name(map_name,true);
			SetKeyInputString( map_name , InputHandle ) ;
			while( ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
			{
				if( CheckKeyInput( InputHandle ) != 0 ) break ;
				DrawKeyInputModeString( 640 , 480 ) ; 
				DrawString( 0 , 0 , "マップ名を入力してください" , GetColor( 255 , 255 , 255 ) ) ;
				DrawString( 0 , 16 , "（未入力で保存を取り消し）" , GetColor( 255 , 255 , 255 ) ) ;
				DrawKeyInputString( 0 , 32 , InputHandle ) ;
			}
			GetKeyInputString( map_name , InputHandle ) ;
			DeleteKeyInput( InputHandle ) ;
			for(int i=0;i<100;i++)if(map_name[i]==' ')space_sw=false;
			if(strcmp("",map_name)!=0 && space_sw)break;
		}while(MessageBox(NULL,"未入力かスペースが入力されています\n保存されませんがよろしいですか","確認",MB_YESNO)==IDNO);

		hFind = FindFirstFile("MapData\\*.*", &win32fd);
		if (hFind == INVALID_HANDLE_VALUE)return;

		do{
			if(win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
			else if(strcmp(win32fd.cFileName,map_name)==0)break;
		}while (FindNextFile(hFind, &win32fd));
		if(strcmp(win32fd.cFileName,map_name)!=0)break;
	}while (MessageBox(NULL,"上書きしますか","確認",MB_YESNO)==IDNO);

	strcat(root,map_name);
	remove(root);
	ofstream mapfile(root);
	for (int j = 0;j < 12; j++) {
		for (int i = 0; i <100 ; i++) {
			mapfile<<map(i,j,-1);	
			mapfile<<',';
		}
		mapfile<<'\n';
	}

}

void input_map(char map_name[100])
{
	char line[12][310];
	char itiji[5];
	char root[100]="MapData\\";
	int count = 0,count2=0;
	for (int k = 0; k < 5; k++)itiji[k] = '\0';
	int FileHandle ;
	strcat(root,map_name);
	FileHandle = FileRead_open( root ) ;
	for(int i=0;i<12;i++)FileRead_gets( line[i],310, FileHandle ) ;
	FileRead_close( FileHandle ) ;
	for (int j = 0;j < 12; j++) {
		for (int i = 0; i <310 ; i++) {
			if (line[j][i] == ',') {
				count = 0;

				map(count2, j, atoi(itiji));
				for (int k = 0; k <5; k++)itiji[k] = '\0';
				count2++;
			}
			else {
				itiji[count] = line[j][i];
				count++;
			}
			if (count2 > 100)break;
		}
		count2 = 0;
}

}

void init_map(void)
{
	for (int j = 0;j < 12; j++) {
		for (int i = 0; i <100 ; i++) {
			map(i,j,0);
		}
	}
}