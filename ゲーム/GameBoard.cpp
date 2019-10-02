#include "GameBoard.h"
#include<Windows.h>
#include"CoreScene.h"
#include"DxLib.h"
#include"Mouse.h"

void GameBoard::initialize()
{
	//�f�[�^�̏�����
	ZeroMemory(this->arr, sizeof(this->arr));
	this->previous_cellPos = Point(-1, -1);
	this->blinkCnt = 0;
	//�`�b�v�ɏ�������
	this->chip = GraphicResource::get_handle("board");
	//�΂��Z�b�g
	set(4);
}

void GameBoard::finalize()
{
}

void GameBoard::update()
{
	//�}�E�X���W���擾
	Point mouse_pos = Mouse::get_mouse_pos();
	//��ʂ̓��͔͈͓����m�F
	if (mouse_pos.x >= 0 && mouse_pos.y >= 0
		&&
		mouse_pos.x < Stone_Width * GameBoard_Width && mouse_pos.y < Stone_Height * GameBoard_Height){
		//�}�X�P�ʂ̍��W�ɕϊ�
		Point masu = Point(mouse_pos.x / Stone_Width, mouse_pos.y / Stone_Height);
		//�}�E�X�J�[�\���ʒu���ȑO�̃Z���ƈقȂ�Ȃ�
		if (this->previous_cellPos.x != masu.x || this->previous_cellPos.y != masu.y) {
			this->previous_cellPos = masu;//�X�V
			//�ڑ��͈͒��o
			erase_check(masu);
		}
		//�}�E�X�̍��{�^���������ꂽ��
		if (Mouse::left_mouse_down()) {
			int e_cnt = erase_cnt();//������΂𐔂���
			if (e_cnt >= 2) {//������΂�2�ȏ�Ȃ�
				//�X�R�A����
				Engine::set_score(Engine::get_score() + (e_cnt * e_cnt));
				//�A�����Ă���΂�����
				erase();
				//�΂𗎂Ƃ�
				fall();
				//�E�ɂ��炷
				move_right();
				//�S��������
				if (check_clear()) {
					Engine::set_score(Engine::get_score() + 1000);
					Engine::set_gameclear_flag(true);
				}
				else if (check_gameover()) {
					Engine::set_gameover_flag(true);
				}
				//�}�E�X�𓮂��Ȃ��Ă��ă`�F�b�N������
				this->previous_cellPos.x = -1;
				this->previous_cellPos.y = -1;
			}
		}
	}
	//�����\���p�̃J�E���^���X�V
	this->blinkCnt++;
	if (this->blinkCnt > INT_MAX)this->blinkCnt = 0;
}

void GameBoard::draw()
{
	//��ʂɕ\������͈͂����\��
	for (int y = 0; y < GameBoard_Height; y++) {
		for (int x = 0; x < GameBoard_Width; x++) {
			//�΂�����Ȃ�
			if (this->arr[y][x] != 0) {
				//������΂�_�ł�����
				if (this->blinkCnt % 20 < 10 && this->erase_log[y][x] == 1) {
					continue;
				}
				Point pos = Point(x * Stone_Width, y * Stone_Height);
				DrawGraph(pos.x, pos.y, this->chip[this->arr[y][x]], TRUE);
			}
		}
	}
}

void GameBoard::set(int value)
{
	//�΂�z�u
	int cnt = 0;
	for (int y = 0; y < GameBoard_Height; y++) {
		for (int x = 0; x < GameBoard_Width; x++) {
			this->arr[y][x] = cnt + 1;
			//1�ȏ�̃f�[�^��p��(0�͋�̂���)
			cnt = (cnt + 1) % value;
		}
	}
	//�΂��V���b�t������
	shuffle();
}

void GameBoard::shuffle()
{
	for (int y = 0; y < GameBoard_Height; y++) {
		for (int x = 0; x < GameBoard_Width; x++) {
			int rand_x = rand() % GameBoard_Width;
			int rand_y = rand() % GameBoard_Height;
			//�z��f�[�^�����ւ�
			int temp = this->arr[y][x];// A <- B
			this->arr[y][x] = this->arr[rand_y][rand_x];// B <- C
			this->arr[rand_y][rand_y] = temp;// C <- A
		}
	}
}

void GameBoard::erase_check(Point pos)
{
	//�͈͒T������
	ZeroMemory(this->erase_log, sizeof(this->erase_log));
	int kind = this->arr[pos.y][pos.x];
	//�w����W���󔒂Ȃ�
	if (kind == 0) { return; }//�I��
	//�͈͒T���J�n
	this->erase_check_recursion(pos.x, pos.y, kind);
}

void GameBoard::erase_check_recursion(int x, int y, int kind)
{
	//���ݒn�����łɒT���ς݂Ȃ璆�f
	if (this->erase_log[y][x] != 0) { return; }
	//�΂̎�ނ��Ⴄ�Ȃ璆�f
	if (this->arr[y][x] != kind) { return; }
	//���ݒn���}�[�L���O
	this->erase_log[y][x] = 1;
	//�אڂ���}�X���`�F�b�N(�㉺���E)
	if (x - 1 >= 0) { this->erase_check_recursion(x - 1, y, kind); }//��
	if (x + 1 < GameBoard_Width) { this->erase_check_recursion(x + 1, y, kind); }//�E
	if (y - 1 >= 0) { this->erase_check_recursion(x, y - 1, kind); }//��
	if (y + 1 < GameBoard_Height) { this->erase_check_recursion(x, y + 1, kind); }//��
}

int GameBoard::erase_cnt()
{
	int cnt = 0;
	for (int y = 0; y < GameBoard_Height; y++) {
		for (int x = 0; x < GameBoard_Width; x++) {
			cnt += this->erase_log[y][x];//erase_log�ɂ�0��1�����Ȃ����߂��̏��������ł���
			//if(this->erase_log[y][x] == 1){  cnt++;  }//���̏�����
		}
	}
	return cnt;
}

void GameBoard::erase()
{
	for (int y = 0; y < GameBoard_Height; y++) {
		for (int x = 0; x < GameBoard_Width; x++) {
			if (this->erase_log[y][x] != 0) {
				this->arr[y][x] = 0;
			}
		}
	}
	//erase_log��S��0�ɂ���
	ZeroMemory(this->erase_log, sizeof(this->erase_log));
}

void GameBoard::fall()
{
	//�S�Ă�0������
	int board[GameBoard_Height][GameBoard_Width] = { {0} };
	for (int x = 0; x < GameBoard_Width; x++) {
		//�������Ɍ������ď������s��
		int y2 = GameBoard_Height - 1;
		//�l�߂����ʂ�board�ɏ�������ł���
		for (int y = GameBoard_Height - 1; y >= 0; y--) {
			//�΂����݂���Ȃ�
			if (this->arr[y][x] != 0) {
				//�㏑��
				board[y2][x] = this->arr[y][x];
				y2--;
			}
		}
	}
	//�f�[�^���㏑������
	memcpy(this->arr, board, sizeof(board));
}

void GameBoard::move_right()
{
	int board[GameBoard_Height][GameBoard_Width] = { {0} };//������
	int x2 = GameBoard_Width - 1;
	//�E���獶�Ɍ������ď������s��
	for (int x = GameBoard_Width - 1; x >= 0; x--) {
		//�c1���C���S�ċ󔒂Ȃ烉�C�����ڂ�
		if (this->arr[9][x] == 0) continue;
		//���C�����l�߂�board�ɏ�������
		for (int y = 0; y < GameBoard_Height; y++) {
			board[y][x2] = this->arr[y][x];
		}
		x2--;
	}
	//�f�[�^���㏑��
	memcpy(this->arr, board, sizeof(board));
}

bool GameBoard::check_clear()
{
	//�E���̃f�[�^����Ȃ�N���A
	return this->arr[GameBoard_Height - 1][GameBoard_Width - 1] == 0;
}

bool GameBoard::check_gameover()
{
	bool check = false;
	for (int y = 0; y < GameBoard_Height; y++) {
		for (int x = 0; x < GameBoard_Width; x++) {
			if (this->arr[y][x] != 0) {
				Point pos = Point(x, y);
				erase_check(pos);
				//������΂��`�F�b�N
				int e_cnt = erase_cnt();
				//������΂�2�����Ȃ�
				if (e_cnt < 2) {
					check = true;
				}
			}
		}
	}
	return check;
}
