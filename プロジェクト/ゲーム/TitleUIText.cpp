#include "TitleUIText.h"
#include "DxLib.h"
#include"ScreenSystem.h"

void TitleUI::initialize()
{
	this->anime = std::make_unique<Animation>();
	this->anime->set("title_ui");
}

void TitleUI::finalize()
{
}

void TitleUI::draw()
{
	Point pos;
	pos.x = ScreenSize::width / 2 - 256 / 2;
	pos.y = ScreenSize::height / 2;
	//•¶Žš‚ð•`‰æ
	this->anime->draw_anime(pos);
}
