#include "object.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                         LPSTR lpCmdLine, int nCmdShow )
{
	//�ϐ��錾
	int Key[256];
	int i;
	int back;
	int count = 0;
	MenuElement_t Menusele[4] = {
		{250,180,GetColor(0,0,0),"�V��"},
		{200,220,GetColor(0,0,0),"���"},
		{200,260,GetColor(0,0,0),"�~�j�Q�[��"},
		{200,300,GetColor(0,0,0),"�I��"}
	};


	//��������
	ChangeWindowMode( TRUE );  // �E�B���h�E���[�h�ɐݒ�
	SetDrawScreen( DX_SCREEN_BACK );  //�`���𗠉�ʂɐݒ�
	SetGraphMode( 800 , 600 , 32 ) ;  //800*600�ɌŒ�
	if( DxLib_Init() == -1 )        // �c�w���C�u��������������
	{
         return -1;        // �G���[���N�����璼���ɏI��
    }
	back = LoadGraph("back.jpg");
	PlaySoundFile("BGM\\bgm_01.mp3", DX_PLAYTYPE_LOOP ) ;
	gpUpdataKey(Key);
	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && Key[KEY_INPUT_ESCAPE] != 1){
		//�v�Z����
		gpUpdataKey(Key);
		if(Key[KEY_INPUT_DOWN] == 1){//���L�[�������ꂽ�牺�ɍs������
			count++;
			count = count % 4;
		}
		if(Key[KEY_INPUT_UP] == 1){//��L�[�������ꂽ���ɍs������
			count = count += 3;
			count = count % 4;
		}
		if(Key[KEY_INPUT_SPACE] == 1 || Key[KEY_INPUT_RETURN] == 1){//Enter �܂��́@�X�y�[�X�������ꂽ��J�E���g�ɉ����ď���
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
		for(i = 0;i <= 3;i++){//�J�E���g�ɉ����đI������Ă���̂��킩��₷������
			if(count == i){
				Menusele[i].cr = GetColor(255,0,255);//�F����
				Menusele[i].x = 250;//�I������Ă�����̂��E�ɏo��
			}
			else{
				Menusele[i].cr = GetColor(0,0,0);//�F����
				Menusele[i].x = 200;//�I������Ă�����̂�����
			}
		}

		//�`�揈��
		DrawGraph(0,0,back,TRUE);//�o�b�N��ʂ�\��
		for(i = 0;i <= 3;i++){
			DrawFormatString(Menusele[i].x,Menusele[i].y,Menusele[i].cr,Menusele[i].name);//�����̕\��
		}

	}
	StopSoundFile() ;
    DxLib_End() ;            // �c�w���C�u�����g�p�̏I������

    return 0 ;            // �\�t�g�̏I��
}