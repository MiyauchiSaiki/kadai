#include "DxLib.h"

const char TITLE[] = "�w�Дԍ����O�F�^�C�g��";

const int WIN_WIDTH = 1200; //�E�B���h�E����
const int WIN_HEIGHT = 400;//�E�B���h�E�c��


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɐݒ�
	//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// �^�C�g����ύX
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�ɍ��킹��j
	SetWindowSizeExtendRate(1.0);				//��ʃT�C�Y��ݒ�i�𑜓x�Ƃ̔䗦�Őݒ�j
	SetBackgroundColor(0x00, 0x00, 0xFF);		// ��ʂ̔w�i�F��ݒ肷��

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1) { return -1; }

	//�i�_�u���o�b�t�@�j�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	//�摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���



	//�Q�[�����[�v�Ŏg���ϐ��̐錾
	char keys[256] = { 0 }; //�ŐV�̃L�[�{�[�h���p
	char oldkeys[256] = { 0 };//1���[�v�i�t���[���j�O�̃L�[�{�[�h���

	int MouseX, MouseY;
	double EasingX1[] = { 100.0 };
	double EasingX2[] = { 100 };
	double Vel1[] = { 50.0 };
	double Vel2[] = { 1.0 };
	int num = 0;

	// �Q�[�����[�v
	while (1)
	{
		//�ŐV�̃L�[�{�[�h��񂾂������̂͂P�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�

		//�ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		//��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		//�X�V����


		if (keys[KEY_INPUT_SPACE] == 1) {
			num = 0;
		}

		num += 1;


		SetDrawBlendMode(DX_BLENDMODE_ADD, 170);

		DrawBox(100, 100, 116, 116, GetColor(255, 0, 0), TRUE);

		for (int i = 0; i < num; i++) {

			if (EasingX1[i] >= 900.0) {
				EasingX1[i] = 900.0;
				DrawBox(EasingX1[i], 100, EasingX1[i] + 16, 116, GetColor(255, 0, 0), TRUE);
				break;
			}

			else if (i >0) {
				Vel1[i] = Vel1[i - 1] * 1.1;
				EasingX1[i] = Vel1[i] + 100;
				DrawBox(EasingX1[i], 100, EasingX1[i] + 16, 116, GetColor(255, 255, 255), TRUE);
			}
		}

		DrawBox(100, 200, 116, 216, GetColor(255, 0, 0), TRUE);

		for (int i = 0; i < num; i++) {

			if (EasingX2[i] >= 900.0) {
				EasingX2[i] = 900.0;
				DrawBox(EasingX2[i], 100, EasingX2[i] + 16, 116, GetColor(255, 0, 0), TRUE);
				break;
			}

			else if (i >0) {
				Vel2[i] = Vel2[i - 1] * 0.9;
				EasingX2[i] = EasingX2[i - 1] + Vel2[i];
				DrawBox(EasingX2[i], 200, EasingX2[i] + 16, 216, GetColor(255, 255, 255), TRUE);
			}
		}


		//�`�揈��




		//---------  �����܂łɃv���O�������L�q  ---------//
		ScreenFlip();//�i�_�u���o�b�t�@�j����
		// 20�~���b�ҋ@�i�^��60FPS�j
		WaitTimer(20);
		// Windows �V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}
		// �d�r�b�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	//Dx���C�u�����I������
	DxLib_End();

	return 0;
}