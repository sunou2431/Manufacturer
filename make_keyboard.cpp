#include "DxLib.h"
#include "make_object.h"
#include "make.h"
#include <math.h>
#include <windows.h>
#include "OBJECT.h"

//MessageBox(NULL,"","確認",MB_YESNO);

bool key_down(void)
{
	int sel_b_x=0,sel_b_y=0,pal_sel;
	bool enter_sw=enter(true,true);
	bool ple_sw=false;
	static int key[256];
	gpUpdataKey(key);
	int pal_no = -10;
	pal_num(&pal_no);



	if(key[KEY_INPUT_UP] == 1){sel_b_y=-1;select_box(&sel_b_x,&sel_b_y,false);}
	if(key[KEY_INPUT_DOWN] == 1){sel_b_y=1;select_box(&sel_b_x,&sel_b_y,false);}
	if(key[KEY_INPUT_RIGHT] == 1){sel_b_x=1;select_box(&sel_b_x,&sel_b_y,false);}
	if(key[KEY_INPUT_LEFT] == 1){sel_b_x=-1;select_box(&sel_b_x,&sel_b_y,false);}
	if(key[KEY_INPUT_M] == 1){
		make_minmap(!make_minmap(true,true),false);
	}
	if(key[KEY_INPUT_TAB] == 1){
		make_help(!make_help(true,true),false);
	}
	if(key[KEY_INPUT_ESCAPE] == 1)if(MessageBox(NULL,"保存せず終了しますか","確認",MB_YESNO)==IDYES)return true;
	if(key[KEY_INPUT_RETURN] == 1 && enter_sw){
		for (int i = 0; i <100; i++){
			for (int j = 0;j < 12; j++){
				if (99==map(i,j,-1)){
					ple_sw=true;
					break;
				}
			}
			if(ple_sw)break;
		}
		if(ple_sw){
		if(MessageBox(NULL,"マップを書き出しますか","確認",MB_YESNO)==IDYES){
			output_map();
			if(MessageBox(NULL,"終了しますか","確認",MB_YESNO)==IDYES)return true;
		}else {
			if(MessageBox(NULL,"保存せず終了しますか","確認",MB_YESNO)==IDYES)return true;
		}
		}else{
			if(MessageBox(NULL,"プレイヤーが配置されていません\n（マウス右ボタン長押しで配置）\n保存せず終了しますか","確認",MB_YESNO)==IDYES)return true;
		}
	}else enter(true,false);
							
						

	select_box(&sel_b_x,&sel_b_y,true);
	pal_sel=((sel_b_y*2)-(2-sel_b_x))+((pal_no - 1)*8);
	pal_col(&pal_sel,false);
	return false;
}

