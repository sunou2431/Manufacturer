#include "DxLib.h"
#include "make.h"
#include "make_object.h"

void make(char fname[100])
{
	if (strcmp(fname, "")==0)init_map();
	else input_map(fname);
	name(fname,false);
	enter(false,false);
	obj_init();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		if(key_down())break;
		if(mouse_down())break;
		show();
	}

}


