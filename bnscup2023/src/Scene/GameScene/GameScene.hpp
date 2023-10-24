﻿#pragma once
#include "../Common.hpp"
#include "../../Utility/Theme.hpp"
#include "../../Utility/Config.hpp"
#include "../../GameObject/Player/Player.hpp"
#include "../../GameObject/Meteo/Meteo.hpp"

class GameScene : public App::Scene {
	BasicCamera2D m_camera;
	Player m_player;
	Array<Meteo> m_meteos;

	// 連続ヒットしないように時間を置く
	static constexpr double DecreasePlayerHPWaitTime = 0.5;
	Stopwatch m_decreasePlayerHPCountor{ StartImmediately::Yes };

public:
	GameScene(const InitData&);

	void update() override;

	void draw() const override;
};
