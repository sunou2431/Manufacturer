#include "DxLib.h"
#include <string.h>


int map(int map_x, int map_y, int map_num)
{
	static int maps[100][12];
	if (map_num >= 0) maps[map_x][map_y] = map_num;
	else return maps[map_x][map_y];
	return 0;
}

void palette(int *pal_x,int *pal_y, int *pal_siz_x,int *pal_siz_y,int *pal_hed)
{
	static int
		palette_x = 500,
		palette_y = 100,
		palette_size_x = 200,
		palette_size_y = 400,
		palette_hed=25;
	
	if (*pal_x >= 0 || *pal_y >= 0) {
		palette_x = *pal_x;
		palette_y = *pal_y;
	}
	else {
		*pal_x = palette_x;
		*pal_y = palette_y;
		*pal_siz_x = palette_size_x;
		*pal_siz_y = palette_size_y;
		*pal_hed=palette_hed;
	}
}

void pal_num(int *num)
{
	static double number=1;
	static bool mouse=true;
	if (*num>-10){
		if (mouse ){
			number+=*num;
			if(number<1)number=1;
			if(number>1)number=1;
			mouse=false;
		}
	}else{
		*num=(int)number;
	}
	if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) == 0 ) mouse=true;

}
void pal_col(int *col,bool sw)
{
	static int select_color;

	if (sw)*col=select_color;
	else select_color=*col;

}

void scroll(double *scr_x)
{
	static double scroll_x =0;

	if(*scr_x==-100)scroll_x=0;
	if (*scr_x>-1){
		scroll_x+=*scr_x;
		if(scroll_x<0)scroll_x=0;
		if(scroll_x>100-16)scroll_x=100-16;
}	else{
		*scr_x=scroll_x;
	}

}

void name(char *input_name,bool sw)
{
	static char name[100];

	if (sw)strcpy(input_name,name);
	else strcpy(name,input_name);

}

void select_box(int *sel_b_x,int *sel_b_y,bool sel_b_sw)
{
	static int select_box_x=1,select_box_y=1;
	static int pal_plus=1,pal_minus=-1;
	int pal_no = -10;
	pal_num(&pal_no);

	if (sel_b_sw){
		*sel_b_x=select_box_x;
		*sel_b_y=select_box_y;
	}else{
		select_box_x+=*sel_b_x;
		select_box_y+=*sel_b_y;
		if(select_box_x<1){
			pal_num(&pal_minus);
			if(pal_no>1)select_box_x=2;
			else select_box_x = 1;
		}
		if(select_box_x>2){
			pal_num(&pal_plus);
			if (pal_no < 2)select_box_x=1;
			else select_box_x = 2;
		}
		if(select_box_y<1)select_box_y=1;		
		if(select_box_y>4)select_box_y=4;		
	}

}
void select_map(int *sel_m_x,int *sel_m_y,bool sel_m_sw)
{
	static int select_map_x=1,select_map_y=1;

	if (sel_m_sw){
		*sel_m_x=select_map_x;
		*sel_m_y=select_map_y;
	}else{
		select_map_x+=*sel_m_x;
		select_map_y+=*sel_m_y;
		if(select_map_x<1)select_map_x=1;
		if(select_map_x>4)select_map_x=4;
		if(select_map_y<1)select_map_y=1;		
		if(select_map_y>4)select_map_y=4;		
	}

}

bool enter(bool sw,bool rw_sw){
	static bool enter_sw=false;
	if(rw_sw)return enter_sw;
	enter_sw=sw;
	return 0;
}

bool make_minmap(bool sw,bool rw_sw){
	static bool map_sw=false;
	if(rw_sw)return map_sw;
	map_sw=sw;
	return 0;
}
bool make_help(bool sw,bool rw_sw){
	static bool help_sw=true;
	if(rw_sw)return help_sw;
	help_sw=sw;
	return 0;
}

void obj_init(void){
	int pal_no=-5;
	pal_num(&pal_no);
	double scr=-100;
	scroll(&scr);
	int sel_col=0;
	pal_col(&sel_col,false);
	int pal_x=500, pal_y=100, pal_siz_x, pal_siz_y,pal_hed;
	palette(&pal_x, &pal_y, &pal_siz_x, &pal_siz_y,&pal_hed);
	int sel_b_x=-5,sel_b_y=-5;
	select_box(&sel_b_x,&sel_b_y,false);
	make_minmap(true,false);


}


