#include "OBJECT.h"
#include <stdio.h>
#include <time.h>

#define MAP_SIZE 50 //一つの大きさ
#define CHIP_SIZE 50
#define C_HEIGHT 64
#define C_WIDTH 34
#define MAX_HNUM 13
#define MAX_WNUM 17
#define MAP_WIDTH 130 //横幅
#define MAP_HEIGHT 30 //縦幅
#define G (0.3F)// キャラに掛かる重力加速度
#define SPEED (5.0F)// キャラの移動スピード
#define JUMP_POWER (9.0F)// キャラのジャンプ力

float PlX, PlY ;            // プレイヤーの座標(中心座標)
float PlDownSp ;            // プレイヤーの落下速度
char PlJumpFlag ;           // プレイヤーがジャンプ中か、のフラグ
int cameraX = 0;
int back;
int Ghan[10];
int win_x = 0;
int win_y = 0;
float cameraY = 0;
int MapData[MAP_HEIGHT][MAP_WIDTH];
Block BlockData[6];

void GraphDraw();
int Map_read();
int tetorismode(void);
int GetChipParam(float,float);
int MapHitCheck(float,float);
int HitCheck(int,int,int,int);
void blockDraw(int,int,int,int);
void Mapchange(int,int,int,int);
int block_read();
int CharMove( float *X, float *Y, float *DownSP,float MoveX, float MoveY, float Size, char *JumpFlag ) ;

void tetomari(void){
	int Key[256];
	int dummy;
	int PlayerGraph ;//プレイヤーの画像
	cameraX = 0;
	cameraY = 936;
	PlX = 0;
	PlY = 300;
	// プレイヤーの落下速度を初期化
	PlDownSp = 0.0F ;
	// ジャンプ中フラグを倒す
	PlJumpFlag = FALSE ;
	if (win_x == 0 && win_y == 0) GetScreenState(&win_x, &win_y, &dummy);
	if(Map_read() == 1){
		return;
	}
	if(block_read() == 1){
		return;
	}
	back = LoadGraph("bg.jpg");
	if(LoadDivGraph("map_block.png",5,4,1,32,32,Ghan) == -1){
		return;
	}

	PlayerGraph = LoadGraph( "Player.bmp" );//PGにLoad
	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0){
		gpUpdataKey(Key);
		//計算処理
		float MoveX, MoveY ;
		// 移動量の初期化
		MoveX = 0.0F ;
		MoveY = 0.0F ;
		// 左右の移動を見る
        if(Key[KEY_INPUT_LEFT]) MoveX -= SPEED ;
        if(Key[KEY_INPUT_RIGHT]) MoveX += SPEED ;
		//スペースのキー入力を見る
		if(Key[KEY_INPUT_SPACE] == 1) tetorismode();
		if(Key[KEY_INPUT_ESCAPE] == 1) return;

            // 地に足が着いている場合のみジャンプボタン(ボタン１ or Ｚキー)を見る
            if( PlJumpFlag == FALSE && Key[KEY_INPUT_UP] != 0 )
            {
                PlDownSp = -JUMP_POWER ;
                PlJumpFlag = TRUE ;
            }

            // 落下処理
            PlDownSp += G ;

            // 落下速度を移動量に加える
            MoveY = PlDownSp ;

            // 移動量に基づいてキャラクタの座標を移動
            if(CharMove( &PlX, &PlY, &PlDownSp, MoveX, MoveY,30, &PlJumpFlag ) == 5){
				return;
			}

			if((int)cameraY >= 1150){
				return;
			}
			if(Key[KEY_INPUT_K]){
				PlDownSp = -JUMP_POWER ;
			}

		//描画処理
		//block描画
		//DrawFormatString(0,0,GetColor(255,255,255),"%d,%f",cameraX,PlX);
		//DrawFormatString(0,20,GetColor(255,255,255),"%f,%f",PlY,cameraY);
		DrawExtendGraph(0,0,win_x,win_y,back,TRUE);
		GraphDraw();
		// プレイヤーを描画する
		DrawGraph( (int)PlX , (int)PlY , PlayerGraph , TRUE ) ;
	}
}

void GraphDraw( void )
{
	int j , i ;
	int PX;
	int PY;
	int a;
	int b;
	int dummy;

	if(cameraX <= 400){
		PX = 0;
		a = 0;
	}
	else{
		PX = (cameraX - 400) / MAP_SIZE;
		a = cameraX % MAP_SIZE;
	}
	if(cameraY <= 300){
		PY = 0;
		b = 0;
	}
	else{
		PY = ((int)cameraY - 300) / MAP_SIZE;
		b = (int)cameraY % MAP_SIZE;
	}

	dummy = PX;
	// マップを描く
	for( i = 0 ; i < MAX_HNUM ; i ++ )
	{
		for( j = 0 ; j < MAX_WNUM ; j ++ )
		{
			// １は当たり判定チップを表しているので１のところだけ描画
			if( MapData[PY][PX] == 1 )
			{
				//DrawBox( j * MAP_SIZE - a,i * MAP_SIZE - b,j * MAP_SIZE + MAP_SIZE - a,i * MAP_SIZE + MAP_SIZE - b,GetColor( 255, 255, 255 ), TRUE ) ;
				DrawExtendGraph( j * MAP_SIZE - a,i * MAP_SIZE - b,j * MAP_SIZE + MAP_SIZE - a,i * MAP_SIZE + MAP_SIZE - b,Ghan[0], TRUE ) ;
            }
			if( MapData[PY][PX] == 2 ){
				DrawBox( j * MAP_SIZE - a,i * MAP_SIZE - b,j * MAP_SIZE + MAP_SIZE - a,i * MAP_SIZE + MAP_SIZE - b,GetColor( 255, 0, 0 ), TRUE ) ;
			}
			PX++;
		}
		PX = dummy;
		PY++;
	}
}
int Map_read(void){
	FILE *fp;
	int i;
	int j;

	//MapData読み込み
	if(fopen_s(&fp,"ore.dat","r") != 0){
		return 1;
	}
	for(i = 0;i<=20;i++){
		for(j = 0;j <= 99;j++){
			fscanf_s(fp,"%d",&MapData[i][j]);
			if(MapData[i][j] / 10 == 1){
				fseek(fp,2, SEEK_CUR);
			}
			else{
				fseek(fp,1,SEEK_CUR);
			}
		}
	}
	fclose(fp);
	return 0;
}
int block_read(void){
	FILE *fp;
	int i,j,k;
	int count;

	//BlockData読み込み
	if(fopen_s(&fp,"block.dat","r") != 0){
		return 1;
	}
	for(i = 0;i <= 5;i++){
		for(j = 0;j <= 3;j++){
			for(k = 0;k <= 3;k++){
				for(count = 0;count <= 3;count++){
					fscanf_s(fp,"%d",&BlockData[i].Data[j][k][count]);
					fseek(fp,1,SEEK_CUR);
				}
			}
		}
	}
	fclose(fp);
	return 0;
}
// キャラクタをマップとの当たり判定を考慮しながら移動する
int CharMove( float *X, float *Y, float *DownSP,float MoveX, float MoveY, float Size, char *JumpFlag )
{
    float Dummy = 0.0F ;
	int Y_flg;
	int X_flg;
    // 先ず上下移動成分だけでチェック
    {
		//DrawFormatString(0,40,GetColor(255,255,255),"%f",PlDownSp);
		Y_flg = MapHitCheck(Dummy,MoveY);
		if(Y_flg == 1 || Y_flg == 2){
			MoveY = 0;
			PlDownSp = 0;
			*JumpFlag = FALSE;
		}
		else{
			if(Y_flg >= 3){
				MoveY = 0;
				PlDownSp = 0;
			}
			else{
				*JumpFlag = TRUE ;
			}
		}
		if(PlY + MoveY <= 300){
			if(cameraY <= 300){
				PlY += MoveY;
				cameraY += MoveY;
			}
			else{
				cameraY += MoveY;
			}
		}
		else{
			cameraY += MoveY;
		}

    }

    // 後に左右移動成分だけでチェック
		X_flg = MapHitCheck(MoveX,Dummy);
		if(X_flg >= 1){
			MoveX = 0;
		}
	// 左右移動成分を加算
		if(PlX + MoveX <= 400){
			if(cameraX <= 400){
				if(PlX + MoveX >= 0){
					*X += MoveX ;
					cameraX += (int)MoveX;
				}
			}
			else{
				cameraX += (int)MoveX;
			}
		}
		else{
			cameraX += (int)MoveX;
		}
		//DrawFormatString(0,60,GetColor(255,255,255),"%d,%d",Y_flg,X_flg);
		if(X_flg >= 5 || Y_flg >= 5){
			return 5;		
		}

    return 0 ;
}
int MapHitCheck(float MoveX,float MoveY){
	//DrawFormatString(0,80,GetColor(255,255,255),"%d,%d,%d",((int)cameraY + (int)MoveY + C_HEIGHT)/MAP_SIZE,(cameraX + (int)MoveX)/MAP_SIZE,MapData[((int)cameraY + (int)MoveY + C_HEIGHT)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE]);
	if(MoveX == 0){
		if(MoveY >= 0){
			//DrawFormatString(0,100,GetColor(255,255,255),"%f,%f",MoveX,MoveY);
			if(MapData[((int)cameraY + (int)MoveY + C_HEIGHT)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE] >= 1){//左下のチェック判定
				return 4 * MapData[((int)cameraY + (int)MoveY + C_HEIGHT)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE] - 3;
			}
			if(MapData[((int)cameraY + (int)MoveY + C_HEIGHT) / MAP_SIZE][(cameraX + (int)MoveX + C_WIDTH) / MAP_SIZE] >= 1){//右下のチェック判定
				return 4 * MapData[((int)cameraY + (int)MoveY + C_HEIGHT)/MAP_SIZE][(cameraX + (int)MoveX + C_WIDTH)/MAP_SIZE] - 2;
			}
		}
		else{
			if(MapData[((int)cameraY + (int)MoveY)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE] >= 1){//左上のチェック判定
				return 4 * MapData[((int)cameraY + (int)MoveY)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE] - 1;
			}
			if(MapData[((int)cameraY + (int)MoveY) / MAP_SIZE][(cameraX + (int)MoveX + C_WIDTH) / MAP_SIZE] >= 1){//右上のチェック判定
				return 4 * MapData[((int)cameraY + (int)MoveY)/MAP_SIZE][(cameraX + (int)MoveX + C_WIDTH)/MAP_SIZE];
			}
		}
	}
	if(MoveY == 0){
		//DrawFormatString(0,120,GetColor(255,255,255),"%f,%f",MoveX,MoveY);
		if(MapData[((int)cameraY + (int)MoveY + C_HEIGHT - 10)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE] >= 1){//左下のチェック判定
			return 4 * MapData[((int)cameraY + (int)MoveY + C_HEIGHT)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE] - 3;
		}
		if(MapData[((int)cameraY + (int)MoveY + C_HEIGHT - 10) / MAP_SIZE][(cameraX + (int)MoveX + C_WIDTH) / MAP_SIZE] >= 1){//右下のチェック判定
			return 4 * MapData[((int)cameraY + (int)MoveY + C_HEIGHT)/MAP_SIZE][(cameraX + (int)MoveX + C_WIDTH)/MAP_SIZE] - 2;
		}
		if(MapData[((int)cameraY + (int)MoveY)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE] >= 1){//左上のチェック判定
			return 4 * MapData[((int)cameraY + (int)MoveY)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE] - 1;
		}
		if(MapData[((int)cameraY + (int)MoveY) / MAP_SIZE][(cameraX + (int)MoveX + C_WIDTH) / MAP_SIZE] >= 1){//右上のチェック判定
			return 4 * MapData[((int)cameraY + (int)MoveY)/MAP_SIZE][(cameraX + (int)MoveX + C_WIDTH)/MAP_SIZE];
		}
	}
	return 0;
}
int tetorismode(void){
	int Key[256];
	int count = 0;
	int X = cameraX/MAP_SIZE;
	int Y;
	if(cameraY <= 300){
		Y = 0;
	}
	else{
		Y = ((int)cameraY - 300)/MAP_SIZE;
	}
	int num;
	int kaiten = 0;
	int PlayerGraph;

	PlayerGraph = LoadGraph( "Player.bmp" );//PGにLoad
	srand((unsigned int)time(NULL));
	num = GetRand(5);
	kaiten = GetRand(3);
	Key[KEY_INPUT_SPACE] = 1;
	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0){
		//計算処理
		gpUpdataKey(Key);
		if(Key[KEY_INPUT_SPACE] == 1){
			return 0;
		}
		//DrawFormatString(0,160,GetColor(255,255,255),"%d,%d",Y,count);
		if(count >= 30){
			count = 0;
			if(HitCheck(X,Y + 1,num,kaiten) == 0){
				Y += 1;
			}
			else{
				Mapchange(X,Y,num,kaiten);
				X = cameraX/MAP_SIZE;
				if(cameraY <= 300){
					Y = 0;
				}
				else{
					Y = ((int)cameraY - 300)/MAP_SIZE;
				}
				num = GetRand(5);
				kaiten = GetRand(3);
			}
		}
		count++;
		if(Key[KEY_INPUT_RIGHT] == 1){
			if(HitCheck(X + 1,Y,num,kaiten) == 0){
				X += 1;
			}
		}
		if(Key[KEY_INPUT_LEFT] == 1){
			if(HitCheck(X - 1,Y,num,kaiten) == 0){
				X += -1;
			}
		}
		if(Key[KEY_INPUT_UP] == 1){
			if(HitCheck(X,Y,num,(kaiten + 1) % 4) == 0){
				kaiten++;
				kaiten = kaiten % 4;
			}
		}
		if(Key[KEY_INPUT_DOWN]){
			count += 4;
		}
		//描画処理
		DrawExtendGraph(0,0,win_x,win_y,back,TRUE);
		GraphDraw();
		DrawGraph((int)PlX , (int)PlY , PlayerGraph , TRUE ) ;
		blockDraw(X,Y,num,kaiten);
	}
	return 0;
}
int HitCheck(int X,int Y,int num,int kaiten){
	int i,j;
	for(i = 0;i < 4;i++){
		for(j = 0;j < 4;j++){
			if(BlockData[num].Data[kaiten][i][j] == 1){
				if(MapData[Y + i][X + j] == 1){
					return 1;//あたった
				}
			}
		}
	}
	return 0;//ノーヒット
}
void blockDraw(int X,int Y,int num,int kaiten){
	int i,j;
	int a,b;
	int dummy_X;
	int dummy_Y;

	if(cameraX >= 400){
		dummy_X = (cameraX / MAP_SIZE) - 8;
		a = cameraX % MAP_SIZE;
	}
	else{ 
		a = 0;
		dummy_X = 0;
	}
	if(cameraY <= 300){
		b = 0;
		dummy_Y = 0;
	}
	else{
		dummy_Y = ((int)cameraY - 300) / MAP_SIZE;
		b = (int)cameraY % MAP_SIZE;
	}

	//DrawFormatString(0,0,GetColor(255,255,255),"%d,%d",dummy_X,dummy_Y);
	for(i = 0;i < 4;i++){
		for(j = 0;j < 4;j++){
			if(BlockData[num].Data[kaiten][i][j] == 1){
				//DrawBox( (X - dummy_X) * MAP_SIZE + (j * MAP_SIZE) - a,(Y - dummy_Y) * MAP_SIZE + (i * MAP_SIZE) - b,(X - dummy_X) * MAP_SIZE + MAP_SIZE + (j * MAP_SIZE) - a,(Y - dummy_Y) * MAP_SIZE + MAP_SIZE + (i * MAP_SIZE) - b,GetColor( 255, 255, 255 ), TRUE ) ;
				DrawExtendGraph( (X - dummy_X) * MAP_SIZE + (j * MAP_SIZE) - a,(Y - dummy_Y) * MAP_SIZE + (i * MAP_SIZE) - b,(X - dummy_X) * MAP_SIZE + MAP_SIZE + (j * MAP_SIZE) - a,(Y - dummy_Y) * MAP_SIZE + MAP_SIZE + (i * MAP_SIZE) - b,Ghan[0], TRUE ) ;
			}
		}
	}
	return;
}
void Mapchange(int X,int Y,int num,int kaiten){
	int i,j;
	for(i = 0;i < 4;i++){
		for(j = 0;j < 4;j++){
			if(BlockData[num].Data[kaiten][i][j] == 1){
				MapData[Y + i][X + j] = 1;
			}
		}
	}
	return ;
}
