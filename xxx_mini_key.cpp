#include "DxLib.h"
#include "xxx_mini.h"
#include "xxx_mini_object.h"
#include "OBJECT.h"

bool mini_key(void)
{
	int hito_x = 0, hito_y = 0, hito_way = 0;
	int hito_x2 = 0, hito_y2 = 0;
	int scr_x, scr_y;
	mini_scroll(&scr_x, &scr_y, true);
	static int time;
	static int turn = 0, next = 1;
	static int move = 50;
	static int win_x = 0, win_y = 0, dummy;
	if (win_x == 0 && win_y == 0) GetScreenState(&win_x, &win_y, &dummy);
	static int key[256];
	gpUpdataKey(key);

	if (key[KEY_INPUT_ESCAPE] == 1)if (MessageBox(NULL, "èIóπÇµÇ‹Ç∑Ç©", "ämîF", MB_YESNO) == IDYES)return true;
	if (key[KEY_INPUT_C] == 1) { map_init(); enemy_init(false); }
	if (key[KEY_INPUT_LSHIFT] == 0 && key[KEY_INPUT_RSHIFT] == 0)time = 10;
	else time = 3;
	if (key[KEY_INPUT_LCONTROL] == 0 && key[KEY_INPUT_RCONTROL] == 0) {
		move = 50;
		next = 1;
	}
	else {
		move = 0;
		next = 0;
	}

	switch (turn % 2)
	{
	case 0:
		hito_data(&hito_x2, &hito_y2, &hito_way, true);
		if (key[KEY_INPUT_UP] == 1) {
			hito_y = -move;
			hito_way = 9;
			hito_data(&hito_x, &hito_y, &hito_way, false);
			hito_data(&hito_x, &hito_y, &hito_way, true);

			if (hito_y2 == hito_y && next == 1)hito_atk();
			turn += next;
		}
		else if (key[KEY_INPUT_UP] == time)key[KEY_INPUT_UP] = 0;
		else if (key[KEY_INPUT_DOWN] == 1) {
			hito_y = move;
			hito_way = 0;
			hito_data(&hito_x, &hito_y, &hito_way, false);
			hito_data(&hito_x, &hito_y, &hito_way, true);

			if (hito_y2 == hito_y && next == 1)hito_atk();
			turn += next;
		}
		else if (key[KEY_INPUT_DOWN] == time)key[KEY_INPUT_DOWN] = 0;
		else if (key[KEY_INPUT_RIGHT] == 1) {
			hito_x = move;
			hito_way = 6;
			hito_data(&hito_x, &hito_y, &hito_way, false);
			hito_data(&hito_x, &hito_y, &hito_way, true);

			if (hito_x2 == hito_x && next == 1)hito_atk();
			turn += next;
		}
		else if (key[KEY_INPUT_RIGHT] == time)key[KEY_INPUT_RIGHT] = 0;
		else if (key[KEY_INPUT_LEFT] == 1) {
			hito_x = -move;
			hito_way = 3;
			hito_data(&hito_x, &hito_y, &hito_way, false);
			hito_data(&hito_x, &hito_y, &hito_way, true);

			if (hito_x2 == hito_x && next == 1)hito_atk();
			turn += next;
		}
		else if (key[KEY_INPUT_LEFT] == time)key[KEY_INPUT_LEFT] = 0;


		else if (key[KEY_INPUT_RETURN] == 1) {
			hito_atk();
			turn += 1;
		}
		else if (key[KEY_INPUT_RETURN] == time)key[KEY_INPUT_RETURN] = 0;
		break;

	case 1:

		enemy_move();
		turn += 1;
		break;
	default:
		break;
	}


	return false;
}