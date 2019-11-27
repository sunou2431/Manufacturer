#include "object.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                         LPSTR lpCmdLine, int nCmdShow )
{
	//変数宣言
	int Key[256];
	int i;
	int back;
	int count = 0;
	MenuElement_t Menusele[4] = {
		{250,180,GetColor(0,0,0),"遊ぶ"},
		{200,220,GetColor(0,0,0),"作る"},
		{200,260,GetColor(0,0,0),"ミニゲーム"},
		{200,300,GetColor(0,0,0),"終了"}
	};


	//初期処理
	ChangeWindowMode( TRUE );  // ウィンドウモードに設定
	SetDrawScreen( DX_SCREEN_BACK );  //描画先を裏画面に設定
	SetGraphMode( 800 , 600 , 32 ) ;  //800*600に固定
	if( DxLib_Init() == -1 )        // ＤＸライブラリ初期化処理
	{
         return -1;        // エラーが起きたら直ちに終了
    }
	back = LoadGraph("back.jpg");
	PlaySoundFile("BGM\\bgm_01.mp3", DX_PLAYTYPE_LOOP ) ;
	gpUpdataKey(Key);
	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && Key[KEY_INPUT_ESCAPE] != 1){
		//計算処理
		gpUpdataKey(Key);
		if(Key[KEY_INPUT_DOWN] == 1){//下キーが押されたら下に行く処理
			count++;
			count = count % 4;
		}
		if(Key[KEY_INPUT_UP] == 1){//上キーが押されたら上に行く処理
			count = count += 3;
			count = count % 4;
		}
		if(Key[KEY_INPUT_SPACE] == 1 || Key[KEY_INPUT_RETURN] == 1){//Enter または　スペースが押されたらカウントに応じて処理
			if(count == 0){
				filesele_play();
				Key[KEY_INPUT_ESCAPE] = 2;
			}
			if(count == 1){
				filesele_make();
				Key[KEY_INPUT_ESCAPE] = 2;
			}
			if(count == 2){
				selectminigame();
				Key[KEY_INPUT_ESCAPE] = 2;
			}
			if(count == 3){
				break;
			}
		}
		for(i = 0;i <= 3;i++){//カウントに応じて選択されてるものをわかりやすく処理
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
		for(i = 0;i <= 3;i++){
			DrawFormatString(Menusele[i].x,Menusele[i].y,Menusele[i].cr,Menusele[i].name);//文字の表示
		}

	}
	StopSoundFile() ;
    DxLib_End() ;            // ＤＸライブラリ使用の終了処理

    return 0 ;            // ソフトの終了
}