#include "TitleScene.h"
#include"Audio.h"
#include"Mouse.h"
#include"CoreScene.h"
#include"ScreenFunction.h"
#include"ScreenSystem.h"
#include"Resource.h"
#include"DxLib.h"

void TitleScene::initialize()
{
	this->back_graph = GraphicResource::get_handle("title_back")[0];
	//�e�L�X�g�̕\���ʒu
	this->title_ui.initialize();

	//�^�C�g��BGM
	Audio::load("title");
	//�^�C�g��SE
	Audio::load("decision");
	//�^�C�g��BGM�Đ�
	Audio::play("title");
}

void TitleScene::finalize()
{
	this->title_ui.finalize();
	//���y���~�߂�
	Audio::stop("title");
	//�I�[�f�B�I�f�[�^�̍폜
	Audio::delete_soundData_scope("title");
}

void TitleScene::update()
{
	//���N���b�N���ꂽ��
	if (Mouse::left_mouse_down()) {
		//�t�F�[�h�A�E�g�J�n
		Engine::set_fade_ioFlag(true);
		Audio::play("decision");
	}
	//�^���ÂɂȂ�����
	if (ScreenFunction::check_brend_max()) { 
		//�V�[����ς���
		core->scene_change(Scene::name_input);//���O���̓V�[���ɑJ��
		Engine::set_fade_ioFlag(false);
	}
}

void TitleScene::draw()
{
	//�w�i�摜���g�k�`��
	DrawExtendGraph(0, 0, ScreenSize::width, ScreenSize::height, this->back_graph, FALSE);
	//UI�̕`��
	this->title_ui.draw();
}
