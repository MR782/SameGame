#pragma once
#include<iostream>
#include<vector>
#include"Purpose.h"

//�e�L�X�g�t�@�C������f�[�^���󂯎��
//�f�[�^��ǉ�����

class RankingData {
public:
	//�����L���O�ɕ\��������̂̒��g
	struct Status {
		Status() { score = 0; name = ""; }
		//�\�[�g�p�̔���
		bool operator < (const Status& right)const {
			return this->score < right.score;
		}
		bool operator > (const Status& right)const {
			return this->score > right.score;
		}
		int score;
		std::string name;
	};
	//���ёւ����@
	enum Sort {
		ASC,//����
		DESC//�~��
	};
	//���\�b�h--------------------------------------------------
	RankingData();
	//�����L���O�ɒǉ�����
	void input_ranking(int score_,std::string name_);
	//�����L���O����ёւ��� �f�t�H���g�͍~��
	void swap_ranking(Sort s = DESC);
	//�����L���O�̒��g���폜
	void reset_ranking();
	//�e�L�X�g�t�@�C������f�[�^��ǂݎ���Ă���
	void input_textfile_data(std::string filepath);
	//�e�L�X�g�t�@�C���Ƀf�[�^���o�͂���
	void output_textfile_data(std::string filepath);
	//�e�L�X�g�t�@�C���̒��g�����Z�b�g����
	void reset_textfile_data(std::string filepath);
	//setter,getter----------------------------------------
	std::vector<Status> get_ranking();//�����L���O�S�̂��擾
	std::vector<Status> get_rank(int val);//�����L���O�擾���w��
private:
	//�S�̂̃����L���O
	std::vector<Status> ranking;
};