#pragma once
#include <Siv3D.hpp>

enum class SceneState {
	Title,
	Game
};

struct GameData {
	int32 score;
};

using App = SceneManager<SceneState, GameData>;
