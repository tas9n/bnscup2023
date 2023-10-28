#pragma once
#include "../Common.hpp"

#include "../../Utility/Theme.hpp"
#include "../../Utility/Config.hpp"

#include "../../GameObject/Player/Player.hpp"
#include "../../GameObject/Meteo/Meteo.hpp"
#include "../../GameObject/Junk/Junk.hpp"

#include "../../Effect/TwinkleStar/TwinkleStar.hpp"

class GameScene : public App::Scene {
	BasicCamera2D m_camera;
	Player m_player;

	Array<Meteo> m_meteos;
	Array<Junk> m_junks;

	// 連続ヒットしないように時間を置く
	static constexpr double DecreasePlayerHPWaitTime = 0.5;
	Stopwatch m_decreasePlayerHPCountor{ StartImmediately::Yes };

	static constexpr double MeteoSpawnWaitTime = 0.75;
	Stopwatch m_meteoSpawnCountor{ StartImmediately::Yes };

	static constexpr int32 JunkScoreAmmount = 100;
	static constexpr double JunkSpawnWaitTime = 1.25;
	Stopwatch m_junkSpawnCountor{ StartImmediately::Yes };

	Effect m_effect;
	static constexpr double EffectAppendTwinkleStarWaitTime = 0.05;
	Stopwatch m_effectAppendTwinkleStarCountor{ StartImmediately::Yes };

	int32 m_level = 1;

public:
	GameScene(const InitData&);

	void update() override;

	void updateFadeIn(double) override;

	void draw() const override;

	void addScore(int32);

	Vec2 getPointOnRandomEdge(const Vec2&) const;
};
