#include "DxLib.h"
#include "xxx_mini.h"
#include "xxx_mini_class.h"
#include "xxx_mini_object.h"


//enemy::enemy()
//	:e_x(0)
//	,e_y(GetRand(100))
//{
//}
//
//void enemy::test(void){
//	e_y=GetRand(100);
//}


void hito(int *hp, int *atk, int *def, int *hit,bool rw_sw) {
	static int hp_s, atk_s, def_s, hit_s;
	if (rw_sw) {
		*hp = hp_s;
		*atk = atk_s;
		*def = def_s;
		*hit = hit_s;
	}
	else {
		hp_s = *hp;
		atk_s = *atk;
		def_s = *def;
		hit_s = *hit;
	}
}

void hito_atk(void)
{
	int hito_x = 0, hito_y = 0, hito_way = 0;
	int scr_x, scr_y;
	mini_scroll(&scr_x, &scr_y, true);

	hito_data(&hito_x, &hito_y, &hito_way, true);
	switch (hito_way) {
	case 0:
	case 1:
	case 2:
		hito_y += 50;
		break;
	case 3:
	case 4:
	case 5:
		hito_x -= 50;
		break;
	case 6:
	case 7:
	case 8:
		hito_x += 50;
		break;
	case 9:
	case 10:
	case 11:
		hito_y -= 50;
		break;
	}

	hito_damage(hito_x,hito_y);
}

void hito_damage(int hito_x,int hito_y) {
	int id, hp, atk, def,hit;
	int  m_hp, m_atk, m_def,m_hit;

	int scr_x, scr_y;
	mini_scroll(&scr_x, &scr_y, true);
	
	id = mini_map(hito_x / 50 + scr_x, hito_y / 50 + scr_y + 1, -1);
	if (id >= 100) {
		enemy(id - 100, &hp, &atk, &def, &hit,true);
		hito(&m_hp, &m_atk, &m_def,&m_hit, true);
		if (m_atk - def < 0)m_atk = def+1;
		DrawFormatString(hito_x + 20, hito_y, GetColor(255, 255, 255), "%d", m_atk - def);
		hp -= m_atk - def;
		if (hp <= 0)mini_map(hito_x / 50 + scr_x, hito_y / 50 + scr_y + 1, 0);
		enemy(id - 100, &hp, &atk, &def,&hit, false);
	}
}

void enemy(int id, int *hp, int *atk, int *def,int *hit, bool rw_sw) {
	static int hp_s[100], atk_s[100], def_s[100],hit_s[100];
	if (rw_sw) {
		*hp = hp_s[id];
		*atk = atk_s[id];
		*def = def_s[id];
		*hit = hit_s[id];
	}
	else {
		hp_s[id] = *hp;
		atk_s[id] = *atk;
		def_s[id] = *def;
		hit_s[id] = *hit;
	}
}
void enemy_etc(int id, int *way, int *type, bool rw_sw) {

	static int way_s[100], type_s[100];
	if (rw_sw) {
		*way = way_s[id];
		*type = type_s[id];
	}
	else {
		way_s[id] = *way;
		if (*type >= 0)type_s[id] = *type;
	}
}

void enemy_atk(int x1, int y1, int id)
{
	int hito_x = 0, hito_y = 0, hito_way = 0;
	int scr_x, scr_y;
	mini_scroll(&scr_x, &scr_y, true);
	int  hp, atk, def,hit;
	int  e_hp, e_atk, e_def,e_hit;

	hito_data(&hito_x, &hito_y, &hito_way, true);
	hito(&hp, &atk, &def,&hit, true);
	enemy(id, &e_hp, &e_atk, &e_def,&e_hit, true);
	if (e_atk - def < 0)e_atk = def+1;
	DrawFormatString(hito_x + 20, hito_y, GetColor(255, 255, 255), "%d", e_atk - def);
	hp -= e_atk - def;
	if (hp <= 0) {
		hito_sta_init();
		map_init();
		enemy_init(false);
	}
	hito(&hp, &atk, &def,&hit, false);

}

void enemy_move(void) {
	int mx, my, type = -1;
	int scr_x, scr_y;
	bool attack = false;
	static int way = 0, way_b = 0, way_send, way_num = 0;
	static int way_s[4] = { 0,1,2,1 };
	mini_scroll(&scr_x, &scr_y, true);

	if (scr_x < 10)scr_x = 10;
	if (scr_y < 10)scr_y = 10;
	if (scr_x + 16 > 75)scr_x = 75 - 16;
	if (scr_y + 12 > 75)scr_y = 75 - 12;
	for (int i = scr_x - 10; i < scr_x + 16 + 10; i++) {
		for (int j = scr_y - 10; j < scr_y + 12 + 10; j++) {
			if (mini_map(i, j, -1) >= 100) {
				mx = 0;
				my = 0;
				if (mini_map(i + 1, j, -1) == 50) {
					attack = true;
					mx = 1;
					way = 6;
				}
				else if (mini_map(i - 1, j, -1) == 50) {
					attack = true;
					mx = -1;
					way = 3;
				}
				else if (mini_map(i, j + 1, -1) == 50) {
					attack = true;
					my = 1;
					way = 0;
				}
				else if (mini_map(i, j - 1, -1) == 50) {
					attack = true;
					my = -1;
					way = 9;
				}
				if (attack) {
					enemy_atk(i + mx, j + my, mini_map(i, j, -1) - 100);
					enemy_etc((mini_map(i, j, -1)) - 100, &way, &type, false);
				}
				else {
					do {
						mx = 0;
						my = 0;
						switch (GetRand(4))
						{
						case 0:
							way = 0;
							my = 1;
							break;
						case 1:
							way = 3;
							mx = -1;
							break;
						case 2:
							way = 6;
							mx = 1;
							break;
						case 3:
							way = 9;
							my = -1;
							break;
						case 4:
							way = way_b;
							break;
						}
						if (mini_map(i + mx, j + my, -1) == mini_map(i, j, -1))break;
					} while (mini_map(i + mx, j + my, -1) != 0);
					if (way == way_b)way_num++;
					else way_num = 0;
					way_send = way;
					way_b = way;
					enemy_etc((mini_map(i, j, -1)) - 100, &way_send, &type, false);
					if (mini_map(i + mx, j + my, -1) != mini_map(i, j, -1)) {
						mini_map(i + mx, j + my, mini_map(i, j, -1));
						mini_map(i, j, 0);
					}
				}
				attack = false;
			}
		}
	}

}

int enemy_init(bool rw_sw) {
	room room[5];
	int id = 100, hp, atk, def,hit;
	int x, y, num;
	static int shu = 50;

	if (rw_sw) {
		return shu;
	}
	else {
		for (int i = 0; i < 5; i++)mini_room(i, &room[i], true);

		for (int i = 0; i < shu; i++) {
			do {
				num = GetRand(4);
				x = GetRand(room[num].x2 - room[num].x1) + room[num].x1;
				y = GetRand(room[num].y2 - room[num].y1) + room[num].y1;
			} while (mini_map(x, y, -1) != 0);
			mini_map(x, y, id + i);
			hp=(GetRand(5)+10)*10;
			atk=(GetRand(5)+10)*4;
			def=(GetRand(5)+10)*4;
			hit=(GetRand(5)+10)*4;
			enemy(i, &hp, &atk, &def,&hit, false);

		}
		return 0;
	}
}
