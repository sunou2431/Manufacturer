#include "DxLib.h"
#include "make_object.h"
#include "make.h"
#include <math.h>
#include <windows.h>

//MessageBox(NULL,"","確認",MB_YESNO);

bool mouse_down(void)
{
	static int win_x = 0, win_y = 0, dummy;
	static int col=1;
	int sel_b_x, sel_b_y;
	select_box(&sel_b_x, &sel_b_y, true);
	int pal_no=-10;
	pal_num(&pal_no);
	double scr_x=-1;
	scroll(&scr_x);
	int pal_x = -1, pal_y, pal_siz_x, pal_siz_y,pal_hed;
	static int pal_xx,pal_yy;
	static bool min_sw=false;
	static int click_x, click_y;
	static int Rclick_time=0;
	bool ple_sw=false;
	int box_itiji,box_itiji2,box_itiji_x,box_itiji_y;
	if (win_x == 0 && win_y == 0) GetScreenState(&win_x, &win_y, &dummy);
	palette(&pal_x, &pal_y, &pal_siz_x, &pal_siz_y,&pal_hed);
	int mouse_x, mouse_y;
	GetMousePoint(&mouse_x, &mouse_y);

	if (mouse_x > 0 && mouse_x < win_x && mouse_y>0 && mouse_y < win_y) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			Rclick_time=0;
			if ((mouse_x > pal_x && mouse_x < pal_x + pal_siz_x &&
				mouse_y > pal_y && mouse_y < pal_y + pal_siz_y) || click_x >= 0) {
				if (mouse_y<pal_y + pal_hed || click_x >= 0) {
					if(pal_x+160<mouse_x&&mouse_x<pal_x + pal_siz_x-2&&
						 pal_y+2<mouse_y&&mouse_y<pal_y + pal_hed-2)min_sw=true;
					else{
						if (click_x < 0) {
							click_x = mouse_x;
							click_y = mouse_y;
						}
						pal_x -= click_x - mouse_x;
						pal_y -= click_y - mouse_y;
						if (pal_x < 0)pal_x = 0;
						if (pal_x + pal_siz_x > win_x)pal_x = win_x - pal_siz_x;
						if (pal_y <0)pal_y = 0;
						if (pal_y +pal_hed> win_y)pal_y = win_y -pal_hed;
						palette(&pal_x, &pal_y, &pal_siz_x, &pal_siz_y,&pal_hed);
						click_x = mouse_x;
						click_y = mouse_y;
					}
				}
				pal_y+=pal_hed+20;
				for (int i=0;i<8;i++){
					if(i%2){
						if(mouse_x>pal_x+120 && mouse_y>pal_y+(80*(i/2)) &&
							mouse_x<pal_x+120+60 && mouse_y<pal_y+(80*(i/2))+60){
							col=(i+1)+((pal_no-1)*8);
							sel_b_x = (i % 2)+1-sel_b_x;
							sel_b_y = (i / 2)+1 - sel_b_y;
							select_box(&sel_b_x, &sel_b_y, false);
							pal_col(&col,false);
						}
					}
					else {
						if(mouse_x>pal_x+20 && mouse_y>pal_y+(80*(i/2)) &&
							mouse_x<pal_x+20+60 && mouse_y<pal_y+(80*(i/2))+60){
							sel_b_x = (i % 2)+1 - sel_b_x;
							sel_b_y = (i / 2)+1 - sel_b_y;
							select_box(&sel_b_x, &sel_b_y, false);
							col=(i+1)+((pal_no-1)*8);
							pal_col(&col,false);
						}
					}
				}
				if(mouse_x>pal_x+20 && mouse_y>pal_y+(80*4) &&
					mouse_x<pal_x+20+60 && mouse_y<pal_y+(80*4)+20){
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

				}
				pal_no=-1;
				if(mouse_x>pal_x+120-5+3 && mouse_y>pal_y+(80*4)+3 &&
					mouse_x<pal_x+120+20-5-3 && mouse_y<pal_y+(80*4)+20-3)pal_num(&pal_no);
				pal_no=1;
				if(mouse_x>pal_x+160+5+3 && mouse_y>pal_y+(80*4)+3 &&
					mouse_x<pal_x+160+20+5-3 && mouse_y<pal_y+(80*4)+20-3)pal_num(&pal_no);

				pal_x=-1;pal_y=-1;
				palette(&pal_x, &pal_y, &pal_siz_x, &pal_siz_y,&pal_hed);


			}
			else if (click_x < 0){
				pal_col(&col,true);
				map((mouse_x / 50)+floor(scr_x), mouse_y / 50, col);
			}

		}
		else if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0){
			map((mouse_x / 50)+floor(scr_x), mouse_y / 50, 0);
			Rclick_time++;
			if(Rclick_time>20){
				for (int i = 0; i <100; i++)for (int j = 0;j < 12; j++)if (99==map(i,j,-1))map(i,j, 0);
				map((mouse_x / 50)+floor(scr_x), mouse_y / 50, 99);
			}
		}
		else if ((GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0){
			Rclick_time=0;
			box_itiji=map((mouse_x / 50)+floor(scr_x), mouse_y / 50,-1);
			if(box_itiji!=0){
			pal_col(&box_itiji,false);
			select_box(&sel_b_x, &sel_b_y, true);
			box_itiji_x=((box_itiji-1)%2)-(sel_b_x-1);
			box_itiji_y=(((box_itiji-1)%8)/2)-(sel_b_y-1);
			select_box(&box_itiji_x, &box_itiji_y, false);
			int pal_no=-10;
			pal_num(&pal_no);
			box_itiji2=(box_itiji/8)-(pal_no-1);
			pal_num(&box_itiji2);
			}
		}
		else {
			Rclick_time=0;
			click_x = -1;
			if(pal_x+160<mouse_x&&mouse_x<pal_x + pal_siz_x-2&&
				pal_y+2<mouse_y&&mouse_y<pal_y + pal_hed-2&&min_sw){
				if(pal_x==0&&pal_y==win_y-pal_hed){				
					pal_x=pal_xx;
					pal_y=pal_yy;
					palette(&pal_x, &pal_y, &pal_siz_x, &pal_siz_y,&pal_hed);	
				}else{
					pal_xx=pal_x;
					pal_x=0;
					pal_yy=pal_y;
					pal_y=win_y-pal_hed;
					palette(&pal_x, &pal_y, &pal_siz_x, &pal_siz_y,&pal_hed);	
				}
			}
			min_sw=false;

		}
		
		if(mouse_x>win_x-50){scr_x=0.1;scroll(&scr_x); }
		if(mouse_x<50){scr_x=-0.1;scroll(&scr_x);}
	}
	return false;
}
