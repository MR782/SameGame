#include "Ranking.h"
#include"ScreenSystem.h"
#include"DxLib.h"
#include"Engine.h"
#include"Resource.h"

void Ranking::initialize()
{
	//���x���ɓ����Ă���p�X����f�[�^��ǂݍ���
	this->data.input_textfile_data("./data/txt/rank.txt");
	//���[�U�[���ƃX�R�A������
		//���͂������O�ƃQ�[���̃X�R�A�������L���O�ɒǉ�
	this->data.input_ranking(Engine::get_score(), Engine::get_user_name());
	//Top5�̃f�[�^�������Ă���
	this->rank_data = this->data.get_rank(5);

	this->rank_no_graph = GraphicResource::get_handle("rank_no");
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
		int posY = 64 * cnt * 2;//�Ԋu
		int posX = ScreenSize::width / 4;
		unsigned int color = GetColor(255, 0, 0);
		//����     �v���C���[�̖��O �X�R�A�̏��ɕ`�悷��
		DrawGraph(posX, posY, this->rank_no_graph[cnt], TRUE);
		DrawFormatString(posX + 64, posY, color, "%s : %d",(*itr).name.c_str(), (*itr).score);
	}
}
