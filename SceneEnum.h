#pragma once

class SceneEnum
{
protected:
	// シーン管理用列挙体
	enum Scene
	{
		TITLE,
		GAMEPLAY,
		GAMEOVER,
		GAMECLEAR
	};
	//switch文に突っ込むようの変数
	Scene scene_;
};