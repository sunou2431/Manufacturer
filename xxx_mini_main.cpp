#include "DxLib.h"
#include "xxx_mini.h"
#include "xxx_mini_object.h"

void mini_rpg(void)
{
	hito_sta_init();
	map_init();
	enemy_init(false);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		if (mini_key())break;
		mini_show();
	}

}