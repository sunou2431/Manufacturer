#include "OBJECT.h"
#include "xxx_mini.h"

void selectminigame(void){
	int Key[256];
	int i;
	int back;
	int count = 0;

	back = LoadGraph("back.jpg");
	MenuElement_t Menusele[3] = {
		{250,180,GetColor(0,0,0),"�e�g���X�}���I"},
		{200,220,GetColor(0,0,0),"test" },
		{200,260,GetColor(0,0,0),"�߂�"}
	};

	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0){
		//�v�Z����
		gpUpdataKey(Key);
		if(Key[KEY_INPUT_DOWN] == 1){//���L�[�������ꂽ�牺�ɍs������
			count++;
			count = count % 3;
		}
		if(Key[KEY_INPUT_UP] == 1){//��L�[�������ꂽ���ɍs������
			count = count += 2;
			count = count % 3;
		}
		if(Key[KEY_INPUT_SPACE] == 1 || Key[KEY_INPUT_RETURN] == 1){//Enter �܂��́@�X�y�[�X�������ꂽ��J�E���g�ɉ����ď���
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
		for(i = 0;i <= 2;i++){//�J�E���g�ɉ����đI������Ă���̂��킩��₷������
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
		for(i = 0;i <= 2;i++){
			DrawFormatString(Menusele[i].x,Menusele[i].y,Menusele[i].cr,Menusele[i].name);//�����̕\��
		}

	}
}