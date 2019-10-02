#pragma once
#include"Object.h"
#include"define.h"

class GameBoard {
	int arr[GameBoard_Height][GameBoard_Width];//�΂̃f�[�^�z��
	int erase_log[GameBoard_Height][GameBoard_Width];//�������邽�߂̔z��
	int* chip;//�u���b�N���
	int  blinkCnt;//�������Ƃ̂ł���ӎv�������\�����邽�߂̃J�E���^
	Point previous_cellPos;//���O�̑I���Z��
	//���\�b�h
	void set(int value);//�΂��Z�b�g����
	void shuffle();//�΂��V���b�t������
	void erase_check(Point pos);//�ڑ��͈͂𒊏o
	void erase_check_recursion(int x,int y,int kind);//�ċA�ɂ���Ĕ͈͒T�����s��
	int erase_cnt();//������΂̐����J�E���g
	void erase();//�Ώۂ̐΂��폜����
	void fall();//�΂����ɗ��Ƃ�����
	void move_right();//�E�ɂ��炷����
	bool check_clear();//�N���A����
	bool check_gameover();//�Q�[���I�[�o�[����
public:
	void initialize();
	void finalize();
	void update();
	void draw();
};