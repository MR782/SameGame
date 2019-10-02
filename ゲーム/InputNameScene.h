#pragma once
#include<memory>
#include"Animation.h"

//�v���C���[���̓��͂��s��

class InputNameScene {
	struct GraphData {
		GraphData();
		Animation anime;
		Point position;//�`����W
		int drawing_order;//�`�悷�鏇��
		std::string name;
		//�\�[�g�p������----------------------------------------
		bool operator < (const GraphData& right)const {
			return this->drawing_order < right.drawing_order;
		}
		bool operator > (const GraphData& right)const {
			return this->drawing_order > right.drawing_order;
		}
	};
	//�w�i�摜�ƃe�L�X�g�{�b�N�X�̉摜�\��
	std::vector<GraphData> anime;
public:
	void initialize();
	void finalize();
	void update();
	void draw();
};