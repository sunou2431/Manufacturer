#include "OBJECT.h"
#include "xxx_mini.h"

void selectminigame(void){
	int Key[256];
	int i;
	int back;
	int count = 0;

	back = LoadGraph("back.jpg");
	MenuElement_t Menusele[3] = {
		{250,180,GetColor(0,0,0),"テトリスマリオ"},
		{200,220,GetColor(0,0,0),"test" },
		{200,260,GetColor(0,0,0),"戻る"}
	};

	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0){
		//計算処理
		gpUpdataKey(Key);
		if(Key[KEY_INPUT_DOWN] == 1){//下キーが押されたら下に行く処理
			count++;
			count = count % 3;
		}
		if(Key[KEY_INPUT_UP] == 1){//上キーが押されたら上に行く処理
			count = count += 2;
			count = count % 3;
		}
		if(Key[KEY_INPUT_SPACE] == 1 || Key[KEY_INPUT_RETURN] == 1){//Enter または　スペースが押されたらカウントに応じて処理
			if(count == 0){
				tetomari();
			}
			if (count == 1) {
				mini_rpg();
			}
			if (count == 2) {
				return;
			}
		}
		for(i = 0;i <= 2;i++){//カウントに応じて選択されてるものをわかりやすく処理
			if(count == i){
				Menusele[i].cr = GetColor(255,0,255);//色を紫
				Menusele[i].x = 250;//選択されているものを右に出す
			}
			else{
				Menusele[i].cr = GetColor(0,0,0);//色を黒
				Menusele[i].x = 200;//選択されているものを左に
			}
		}

		//描画処理
		DrawGraph(0,0,back,TRUE);//バック画面を表示
		for(i = 0;i <= 2;i++){
			DrawFormatString(Menusele[i].x,Menusele[i].y,Menusele[i].cr,Menusele[i].name);//文字の表示
		}

	}
}