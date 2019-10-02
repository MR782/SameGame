#include "Ranking.h"
#include"ScreenSystem.h"
#include"DxLib.h"
#include"Engine.h"

void Ranking::initialize()
{
	//���x���ɓ����Ă���p�X����f�[�^��ǂݍ���
	this->data.input_textfile_data("./data/txt/rank.txt");
	//���[�U�[���ƃX�R�A������
		//���͂������O�ƃQ�[���̃X�R�A�������L���O�ɒǉ�
	this->data.input_ranking(Engine::get_score(), Engine::get_user_name());
	//Top5�̃f�[�^�������Ă���
	this->rank_data = this->data.get_rank(5);
}

void Ranking::finalize()
{
	this->rank_data.clear();
}

void Ranking::draw()
{
	int cnt = 0;
	for (auto itr = this->rank_data.begin(); itr != this->rank_data.end(); itr++,cnt++) {
		//�ォ�牺�ɕ`��
		int posY = 25 * cnt;//�Ԋu
		int posX = ScreenSize::width / 2;
		unsigned int color = GetColor(255, 0, 0);
		//����     �v���C���[�̖��O �X�R�A�̏��ɕ`�悷��
		DrawString(posX, 75, "Rank   Name  SCORE",color);
		DrawFormatString(posX, posY + 100, color, "%d      %s : %d", cnt + 1 , (*itr).name.c_str(), (*itr).score);
	}
}
