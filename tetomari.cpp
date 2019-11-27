#include "OBJECT.h"
#include <stdio.h>
#include <time.h>

#define MAP_SIZE 50 //��̑傫��
#define CHIP_SIZE 50
#define C_HEIGHT 64
#define C_WIDTH 34
#define MAX_HNUM 13
#define MAX_WNUM 17
#define MAP_WIDTH 130 //����
#define MAP_HEIGHT 30 //�c��
#define G (0.3F)// �L�����Ɋ|����d�͉����x
#define SPEED (5.0F)// �L�����̈ړ��X�s�[�h
#define JUMP_POWER (9.0F)// �L�����̃W�����v��

float PlX, PlY ;            // �v���C���[�̍��W(���S���W)
float PlDownSp ;            // �v���C���[�̗������x
char PlJumpFlag ;           // �v���C���[���W�����v�����A�̃t���O
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
	int PlayerGraph ;//�v���C���[�̉摜
	cameraX = 0;
	cameraY = 936;
	PlX = 0;
	PlY = 300;
	// �v���C���[�̗������x��������
	PlDownSp = 0.0F ;
	// �W�����v���t���O��|��
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

	PlayerGraph = LoadGraph( "Player.bmp" );//PG��Load
	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0){
		gpUpdataKey(Key);
		//�v�Z����
		float MoveX, MoveY ;
		// �ړ��ʂ̏�����
		MoveX = 0.0F ;
		MoveY = 0.0F ;
		// ���E�̈ړ�������
        if(Key[KEY_INPUT_LEFT]) MoveX -= SPEED ;
        if(Key[KEY_INPUT_RIGHT]) MoveX += SPEED ;
		//�X�y�[�X�̃L�[���͂�����
		if(Key[KEY_INPUT_SPACE] == 1) tetorismode();
		if(Key[KEY_INPUT_ESCAPE] == 1) return;

            // �n�ɑ��������Ă���ꍇ�̂݃W�����v�{�^��(�{�^���P or �y�L�[)������
            if( PlJumpFlag == FALSE && Key[KEY_INPUT_UP] != 0 )
            {
                PlDownSp = -JUMP_POWER ;
                PlJumpFlag = TRUE ;
            }

            // ��������
            PlDownSp += G ;

            // �������x���ړ��ʂɉ�����
            MoveY = PlDownSp ;

            // �ړ��ʂɊ�Â��ăL�����N�^�̍��W���ړ�
            if(CharMove( &PlX, &PlY, &PlDownSp, MoveX, MoveY,30, &PlJumpFlag ) == 5){
				return;
			}

			if((int)cameraY >= 1150){
				return;
			}
			if(Key[KEY_INPUT_K]){
				PlDownSp = -JUMP_POWER ;
			}

		//�`�揈��
		//block�`��
		//DrawFormatString(0,0,GetColor(255,255,255),"%d,%f",cameraX,PlX);
		//DrawFormatString(0,20,GetColor(255,255,255),"%f,%f",PlY,cameraY);
		DrawExtendGraph(0,0,win_x,win_y,back,TRUE);
		GraphDraw();
		// �v���C���[��`�悷��
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
	// �}�b�v��`��
	for( i = 0 ; i < MAX_HNUM ; i ++ )
	{
		for( j = 0 ; j < MAX_WNUM ; j ++ )
		{
			// �P�͓����蔻��`�b�v��\���Ă���̂łP�̂Ƃ��낾���`��
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

	//MapData�ǂݍ���
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

	//BlockData�ǂݍ���
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
// �L�����N�^���}�b�v�Ƃ̓����蔻����l�����Ȃ���ړ�����
int CharMove( float *X, float *Y, float *DownSP,float MoveX, float MoveY, float Size, char *JumpFlag )
{
    float Dummy = 0.0F ;
	int Y_flg;
	int X_flg;
    // �悸�㉺�ړ����������Ń`�F�b�N
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

    // ��ɍ��E�ړ����������Ń`�F�b�N
		X_flg = MapHitCheck(MoveX,Dummy);
		if(X_flg >= 1){
			MoveX = 0;
		}
	// ���E�ړ����������Z
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
			if(MapData[((int)cameraY + (int)MoveY + C_HEIGHT)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE] >= 1){//�����̃`�F�b�N����
				return 4 * MapData[((int)cameraY + (int)MoveY + C_HEIGHT)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE] - 3;
			}
			if(MapData[((int)cameraY + (int)MoveY + C_HEIGHT) / MAP_SIZE][(cameraX + (int)MoveX + C_WIDTH) / MAP_SIZE] >= 1){//�E���̃`�F�b�N����
				return 4 * MapData[((int)cameraY + (int)MoveY + C_HEIGHT)/MAP_SIZE][(cameraX + (int)MoveX + C_WIDTH)/MAP_SIZE] - 2;
			}
		}
		else{
			if(MapData[((int)cameraY + (int)MoveY)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE] >= 1){//����̃`�F�b�N����
				return 4 * MapData[((int)cameraY + (int)MoveY)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE] - 1;
			}
			if(MapData[((int)cameraY + (int)MoveY) / MAP_SIZE][(cameraX + (int)MoveX + C_WIDTH) / MAP_SIZE] >= 1){//�E��̃`�F�b�N����
				return 4 * MapData[((int)cameraY + (int)MoveY)/MAP_SIZE][(cameraX + (int)MoveX + C_WIDTH)/MAP_SIZE];
			}
		}
	}
	if(MoveY == 0){
		//DrawFormatString(0,120,GetColor(255,255,255),"%f,%f",MoveX,MoveY);
		if(MapData[((int)cameraY + (int)MoveY + C_HEIGHT - 10)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE] >= 1){//�����̃`�F�b�N����
			return 4 * MapData[((int)cameraY + (int)MoveY + C_HEIGHT)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE] - 3;
		}
		if(MapData[((int)cameraY + (int)MoveY + C_HEIGHT - 10) / MAP_SIZE][(cameraX + (int)MoveX + C_WIDTH) / MAP_SIZE] >= 1){//�E���̃`�F�b�N����
			return 4 * MapData[((int)cameraY + (int)MoveY + C_HEIGHT)/MAP_SIZE][(cameraX + (int)MoveX + C_WIDTH)/MAP_SIZE] - 2;
		}
		if(MapData[((int)cameraY + (int)MoveY)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE] >= 1){//����̃`�F�b�N����
			return 4 * MapData[((int)cameraY + (int)MoveY)/MAP_SIZE][(cameraX + (int)MoveX)/MAP_SIZE] - 1;
		}
		if(MapData[((int)cameraY + (int)MoveY) / MAP_SIZE][(cameraX + (int)MoveX + C_WIDTH) / MAP_SIZE] >= 1){//�E��̃`�F�b�N����
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

	PlayerGraph = LoadGraph( "Player.bmp" );//PG��Load
	srand((unsigned int)time(NULL));
	num = GetRand(5);
	kaiten = GetRand(3);
	Key[KEY_INPUT_SPACE] = 1;
	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0){
		//�v�Z����
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
		//�`�揈��
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
					return 1;//��������
				}
			}
		}
	}
	return 0;//�m�[�q�b�g
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
