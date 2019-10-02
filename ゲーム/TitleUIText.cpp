#include "TitleUIText.h"
#include "DxLib.h"

void TitleUI::initialize()
{
}

void TitleUI::finalize()
{
}

void TitleUI::draw()
{
	//•¶Žš‚ð•`‰æ
	DrawString(this->position.x, this->position.y, "CLICK TO START", GetColor(0, 0, 0));
}
