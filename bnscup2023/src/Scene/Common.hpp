#pragma once
#include <Siv3D.hpp>
#include "../Utility/Config.hpp"
#include "../Utility/__environment.hpp"

enum class SceneState {
	Title,
	Game,
	Score
};

struct GameData {
	Config config{ U"space_collector.config.json" };
	const String LeaderboardURL = Environment::LeaderboardURLRaw;
	int32 score;
};

using App = SceneManager<SceneState, GameData>;
