#include "TitleScene.h"
#include"Audio.h"
#include"Mouse.h"
#include"CoreScene.h"
#include"ScreenFunction.h"
#include"ScreenSystem.h"

void TitleScene::initialize()
{
	this->anime = std::make_unique<Animation>();
	this->anime->set("title_back");//�摜�Z�b�g
	//�e�L�X�g�̕\���ʒu
	this->title_ui.initialize();
	this->title_ui.position = Point(ScreenSize::width / 3, ScreenSize::height / 2);

	//�^�C�g��BGM
	Audio::load("title");
	//�^�C�g��SE
	Audio::load("decision");
	//�^�C�g��BGM�Đ�
	Audio::play("title");
}

void TitleScene::finalize()
{
	this->anime.reset();
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
	//�w�i�摜��`��
	this->anime->draw_anime(Point(0, 0));
	//UI�̕`��
	this->title_ui.draw();
}
