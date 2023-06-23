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
	Scene scene_;
};