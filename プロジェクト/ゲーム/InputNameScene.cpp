#include "InputNameScene.h"
#include"Engine.h"
#include"DxLib.h"
#include <algorithm>
#include <functional>
#include"KeyBoard.h"
#include"Audio.h"
#include"CoreScene.h"
#include"ScreenFunction.h"
#include"ScreenSystem.h"

void InputNameScene::initialize()
{
	//�I�[�f�B�I�f�[�^�ǂݍ���
	Audio::load("decision");
	Audio::load("input_name");
	//�w�i�摜�p�̃������m�ۂƉ摜�Z�b�g
	GraphData g_data_back;
	g_data_back.anime.set("input_name_back");
	g_data_back.position = Point(0, 0);
	g_data_back.drawing_order = 1;
	g_data_back.name = "back";
	//�e�L�X�g�{�b�N�X�摜
	GraphData g_data_txtBox;
	g_data_txtBox.anime.set("text_box");
	g_data_txtBox.position = Point(ScreenSize::width / 2 - 150 / 2, ScreenSize::height / 2);
	g_data_txtBox.drawing_order = 2;
	g_data_txtBox.name = "text_box";
	//vector�ɒǉ�
	anime.push_back(g_data_back);
	anime.push_back(g_data_txtBox);
	//�����ɕ��ёւ���
	std::sort(anime.begin(), anime.end());
}

void InputNameScene::finalize()
{
	anime.clear();
	Audio::delete_soundData_name("input_name");
}

void InputNameScene::update()
{
	Engine::input_name();
	//Enter�L�[�������ꂽ��
	if (KeyBoard::key_down(KEY_INPUT_RETURN)) {
		//���O�������͂̏ꍇ�f�t�H���g�̖��O������
		Engine::set_default_name();
		//���ʉ���炷
		Audio::play("decision");
		//�t�F�[�h�A�E�g�J�n
		Engine::set_fade_ioFlag(true);
	}
	if (ScreenFunction::check_brend_max()) {
		//�V�[���ύX
		core->scene_change(Scene::game);
		//�t�F�[�h�C���J�n
		Engine::set_fade_ioFlag(false);
	}
}

void InputNameScene::draw()
{
	//�`����s��
	for (auto itr = anime.begin(); itr != anime.end(); itr++) {
		(*itr).anime.draw_anime((*itr).position);
		//�e�L�X�g�{�b�N�X�̏ꏊ�ɕ������o��
		if ((*itr).name == "text_box") {
			//���͂������O������
			DrawString((*itr).position.x, (*itr).position.y - 50, "���O����͂��Ă�������(���p�啶���p��)", GetColor(255, 255, 255));
			DrawString((*itr).position.x, (*itr).position.y + 50, "Enter�œ��͏I��", GetColor(255, 255, 255));
			DrawFormatString((*itr).position.x, (*itr).position.y + 5, GetColor(0, 0, 0), "      %s", Engine::get_user_name());
		}
	}
}

InputNameScene::GraphData::GraphData()
{
	this->drawing_order = 0;
	this->name = "";
	this->position = Point(0, 0);
}
