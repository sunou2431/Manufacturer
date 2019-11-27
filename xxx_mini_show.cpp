#include "DxLib.h"
#include "xxx_mini.h"
#include "xxx_mini_object.h"
#include <math.h>

void mini_show(void)
{
	static int hito_g[12];
	static int ene[12];
	int enemy_way, enemy_type;
	int scr_x, scr_y;
	mini_scroll(&scr_x, &scr_y, true);
	static int win_x = 0, win_y = 0, dummy;
	if (win_x == 0 && win_y == 0) GetScreenState(&win_x, &win_y, &dummy);
	int hito_x = 0, hito_y = 0, hito_way = 0;
	hito_data(&hito_x, &hito_y, &hito_way, true);
	int  hp, atk, def,hit;
	hito(&hp, &atk, &def,&hit, true);
	int  e_hp, e_atk, e_def,e_hit;
	static int GHandle[16], Gnum;
	if (GHandle[0] == 0) LoadDivGraph("map3.png", 16, 4, 4, 50, 50, GHandle);
	if (hito_g[0] == 0)LoadDivGraph("minigame\\hito1.png", 12, 3, 4, 20, 28, hito_g);
	if (ene[0] == 0)LoadDivGraph("minigame\\enemy.png", 12, 3, 4, 20, 28, ene);
	for (int i = 0 + scr_x; i < 16 + scr_x; i++) {
		//for (int i = 0 + scr_x; i < 200 + scr_x; i++) {
		for (int j = 0 + scr_y; j < 12 + scr_y; j++) {
			//for (int j = 0 + scr_y; j < 200 + scr_y; j++) {
			Gnum = mini_map(i, j, -1);
			if (Gnum)DrawGraph((i * 50) - (scr_x * 50), (j * 50) - (scr_y * 50), GHandle[Gnum - 1], FALSE);

			if(Gnum==75)DrawGraph((i * 50) - (scr_x * 50), (j * 50) - (scr_y * 50), GHandle[12], FALSE);
			if (Gnum >= 100) {
				enemy(Gnum-100, &e_hp, &e_atk, &e_def,&e_hit, true);
				enemy_etc(Gnum - 100, &enemy_way, &enemy_type, true);
				DrawRotaGraph3((i * 50) - (scr_x * 50), (j * 50) - (scr_y * 50) - 20, 0, 0, 2.5, 2.5, 0, ene[enemy_way], TRUE, FALSE);
				DrawFormatString((i * 50) - (scr_x * 50), (j * 50) - (scr_y * 50) - 20, GetColor(255, 255, 255), "HP:%d", e_hp);

			}
			//if (Gnum)DrawRotaGraph3((i * 5) - (scr_x * 5)+10, (j * 5) - (scr_y * 5) + 10, 0, 0, 0.1, 0.1, 0, GHandle[Gnum - 1], TRUE, FALSE);

		}
	}
	for (int i = 0; i < 75; i++) {
		for (int j = 0; j <75; j++) {
			Gnum = mini_map(i, j, -1);
			if (Gnum)DrawRotaGraph3((i * 1) + 10, (j * 1) + 10, 0, 0, 0.02, 0.02, 0, GHandle[Gnum], TRUE, FALSE);
			if (Gnum == 75)DrawRotaGraph3((i * 1) + 10, (j * 1) + 10, 0, 0, 0.02, 0.02, 0, GHandle[12], TRUE, FALSE);
			if ((hito_x / 50) + scr_x == i && (hito_y / 50) + scr_y + 1 == j)DrawRotaGraph3((i * 1) + 10, (j * 1) + 10, 0, 0, 0.02, 0.02, 0, GHandle[4], TRUE, FALSE);

		}
	}
	DrawRotaGraph3(hito_x, hito_y, 0, 0, 2.5, 2.5, 0, hito_g[hito_way], TRUE, FALSE);
	DrawFormatString(100, 0, GetColor(255, 255, 255), "HP:%d", hp);
	//for (int i = 0; i < 5; i++) {
	//	mini_room(i, &r, true);

	//	DrawFormatString(0, 200+(i*16), GetColor(255, 255, 255), "%d,%d,%d,%d", r.x1,r.y1,r.x2,r.y2);
	//}

}

