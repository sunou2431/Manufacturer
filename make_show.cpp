#include "DxLib.h"
#include "make_object.h"
#include <math.h>


void show(void)
{
	static int win_x = 0, win_y = 0, dummy;
	static int line_c = GetColor(100, 100, 100);
	static int box_c = GetColor(255, 255, 255);
	static int pal_c = GetColor(175, 175, 175);
	static int boxs_c[3]={GetColor(0, 0, 200),GetColor(0, 200, 0),GetColor(200, 0, 0)};
//	static int GHandle[2][ 8 ] ,Gnum;
	static int GHandle[ 12 ] ,Gnum;
	static int lr[2],out,bg,ple;
	static char help[11][70]={
		"枠内のブロックを左クリック　＝　選択ブロックの変更",
		"矢印キー　＝　選択ブロックの変更",
		"マス目を左クリック　＝　選択ブロックの設置",
		"設置されたブロックでマウスホイールをクリック　＝　選択ブロックの変更",
		"設置されたブロックを右クリック　＝　設置ブロックの削除",
		"マス目をマウス右ボタン長押し　＝　プレイヤーの設置",
		"outputボタンを左クリック　＝　保存",
		"Enterキー　＝　保存",
		"Escキー　＝　保存せず終了",
		"Mキー　＝　ミニマップの表示切り替え",
		"Tabキー　＝　ヘルプの表示切り替え"
	},help_num=0;
	static int help_time=0,help_max[10];
	if(help_max[0]==0)for(int i=0;i<10;i++)for(help_max[i]=0;help[i][help_max[i]]!='\0';help_max[i]++);

	int pal_no=-10;
	pal_num(&pal_no);
	double scr=-1;
	scroll(&scr);
	int sel_col;
	pal_col(&sel_col,true);
	int pal_x=-1, pal_y, pal_siz_x, pal_siz_y,pal_hed;
	palette(&pal_x, &pal_y, &pal_siz_x, &pal_siz_y,&pal_hed);
	//if(GHandle[0][0]==0)LoadDivGraph( "map.png" , 8, 2,4 , 50 , 50 , GHandle[0] ) ;
	//if(GHandle[1][0]==0)LoadDivGraph( "map2.png" , 8, 2,4 , 50 , 50 , GHandle[1] ) ;
	if(GHandle[0]==0){
		LoadDivGraph( "map_block.png" , 4, 4,1 , 32 , 32 , GHandle ) ;
		lr[0]=LoadGraph( "l.png" ) ;
		lr[1]=LoadGraph( "r.png" ) ;
		out=LoadGraph( "out.png" ) ;
		bg=LoadGraph( "bg.jpg" ) ;
		ple=LoadGraph( "p.bmp" ) ;
		for(int i=4;i<12;i++)GHandle[i]=0;

	}
	if (win_x == 0 && win_y == 0) GetScreenState(&win_x, &win_y, &dummy);
	DrawExtendGraph(0,0,win_x,win_y,bg,TRUE);
	for (int i = 0; i <= win_x+(floor(scr)*50); i += 50) DrawLine(i-(floor(scr)*50), 0, i-(floor(scr)*50), win_y, line_c);
	for (int i = 0; i <= win_y; i += 50) DrawLine(0, i, win_x, i, line_c);

	for (int i = 0+floor(scr); i <16+floor(scr) ; i++) {
		for (int j = 0;j <= 12; j++) {
			Gnum=map(i,j,-1);
			if(Gnum==99)DrawExtendGraph( i*50-(floor(scr)*50) , j*50 ,(i*50-(floor(scr)*50))+50,(j*50)+50, ple, TRUE ) ;
			else if(Gnum)DrawExtendGraph( i*50-(floor(scr)*50) , j*50 ,(i*50-(floor(scr)*50))+50,(j*50)+50, GHandle[ Gnum-1 ] , TRUE ) ;
			
		}
	}
	if(make_minmap(true,true)){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150); 
	DrawBox(20, 25, 230, 75, pal_c, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200); 
	DrawBox(floor(scr)*2+25, 40, floor(scr)*2+16*2+25, 12*2+40, box_c, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255); 
	for (int i = 0; i <100; i++) {
		for (int j = 0;j < 12; j++) {
			Gnum=map(i,j,-1);
			if(Gnum)DrawExtendGraph( (i*2)+25 , (j*2)+40 ,(i*2)+2+25,(j*2)+2+40, GHandle[ Gnum-1 ] , TRUE ) ;
			
		}
	}
	}

	if(make_help(true,true)){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); 
	DrawBox(0,win_y-25,win_x,win_y, pal_c, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawString(10,win_y-20,"HELP :",GetColor( 255 , 255 , 255 )) ;
	DrawFormatString(100,win_y-20, GetColor( 255 , 255 , 255 ), "%s",help[help_num] ) ;
	help_time++;
	if(help_time>help_max[help_num]*4+30){
		help_time=0;
		help_num=(help_num+1)%11;
	}
	}
	DrawBox(pal_x, pal_y, pal_x + pal_siz_x, pal_y + pal_hed, pal_c, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); 
	DrawBox(pal_x, pal_y, pal_x + pal_siz_x, pal_y + pal_siz_y, pal_c, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawExtendGraph(pal_x+160, pal_y+2, pal_x + pal_siz_x-2, pal_y + pal_hed-2, out, TRUE);
	DrawBox(pal_x+170, pal_y+11, pal_x + pal_siz_x-12, pal_y + pal_hed-11, GetColor( 0,0,0 ), TRUE);
	pal_y+=pal_hed+20;


	for (int i=0;i<8;i++){
		if(i%2){
			if (sel_col==(i+((pal_no-1)*8))+1)DrawExtendGraph((pal_x+120)-5,(pal_y+(80*(i/2)))-5,(pal_x+120+60)+5,(pal_y+(80*(i/2))+60)+5,GHandle[i+((pal_no-1)*8)],TRUE);
			else DrawExtendGraph(pal_x+120,pal_y+(80*(i/2)),pal_x+120+60,pal_y+(80*(i/2))+60,GHandle[i+((pal_no-1)*8)],TRUE);
		}
		else {
			if (sel_col==(i+((pal_no-1)*8))+1)DrawExtendGraph((pal_x+20)-5,(pal_y+(80*(i/2)))-5,(pal_x+20+60)+5,(pal_y+(80*(i/2))+60)+5,GHandle[i+((pal_no-1)*8)],TRUE);
			else DrawExtendGraph(pal_x+20,pal_y+(80*(i/2)),pal_x+20+60,pal_y+(80*(i/2))+60,GHandle[i+((pal_no-1)*8)],TRUE);
		}
	}

	DrawExtendGraph(pal_x+20,pal_y+(80*4),pal_x+20+60,pal_y+(80*4)+20,out,TRUE);
	DrawString(pal_x+24,pal_y+(80*4)+2,"output",GetColor( 0,0,0 )) ;

	DrawExtendGraph(pal_x+120-5+3,pal_y+(80*4)+3,pal_x+120+20-5-3,pal_y+(80*4)+20-3,lr[0],TRUE);
	DrawFormatString(pal_x+145,pal_y+(80*4)+5, GetColor( 255 , 255 , 255 ), "%d",pal_no ) ;
	DrawExtendGraph(pal_x+160+5+3,pal_y+(80*4)+3,pal_x+160+20+5-3,pal_y+(80*4)+20-3,lr[1],TRUE);
}