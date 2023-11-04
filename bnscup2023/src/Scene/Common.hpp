#pragma once
#include <Siv3D.hpp>
#include "../Utility/Config.hpp"

enum class SceneState {
	Title,
	Game,
	Score
};

struct GameData {
	Config config{ U"resource/config.json" };
	const String LeaderboardURL = Unicode::Widen(std::string{ SIV3D_OBFUSCATE("https://script.google.com/macros/s/AKfycbyjvsM1lxnFtOaFXgfZnVq6fvsC2yc-2D3TlCKgPAnFL6GgRfr3luwjSbPdRhCSaP-p4A/exec") });
	int32 score;
};

using App = SceneManager<SceneState, GameData>;
