#include "DxLib.h"
#include "OBJECT.h"
#include "xxx_mini.h"
#include "xxx_mini_object.h"

void hito_data(int *hito_x, int *hito_y, int *hito_way, bool rw_sw) {
	static int x = 50 * (16 / 2 - 1), y = -20 + 50 * (12 / 2 - 1), way = 0, move = 0, move2 = 1, before = 0;
	static int win_x = 0, win_y = 0, dummy;
	static int scr_x, scr_y, scr_xx, scr_yy, x_sw = 0, y_sw = 0;
	mini_scroll(&scr_x, &scr_y, true);
	if (win_x == 0 && win_y == 0) GetScreenState(&win_x, &win_y, &dummy);
	mini_map(((x) / 50) + scr_x, ((y - 30) / 50) + 1 + scr_y, 0);
	if (rw_sw) {
		if(*hito_way==-100){ y_sw = 0; x_sw = 0; }
		*hito_x = x;
		*hito_y = y;
		*hito_way = way;
	}
	else {
		if (mini_map(((x + *hito_x) / 50) + scr_x, ((y + *hito_y - 30) / 50) + 1 + scr_y, -1) == 0) {
			if (0 <= x + *hito_x && win_x >= x + *hito_x + 50) {
				scr_y = 0;
				if (x + *hito_x + 50 <= 150) {
					scr_x = -1;
					mini_scroll(&scr_x, &scr_y, false);
					mini_scroll(&scr_x, &scr_y, true);
					if (scr_x == scr_xx&&scr_x == 0)x_sw = -1;
					if (x + 50 >= 150 && scr_x != scr_xx && x_sw != -1) {
						x -= *hito_x;
						x_sw = 0;
					}
				}
				else if (x + *hito_x >= win_x - 150) {
					scr_x = 1;
					mini_scroll(&scr_x, &scr_y, false);
					mini_scroll(&scr_x, &scr_y, true);
					if (scr_x == scr_xx&&scr_x == 75 - 16)x_sw = 1;
					if (x < win_x - 150 && scr_x != scr_xx&& x_sw != 1) {
						x -= *hito_x;
						x_sw = 0;
					}
				}
				x += *hito_x;
				scr_xx = scr_x;
			}
			if (0 <= y + *hito_y + 30 && win_y >= y + *hito_y + 70) {
				scr_x = 0;
				if (y + *hito_y + 70 <= 150) {
					scr_y = -1;
					mini_scroll(&scr_x, &scr_y, false);
					mini_scroll(&scr_x, &scr_y, true);
					if (scr_y == scr_yy&&scr_y == 0)y_sw = -1;
					if (y + 70 >= 150 && scr_y != scr_yy&&y_sw != -1) {
						y -= *hito_y;
						y_sw = 0;
					}
				}
				else if (y + *hito_y >= win_y - 200) {
					scr_y = 1;
					mini_scroll(&scr_x, &scr_y, false);
					mini_scroll(&scr_x, &scr_y, true);
					if (scr_y == scr_yy&&scr_y == 75 - 12 - 1)y_sw = 1;
					if (y < win_y - 200 && scr_y != scr_yy&&y_sw != 1) {
						y -= *hito_y;
						y_sw = 0;
					}
				}
				y += *hito_y;
				scr_yy = scr_y;
			}
		}
		else if (mini_map(((x + *hito_x) / 50) + scr_x, ((y + *hito_y - 30) / 50) + 1 + scr_y, -1) == 75) {
			map_init();
			enemy_init(false);

		}
		else {
			scr_xx = -1;
			scr_yy = -1;
		}
		if (before == *hito_way) {
			if (move == 2)move2 = -1;
			else if (move == 0)move2 = 1;
			move += move2;
		}
		else {
			move = 0;
			move2 = 1;
		}
		way = *hito_way + move;
		before = *hito_way;
	}

	mini_scroll(&scr_x, &scr_y, true);
	mini_map(((x) / 50) + scr_x, ((y - 30) / 50) + 1 + scr_y, 50);
}

int mini_map(int map_x, int map_y, int map_num)
{
	static int maps[75][75];
	if (map_num >= 0) maps[map_x][map_y] = map_num;
	else return maps[map_x][map_y];
	return 0;
}

void mini_scroll(int *scr_x, int *scr_y, bool rw_sw)
{
	static double scroll_x = 0, scroll_y = 0;

	if (rw_sw) {
		*scr_x = int(scroll_x);
		*scr_y = int(scroll_y);
	}
	else {
		scroll_x += *scr_x;
		if (scroll_x<0)scroll_x = 0;
		if (scroll_x>75 - 16)scroll_x = 75 - 16;
		scroll_y += *scr_y;
		if (scroll_y<0)scroll_y = 0;
		if (scroll_y>75 - 12 - 1)scroll_y = 75 - 12 - 1;
	}

}

void mini_room(int r_num, room *r, bool rw_sw)
{
	static room rooms[5];

	if (rw_sw) {
		r->x1 = rooms[r_num].x1;
		r->y1 = rooms[r_num].y1;
		r->x2 = rooms[r_num].x2;
		r->y2 = rooms[r_num].y2;
	}
	else
	{
		rooms[r_num].x1 = r->x1;
		rooms[r_num].y1 = r->y1;
		rooms[r_num].x2 = r->x2;
		rooms[r_num].y2 = r->y2;
	}
}
void hito_status(int *str,int *def,int *vit,int *dex,bool rw_sw){
	static int str_k,def_k,vit_k,dex_k;
	if(rw_sw){
		*str=str_k;
		*def=def_k;
		*vit=vit_k;
		*dex=dex_k;
	}else{
		str_k=*str;
		def_k=*def;
		vit_k=*vit;
		dex_k=*dex;
	}

}
void hito_sta_init(void){
	const int num=4;
	int sta[num];
	int min[num]={5,5,5,5};
	int max[num]={15,15,15,15};
	int rook_num=0,rook_max=2;
	bool rook[num];
	for (int j=0;j<num;j++)rook[j]=true;

	int Key[256];
	int i;
	int count = 0;

	MenuElement_t Menusele[num*2+2] = {
		{250,180,GetColor(255, 255, 255),"STR:"},
		{200,210,GetColor(255, 255, 255),"DEF:" },
		{200,240,GetColor(255, 255, 255),"VIT:"},
		{200,270,GetColor(255, 255, 255),"DEX:" },
		{200,350,GetColor(255, 255, 255),"やり直し"},
		{200,380,GetColor(255, 255, 255),"決定"},
		{350,180,GetColor(255, 255, 255),""},
		{300,210,GetColor(255, 255, 255),""},
		{300,240,GetColor(255, 255, 255),""},
		{300,270,GetColor(255, 255, 255),""},
	};
	for(int j=0;j<num;j++){
		if(rook[j])sta[j]=GetRand(max[j]-min[j])+min[j];
	}

	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0){
	
		gpUpdataKey(Key);
		if(Key[KEY_INPUT_DOWN] == 1){
			count++;
			count = count % (num+2);
		}
		if(Key[KEY_INPUT_UP] == 1){
			count = count += (num+1);
			count = count % (num+2);
		}
		if( Key[KEY_INPUT_RETURN] == 1){
			if(count <num){
				rook[count]=!rook[count];
				rook_num=0;
				for(int j=0;j<num;j++)if(!rook[j])rook_num++;
				if(rook_num>rook_max){
					rook[count]=!rook[count];
					rook_num--;
				}
			}
			if (count == num) {
				for(int j=0;j<num;j++){
					if(rook[j]){
						sta[j]=GetRand(max[j]-min[j])+min[j];
					}
				}				
			}
			if (count == num+1) {
				hito_status(&sta[0],&sta[1],&sta[2],&sta[3],false);
				hito_sta_conv();
				return;
			}
		}
		for(i = 0;i <num+2;i++){
			if(count == i){
				Menusele[i].cr = GetColor(255,0,255);
				Menusele[i].x = 250;
				if(i<num){
					Menusele[i+num+2].cr = GetColor(255,0,255);
					Menusele[i+num+2].x = 350;
				}
			}
			else{
				Menusele[i].cr = GetColor(255,255,255);
				Menusele[i].x = 200;
				if(i<num){
					Menusele[i+num+2].cr = GetColor(255,255,255);
					Menusele[i+num+2].x = 300;
				}
			}
		}

		DrawFormatString(100,100 , GetColor(255, 255, 255), "初期ステータス");
		DrawFormatString(400,100 , GetColor(255, 255, 255), "残りロック数：%d",rook_max-rook_num);
		for(i = 0;i <num+2;i++){
			DrawFormatString(Menusele[i].x,Menusele[i].y,Menusele[i].cr,Menusele[i].name);
			if(i<num){
				if(rook[i])DrawFormatString(Menusele[i+num+2].x,Menusele[i+num+2].y,Menusele[i+num+2].cr, "%d",sta[i]);
				else DrawFormatString(Menusele[i+num+2].x,Menusele[i+num+2].y,Menusele[i+num+2].cr, "[%d]",sta[i]);
			}
		}

	}

}
void hito_sta_conv(void)
{
	int str_k,def_k,vit_k,dex_k;
	int hp,atk,def,hit;

	hito_status(&str_k,&def_k,&vit_k,&dex_k,true);
	hp=vit_k*20;
	atk=str_k*5;
	def=def_k*5;
	hit=dex_k*5;
	hito(&hp,&atk,&def,&hit,false);

}