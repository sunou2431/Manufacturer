#include "DxLib.h"
#include <fstream>

#define PlayerWidth 40
#define PlayerHeight 40

int GamePlay(int);
int move();
int map();
int attack();
int enemyfunc();
int damage();
int GameOver();
int HitBlock();

const int BlockSize = 40;
int PlayerX, PlayerY;
int PlayerHP;
int PlayerMuteki;
int JumpPower;
bool JumpFlg;
char muki;
int PlayerX_syoki;
int PlayerY_syoki;

int MapData[15][100];
int BlockGraph[10];
int EnemyGraph[10];
char KeyBuf[256];

int MapX;
bool gameoverflg = false;

typedef struct ENEMY {
	int no;
	int x;
	int y;
	int w;
	int h;
	int hp;
	int count;
	double jump;
	char muki;
}Enemy;

Enemy enemy[15][100];

int GamePlay(int MapNum)
{
	int i, j, count;
	int FileHandle;
	char MapBuf[205];
	int enemy_count = 0;

	
	//キャラクターの初期データをセット
	PlayerX = 640 / 2 - 50;
	PlayerY = 0;
	PlayerHP = 10;
	PlayerMuteki = 0;
	JumpPower = 0;
	JumpFlg = false;
	muki = 'r';
	MapX = 0;

	count = 0;
	FileHandle = MapNum;
	for (i = 0; i < 12; i++) {
		// 一行読む
		FileRead_gets(MapBuf, 205, FileHandle);
		for (j = 0; MapBuf[j] != '\0'; j++) {
			if (MapBuf[j] != ',') {
				switch (MapBuf[j]) {
				case '1':
					MapData[i][count] = 1;
					break;

				case '2':
					MapData[i][count] = 2;
					break;

				case '3':
					MapData[i][count] = 3;

					enemy[i][count].no = 1;
					enemy[i][count].x = count * BlockSize;
					enemy[i][count].y = i * BlockSize;
					enemy[i][count].w = 40;
					enemy[i][count].h = 40;
					enemy[i][count].hp = 10;
					enemy[i][count].count = 0;
					enemy[i][count].jump = 0.0;
					enemy[i][count].muki = 'l';
					break;

				case '4':
					MapData[i][count] = 4;

					enemy[i][count].no = 2;
					enemy[i][count].x = count * BlockSize;
					enemy[i][count].y = i * BlockSize;
					enemy[i][count].w = 40;
					enemy[i][count].h = 40;
					enemy[i][count].hp = 10;
					enemy[i][count].count = 0;
					enemy[i][count].jump = 0.0;
					enemy[i][count].muki = 'l';
					break;

				case '9':
					PlayerX_syoki = PlayerX = count * BlockSize;
					PlayerY_syoki = PlayerY = i * BlockSize;

					break;

				default:
					MapData[i][count] = 0;
					break;
				}
				MapData[i][count] = MapBuf[j] - 48;
				count++;
			}
		}
		count = 0;
	}
	FileRead_close(FileHandle);


	//ブロックデータ読み込み
	BlockGraph[0] = LoadGraph("block0.bmp");
	BlockGraph[1] = LoadGraph("block1.bmp");
	BlockGraph[2] = LoadGraph("block2.bmp");

	//エネミーデータ読み込み
	EnemyGraph[0] = LoadGraph("enemy0.bmp");
	EnemyGraph[1] = LoadGraph("enemy1.bmp");
	EnemyGraph[2] = LoadGraph("enemy2.bmp");



	//ループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && gameoverflg == false)
	{

		//画面を初期化する
		ClearDrawScreen();

		//キー入力取得
		GetHitKeyStateAll(KeyBuf);

		map();
		move();
		enemyfunc();
		attack();


		DrawFormatString(300, 300, GetColor(255, 255, 255), "%d    %d", enemy[2][9].y, PlayerHP);

		//裏画面の内容を表画面に反映させる
		ScreenFlip();

	}

	return 0;
}

int move()
{
	int PlayerGraph;
	int BlockNum[] = { 1,2,3 };

	//グラフィックのロード
	PlayerGraph = LoadGraph("test1.bmp");



	//if (KeyBuf[KEY_INPUT_UP] == 1) PlayerY -= 3;		// 上を押していたら上に進む
	if (KeyBuf[KEY_INPUT_DOWN] == 1) {	// 下を押していたら下に進む
		PlayerY += 3;
	}
	if (KeyBuf[KEY_INPUT_RIGHT] == 1) {	// 右を押していたら右に進む
		PlayerX += 5;
		muki = 'r';
		if (MapData[PlayerY / BlockSize][(PlayerX + BlockSize + MapX - 1) / BlockSize] == 1) {
			PlayerX -= 5;
		}
		if (MapData[(PlayerY + BlockSize - 1) / BlockSize][(PlayerX + BlockSize + MapX - 1) / BlockSize] == 1) {
			PlayerX -= 5;
		}
	}
	if (KeyBuf[KEY_INPUT_LEFT] == 1) {	// 左を押していたら左に進む
		PlayerX -= 5;
		muki = 'l';
		if (MapData[PlayerY / BlockSize][(PlayerX + MapX) / BlockSize] == 1) {
			PlayerX += 5;
		}
		if (MapData[(PlayerY + BlockSize - 1) / BlockSize][(PlayerX + MapX) / BlockSize] == 1) {
			PlayerX += 5;

		}
	}


	if (KeyBuf[KEY_INPUT_RIGHT] == 1 && PlayerX > 320) {
		if (MapX >= 3360) {
			MapX = 3360;
			if (PlayerX >= 640 - PlayerWidth)	PlayerX = 640 - PlayerWidth;
		}
		else {
			PlayerX = 320;
			MapX = MapX + 5;
		}
	}
	if (KeyBuf[KEY_INPUT_LEFT] == 1 && PlayerX < 250) {
		if (MapX <= 0) {
			MapX = 0;
			if (PlayerX <= 0)	PlayerX = 0;
		}
		else {
			PlayerX = 250;
			MapX = MapX - 5;
		}
	}

	//落下処理
	PlayerY -= JumpPower;

	//落下加速度を加える
	JumpPower -= 1;

	//ここから
	for(int i = 0; i < sizeof BlockNum /sizeof BlockNum[0]; i++){
		if (MapData[PlayerY / BlockSize][(PlayerX + MapX) / BlockSize] == BlockNum[i]) {
			PlayerY = (PlayerY / BlockSize + 1) * BlockSize;
			JumpPower = 0;
			MapData[PlayerY / BlockSize - 1][(PlayerX + MapX) / BlockSize] = 0;
		}
		if (MapData[PlayerY / BlockSize][(PlayerX + BlockSize + MapX - 1) / BlockSize] == BlockNum[i]) {
			PlayerY = (PlayerY / BlockSize + 1) * BlockSize;
			JumpPower = 0;
			MapData[PlayerY / BlockSize - 1][(PlayerX + BlockSize + MapX - 1) / BlockSize] = 0;
		}
		if (MapData[(PlayerY + BlockSize) / BlockSize][(PlayerX + MapX) / BlockSize] == BlockNum[i]) {
			PlayerY = (PlayerY + BlockSize) / BlockSize * BlockSize - BlockSize;
			JumpPower = 0;
			JumpFlg = false;

		}
		if (MapData[(PlayerY + BlockSize) / BlockSize][(PlayerX + BlockSize + MapX - 1) / BlockSize] == BlockNum[i]) {
			PlayerY = (PlayerY + BlockSize) / BlockSize * BlockSize - BlockSize;
			JumpPower = 0;
			JumpFlg = false;
		}

		switch (true){
		case 1:

		default:
			break;
		}
	}

	//ジャンプボタンを押していて、地面についていたらジャンプ
	if ((KeyBuf[KEY_INPUT_UP] == 1) && (JumpFlg == false)) {
		JumpPower = 20;
		JumpFlg = true;
	}


	if (PlayerY >= 600) {
		PlayerY = 0;
		//JumpPower = 0;
	}

	//プレイヤーを描画する
	//DrawGraph(PlayerX, PlayerY, PlayerGraph, TRUE);
	if (muki == 'r') {
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + PlayerWidth, PlayerY + PlayerHeight, PlayerGraph, true);
	}
	else {
		DrawTurnGraph(PlayerX, PlayerY, PlayerGraph, true);
	}


	return 0;					// ソフトの終了
}

int attack()
{
	int PlayerGraph;
	int BlockNum[] = { 2,4 };
	int i;

	if (KeyBuf[KEY_INPUT_Z] == 1) {
		PlayerGraph = LoadGraph("Player_attack.bmp");
		if (muki == 'r') {
			DrawExtendGraph(PlayerX, PlayerY, PlayerX + PlayerWidth, PlayerY + PlayerHeight, PlayerGraph, true);
		}
		else {
			DrawTurnGraph(PlayerX, PlayerY, PlayerGraph, true);
		}
		for (i = 0; i < sizeof BlockNum /sizeof BlockNum[0]; i++) {
			if (muki == 'l') {
				if (MapData[PlayerY / BlockSize][(PlayerX + MapX - 20) / BlockSize] == BlockNum[i]) {
					MapData[PlayerY / BlockSize][(PlayerX + MapX - 20) / BlockSize] = 0;
				}
				if (MapData[(PlayerY + BlockSize - 1) / BlockSize][(PlayerX + MapX - 20) / BlockSize] == BlockNum[i]) {
					MapData[(PlayerY + BlockSize - 1) / BlockSize][(PlayerX + MapX - 20) / BlockSize] = 0;

				}
			}
			else{
				if (MapData[PlayerY / BlockSize][(PlayerX + BlockSize + MapX + 11) / BlockSize] == BlockNum[i]) {
					MapData[PlayerY / BlockSize][(PlayerX + BlockSize + MapX + 11) / BlockSize] = 0;
				}
				if (MapData[(PlayerY + BlockSize - 1) / BlockSize][(PlayerX + BlockSize + MapX + 11) / BlockSize] == BlockNum[i]) {
					MapData[(PlayerY + BlockSize - 1) / BlockSize][(PlayerX + BlockSize + MapX + 11) / BlockSize] = 0;
				}
			}
		}
	}


	return 0;
}

int damage()
{

	PlayerHP -=1;

	if (PlayerHP <= 0){
		GameOver();
	}
	else{
		PlayerX = PlayerX_syoki;
		PlayerY = PlayerY_syoki;
		JumpPower = 0;
		JumpFlg = false;
		muki = 'r';
		MapX = 0;
	}

	return 0;
}

int GameOver()
{
	gameoverflg = true;
	return 0;
}

int enemyfunc()
{
	int i, j, w, h, size;

	w = 100;
	h = 12;
	size = BlockSize;

	for (i = 0; i < h; i++) {
		for (j = 0; j < w + 1; j++) {
			//敵が表示範囲にいるか
			if ((enemy[i][j].hp > 0) && (MapX - BlockSize * 20 <= enemy[i][j].x) && (enemy[i][j].x <= MapX + BlockSize * 20)) {
				switch (enemy[i][j].no) {
					case 1:
							if (enemy[i][j].muki == 'l') {
								enemy[i][j].x -= 1;
							}
							else {
								enemy[i][j].x += 1;
							}


						//左右の判定
						if (MapData[enemy[i][j].y / BlockSize][(enemy[i][j].x + enemy[i][j].w - 1) / BlockSize] == 1) {
							enemy[i][j].x -= 5;
							enemy[i][j].muki = 'l';
						}
						if (MapData[(enemy[i][j].y + BlockSize - 1) / BlockSize][(enemy[i][j].x + enemy[i][j].w - 1) / BlockSize] == 1) {
							enemy[i][j].x -= 5;
							enemy[i][j].muki = 'l';
						}
						if (MapData[enemy[i][j].y / BlockSize][(enemy[i][j].x) / BlockSize] == 1) {
							enemy[i][j].x += 5;
							enemy[i][j].muki = 'r';
						}
						if (MapData[(enemy[i][j].y + BlockSize - 1) / BlockSize][(enemy[i][j].x) / BlockSize] == 1) {
							enemy[i][j].x += 5;
							enemy[i][j].muki = 'r';
						}

						enemy[i][j].y -= enemy[i][j].jump;
						enemy[i][j].jump -= 0.1;
						//上下の判定
						if (MapData[enemy[i][j].y / BlockSize][(enemy[i][j].x) / BlockSize] == 1) {
							enemy[i][j].y = (enemy[i][j].y / BlockSize + 1) * BlockSize;
							enemy[i][j].jump = 0;
						}
						if (MapData[enemy[i][j].y / BlockSize][(enemy[i][j].x + enemy[i][j].w - 1) / BlockSize] == 1) {
							enemy[i][j].y = (enemy[i][j].y / BlockSize + 1) * BlockSize;
							enemy[i][j].jump = 0;
						}
						if (MapData[(enemy[i][j].y + BlockSize) / BlockSize][(enemy[i][j].x) / BlockSize] == 1) {
							enemy[i][j].y = (enemy[i][j].y + enemy[i][j].h) / BlockSize * BlockSize - enemy[i][j].h;
							enemy[i][j].jump = 0;
						}
						if (MapData[(enemy[i][j].y + BlockSize) / BlockSize][(enemy[i][j].x + enemy[i][j].w - 1) / BlockSize] == 1) {
							enemy[i][j].y = (enemy[i][j].y + enemy[i][j].h) / BlockSize * BlockSize - enemy[i][j].h;
							enemy[i][j].jump = 0;
						}
						break;

					case 2:
						int enemy_move_height=100;
						enemy[i][j].count += 1;
						if(enemy[i][j].count % 2 != 0){break;}
							if(enemy[i][j].count < enemy_move_height){
								enemy[i][j].y -= 1;
							}
							else{
								enemy[i][j].y += 1;
								if(enemy[i][j].count > enemy_move_height * 2 - 1){enemy[i][j].count = -1;}
							}
						break;

				}

				if (PlayerX + MapX <= enemy[i][j].x + enemy[i][j].w &&
					PlayerX + BlockSize + MapX >= enemy[i][j].x &&
					PlayerY <= enemy[i][j].y + enemy[i][j].h &&
					PlayerY + BlockSize >=enemy[i][j].y &&
					KeyBuf[KEY_INPUT_Z] != 1){

						damage();
				}

				DrawExtendGraph(enemy[i][j].x - MapX, enemy[i][j].y, enemy[i][j].x + enemy[i][j].w - MapX, enemy[i][j].y + enemy[i][j].h, EnemyGraph[enemy[i][j].no], true);
			}
		}
	}

	return 0;
}

//マップの表示
int map()
{

	int i, j, w, h,  size;
	int con = 0;

	w = 16;
	h = 12;
	size = BlockSize;

	for (i = 0; i < h; i++) {
		for (j = 0; j < w + 1; j++) {
			if (MapData[i][MapX / size + j] != 0) {
				DrawExtendGraph(j * size - MapX % size, i * size, j * size + size - MapX % size, i*size + size, BlockGraph[MapData[i][MapX / size + j]], true);
			}
		}
	}

	return 0;
}

