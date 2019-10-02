#include "EndingScene.h"
#include"Mouse.h"
#include"ScreenFunction.h"
#include"CoreScene.h"
#include"Engine.h"

void EndingScene::initialize()
{
	ranking.initialize();
	//�e�L�X�g�t�@�C���Ƀ����L���O�f�[�^�����
	ranking.data.reset_textfile_data("./data/txt/rank.txt");//���łɓ��͍ς݂̃f�[�^���폜
	ranking.data.output_textfile_data("./data/txt/rank.txt");//�V�����f�[�^�����
}

void EndingScene::finalize()
{
	ranking.finalize();
}

void EndingScene::update()
{
	if (Mouse::left_mouse_down()) {
		//�^�C�g���V�[���ɖ߂�
		Engine::set_fade_ioFlag(true);
	}
	if (ScreenFunction::check_brend_max()) {
		core->scene_change(Scene::title);
		Engine::set_fade_ioFlag(false);
	}
}

void EndingScene::draw()
{
	ranking.draw();
}
