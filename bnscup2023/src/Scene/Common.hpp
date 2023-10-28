#pragma once
#include <Siv3D.hpp>

enum class SceneState {
	Title,
	Game,
	Score
};

struct GameData {
	int32 score;
};

using App = SceneManager<SceneState, GameData>;
