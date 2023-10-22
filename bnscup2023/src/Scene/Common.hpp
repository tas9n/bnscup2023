#pragma once
#include <Siv3D.hpp>

enum class SceneState {
	Title,
	Game
};

struct GameData {

};

using App = SceneManager<SceneState, GameData>;
